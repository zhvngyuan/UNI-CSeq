#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
实验二统计口径：源断言站点 + CBMC Results 身份键塌缩。

同一源断言的循环展开副本按 (函数, 表达式) 合并；同一函数里多条源断言
即使表达式相同（如 svp_simple_700_001、svp_simple_014）也按 assertion.N
分开计数，与实验三单断言实例口径对齐。

只给 genTable_scripts 使用，不参与批跑或顺序化。
"""

import glob
import os
import re

ASSERT_LINE_RE = re.compile(
    r"\[([^\]]+\.assertion\.\d+)\] assertion (.+): (SUCCESS|FAILURE)\s*$"
)
FAILED_SUMMARY_RE = re.compile(r"\*\*\s+(\d+)\s+of\s+(\d+)\s+failed")
NICHECKER_CE_RE = re.compile(
    r"(?:SAFE|UNSAFE),\s*counterexample:\s*(\d+),\s*time:\s*([0-9.]+)\s*s"
)
# 含自定义 void assert(...) 包装；只匹配定义/声明行，不匹配 assert(expr) 调用。
HARNESS_DEF_RE = re.compile(
    r"^\s*(?:extern\s+)?(?:static\s+)?void\s+(reach_error|__VERIFIER_assert|assert)\s*\("
)
ASSERT_CALL_RE = re.compile(r"(?<![\w])(?:__VERIFIER_assert|assert)\s*\(")
FUNC_DEF_RE = re.compile(
    r"^\s*(?:(?:static|extern|inline)\s+)*"
    r"(?:void|int|char|long|short|unsigned|signed|bool|_Bool)"
    r"(?:\s+\*|\s)+([A-Za-z_][A-Za-z0-9_]*)\s*\("
)
ASSERT_INDEX_RE = re.compile(r"\.assertion\.(\d+)\s*$")
ANSI_RE = re.compile(r"\x1b\[[0-9;]*m")


def strip_ansi(text):
    return ANSI_RE.sub("", text)


def is_assert_uncommented(lines, idx):
    """判断第 idx 行中的 assert 是否未被 // 或 /* */ 注释。"""
    line = lines[idx]
    if re.match(r"^\s*//", line):
        return False
    before = line.split("//")[0]
    if "assert" not in before:
        return False
    count = 0
    for i in range(idx, -1, -1):
        if "*/" in lines[i]:
            count += lines[i].count("*/")
        if "/*" in lines[i]:
            count -= lines[i].count("/*")
    if count > 0:
        return False
    return True


def source_path_for_subdir(test_dir, subdir):
    return os.path.join(test_dir, subdir + ".c")


def _assert_span(lines, start):
    """返回从 start 起一条 assert 调用的结束行号。"""
    content = lines[start]
    left = content.count("(")
    right = content.count(")")
    end = start
    while left > right and end + 1 < len(lines):
        end += 1
        nxt = lines[end]
        if not is_assert_uncommented(lines, end):
            break
        left += nxt.count("(")
        right += nxt.count(")")
    return end


def _assert_expr_text(lines, start, end):
    chunk = []
    for idx in range(start, end + 1):
        chunk.append(lines[idx].split("//")[0])
    text = " ".join(chunk)
    m = re.search(r"(?:__VERIFIER_assert|assert)\s*\(", text)
    if not m:
        return ""
    i = m.end()
    depth = 1
    j = i
    while j < len(text) and depth:
        if text[j] == "(":
            depth += 1
        elif text[j] == ")":
            depth -= 1
        j += 1
    return text[i : j - 1].strip() if depth == 0 else text[i:].strip()


def extract_source_assert_sites(src_path):
    """源断言站点列表 [(enclosing_func, expr), ...]，口径与 count_source_assertions 一致。"""
    if not src_path or not os.path.isfile(src_path):
        return []
    with open(src_path, "r", encoding="utf-8", errors="ignore") as f:
        lines = f.readlines()

    sites = []
    in_harness = False
    harness_depth = 0
    brace_depth = 0
    current_func = ""
    i = 0
    while i < len(lines):
        line = lines[i]
        if not in_harness and HARNESS_DEF_RE.match(line):
            if "{" not in line:
                i += 1
                continue
            in_harness = True
            harness_depth = line.count("{") - line.count("}")
            if harness_depth <= 0:
                in_harness = False
            i += 1
            continue
        if in_harness:
            harness_depth += line.count("{") - line.count("}")
            if harness_depth <= 0:
                in_harness = False
            i += 1
            continue
        if brace_depth == 0:
            fm = FUNC_DEF_RE.match(line)
            if fm:
                current_func = fm.group(1)
        if ASSERT_CALL_RE.search(line) and is_assert_uncommented(lines, i):
            end = _assert_span(lines, i)
            expr = _assert_expr_text(lines, i, end)
            sites.append((current_func, expr))
            i = end + 1
            continue
        brace_depth += line.count("{") - line.count("}")
        if brace_depth < 0:
            brace_depth = 0
        i += 1
    return sites


