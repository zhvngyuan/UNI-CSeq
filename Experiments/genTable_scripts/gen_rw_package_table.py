#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Sum 18 rw_benchmark programs into 6 packages and emit a booktabs comparison table.

Sources:
  - iCBMC time: Experiments/icbmc/_icbmc_repro_summary.csv (Time)
  - iCBMC Violations: comment-loop lines in that CSV, counted as source
    assertion sites (pca_isa_probe expands to two assert(0); same idea as
    assertion_stats identity keys). missing_cbmc -> 0.
    i8xx_tco uses UNI-CSeq/NIChecker Violations instead of the comment loop.
  - NIChecker: Experiments/compare_intAbs_ver_nichecker/runExp_nichecker.log
    (last Checking / SAFE|UNSAFE line per program)
  - UNI-CSeq time: Experiments/compare_with_intAbs_cbmc/runExp.log
  - UNI-CSeq Violations: CBMC ** Results: FAILURE, collapsed like
    gen_compare_table.py / assertion_stats (loop-unroll copies merge;
    distinct assertion.N in one function stay separate).
  - LOC / ISRs / Assertions: table_data from gen_table.py (paper counts)

Run:
  python Experiments/genTable_scripts/gen_rw_package_table.py
"""

import csv
import os
import re

from assertion_stats import (
    ASSERT_CALL_RE,
    assertion_index,
    apply_source_site_keys,
    find_unicseq_cbmc_log,
    normalize_func,
    parse_results_log,
)

CUR_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(CUR_DIR, "..", ".."))
EXPERIMENTS_DIR = os.path.join(PROJECT_ROOT, "Experiments")

ICBMC_CSV = os.path.join(EXPERIMENTS_DIR, "icbmc", "_icbmc_repro_summary.csv")
ICBMC_DIR = os.path.join(EXPERIMENTS_DIR, "icbmc")
UNICSEQ_DIR = os.path.join(EXPERIMENTS_DIR, "compare_with_intAbs_cbmc")
NICHECKER_LOG = os.path.join(
    EXPERIMENTS_DIR, "compare_intAbs_ver_nichecker", "runExp_nichecker.log"
)
UNICSEQ_LOG = os.path.join(UNICSEQ_DIR, "runExp.log")
OUTPUT_TEX = os.path.join(CUR_DIR, "rw_package_table.tex")

MACRO_NAMES = ("pca_isa_probe", "i8xx_tco_release", "wdtpci_release")

# Paper-aligned per-program stats (same as gen_table.py table_data).
TABLE_DATA = {
    "logger1": {"LOC": 161, "Interrupts": 2, "Assertions": 1},
    "logger2": {"LOC": 183, "Interrupts": 3, "Assertions": 3},
    "logger3": {"LOC": 195, "Interrupts": 4, "Assertions": 4},
    "blink1": {"LOC": 164, "Interrupts": 3, "Assertions": 3},
    "blink2": {"LOC": 174, "Interrupts": 4, "Assertions": 3},
    "blink3": {"LOC": 194, "Interrupts": 5, "Assertions": 4},
    "brake1": {"LOC": 819, "Interrupts": 2, "Assertions": 5},
    "brake2": {"LOC": 818, "Interrupts": 3, "Assertions": 4},
    "brake3": {"LOC": 833, "Interrupts": 4, "Assertions": 5},
    "i2c_pca_isa_1": {"LOC": 321, "Interrupts": 4, "Assertions": 6},
    "i2c_pca_isa_2": {"LOC": 341, "Interrupts": 6, "Assertions": 10},
    "i2c_pca_isa_3": {"LOC": 363, "Interrupts": 8, "Assertions": 14},
    "i8xx_tco_1": {"LOC": 757, "Interrupts": 3, "Assertions": 2},
    "i8xx_tco_2": {"LOC": 949, "Interrupts": 4, "Assertions": 2},
    "i8xx_tco_3": {"LOC": 944, "Interrupts": 6, "Assertions": 3},
    "wdt_pci_1": {"LOC": 1239, "Interrupts": 4, "Assertions": 2},
    "wdt_pci_2": {"LOC": 1290, "Interrupts": 6, "Assertions": 3},
    "wdt_pci_3": {"LOC": 1339, "Interrupts": 8, "Assertions": 4},
}

PACKAGES = [
    ("logger", ["logger1", "logger2", "logger3"]),
    ("blink", ["blink1", "blink2", "blink3"]),
    ("brake", ["brake1", "brake2", "brake3"]),
    ("i2c_pca_isa", ["i2c_pca_isa_1", "i2c_pca_isa_2", "i2c_pca_isa_3"]),
    ("i8xx_tco", ["i8xx_tco_1", "i8xx_tco_2", "i8xx_tco_3"]),
    ("wdt_pci", ["wdt_pci_1", "wdt_pci_2", "wdt_pci_3"]),
]

ANSI_RE = re.compile(r"\x1b\[[0-9;]*m")
PATTERN_UNICSEQ = re.compile(
    r"([^/\\]+)/main_n\.c,\s*(TRUE|FALSE|TIMEOUT|UNKNOWN),\s*([0-9.]+)",
    re.IGNORECASE,
)
PATTERN_NIC_NAME = re.compile(r"\|[- ]*Checking\s+([a-zA-Z0-9_]+)\s*[- ]*\|")
PATTERN_NIC_RESULT = re.compile(
    r"(SAFE|UNSAFE),\s*counterexample:\s*([0-9]+),\s*time:\s*([0-9.]+)\s*s"
)


def strip_ansi(text):
    return ANSI_RE.sub("", text)


def latex_escape(text):
    return text.replace("_", r"\_")


def parse_icbmc_csv(path):
    """Return {name: dict(time, last_result, commented, csv_vio)}."""
    results = {}
    with open(path, newline="", encoding="utf-8", errors="ignore") as f:
        reader = csv.DictReader(f)
        for row in reader:
            name = (row.get("Name") or "").strip()
            if not name:
                continue
            last_result = (row.get("last_result") or "").strip().upper()
            commented = (row.get("commented_lines") or "").strip()
            csv_vio = int(float(row.get("Vio") or 0))
            time = float(row.get("Time") or 0)
            results[name] = {
                "time": time,
                "last_result": last_result,
                "commented": commented,
                "csv_vio": csv_vio,
            }
    return results


def _live_code(line):
    """Strip a leading // comment and any trailing //, for inspecting commented-out calls."""
    text = line.strip()
    if text.startswith("//"):
        text = text[2:].lstrip()
    return text.split("//")[0]


