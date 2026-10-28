#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
使用:
    python3 gen_goblint_regression_ground_truth.py

功能:
1. 读取 goblint-regression 的 CBMC 和 CPAchecker 日志
2. 提取每个 benchmark 程序的 verdict 和运行时间
3. 比较两个后端结果是否一致
4. 自动生成 ground truth 候选:
   - 若 CBMC 和 CPAchecker 结果一致，且结果为 TRUE/FALSE，则记为 AUTO
   - 若不一致 / UNKNOWN / TIMEOUT / 缺失，则记为 NEED_MANUAL
5. 输出:
   - goblint_regression_ground_truth_candidates.py
   - goblint_regression_manual_review.csv
   - goblint_regression_compare_all.csv
   - goblint_regression_summary.txt

放置位置建议:
    /home/dell/zyworkspace/unichecker/Experiments/Check
"""

import os
import re
import csv
from collections import defaultdict, Counter

# =========================
# 路径配置
# =========================
CUR_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(CUR_DIR, ".."))

BASE_COMEXP = os.path.join(PROJECT_ROOT, "ComExp_Split")

CBMC_LOG = os.path.join(BASE_COMEXP, "results_goblint-regression_cbmc.log")
CPACHECKER_LOG = os.path.join(BASE_COMEXP, "results_goblint-regression_cpachecker.log")

# 输出文件
OUT_CANDIDATE_PY = os.path.join(CUR_DIR, "goblint_regression_ground_truth_candidates.py")
OUT_MANUAL_CSV = os.path.join(CUR_DIR, "goblint_regression_manual_review.csv")
OUT_ALL_CSV = os.path.join(CUR_DIR, "goblint_regression_compare_all.csv")
OUT_SUMMARY = os.path.join(CUR_DIR, "goblint_regression_summary.txt")

TRUE_SET = {"TRUE"}
FALSE_SET = {"FALSE"}
UNKNOWN_SET = {"UNKNOWN", "ERROR"}
TIMEOUT_SET = {"TIMEOUT"}

# =========================
# 工具函数
# =========================
def strip_ansi(text: str) -> str:
    """去掉 ANSI 颜色转义"""
    return re.sub(r'\x1b\[[0-9;]*m', '', text)

def normalize_filename(filepath: str) -> str:
    """
    统一路径格式，截取 goblint-regression 开始的相对路径
    例如:
      /home/.../ComExp_Split/goblint-regression/svp_simple_500_001/svp_simple_500_001_assert1.c
    转成:
      goblint-regression/svp_simple_500_001/svp_simple_500_001_assert1.c
    """
    filepath = filepath.replace("\\", "/")
    parts = filepath.split("/")
    for i, p in enumerate(parts):
        if p == "goblint-regression":
            return "/".join(parts[i:])
    return filepath

def classify_result(res: str) -> str:
    """标准化结果类别"""
    r = res.strip().upper()
    if r in TRUE_SET:
        return "TRUE"
    if r in FALSE_SET:
        return "FALSE"
    if r in TIMEOUT_SET:
        return "TIMEOUT"
    if r in UNKNOWN_SET:
        return "UNKNOWN"
    return r

# =========================
# 解析日志
# =========================
def parse_backend_log(logfile: str, tool_name: str):
    """
    解析形如:
      Analysis result:
      /path/to/file.c, FALSE, 3.45
    的日志
    返回:
      {
        "goblint-regression/.../xxx_assert1.c": ("FALSE", 3.45)
      }
    """
    results = {}

    if not os.path.exists(logfile):
        print(f"[ERROR] Log file not found: {logfile}")
        return results

    with open(logfile, "r", encoding="utf-8", errors="ignore") as f:
        lines = f.readlines()

    stat_counter = Counter()
    total_time = 0.0

    for line in lines:
        text = strip_ansi(line).strip()

        m = re.search(r'([^,]+),\s*(TRUE|FALSE|UNKNOWN|TIMEOUT|ERROR)\s*,\s*([-.\d]+)', text, re.IGNORECASE)
        if not m:
            continue

        raw_file = m.group(1).strip()
        result = classify_result(m.group(2))
        used_time = float(m.group(3))

        file_key = normalize_filename(raw_file)
        results[file_key] = (result, used_time)

        stat_counter[result] += 1
        total_time += used_time

    print(f"[DEBUG][{tool_name}] parsed {len(results)} entries from {logfile}")
    print(f"[DEBUG][{tool_name}] stats = {dict(stat_counter)}, total_time = {total_time:.2f}s")
    return results

# =========================
# 核心比较逻辑
# =========================
def compare_results(cbmc_map, cpa_map):
    """
    生成逐文件比较结果
    输出列表中每项格式:
    {
        "file": ...,
        "cbmc_result": ...,
        "cbmc_time": ...,
        "cpa_result": ...,
        "cpa_time": ...,
        "status": "AUTO" / "NEED_MANUAL",
        "candidate_gt": "TRUE"/"FALSE"/"",
        "reason": ...
    }
    """
    all_files = sorted(set(cbmc_map.keys()) | set(cpa_map.keys()))
    rows = []

    for f in all_files:
        cbmc_res, cbmc_time = cbmc_map.get(f, ("MISSING", 0.0))
        cpa_res, cpa_time = cpa_map.get(f, ("MISSING", 0.0))

        status = "NEED_MANUAL"
        candidate_gt = ""
        reason = ""

        if cbmc_res == "MISSING" or cpa_res == "MISSING":
            reason = "missing_result"
        elif cbmc_res == cpa_res and cbmc_res in {"TRUE", "FALSE"}:
            status = "AUTO"
            candidate_gt = cbmc_res
            reason = "agreed_true_false"
        elif cbmc_res == cpa_res and cbmc_res in {"UNKNOWN", "TIMEOUT"}:
            reason = "agreed_but_non_final"
        elif cbmc_res != cpa_res:
            reason = "disagree"
        else:
            reason = "other"

        rows.append({
            "file": f,
            "cbmc_result": cbmc_res,
            "cbmc_time": f"{cbmc_time:.2f}",
            "cpachecker_result": cpa_res,
            "cpachecker_time": f"{cpa_time:.2f}",
            "status": status,
            "candidate_gt": candidate_gt,
            "reason": reason,
        })

    return rows

# =========================
# 输出文件
# =========================
def write_all_csv(rows):
    with open(OUT_ALL_CSV, "w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=[
                "file",
                "cbmc_result",
                "cbmc_time",
                "cpachecker_result",
                "cpachecker_time",
                "status",
                "candidate_gt",
                "reason",
            ],
        )
        writer.writeheader()
        writer.writerows(rows)

def write_manual_csv(rows):
    manual_rows = [r for r in rows if r["status"] == "NEED_MANUAL"]
    with open(OUT_MANUAL_CSV, "w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=[
                "file",
                "cbmc_result",
                "cbmc_time",
                "cpachecker_result",
                "cpachecker_time",
                "status",
                "candidate_gt",
                "reason",
            ],
        )
        writer.writeheader()
        writer.writerows(manual_rows)

def write_candidate_py(rows):
    auto_rows = [r for r in rows if r["status"] == "AUTO"]

    with open(OUT_CANDIDATE_PY, "w", encoding="utf-8") as f:
        f.write("# -*- coding: utf-8 -*-\n")
        f.write('"""\n')
        f.write("自动生成的 goblint-regression ground truth 候选表\n")
        f.write("\n")
        f.write("说明:\n")
        f.write("- 本文件仅包含 CBMC 与 CPAchecker 结果一致，且均为 TRUE/FALSE 的条目\n")
        f.write("- 这些条目可作为 ground truth 候选，但建议最终仍进行抽查\n")
        f.write("- 所有不一致/UNKNOWN/TIMEOUT/缺失项请查看 goblint_regression_manual_review.csv\n")
        f.write('"""\n\n')

        f.write("GOBLINT_REGRESSION_GROUND_TRUTH_CANDIDATES = {\n")
        for row in sorted(auto_rows, key=lambda x: x["file"]):
            f.write(f'    "{row["file"]}": "{row["candidate_gt"]}",\n')
        f.write("}\n")

