#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Dual-axis trade-off plot for CBMC unwind bounds:
  left:  #Unsafe detected (line)
  right: Total runtime (s, log scale)
  annotations: U/T = unknown/timeout counts.
"""

import csv
import os
import sys

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.lines import Line2D

CUR_DIR = os.path.dirname(os.path.abspath(__file__))
CSV_PATH = os.path.join(CUR_DIR, "all_results.csv")
OUTPUT_PNG = os.path.join(CUR_DIR, "cbmc_trade_off.png")

TIME_LIMIT = 900.0
CBMC_UNWINDS = (2, 4, 8, 16, 32)
INCONCLUSIVE = {"UNKNOWN", "TIMEOUT"}

COLOR_UNSAFE = "C0"
COLOR_RUNTIME = "#E64B35"
COLOR_TIMEOUT = "#3C5488"


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
        return float(text)
    except (TypeError, ValueError):
        return None


def init_stat():
    return {"n": 0, "unsafe": 0, "unknown": 0, "timeout": 0, "time": 0.0}


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


def aggregate_cbmc(rows):
    stats = {u: init_stat() for u in CBMC_UNWINDS}
    for row in rows:
        if (row.get("tool") or "").strip() != "CBMC":
            continue
        u = parse_unwind(row.get("unwind"))
        if u not in stats:
            continue

        result = (row.get("result") or "").strip().upper()
        t = parse_time(row.get("time"))
        s = stats[u]
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
                        "Warning: u%d has %s with missing/non-positive time; "
                        "counted as Timeout and 900s\n" % (u, result)
                    )
            else:
                s["unknown"] += 1
                s["time"] += t
        else:
            if missing_or_nonpos:
                sys.stderr.write(
                    "Warning: u%d has %s with missing/non-positive time; "
                    "time contribution 0\n" % (u, result)
                )
            else:
                s["time"] += t
    return stats


def print_summary(stats):
    print("[SUMMARY]")
    print(
        "%-6s %6s %8s %8s %8s %12s"
        % ("u", "n", "Unsafe", "Unknown", "Timeout", "Time (s)")
    )
    for u in CBMC_UNWINDS:
        s = stats[u]
        print(
            "u%-5d %6d %8d %8d %8d %12.1f"
            % (u, s["n"], s["unsafe"], s["unknown"], s["timeout"], s["time"])
        )


def plot_tradeoff(stats):
    xs = np.arange(len(CBMC_UNWINDS))
    labels = ["u%d" % u for u in CBMC_UNWINDS]
    unsafe = np.array([stats[u]["unsafe"] for u in CBMC_UNWINDS], dtype=float)
    runtime = np.array([stats[u]["time"] for u in CBMC_UNWINDS], dtype=float)
    unknown = np.array([stats[u]["unknown"] for u in CBMC_UNWINDS], dtype=int)
    timeout = np.array([stats[u]["timeout"] for u in CBMC_UNWINDS], dtype=int)

    fig, ax_left = plt.subplots(figsize=(6, 4))
    ax_left.plot(
        xs, unsafe,
        color=COLOR_UNSAFE,
        marker="o",
        markersize=6,
        linewidth=1.6,
        zorder=3,
        label="#Unsafe detected",
    )
    ax_left.set_ylabel("#Unsafe detected", color=COLOR_UNSAFE)
    ax_left.tick_params(axis="y", colors=COLOR_UNSAFE)
    ax_left.set_xlabel("CBMC Configuration")
    ax_left.set_xticks(xs)
    ax_left.set_xticklabels(labels)
    ax_left.set_ylim(138, 155)
    ax_left.spines["top"].set_visible(False)

    ax_right = ax_left.twinx()
    ax_right.plot(
        xs, runtime,
        color=COLOR_RUNTIME,
        marker="s",
        markersize=5.5,
        linewidth=1.6,
        zorder=3,
        label="Total runtime",
    )
    ax_right.set_yscale("log")
    ax_right.set_ylabel("Total runtime (s, log scale)", color=COLOR_RUNTIME)
    ax_right.tick_params(axis="y", colors=COLOR_RUNTIME)
    ax_right.spines["top"].set_visible(False)
    ax_right.spines["right"].set_color(COLOR_RUNTIME)
    ax_left.spines["left"].set_color(COLOR_UNSAFE)

    # Per-point offsets so labels stay inside the axes.
    # u16: slightly left of the marker; u32: lower-left to avoid the right spine.
    annotate_style = {
        16: dict(xytext=(8, 10), ha="left", va="bottom"),
        32: dict(xytext=(-8, -10), ha="right", va="top"),
    }
    for i, u in enumerate(CBMC_UNWINDS):
        u_cnt, t_cnt = unknown[i], timeout[i]
        if u_cnt <= 0 and t_cnt <= 0:
            continue
        style = annotate_style.get(u, dict(xytext=(8, 10), ha="left", va="bottom"))
        ax_left.annotate(
            "U/T = %d/%d" % (u_cnt, t_cnt),
            xy=(xs[i], unsafe[i]),
            xytext=style["xytext"],
            textcoords="offset points",
            fontsize=8,
            color=COLOR_TIMEOUT,
            ha=style["ha"],
            va=style["va"],
        )

    legend_handles = [
        Line2D([0], [0], color=COLOR_UNSAFE, marker="o", linewidth=1.6,
               label="#Unsafe detected"),
        Line2D([0], [0], color=COLOR_RUNTIME, marker="s", linewidth=1.6,
               label="Total runtime"),
    ]
    ax_left.legend(handles=legend_handles, loc="upper left", frameon=True)

    fig.tight_layout()
    fig.savefig(OUTPUT_PNG, dpi=300)
    print("Wrote %s" % OUTPUT_PNG)


def main():
    if not os.path.isfile(CSV_PATH):
        raise SystemExit("CSV not found: %s" % CSV_PATH)
    stats = aggregate_cbmc(load_rows(CSV_PATH))
    print_summary(stats)
    plot_tradeoff(stats)


if __name__ == "__main__":
    main()