def count_source_assertions(src_path):
    """统计源文件中未注释的用户断言站点，排除 harness 函数体。

    harness 包括 reach_error、__VERIFIER_assert，以及自定义的 void assert(...)。
    仅有声明、没有函数体的行只跳过该行，避免把后续用户断言吞掉。
    """
    return len(extract_source_assert_sites(src_path))


def normalize_func(prop_name):
    """dispose_isr_3_0.assertion.1 -> dispose_isr_3；只去掉副本后缀 _0。"""
    func = prop_name.split(".assertion.")[0]
    if func.endswith("_0"):
        func = func[:-2]
    return func


def _strip_func_ident_prefix(ident, func):
    """main_task 下的 main_x -> x；完整函数名前缀也去掉。"""
    if not func:
        return ident
    candidates = [func + "_"]
    if func.endswith("_task"):
        candidates.append(func[: -len("_task")] + "_")
    for prefix in candidates:
        if ident.startswith(prefix) and len(ident) > len(prefix):
            return ident[len(prefix):]
    return ident


def normalize_expr(expr, func):
    """去掉顺序化局部变量前缀与标识符尾部 _N。"""
    prefixes = []
    if func:
        prefixes.append("__cs_local_%s_" % func)
        prefixes.append("__cs_l_%s_" % func)
    prefixes.extend(["__cs_local_", "__cs_l_"])
    text = expr
    for prefix in prefixes:
        text = text.replace(prefix, "")

    def repl_ident(match):
        return _strip_func_ident_prefix(match.group(0), func)

    text = re.sub(r"\b[A-Za-z_][A-Za-z0-9_]*\b", repl_ident, text)
    text = re.sub(r"\b([A-Za-z_][A-Za-z0-9_]*)_\d+\b", r"\1", text)
    return " ".join(text.split())


def identity_key(prop_name, expr):
    func = normalize_func(prop_name)
    return (func, normalize_expr(expr, func))


def assertion_index(prop_name):
    m = ASSERT_INDEX_RE.search(prop_name or "")
    return int(m.group(1)) if m else 0


def canon_expr(expr):
    text = " ".join((expr or "").split())
    text = re.sub(r"\s*([=!<>]+)\s*", r" \1 ", text)
    return " ".join(text.split())


def cbmc_func_aliases(cbmc_func):
    aliases = {cbmc_func}
    if cbmc_func.endswith("_task"):
        aliases.add(cbmc_func[: -len("_task")])
    return aliases


def source_site_count_for_group(sites, cbmc_func, cbmc_expr):
    """源文件中与该 CBMC (函数, 表达式) 对应的断言站点数。"""
    aliases = cbmc_func_aliases(cbmc_func)
    target = canon_expr(cbmc_expr)
    n = 0
    for src_func, src_expr in sites:
        if src_func not in aliases:
            continue
        if canon_expr(normalize_expr(src_expr, cbmc_func)) == target:
            n += 1
    return n


def apply_source_site_keys(parsed, src_path):
    """同一函数、同一表达式的多条源断言按 assertion.N 分开，避免误合并。

    单条源断言被循环展开成多个 VCC 时仍按 (函数, 表达式) 计 1。
    """
    if parsed.get("source") != "results" or not parsed.get("items"):
        return parsed
    sites = extract_source_assert_sites(src_path)
    groups = {}
    for item in parsed["items"]:
        groups.setdefault(item["key"], []).append(item)

    src_keys = set()
    failed_keys = set()
    for key, group_items in groups.items():
        func, expr = key
        n_src = source_site_count_for_group(sites, func, expr)
        failed_items = [it for it in group_items if it["status"] == "FAILURE"]
        if n_src > 1:
            failed_ns = sorted(
                {
                    assertion_index(it["name"])
                    for it in group_items
                    if it["status"] == "FAILURE"
                }
            )
            all_ns = sorted(
                {assertion_index(it["name"]) for it in group_items}
            )
            for n in all_ns[:n_src]:
                src_keys.add((func, expr, n))
            for n in failed_ns[:n_src]:
                failed_keys.add((func, expr, n))
        else:
            src_keys.add(key)
            if failed_items:
                failed_keys.add(key)

    parsed["src_keys"] = src_keys
    parsed["failed_keys"] = failed_keys
    return parsed


def format_key(key):
    if len(key) >= 3:
        func, expr, idx = key[0], key[1], key[2]
        return "%s | %s #%s" % (func, expr, idx)
    func, expr = key
    return "%s | %s" % (func, expr)


