#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Generate a paper-ready LaTeX table comparing CBMC unwind bounds,
CPAchecker, and the CBMC+CPAchecker portfolio.

Usage:
    python gen_cbmc_u_effec.py
    python gen_cbmc_u_effec.py --csv all_results_with_unicseq.csv
"""

from __future__ import print_function

import argparse
import csv
import os
import sys
from collections import OrderedDict

CUR_DIR = os.path.dirname(os.path.abspath(__file__))
DEFAULT_CSV = os.path.join(CUR_DIR, "all_results_with_unicseq.csv")
DEFAULT_TEX = os.path.join(CUR_DIR, "cbmc_u_effec.tex")

TIME_LIMIT = 900.0
EXPECTED_N = 271

CBMC_UNWINDS = (2, 4, 8, 16, 32)
INCONCLUSIVE = {"UNKNOWN", "TIMEOUT"}

CONFIG_ORDER = (
    ["CBMC-u%d" % u for u in CBMC_UNWINDS]
    + ["CPAchecker", "Portfolio"]
)


def parse_unwind(value):
    if value is None:
        return None
    text = str(value).strip()
    if not text:
        return None
    try:
        return int(float(text))
    except (TypeError, ValueError):
        return None


def parse_time(value):
    if value is None:
        return None
    text = str(value).strip()
    if not text:
        return None
    try:
        t = float(text)
    except (TypeError, ValueError):
        return None
    return t


def config_label(tool, unwind):
    tool = (tool or "").strip()
    if tool == "CBMC":
        u = parse_unwind(unwind)
        if u in CBMC_UNWINDS:
            return "CBMC-u%d" % u
        return None
    if tool == "CPAchecker":
        return "CPAchecker"
    if tool == "UnicSeq":
        return "Portfolio"
    return None


def init_stat():
    return {
        "n": 0,
        "unsafe": 0,
        "unknown": 0,
        "timeout": 0,
        "time": 0.0,
    }


def load_rows(csv_path):
    with open(csv_path, "r", newline="") as f:
        reader = csv.DictReader(f)
        if reader.fieldnames is None:
            raise SystemExit("CSV has no header: %s" % csv_path)
        required = {"tool", "unwind", "result", "time"}
        missing = required - {name.strip() for name in reader.fieldnames}
        if missing:
            raise SystemExit(
                "CSV missing columns %s: %s" % (sorted(missing), csv_path)
            )
        return list(reader)


def aggregate(rows):
    stats = OrderedDict((name, init_stat()) for name in CONFIG_ORDER)
    seen_unicseq = False

    for row in rows:
        label = config_label(row.get("tool"), row.get("unwind"))
        if label is None:
            continue
        if label == "Portfolio":
            seen_unicseq = True

        result = (row.get("result") or "").strip().upper()
        t = parse_time(row.get("time"))
        s = stats[label]
        s["n"] += 1

        if result == "FALSE":
            s["unsafe"] += 1

        inconclusive = result in INCONCLUSIVE
        missing_or_nonpos = t is None or t <= 0

        if inconclusive:
            if missing_or_nonpos or t >= TIME_LIMIT:
                s["timeout"] += 1
                s["time"] += TIME_LIMIT
                if missing_or_nonpos:
                    sys.stderr.write(
                        "Warning: %s has %s with missing/non-positive time; "
                        "counted as Timeout and 900s\n" % (label, result)
                    )
            else:
                s["unknown"] += 1
                s["time"] += t
        else:
            if missing_or_nonpos:
                sys.stderr.write(
                    "Warning: %s has %s with missing/non-positive time; "
                    "time contribution 0\n" % (label, result)
                )
            else:
                s["time"] += t

    if not seen_unicseq or stats["Portfolio"]["n"] == 0:
        raise SystemExit(
            "CSV has no UnicSeq/Portfolio rows. "
            "Run extract_unicseq.py and combine_results.py first."
        )

    for name, s in stats.items():
        if s["n"] != EXPECTED_N:
            sys.stderr.write(
                "Warning: %s has %d rows, expected %d\n"
                % (name, s["n"], EXPECTED_N)
            )

    return stats


def build_latex(stats):
    lines = [
        r"\begin{table}[ht]",
        r"\centering",
        r"\caption{Effectiveness of CBMC with different unwinding bounds, CPAchecker, and the CBMC+CPAchecker portfolio.}",
        r"\label{tab:cbmc_u_effec}",
        r"\setlength{\tabcolsep}{8pt}",
        r"\resizebox{0.65\textwidth}{!}{",
        r"\begin{tabular}{l *{3}{S[table-format=3.0]} S[table-format=6.1]}",
        r"\toprule[1pt]",
        r"{Backend Configuration} & {Unsafe} & {Unknown} & {Timeout} & {Time (s)} \\",
        r"\midrule",
    ]
    for name in CONFIG_ORDER:
        s = stats[name]
        lines.append(
            "%s & %d & %d & %d & %.1f \\\\"
            % (name, s["unsafe"], s["unknown"], s["timeout"], s["time"])
        )
    lines.extend([
        r"\bottomrule[1pt]",
        r"\end{tabular}",
        r"}",
        r"\end{table}",
        "",
    ])
    return "\n".join(lines)


def print_summary(stats):
    print("[SUMMARY]")
    print(
        "%-14s %6s %8s %8s %8s %12s"
        % ("Configuration", "n", "Unsafe", "Unknown", "Timeout", "Time (s)")
    )
    for name in CONFIG_ORDER:
        s = stats[name]
        print(
            "%-14s %6d %8d %8d %8d %12.1f"
            % (name, s["n"], s["unsafe"], s["unknown"], s["timeout"], s["time"])
        )


def parse_args(argv):
    parser = argparse.ArgumentParser(
        description="Generate CBMC unwind effectiveness LaTeX table."
    )
    parser.add_argument(
        "--csv",
        default=DEFAULT_CSV,
        help="Input CSV (default: all_results_with_unicseq.csv)",
    )
    parser.add_argument(
        "--tex",
        default=DEFAULT_TEX,
        help="Output .tex path (default: cbmc_u_effec.tex)",
    )
    return parser.parse_args(argv)


def main(argv=None):
    args = parse_args(argv if argv is not None else sys.argv[1:])
    csv_path = os.path.abspath(args.csv)
    tex_path = os.path.abspath(args.tex)

    if not os.path.isfile(csv_path):
        raise SystemExit("CSV not found: %s" % csv_path)

    stats = aggregate(load_rows(csv_path))
    print_summary(stats)

    latex = build_latex(stats)
    with open(tex_path, "w", newline="\n") as f:
        f.write(latex)
    print("")
    print(latex.rstrip("\n"))
    print("")
    print("Wrote %s" % tex_path)


if __name__ == "__main__":
    main()