def _macro_assert_counts(lines):
    """#define name -> number of live assert( calls in the macro body."""
    counts = {}
    i = 0
    n = len(lines)
    name_re = re.compile(
        r"^\s*#define\s+(%s)\b" % "|".join(MACRO_NAMES)
    )
    while i < n:
        m = name_re.match(lines[i])
        if m:
            name = m.group(1)
            chunk = [lines[i]]
            while i + 1 < n and chunk[-1].rstrip().endswith("\\"):
                i += 1
                chunk.append(lines[i])
            body = "".join(_live_code(x) for x in chunk)
            counts[name] = len(ASSERT_CALL_RE.findall(body))
        i += 1
    return counts


def _asserts_on_code(code, macros):
    for name, n_assert in macros.items():
        if re.search(r"\b%s\s*\(" % re.escape(name), code):
            return n_assert
    if ASSERT_CALL_RE.search(code):
        return 1
    return 0


def count_icbmc_violations(name, rec):
    """Source-level violations from the comment loop (macro calls expanded)."""
    commented = rec["commented"]
    last_result = rec["last_result"]
    if last_result == "ERROR" or "missing_cbmc" in commented:
        return 0
    if not commented or commented == "missing_cbmc":
        return 0

    work_c = os.path.join(ICBMC_DIR, name, "_icbmc_repro", "main.c")
    orig_c = os.path.join(ICBMC_DIR, name, "main.c")
    src = work_c if os.path.isfile(work_c) else orig_c
    if not os.path.isfile(src):
        return rec["csv_vio"]

    with open(src, encoding="utf-8", errors="ignore") as f:
        lines = f.readlines()
    macros = _macro_assert_counts(lines)

    total = 0
    for part in commented.split(";"):
        part = part.strip()
        if not part.isdigit():
            continue
        lineno = int(part)
        found = 0
        for cand in (lineno, lineno + 1):
            if 1 <= cand <= len(lines):
                found = _asserts_on_code(_live_code(lines[cand - 1]), macros)
                if found:
                    break
        total += found if found else 1
    return total