def write_summary(rows):
    total = len(rows)
    auto = sum(1 for r in rows if r["status"] == "AUTO")
    manual = sum(1 for r in rows if r["status"] == "NEED_MANUAL")

    reason_counter = Counter(r["reason"] for r in rows)
    agree_true = sum(1 for r in rows if r["status"] == "AUTO" and r["candidate_gt"] == "TRUE")
    agree_false = sum(1 for r in rows if r["status"] == "AUTO" and r["candidate_gt"] == "FALSE")

    with open(OUT_SUMMARY, "w", encoding="utf-8") as f:
        f.write("goblint-regression ground truth candidate generation summary\n")
        f.write("=" * 60 + "\n\n")
        f.write(f"CBMC log       : {CBMC_LOG}\n")
        f.write(f"CPAchecker log : {CPACHECKER_LOG}\n\n")

        f.write(f"Total files           : {total}\n")
        f.write(f"Auto candidates       : {auto}\n")
        f.write(f"Need manual review    : {manual}\n")
        f.write(f"Auto TRUE candidates  : {agree_true}\n")
        f.write(f"Auto FALSE candidates : {agree_false}\n\n")

        f.write("Reason breakdown:\n")
        for k, v in sorted(reason_counter.items()):
            f.write(f"  - {k}: {v}\n")

        f.write("\nExamples of NEED_MANUAL entries:\n")
        cnt = 0
        for r in rows:
            if r["status"] == "NEED_MANUAL":
                f.write(
                    f"  {r['file']} | cbmc={r['cbmc_result']} | cpa={r['cpachecker_result']} | reason={r['reason']}\n"
                )
                cnt += 1
                if cnt >= 20:
                    break

# =========================
# 主程序
# =========================
def main():
    print("[INFO] Parsing logs...")
    cbmc_map = parse_backend_log(CBMC_LOG, "cbmc")
    cpa_map = parse_backend_log(CPACHECKER_LOG, "cpachecker")

    print("[INFO] Comparing results...")
    rows = compare_results(cbmc_map, cpa_map)

    print("[INFO] Writing outputs...")
    write_all_csv(rows)
    write_manual_csv(rows)
    write_candidate_py(rows)
    write_summary(rows)

    total = len(rows)
    auto = sum(1 for r in rows if r["status"] == "AUTO")
    manual = total - auto

    print("\n[SUMMARY]")
    print(f"  Total files        : {total}")
    print(f"  Auto candidates    : {auto}")
    print(f"  Need manual review : {manual}")
    print(f"\n[OUTPUT]")
    print(f"  {OUT_CANDIDATE_PY}")
    print(f"  {OUT_MANUAL_CSV}")
    print(f"  {OUT_ALL_CSV}")
    print(f"  {OUT_SUMMARY}")

if __name__ == "__main__":
    main()