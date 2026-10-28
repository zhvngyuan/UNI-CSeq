#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
逐文件比较 UNI-CSeq 与 NIChecker 的源断言级实验结果。

数据来源与 gen_compare_table.py 一致：
- 源断言：<subdir>/<subdir>.c 静态扫描
- UNI-CSeq：*.c.cbmc.log 的 ** Results:（身份键塌缩）
    程序集 output_cbmc.log（判定与时间）
- NIChecker：_mt_*_result/*.from0to0.log 的 ** Results:
    缺失则回退 output.log / output_NIChecker.log 的 counterexample

默认比较四个程序集：Idv-races、pthread、goblint-regression、racebench2.1。

输出：
1. unicseq_nichecker_compare_all.csv   全部程序
2. unicseq_nichecker_compare_diff.csv  源级违例数量或集合不一致的程序

使用：
    python3 compare_unicseq_nichecker_per_file.py
    python3 compare_unicseq_nichecker_per_file.py --packages goblint-regression racebench2.1
"""

import argparse
import csv
import os
import re
import sys

from assertion_stats import (
    analyze_test_dir,
    format_key,
    parse_nichecker_output_fallback,
    strip_ansi,
)

CUR_DIR = os.path.dirname(os.path.abspath(__file__))
EXPERIMENTS_DIR = os.path.abspath(os.path.join(CUR_DIR, ".."))

PACKAGES = [
    {
        "name": "Idv-races",
        "path": os.path.join(EXPERIMENTS_DIR, "svcomp2022", "Idv-races"),
    },
    {
        "name": "pthread",
        "path": os.path.join(EXPERIMENTS_DIR, "svcomp2022", "pthread"),
    },
    {
        "name": "goblint-regression",
        "path": os.path.join(EXPERIMENTS_DIR, "svcomp2022", "goblint-regression"),
    },
    {
        "name": "racebench2.1",
        "path": os.path.join(EXPERIMENTS_DIR, "racebench2.1"),
    },
]

TESTDIRS_RE = re.compile(r"(BENCHMARK_DIRS|TEST_DIRS)=(['\"])(.*?)\2", re.DOTALL)
CBMC_RESULT_RE = re.compile(
    r"\.c,\s*(?:\x1b\[[0-9;]*m)?(FALSE|TRUE|UNKNOWN|TIMEOUT)(?:\x1b\[[0-9;]*m)?,\s*([0-9.]+)"
)
NICHECKER_RESULT_RE = re.compile(
    r"(SAFE|UNSAFE),\s*counterexample:\s*(\d+),\s*time:\s*([0-9.]+)\s*s"
)
DIR_HEADER_RE = re.compile(r"Checking directory:\s+(\S+)")
FILE_PATH_RE = re.compile(r"File path:\s+(\S+)")


def parse_testdirs(testdirs_path):
    with open(testdirs_path, "r", encoding="utf-8", errors="ignore") as f:
        txt = f.read()
    m = TESTDIRS_RE.search(txt)
    if not m:
        raise ValueError("testdirs.sh 格式不正确: %s" % testdirs_path)
    return [d.strip() for d in m.group(3).strip().splitlines() if d.strip()]


def _path_belongs_to_package(file_path, base_path):
    """判断日志中的 Linux/Windows 路径是否属于当前程序集。"""
    if not file_path:
        return False
    norm = file_path.replace("\\", "/")
    markers = []
    base_norm = base_path.replace("\\", "/")
    markers.append(os.path.basename(base_path))
    exp_norm = EXPERIMENTS_DIR.replace("\\", "/")
    if base_norm.startswith(exp_norm):
        rel = base_norm[len(exp_norm):].lstrip("/")
        if rel:
            markers.append("Experiments/" + rel)
            markers.append(rel)
    return any(marker in norm for marker in markers if marker)


def parse_package_cbmc_summary(cbmc_log_path, base_path):
    """解析程序集 output_cbmc.log，返回 {subdir: {verdict, time}}。"""
    results = {}
    if not os.path.isfile(cbmc_log_path):
        return results

    current_dir = None
    current_file = None
    with open(cbmc_log_path, "r", encoding="utf-8", errors="ignore") as f:
        for raw in f:
            line = strip_ansi(raw)
            m_dir = DIR_HEADER_RE.search(line)
            if m_dir:
                current_dir = m_dir.group(1)
                current_file = None
                continue
            m_file = FILE_PATH_RE.search(line)
            if m_file:
                current_file = m_file.group(1)
                continue
            m_res = CBMC_RESULT_RE.search(line)
            if m_res and current_dir:
                if current_file and not _path_belongs_to_package(current_file, base_path):
                    continue
                if not current_file and not _path_belongs_to_package(line, base_path):
                    continue
                results[current_dir] = {
                    "verdict": m_res.group(1),
                    "time": float(m_res.group(2)),
                }
    return results


def parse_package_nichecker_summary(nic_log_path, base_path):
    """解析程序集 output_NIChecker.log，返回 {subdir: {verdict, counterexample, time}}。"""
    results = {}
    if not os.path.isfile(nic_log_path):
        return results

    current_dir = None
    current_file = None
    with open(nic_log_path, "r", encoding="utf-8", errors="ignore") as f:
        for raw in f:
            line = strip_ansi(raw)
            m_dir = DIR_HEADER_RE.search(line)
            if m_dir:
                current_dir = m_dir.group(1)
                current_file = None
                continue
            m_file = FILE_PATH_RE.search(line)
            if m_file:
                current_file = m_file.group(1)
                continue
            m_res = NICHECKER_RESULT_RE.search(line)
            if m_res and current_dir:
                if current_file and not _path_belongs_to_package(current_file, base_path):
                    continue
                results[current_dir] = {
                    "verdict": m_res.group(1),
                    "counterexample": int(m_res.group(2)),
                    "time": float(m_res.group(3)),
                }
    return results


def verdicts_equivalent(nic_verdict, uni_verdict):
    """SAFE↔TRUE、UNSAFE↔FALSE 视为判定一致。"""
    mapping = {
        ("SAFE", "TRUE"),
        ("UNSAFE", "FALSE"),
        ("TRUE", "TRUE"),
        ("FALSE", "FALSE"),
    }
    if not nic_verdict or not uni_verdict:
        return ""
    return "YES" if (nic_verdict, uni_verdict) in mapping else "NO"


def compare_one_dir(pkg_name, subdir, base_path, nic_summary, uni_summary):
    test_dir = os.path.join(base_path, subdir)
    output_log = os.path.join(test_dir, "output.log")
    stats = analyze_test_dir(test_dir, subdir)
    uni = stats["uni"]
    nic = stats["nic"]

    uni_from_pkg = uni_summary.get(subdir, {})
    uni_verdict = uni_from_pkg.get("verdict") or uni["verdict"]
    uni_time = uni_from_pkg.get("time", "")

    fallback = parse_nichecker_output_fallback(output_log)
    nic_from_pkg = nic_summary.get(subdir, {})
    nic_verdict = (
        fallback["verdict"]
        or nic_from_pkg.get("verdict")
        or nic["verdict"]
    )
    if nic_verdict in ("TRUE", "FALSE"):
        nic_verdict = {"TRUE": "SAFE", "FALSE": "UNSAFE"}[nic_verdict]
    nic_time = fallback["time"]
    if nic_time is None:
        nic_time = nic_from_pkg.get("time", "")

    uni_failed = set(uni["failed_keys"])
    if nic["source"] == "counterexample_fallback":
        nic_src_vio = nic.get("fallback_counterexample")
        if nic_src_vio is None:
            nic_src_vio = nic_from_pkg.get("counterexample")
            if nic_src_vio is not None:
                nic["source"] = "counterexample_fallback"
        nic_failed = set()
        same_set = ""
        same_count = ""
        if nic_src_vio is not None:
            same_count = "YES" if int(nic_src_vio) == len(uni_failed) else "NO"
    elif nic["source"] == "results":
        nic_failed = set(nic["failed_keys"])
        nic_src_vio = len(nic_failed)
        same_count = "YES" if nic_src_vio == len(uni_failed) else "NO"
        same_set = "YES" if nic_failed == uni_failed else "NO"
    else:
        nic_failed = set()
        nic_src_vio = nic_from_pkg.get("counterexample", "")
        same_set = ""
        same_count = ""
        if nic_src_vio != "":
            same_count = "YES" if int(nic_src_vio) == len(uni_failed) else "NO"
            nic["source"] = "counterexample_fallback"

    if nic["source"] == "missing" and nic_src_vio == "":
        nic_source = "MISSING"
    else:
        nic_source = nic["source"]

    rel_file = os.path.join(subdir, subdir + ".c").replace("\\", "/")
    uni_log = uni.get("log_path")

    return {
        "package": pkg_name,
        "subdir": subdir,
        "file": rel_file,
        "src_assertions": stats["src_assertions"],
        "UNI-CSeq_src_violations": len(uni_failed),
        "NIChecker_src_violations": nic_src_vio if nic_src_vio != "" else "",
        "UNI-CSeq_vcc_total": uni["vcc_total"],
        "UNI-CSeq_vcc_fail": uni["vcc_fail"],
        "NIChecker_vcc_total": nic["vcc_total"],
        "NIChecker_vcc_fail": nic["vcc_fail"],
        "UNI-CSeq_verdict": uni_verdict,
        "UNI-CSeq_time": uni_time,
        "NIChecker_verdict": nic_verdict,
        "NIChecker_time": nic_time if nic_time is not None else "",
        "diff(NIChecker-UNI-CSeq)": (
            (int(nic_src_vio) - len(uni_failed)) if nic_src_vio != "" else ""
        ),
        "same_src_vio_count": same_count,
        "same_src_vio_set": same_set,
        "same_verdict": verdicts_equivalent(nic_verdict, uni_verdict),
        "UNI-CSeq_failed_keys": "; ".join(sorted(format_key(k) for k in uni_failed)),
        "NIChecker_failed_keys": "; ".join(sorted(format_key(k) for k in nic_failed)),
        "output_log_exists": "YES" if os.path.isfile(output_log) else "NO",
        "cbmc_log_exists": "YES" if uni_log and os.path.isfile(uni_log) else "NO",
        "NIChecker_source": nic_source,
    }


FIELDNAMES = [
    "package",
    "subdir",
    "file",
    "src_assertions",
    "UNI-CSeq_src_violations",
    "NIChecker_src_violations",
    "UNI-CSeq_vcc_total",
    "UNI-CSeq_vcc_fail",
    "NIChecker_vcc_total",
    "NIChecker_vcc_fail",
    "UNI-CSeq_verdict",
    "UNI-CSeq_time",
    "NIChecker_verdict",
    "NIChecker_time",
    "diff(NIChecker-UNI-CSeq)",
    "same_src_vio_count",
    "same_src_vio_set",
    "same_verdict",
    "UNI-CSeq_failed_keys",
    "NIChecker_failed_keys",
    "output_log_exists",
    "cbmc_log_exists",
    "NIChecker_source",
]


def write_csv(path, rows):
    with open(path, "w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=FIELDNAMES)
        writer.writeheader()
        writer.writerows(rows)


def configure_stdout():
    if hasattr(sys.stdout, "reconfigure"):
        try:
            sys.stdout.reconfigure(encoding="utf-8")
        except Exception:
            pass


def print_diff_table(diff_rows):
    if not diff_rows:
        print("\n[INFO] 所有程序的源级违例一致。")
        return

    print("\n[INFO] 源级违例数量或集合不一致的程序：")
    header = (
        "%-20s %-22s %8s %10s %10s %8s %10s %10s %6s %6s"
        % (
            "package",
            "subdir",
            "src",
            "UNI-Vio",
            "NIC-Vio",
            "diff",
            "UNI",
            "NIC",
            "count",
            "set",
        )
    )
    print(header)
    print("-" * len(header))
    for r in diff_rows:
        print(
            "%-20s %-22s %8s %10s %10s %8s %10s %10s %6s %6s"
            % (
                r["package"],
                r["subdir"],
                r["src_assertions"],
                r["UNI-CSeq_src_violations"],
                r["NIChecker_src_violations"],
                r["diff(NIChecker-UNI-CSeq)"],
                r["UNI-CSeq_verdict"] or "-",
                r["NIChecker_verdict"] or "-",
                r["same_src_vio_count"] or "-",
                r["same_src_vio_set"] or "-",
            )
        )
        if r["UNI-CSeq_failed_keys"] or r["NIChecker_failed_keys"]:
            print("    UNI failed: %s" % (r["UNI-CSeq_failed_keys"] or "-"))
            print("    NIC failed: %s" % (r["NIChecker_failed_keys"] or "-"))


def parse_args(argv):
    parser = argparse.ArgumentParser(
        description="筛选 UNI-CSeq 与 NIChecker 源断言违例不一致的程序"
    )
    parser.add_argument(
        "--packages",
        nargs="+",
        default=[pkg["name"] for pkg in PACKAGES],
        help="要比较的程序集名称，默认全部四个",
    )
    parser.add_argument(
        "--outdir",
        default=CUR_DIR,
        help="CSV 输出目录，默认为本脚本所在目录",
    )
    return parser.parse_args(argv)


def main(argv=None):
    configure_stdout()
    args = parse_args(argv if argv is not None else sys.argv[1:])
    wanted = set(args.packages)
    unknown = wanted - set(pkg["name"] for pkg in PACKAGES)
    if unknown:
        raise SystemExit("未知程序集: %s" % ", ".join(sorted(unknown)))

    os.makedirs(args.outdir, exist_ok=True)
    all_out = os.path.join(args.outdir, "unicseq_nichecker_compare_all.csv")
    diff_out = os.path.join(args.outdir, "unicseq_nichecker_compare_diff.csv")

    rows = []
    package_stats = []

    for pkg in PACKAGES:
        if pkg["name"] not in wanted:
            continue
        pkg_name = pkg["name"]
        base_path = pkg["path"]
        testdirs_file = os.path.join(base_path, "testdirs.sh")
        if not os.path.isfile(testdirs_file):
            print("[WARN] 未找到 testdirs.sh，跳过: %s" % testdirs_file)
            continue

        testdirs = parse_testdirs(testdirs_file)
        nic_summary = parse_package_nichecker_summary(
            os.path.join(base_path, "output_NIChecker.log"), base_path
        )
        uni_summary = parse_package_cbmc_summary(
            os.path.join(base_path, "output_cbmc.log"), base_path
        )

        pkg_rows = []
        for subdir in testdirs:
            row = compare_one_dir(pkg_name, subdir, base_path, nic_summary, uni_summary)
            pkg_rows.append(row)
            rows.append(row)

        nic_total = sum(
            int(r["NIChecker_src_violations"])
            for r in pkg_rows
            if r["NIChecker_src_violations"] != ""
        )
        uni_total = sum(r["UNI-CSeq_src_violations"] for r in pkg_rows)
        assert_total = sum(r["src_assertions"] for r in pkg_rows)
        n_diff = sum(
            1
            for r in pkg_rows
            if r["same_src_vio_count"] == "NO" or r["same_src_vio_set"] == "NO"
        )
        n_missing = sum(1 for r in pkg_rows if r["same_src_vio_count"] == "")
        package_stats.append(
            {
                "name": pkg_name,
                "files": len(pkg_rows),
                "assertions": assert_total,
                "nic_vio": nic_total,
                "uni_vio": uni_total,
                "diff_files": n_diff,
                "missing": n_missing,
            }
        )

    def sort_key(r):
        same_count = r["same_src_vio_count"]
        same_set = r["same_src_vio_set"]
        diff = r["diff(NIChecker-UNI-CSeq)"]
        abs_diff = abs(diff) if diff != "" else -1
        inconsistent = same_count == "NO" or same_set == "NO"
        missing = same_count == ""
        order = 0 if inconsistent else (1 if missing else 2)
        return (order, -abs_diff, r["package"], r["subdir"])

    rows.sort(key=sort_key)
    diff_rows = [
        r for r in rows
        if r["same_src_vio_count"] == "NO" or r["same_src_vio_set"] == "NO"
    ]

    write_csv(all_out, rows)
    write_csv(diff_out, diff_rows)

    print("[INFO] 程序集统计（源断言站点 + Results 身份键塌缩）：")
    print(
        "%-20s %6s %10s %10s %10s %10s %8s"
        % ("package", "files", "asserts", "NIC-Vio", "UNI-Vio", "diff-files", "missing")
    )
    print("-" * 80)
    for st in package_stats:
        print(
            "%-20s %6d %10d %10d %10d %10d %8d"
            % (
                st["name"],
                st["files"],
                st["assertions"],
                st["nic_vio"],
                st["uni_vio"],
                st["diff_files"],
                st["missing"],
            )
        )

    total_files = sum(st["files"] for st in package_stats)
    total_assert = sum(st["assertions"] for st in package_stats)
    total_nic = sum(st["nic_vio"] for st in package_stats)
    total_uni = sum(st["uni_vio"] for st in package_stats)
    total_diff = sum(st["diff_files"] for st in package_stats)
    print("-" * 80)
    print(
        "%-20s %6d %10d %10d %10d %10d"
        % ("Total", total_files, total_assert, total_nic, total_uni, total_diff)
    )

    print_diff_table(diff_rows)

    print("\n[INFO] 全量结果: %s" % all_out)
    print("[INFO] 差异结果: %s" % diff_out)
    print("[INFO] 不一致程序数: %d / %d" % (len(diff_rows), total_files))


if __name__ == "__main__":
    main()