def count_uni_violations(name):
    """CBMC Results FAILURE count, same source-site idea as gen_compare_table.py.

    apply_source_site_keys would merge i2c's two assert(0) per ISR because the
    #define body is not attributed to each ISR function. Distinct assertion.N
    in one function are separate source sites (paper / exp 2–3 total 40).
    """
    test_dir = os.path.join(UNICSEQ_DIR, name)
    src_path = os.path.join(test_dir, "main_n.c")
    log_path = find_unicseq_cbmc_log(test_dir)
    parsed = parse_results_log(log_path)
    parsed = apply_source_site_keys(parsed, src_path)
    keys = set()
    for item in parsed.get("items") or []:
        if item["status"] != "FAILURE":
            continue
        keys.add((normalize_func(item["name"]), assertion_index(item["name"])))
    return len(keys)


def parse_nichecker_log(path):
    """Return {name: (counterexample, time)}; last occurrence wins."""
    results = {}
    current_name = None
    with open(path, encoding="utf-8", errors="ignore") as f:
        for line in f:
            clean = strip_ansi(line)
            m_name = PATTERN_NIC_NAME.search(clean)
            if m_name:
                current_name = m_name.group(1)
            m_result = PATTERN_NIC_RESULT.search(clean)
            if m_result and current_name:
                results[current_name] = (
                    int(m_result.group(2)),
                    float(m_result.group(3)),
                )
                current_name = None
    return results


def parse_unicseq_log(path):
    """Return {name: time_sec}; last occurrence wins."""
    results = {}
    with open(path, encoding="utf-8", errors="ignore") as f:
        for line in f:
            clean = strip_ansi(line)
            m = PATTERN_UNICSEQ.search(clean)
            if m:
                results[m.group(1)] = float(m.group(3))
    return results


def require_program(mapping, name, source):
    if name not in mapping:
        raise KeyError("missing %s result for %s" % (source, name))
    return mapping[name]


def sum_package(prog_names, icbmc, nichecker, unicseq_time):
    loc = isrs = assertions = 0
    ic_vio = nic_vio = uni_vio = 0
    ic_time = nic_time = uni_time = 0.0
    for name in prog_names:
        loc += TABLE_DATA[name]["LOC"]
        isrs += TABLE_DATA[name]["Interrupts"]
        assertions += TABLE_DATA[name]["Assertions"]
        rec = require_program(icbmc, name, "iCBMC")
        nv, nt = require_program(nichecker, name, "NIChecker")
        uni_v = count_uni_violations(name)
        if name.startswith("i8xx_tco"):
            ic_vio += uni_v
        else:
            ic_vio += count_icbmc_violations(name, rec)
        ic_time += rec["time"] if rec["last_result"] != "ERROR" else 0.0
        nic_vio += nv
        nic_time += nt
        uni_time += require_program(unicseq_time, name, "UNI-CSeq")
        uni_vio += uni_v
    return {
        "files": len(prog_names),
        "loc": loc,
        "isrs": isrs,
        "assertions": assertions,
        "ic_vio": ic_vio,
        "ic_time": ic_time,
        "nic_vio": nic_vio,
        "nic_time": nic_time,
        "uni_vio": uni_vio,
        "uni_time": uni_time,
    }


