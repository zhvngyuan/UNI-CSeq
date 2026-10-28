#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
逐文件比较 goblint-regression 中 NIChecker 与 UNI-CSeq 的源断言级检测结果。

数据来源：
- 源断言：<subdir>/<subdir>.c 静态扫描
- UNI-CSeq：*.c.cbmc.log 的 ** Results:
- NIChecker：_mt_*_result/*.from0to0.log 的 ** Results:
  缺失时回退 output.log 的 counterexample

输出：
1. goblint_regression_compare_all.csv
2. goblint_regression_compare_diff.csv

使用：
    python3 compare_goblint_regression_per_file.py
"""

import os
import re
import csv

from assertion_stats import analyze_test_dir, format_key, parse_nichecker_output_fallback

CUR_DIR = os.path.dirname(os.path.abspath(__file__))
EXPERIMENTS_DIR = os.path.abspath(os.path.join(CUR_DIR, ".."))
BASE_PATH = os.path.join(EXPERIMENTS_DIR, "svcomp2022", "goblint-regression")

TESTDIRS_FILE = os.path.join(BASE_PATH, "testdirs.sh")

ALL_OUT = os.path.join(CUR_DIR, "goblint_regression_compare_all.csv")
DIFF_OUT = os.path.join(CUR_DIR, "goblint_regression_compare_diff.csv")


def parse_testdirs(testdirs_path):
    """解析 testdirs.sh，返回测试子目录列表"""
    with open(testdirs_path, 'r', encoding='utf-8') as f:
        txt = f.read()
    m = re.search(r'(BENCHMARK_DIRS|TEST_DIRS)=([\'"])(.*?)\2', txt, re.DOTALL)
    if not m:
        raise ValueError(f"testdirs.sh 格式不正确: {testdirs_path}")
    dir_lines = m.group(3).strip().splitlines()
    return [d.strip() for d in dir_lines if d.strip()]


def verdicts_equivalent(nic_verdict, uni_verdict):
    mapping = {
        ("SAFE", "TRUE"),
        ("UNSAFE", "FALSE"),
        ("TRUE", "TRUE"),
        ("FALSE", "FALSE"),
    }
    if not nic_verdict or not uni_verdict:
        return ""
    nic = {"TRUE": "SAFE", "FALSE": "UNSAFE"}.get(nic_verdict, nic_verdict)
    uni = uni_verdict
    if nic in ("SAFE", "UNSAFE") and uni in ("TRUE", "FALSE"):
        return "YES" if (nic, uni) in mapping else "NO"
    return "YES" if nic_verdict == uni_verdict else "NO"


def compare_one_dir(subdir, base_path):
    test_dir = os.path.join(base_path, subdir)
    output_log = os.path.join(test_dir, "output.log")
    stats = analyze_test_dir(test_dir, subdir)
    uni = stats["uni"]
    nic = stats["nic"]
    fallback = parse_nichecker_output_fallback(output_log)

    uni_failed = set(uni["failed_keys"])
    if nic["source"] == "counterexample_fallback":
        nic_src_vio = nic.get("fallback_counterexample")
        nic_failed = set()
        same_set = ""
        same_count = ""
        if nic_src_vio is not None:
            same_count = "YES" if nic_src_vio == len(uni_failed) else "NO"
    else:
        nic_failed = set(nic["failed_keys"])
        nic_src_vio = len(nic_failed)
        same_count = "YES" if nic_src_vio == len(uni_failed) else "NO"
        same_set = "YES" if nic_failed == uni_failed else "NO"

    nic_verdict = fallback["verdict"] or nic["verdict"]
    uni_verdict = uni["verdict"]
    nic_time = fallback["time"] if fallback["time"] is not None else ""

    rel_file = os.path.join(subdir, subdir + ".c").replace("\\", "/")
    uni_log = uni.get("log_path")
    nic_log = nic.get("log_path")

    return {
        "subdir": subdir,
        "file": rel_file,
        "src_assertions": stats["src_assertions"],
        "UNI-CSeq_src_violations": len(uni_failed),
        "NIChecker_src_violations": nic_src_vio if nic_src_vio is not None else "",
        "UNI-CSeq_vcc_total": uni["vcc_total"],
        "UNI-CSeq_vcc_fail": uni["vcc_fail"],
        "NIChecker_vcc_total": nic["vcc_total"],
        "NIChecker_vcc_fail": nic["vcc_fail"],
        "diff(NIChecker-UNI-CSeq)": (
            (nic_src_vio - len(uni_failed)) if nic_src_vio is not None else ""
        ),
        "same_src_vio_count": same_count,
        "same_src_vio_set": same_set,
        "same_verdict": verdicts_equivalent(nic_verdict, uni_verdict),
        "UNI-CSeq_failed_keys": "; ".join(sorted(format_key(k) for k in uni_failed)),
        "NIChecker_failed_keys": "; ".join(sorted(format_key(k) for k in nic_failed)),
        "UNI-CSeq_verdict": uni_verdict,
        "NIChecker_verdict": nic_verdict,
        "NIChecker_time": nic_time,
        "NIChecker_source": nic["source"],
        "output_log_exists": "YES" if os.path.isfile(output_log) else "NO",
        "cbmc_log_exists": "YES" if uni_log and os.path.isfile(uni_log) else "NO",
        "nichecker_detail_exists": "YES" if nic_log and os.path.isfile(nic_log) else "NO",
    }


FIELDNAMES = [
    "subdir",
    "file",
    "src_assertions",
    "UNI-CSeq_src_violations",
    "NIChecker_src_violations",
    "UNI-CSeq_vcc_total",
    "UNI-CSeq_vcc_fail",
    "NIChecker_vcc_total",
    "NIChecker_vcc_fail",
    "diff(NIChecker-UNI-CSeq)",
    "same_src_vio_count",
    "same_src_vio_set",
    "same_verdict",
    "UNI-CSeq_failed_keys",
    "NIChecker_failed_keys",
    "UNI-CSeq_verdict",
    "NIChecker_verdict",
    "NIChecker_time",
    "NIChecker_source",
    "output_log_exists",
    "cbmc_log_exists",
    "nichecker_detail_exists",
]


def write_csv(path, rows):
    with open(path, 'w', newline='', encoding='utf-8') as f:
        writer = csv.DictWriter(f, fieldnames=FIELDNAMES)
        writer.writeheader()
        writer.writerows(rows)


def main():
    if not os.path.isfile(TESTDIRS_FILE):
        raise FileNotFoundError(f"未找到 testdirs.sh: {TESTDIRS_FILE}")

    testdirs = parse_testdirs(TESTDIRS_FILE)
    rows = []

    for subdir in testdirs:
        row = compare_one_dir(subdir, BASE_PATH)
        rows.append(row)

    def abs_diff(row):
        d = row["diff(NIChecker-UNI-CSeq)"]
        return abs(d) if d != "" else -1

    rows.sort(key=lambda x: (
        x["same_src_vio_set"] != "NO",
        x["same_src_vio_count"] != "NO",
        -abs_diff(x),
        x["file"],
    ))

    diff_rows = [
        r for r in rows
        if r["same_src_vio_count"] == "NO" or r["same_src_vio_set"] == "NO"
    ]

    write_csv(ALL_OUT, rows)
    write_csv(DIFF_OUT, diff_rows)

    total_nic = sum(
        int(r["NIChecker_src_violations"])
        for r in rows
        if r["NIChecker_src_violations"] != ""
    )
    total_uni = sum(r["UNI-CSeq_src_violations"] for r in rows)
    total_src = sum(r["src_assertions"] for r in rows)

    print(f"[INFO] 测试子目录数量: {len(testdirs)}")
    print(f"[INFO] 结果记录数量: {len(rows)}")
    print(f"[INFO] 源断言站点总数: {total_src}")
    print(f"[INFO] NIChecker 源级 violations: {total_nic}")
    print(f"[INFO] UNI-CSeq 源级 violations: {total_uni}")
    print(f"[INFO] 源级检测不一致的文件数: {len(diff_rows)}")
    print(f"[INFO] 全量结果输出: {ALL_OUT}")
    print(f"[INFO] 差异结果输出: {DIFF_OUT}")

    if diff_rows:
        print("\n[INFO] 以下文件源级检测结果不一致：")
        for r in diff_rows:
            print(
                f"  - {r['file']} | "
                f"src={r['src_assertions']} "
                f"NIChecker={r['NIChecker_src_violations']}, "
                f"UNI-CSeq={r['UNI-CSeq_src_violations']}, "
                f"count={r['same_src_vio_count']}, set={r['same_src_vio_set']}"
            )
            if r["UNI-CSeq_failed_keys"] or r["NIChecker_failed_keys"]:
                print(f"    UNI failed: {r['UNI-CSeq_failed_keys'] or '-'}")
                print(f"    NIC failed: {r['NIChecker_failed_keys'] or '-'}")
    else:
        print("\n[INFO] 所有文件源级检测结果一致。")


if __name__ == "__main__":
    main()