def parse_results_log(log_path):
    """
    解析 CBMC ** Results: 段。

    返回:
        vcc_total, vcc_fail, src_keys (set), failed_keys (set),
        verdict, items (list of dict)
    """
    empty = {
        "vcc_total": 0,
        "vcc_fail": 0,
        "src_keys": set(),
        "failed_keys": set(),
        "verdict": "",
        "items": [],
        "source": "missing",
    }
    if not log_path or not os.path.isfile(log_path):
        return empty

    with open(log_path, "r", encoding="utf-8", errors="ignore") as f:
        lines = [strip_ansi(raw.rstrip("\n")) for raw in f]

    items = []
    in_results = False
    verdict = ""
    for line in lines:
        stripped = line.strip()
        if stripped == "VERIFICATION FAILED":
            verdict = "FALSE"
        elif stripped == "VERIFICATION SUCCESSFUL":
            verdict = "TRUE"
        if stripped.startswith("** Results:"):
            in_results = True
            continue
        if not in_results:
            continue
        if (
            stripped.startswith("Trace for")
            or FAILED_SUMMARY_RE.search(stripped)
            or stripped in ("VERIFICATION FAILED", "VERIFICATION SUCCESSFUL")
        ):
            break
        m = ASSERT_LINE_RE.search(line)
        if m:
            name, expr, status = m.group(1), m.group(2), m.group(3)
            key = identity_key(name, expr)
            items.append(
                {
                    "name": name,
                    "expr": expr,
                    "status": status,
                    "key": key,
                }
            )

    src_keys = set()
    failed_keys = set()
    vcc_fail = 0
    for item in items:
        src_keys.add(item["key"])
        if item["status"] == "FAILURE":
            vcc_fail += 1
            failed_keys.add(item["key"])

    return {
        "vcc_total": len(items),
        "vcc_fail": vcc_fail,
        "src_keys": src_keys,
        "failed_keys": failed_keys,
        "verdict": verdict,
        "items": items,
        "source": "results",
    }


def find_unicseq_cbmc_log(test_dir):
    matches = glob.glob(os.path.join(test_dir, "*.c.cbmc.log"))
    if not matches:
        return None
    matches.sort(key=lambda x: (len(os.path.basename(x)), x))
    return matches[0]


def find_nichecker_detail_log(test_dir):
    matches = glob.glob(os.path.join(test_dir, "_mt_*_result", "*.c1.from0to0.log"))
    if not matches:
        matches = glob.glob(os.path.join(test_dir, "_mt_*_result", "*from0to0.log"))
    if not matches:
        return None
    matches.sort(key=lambda x: (len(os.path.basename(x)), x))
    return matches[0]


def parse_nichecker_output_fallback(output_log_path):
    """detail log 缺失时回退 output.log 的 counterexample。"""
    result = {
        "counterexample": None,
        "time": None,
        "verdict": "",
    }
    if not output_log_path or not os.path.isfile(output_log_path):
        return result
    with open(output_log_path, "r", encoding="utf-8", errors="ignore") as f:
        text = strip_ansi(f.read())
    matches = re.findall(
        r"(SAFE|UNSAFE),\s*counterexample:\s*(\d+),\s*time:\s*([0-9.]+)\s*s",
        text,
    )
    if not matches:
        return result
    verdict, ce, used_time = matches[-1]
    result["verdict"] = verdict
    result["counterexample"] = int(ce)
    result["time"] = float(used_time)
    return result


def analyze_unicseq(test_dir):
    log_path = find_unicseq_cbmc_log(test_dir)
    parsed = parse_results_log(log_path)
    parsed["log_path"] = log_path
    return parsed


def analyze_nichecker(test_dir):
    detail = find_nichecker_detail_log(test_dir)
    parsed = parse_results_log(detail)
    parsed["log_path"] = detail
    if parsed["source"] == "results":
        return parsed

    output_log = os.path.join(test_dir, "output.log")
    fallback = parse_nichecker_output_fallback(output_log)
    if fallback["counterexample"] is not None:
        parsed["vcc_fail"] = fallback["counterexample"]
        parsed["vcc_total"] = fallback["counterexample"]
        parsed["verdict"] = {"SAFE": "TRUE", "UNSAFE": "FALSE"}.get(
            fallback["verdict"], fallback["verdict"]
        )
        parsed["source"] = "counterexample_fallback"
        parsed["fallback_counterexample"] = fallback["counterexample"]
        parsed["fallback_time"] = fallback["time"]
        parsed["fallback_verdict"] = fallback["verdict"]
    return parsed


def analyze_test_dir(test_dir, subdir):
    src_path = source_path_for_subdir(test_dir, subdir)
    uni = analyze_unicseq(test_dir)
    nic = analyze_nichecker(test_dir)
    uni = apply_source_site_keys(uni, src_path)
    nic = apply_source_site_keys(nic, src_path)
    return {
        "src_path": src_path,
        "src_assertions": count_source_assertions(src_path),
        "uni": uni,
        "nic": nic,
    }
