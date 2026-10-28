#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
CDF of verification time for Experiment 3 main-table tools:
  CBMC, CPAchecker, Parallel Portfolio.

Reads the same logs as score_table_all_correctness.py.
Prefers WALLTIME when present; otherwise uses the tool-reported time.
"""

import os
import re

import matplotlib.pyplot as plt
import numpy as np

TIME_LIMIT = 900.0

CUR_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(CUR_DIR, "..", ".."))

BASE = os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split")
BASE_CC = os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split_unicseq_CC")
OUTPUT_PNG = os.path.join(CUR_DIR, "exp3_runtime_cdf.png")

LOG_FILE_MAP = {
    "CBMC": [
        os.path.join(BASE, "results_cbmc.log"),
        os.path.join(BASE, "results_goblint-regression_cbmc.log"),
    ],
    "CPAchecker": [
        os.path.join(BASE, "results_cpachecker.log"),
        os.path.join(BASE, "results_goblint-regression_cpachecker.log"),
    ],
    "Parallel Portfolio": [
        os.path.join(BASE_CC, "results_unicseq_cbmc-cpachecker.log"),
        os.path.join(BASE_CC, "results_unicseq_goblint-regression_cbmc-cpachecker.log"),
    ],
}

ANSI_ESCAPE = re.compile(r"\x1b\[[0-9;]*m")
RESULT_LINE_RE = re.compile(
    r"([^,]+),\s*(TRUE|FALSE|UNKNOWN|TIMEOUT|ERROR),\s*([-.\d]+)"
)
UNICSEQ_FILE_RE = re.compile(
    r"UnicSeq Checking(?:\s+\([^)]+\))?\s*:\s+([^\s=]+)"
)
TOTAL_TIME_RE = re.compile(r"Total running time:\s*([0-9.]+)")
WALLTIME_RE = re.compile(r"WALLTIME\s+([0-9.]+)")


def clean_ansi(s):
    return ANSI_ESCAPE.sub("", s)


def sanitize_time(t):
    if t is None:
        return None
    try:
        t = float(t)
    except (TypeError, ValueError):
        return None
    if t < 0:
        return None
    return t


def parse_walltime(line):
    m = WALLTIME_RE.search(clean_ansi(line))
    if m:
        return sanitize_time(m.group(1))
    return None


def peek_walltime(lines, start, stop_markers):
    j = start
    while j < len(lines):
        cl = clean_ansi(lines[j])
        if any(m in cl for m in stop_markers):
            break
        wall = parse_walltime(cl)
        if wall is not None:
            return wall
        j += 1
    return None


def normalize_runtime(t):
    try:
        t = float(t)
    except (TypeError, ValueError):
        return np.nan
    if np.isnan(t) or t <= 0:
        return np.nan
    if t >= TIME_LIMIT:
        return TIME_LIMIT
    return t


def parse_simple_log(logfile):
    """CBMC / CPAchecker: path, RESULT, time. Prefer WALLTIME in the same case."""
    rows = []
    if not os.path.exists(logfile):
        print("[WARNING] File not found: %s" % logfile)
        return rows

    with open(logfile, "r", encoding="utf-8", errors="ignore") as f:
        lines = f.readlines()

    for i, line in enumerate(lines):
        text = clean_ansi(line)
        m = RESULT_LINE_RE.search(text)
        if not m:
            continue
        used_time = sanitize_time(m.group(3))
        wall = peek_walltime(
            lines, i + 1, ("Analysis result:", "========== Checking:")
        )
        if wall is not None:
            used_time = wall
        rows.append({"time": used_time})
    return rows


def parse_unicseq_log(logfile):
    """Portfolio: Total running time, overridden by WALLTIME if present."""
    rows = []
    if not os.path.exists(logfile):
        print("[WARNING] File not found: %s" % logfile)
        return rows

    with open(logfile, "r", encoding="utf-8", errors="ignore") as f:
        lines = f.readlines()

    current_file = None
    used_time = None
    saw_wall = False
    for line in lines:
        text = clean_ansi(line)
        mfile = UNICSEQ_FILE_RE.search(text)
        if mfile:
            if current_file is not None:
                rows.append({"time": used_time})
            current_file = mfile.group(1).strip()
            used_time = None
            saw_wall = False
            continue

        if current_file is None:
            continue

        mtime = TOTAL_TIME_RE.search(text)
        if mtime and not saw_wall:
            used_time = sanitize_time(mtime.group(1))

        wall = parse_walltime(text)
        if wall is not None:
            used_time = wall
            saw_wall = True

    if current_file is not None:
        rows.append({"time": used_time})
    return rows


def load_tool_times():
    times_by_label = {}
    for label, logfiles in LOG_FILE_MAP.items():
        rows = []
        for logfile in logfiles:
            if label == "Parallel Portfolio":
                part = parse_unicseq_log(logfile)
            else:
                part = parse_simple_log(logfile)
            rows.extend(part)
        print("[INFO] %s: %d cases from logs" % (label, len(rows)))
        times_by_label[label] = [normalize_runtime(row["time"]) for row in rows]
    return times_by_label


times_by_label = load_tool_times()

line_styles = {
    "CBMC": {
        "color": "C0",
        "marker": "^",
        "markerfacecolor": "none",
        "markeredgecolor": "C0",
        "label": "CBMC",
    },
    "CPAchecker": {
        "color": "C1",
        "marker": "*",
        "markerfacecolor": "C1",
        "markeredgecolor": "C1",
        "label": "CPAchecker",
    },
    "Parallel Portfolio": {
        "color": "C2",
        "marker": "o",
        "markerfacecolor": "none",
        "markeredgecolor": "C2",
        "label": "Parallel Portfolio",
    },
}

fig, ax = plt.subplots(figsize=(8, 4))
for label in line_styles:
    raw = np.asarray(times_by_label.get(label, []), dtype=float)
    x = np.sort(raw[~np.isnan(raw)])
    if len(x) == 0:
        print("[WARNING] no valid times for %s" % label)
        continue
    y = np.arange(1, len(x) + 1) / len(x)
    style = line_styles[label]
    ax.plot(
        x, y,
        color=style["color"],
        label=style["label"],
        marker=style["marker"],
        markevery=0.08,
        markersize=5,
        markerfacecolor=style.get("markerfacecolor", style["color"]),
        markeredgecolor=style.get("markeredgecolor", style["color"]),
        linewidth=1.3,
    )
    print("[INFO] %s: %d points in CDF" % (label, len(x)))

ax.set_xscale("log")
ax.axvline(
    TIME_LIMIT,
    color="0.4",
    linestyle="--",
    linewidth=1.1,
    label="Timeout = 900s",
)
ax.set_xlabel("Verification Time (s, log scale)")
ax.set_ylabel("Cumulative Ratio")
ax.legend(loc="lower right", bbox_to_anchor=(0.92, 0.02))

plt.tight_layout()
plt.savefig(OUTPUT_PNG, dpi=300)
print("Wrote %s" % OUTPUT_PNG)