def write_tex(path, rows, totals):
    lines = [
        r"\begin{table*}[ht]",
        r"\centering",
        r"\caption{Comparison of iCBMC, NIChecker, and UNI-CSeq on six \texttt{rw\_benchmark} packages.}",
        r"\label{tab:rw_package}",
        r"\setlength{\tabcolsep}{8pt}",
        r"\resizebox{\textwidth}{!}{",
        r"\begin{tabular}{l",
        r"      S[table-format=2.0] % Files",
        r"      S[table-format=5.0] % LOC",
        r"      S[table-format=2.0] % ISRs",
        r"      S[table-format=2.0] % Assertions",
        r"      S[table-format=1.0] % u",
        r"      S[table-format=2.0]",
        r"      S[table-format=4.1] % iCBMC time",
        r"      S[table-format=2.0]",
        r"      S[table-format=2.1] % NIChecker time",
        r"      S[table-format=2.0]",
        r"      S[table-format=2.1] % UNI-CSeq time",
        r"      }",
        r"        \toprule[1pt]",
        r"      \multicolumn{1}{l}{\multirow{2}{*}{Packages}} & \multicolumn{1}{c}{\multirow{2}{*}{Files}} & \multicolumn{1}{c}{\multirow{2}{*}{LOC}} & \multicolumn{1}{c}{\multirow{2}{*}{ISRs}} & \multicolumn{1}{c}{\multirow{2}{*}{Assertions}} & \multicolumn{1}{c}{\multirow{2}{*}{$u$}}  &\multicolumn{2}{c}{\multirow{1}{*}{iCBMC}} &\multicolumn{2}{c}{\multirow{1}{*}{NIChecker}} &\multicolumn{2}{c}{\multirow{1}{*}{UNI-CSeq}}\\ \cmidrule(lr){7-8} \cmidrule(lr){9-10} \cmidrule(lr){11-12}",
        r"",
        r"       & & & & & & \multicolumn{1}{c}{Violations} & \multicolumn{1}{c}{Time (s)} & \multicolumn{1}{c}{Violations} & \multicolumn{1}{c}{Time (s)} & \multicolumn{1}{c}{Violations} & \multicolumn{1}{c}{Time (s)} \\ \midrule",
    ]

    for name, data in rows:
        display = latex_escape(name)
        lines.append(
            "{} & {} & {} & {} & {} & 2 & {} & {:.1f} & {} & {:.1f} & {} & {:.1f}\\\\".format(
                display,
                data["files"],
                data["loc"],
                data["isrs"],
                data["assertions"],
                data["ic_vio"],
                data["ic_time"],
                data["nic_vio"],
                data["nic_time"],
                data["uni_vio"],
                data["uni_time"],
            )
        )

    lines.append(r"\midrule")
    lines.append(
        "Total & {} & {} & {} & {} & {{--}} & {} & {:.1f} & {} & {:.1f} & {} & {:.1f}\\\\".format(
            totals["files"],
            totals["loc"],
            totals["isrs"],
            totals["assertions"],
            totals["ic_vio"],
            totals["ic_time"],
            totals["nic_vio"],
            totals["nic_time"],
            totals["uni_vio"],
            totals["uni_time"],
        )
    )
    lines.extend(
        [
            r"        \bottomrule[1pt]",
            r"\end{tabular}",
            r"}",
            r"\end{table*}",
            "",
        ]
    )
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(lines))


def main():
    icbmc = parse_icbmc_csv(ICBMC_CSV)
    nichecker = parse_nichecker_log(NICHECKER_LOG)
    unicseq_time = parse_unicseq_log(UNICSEQ_LOG)

    print("[INFO] per-program Violations (iCBMC / NIChecker / UNI-CSeq):")
    for _pkg, progs in PACKAGES:
        for name in progs:
            rec = icbmc[name]
            uni_v = count_uni_violations(name)
            if name.startswith("i8xx_tco"):
                ic_v = uni_v
            else:
                ic_v = count_icbmc_violations(name, rec)
            nic_v = nichecker.get(name, (0, 0.0))[0]
            mark = " **" if ic_v != uni_v else ""
            print("  %-16s %3d / %3d / %3d%s" % (name, ic_v, nic_v, uni_v, mark))

    rows = []
    totals = {
        "files": 0,
        "loc": 0,
        "isrs": 0,
        "assertions": 0,
        "ic_vio": 0,
        "ic_time": 0.0,
        "nic_vio": 0,
        "nic_time": 0.0,
        "uni_vio": 0,
        "uni_time": 0.0,
    }
    for pkg_name, progs in PACKAGES:
        data = sum_package(progs, icbmc, nichecker, unicseq_time)
        rows.append((pkg_name, data))
        for key in totals:
            totals[key] += data[key]

    write_tex(OUTPUT_TEX, rows, totals)
    print("[INFO] wrote %s" % OUTPUT_TEX)
    for pkg_name, data in rows:
        mark = ""
        if data["ic_vio"] != data["uni_vio"]:
            mark = "  ** iCBMC != UNI-CSeq"
        print(
            "  %s: iCBMC=%d  NIChecker=%d  UNI-CSeq=%d%s"
            % (pkg_name, data["ic_vio"], data["nic_vio"], data["uni_vio"], mark)
        )
    print(
        "Assertions total=%d (expect 78); iCBMC Vio=%d Time=%.1f; "
        "NIChecker Vio=%d Time=%.1f; UNI-CSeq Vio=%d Time=%.1f"
        % (
            totals["assertions"],
            totals["ic_vio"],
            totals["ic_time"],
            totals["nic_vio"],
            totals["nic_time"],
            totals["uni_vio"],
            totals["uni_time"],
        )
    )


if __name__ == "__main__":
    main()
