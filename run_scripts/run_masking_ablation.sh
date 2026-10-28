#!/bin/bash
# 用法:
#   ./run_scripts/run_masking_ablation.sh
#   ./run_scripts/run_masking_ablation.sh 900
#   ./run_scripts/run_masking_ablation.sh 900 --until split
#   ./run_scripts/run_masking_ablation.sh --from table --until table
#
# 功能:
#   中断屏蔽消融：marking_sensitive_subset（默认编码）与
#   marking_sensitive_subset_nomasking（--ignore-masking）。
#   阶段: clean -> split -> run_ignore -> run_mask -> table
#   split 按实验三口径生成 *_assertN.c。
#   检测用 unicseq.py --mode cbmc-cpachecker（实验三 parallel portfolio）：
#     run_ignore  nomasking + --ignore-masking -> output_cbmc_ignore_masking.log
#     run_mask    subset，不加该参数           -> output_cbmc.log
#   unwind=3，RespCount=2，CBMC 与 CPAchecker 均 --loopAbs。
#   表格按程序汇总 TP/FP/TN/FN，时间对同名程序全部断言求和。

usage() {
    cat <<'EOF'
Usage: ./run_scripts/run_masking_ablation.sh [timelimit] [--from STAGE] [--until STAGE]

Stages (in order): clean, split, run_ignore, run_mask, table
  --from STAGE    start from this stage (default: clean)
  --until STAGE   stop after this stage (default: table)
  timelimit       seconds for unicseq (default: 900)

run_ignore  scans marking_sensitive_subset_nomasking with --ignore-masking
run_mask    scans marking_sensitive_subset without --ignore-masking
table       scores TP/FP/TN/FN from ground_th.csv; writes masking_ablation_table.tex

Examples:
  ./run_scripts/run_masking_ablation.sh
  ./run_scripts/run_masking_ablation.sh 900
  ./run_scripts/run_masking_ablation.sh 900 --until split
  ./run_scripts/run_masking_ablation.sh --from table --until table
EOF
}

ORIG_ARGS="$*"
TIMELIMIT="900"
FROM_STAGE="clean"
UNTIL_STAGE="table"

while [[ $# -gt 0 ]]; do
    case "$1" in
        --from)
            if [[ $# -lt 2 ]]; then
                echo "error: --from requires a stage"
                usage
                exit 1
            fi
            FROM_STAGE="$2"
            shift 2
            ;;
        --from=*)
            FROM_STAGE="${1#*=}"
            shift
            ;;
        --until)
            if [[ $# -lt 2 ]]; then
                echo "error: --until requires a stage"
                usage
                exit 1
            fi
            UNTIL_STAGE="$2"
            shift 2
            ;;
        --until=*)
            UNTIL_STAGE="${1#*=}"
            shift
            ;;
        --help|-h)
            usage
            exit 0
            ;;
        ''|*[!0-9]*)
            echo "error: unknown argument: $1"
            usage
            exit 1
            ;;
        *)
            TIMELIMIT="$1"
            shift
            ;;
    esac
done

stage_rank() {
    case "$1" in
        clean) echo 0 ;;
        split) echo 1 ;;
        run_ignore) echo 2 ;;
        run_mask) echo 3 ;;
        table) echo 4 ;;
        *) echo -1 ;;
    esac
}

FROM_RANK="$(stage_rank "$FROM_STAGE")"
UNTIL_RANK="$(stage_rank "$UNTIL_STAGE")"
if [[ "$FROM_RANK" -lt 0 ]]; then
    echo "error: invalid --from stage: $FROM_STAGE"
    usage
    exit 1
fi
if [[ "$UNTIL_RANK" -lt 0 ]]; then
    echo "error: invalid --until stage: $UNTIL_STAGE"
    usage
    exit 1
fi
if [[ "$FROM_RANK" -gt "$UNTIL_RANK" ]]; then
    echo "error: --from $FROM_STAGE is after --until $UNTIL_STAGE"
    exit 1
fi

should_run_stage() {
    local rank
    rank="$(stage_rank "$1")"
    [[ "$rank" -ge "$FROM_RANK" && "$rank" -le "$UNTIL_RANK" ]]
}

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."
UNICSEQ="$PROJECT_ROOT/unicseq.py"
SPLIT_DIR="$PROJECT_ROOT/Experiments/ComExp_Split"
MASKING_DIR="$PROJECT_ROOT/Experiments/Masking_Isolation"
SUBSET_MASK="$MASKING_DIR/marking_sensitive_subset"
SUBSET_NOMASK="$MASKING_DIR/marking_sensitive_subset_nomasking"
INFO_TXT="$MASKING_DIR/info.txt"
GROUND_CSV="$MASKING_DIR/ground_th.csv"
LOG_IGNORE="$MASKING_DIR/output_cbmc_ignore_masking.log"
LOG_MASK="$MASKING_DIR/output_cbmc.log"
TABLE_TEX="$MASKING_DIR/masking_ablation_table.tex"

MODE="cbmc-cpachecker"
UNWIND="3"
RESPCOUNT="2"
EXPECTED_ASSERT="21"

list_programs() {
    local root="$1"
    local d base
    if [[ ! -d "$root" ]]; then
        return
    fi
    for d in "$root"/*/; do
        [[ -d "$d" ]] || continue
        base="$(basename "$d")"
        if [[ -f "$d${base}.c" ]]; then
            echo "$base"
        fi
    done | sort
}

START_TIME="$(date "+%Y年%-m月%-d日%H:%M")"
CMD_LINE="$0 $ORIG_ARGS"

echo -e "\033[1;33m===== UNI-CSeq masking ablation runner =====\033[0m"
echo "project: $PROJECT_ROOT"
echo "mask:    $SUBSET_MASK"
echo "nomask:  $SUBSET_NOMASK"
echo "mode:    $MODE unwind=$UNWIND RespCount=$RESPCOUNT timelimit=$TIMELIMIT --loopAbs"
echo "stages:  $FROM_STAGE .. $UNTIL_STAGE"
echo ""

if [[ ! -f "$UNICSEQ" ]]; then
    echo "error: missing $UNICSEQ"
    exit 1
fi
if [[ ! -d "$SUBSET_MASK" ]]; then
    echo "error: missing $SUBSET_MASK"
    exit 1
fi
if [[ ! -d "$SUBSET_NOMASK" ]]; then
    echo "error: missing $SUBSET_NOMASK"
    exit 1
fi
if [[ ! -f "$INFO_TXT" ]]; then
    echo "error: missing $INFO_TXT"
    exit 1
fi

# ---------------------------------------------------------------------------
# clean
# ---------------------------------------------------------------------------
stage_clean() {
    echo -e "\033[1;32m===== [clean] removing split files and sequentialization artifacts =====\033[0m"
    local sub
    for sub in "$SUBSET_MASK" "$SUBSET_NOMASK"; do
        if [[ -d "$sub" ]]; then
            echo "cleaning $sub"
            find "$sub" -type f \( -name '*_assert*.c' -o -name '_cseq_*' -o -name '*.c.cbmc.log' \) -delete
        fi
    done
    rm -f "$LOG_IGNORE" "$LOG_MASK" "$TABLE_TEX"
    echo -e "\033[1;32m===== [clean] done =====\033[0m"
    echo ""
}

# ---------------------------------------------------------------------------
# split
# ---------------------------------------------------------------------------
stage_split() {
    echo -e "\033[1;32m===== [split] generating *_assertN.c =====\033[0m"
    if [[ ! -f "$SPLIT_DIR/split_asserts.py" ]]; then
        echo "error: missing $SPLIT_DIR/split_asserts.py"
        exit 1
    fi
    python3 - "$SUBSET_MASK" "$SUBSET_NOMASK" "$SPLIT_DIR" "$EXPECTED_ASSERT" <<'PY'
import os
import sys
import builtins

subset_mask, subset_nomask, split_dir, expected_s = sys.argv[1:]
expected = int(expected_s)

_real_open = builtins.open

def _open_utf8(file, mode="r", *args, **kwargs):
    if "b" not in mode and kwargs.get("encoding") is None:
        kwargs["encoding"] = "utf-8"
        kwargs.setdefault("errors", "ignore")
    return _real_open(file, mode, *args, **kwargs)

builtins.open = _open_utf8
sys.path.insert(0, split_dir)
from split_asserts import split_one_cfile, should_split_cfile


def count_assert_files(root):
    n = 0
    for dirpath, _dirnames, filenames in os.walk(root):
        for fn in filenames:
            if "_assert" in fn and fn.endswith(".c") and not fn.startswith("_cseq_"):
                n += 1
    return n


def split_tree(root):
    total = 0
    for name in sorted(os.listdir(root)):
        case = os.path.join(root, name)
        if not os.path.isdir(case):
            continue
        for fn in os.listdir(case):
            if not should_split_cfile(fn):
                continue
            path = os.path.join(case, fn)
            n = split_one_cfile(path)
            total += n
            print("%s: split %d asserts" % (path, n))
    return total


ok = True
for root in (subset_mask, subset_nomask):
    print("purging old *_assert*.c under %s" % root)
    for dirpath, _dirnames, filenames in os.walk(root):
        for fn in filenames:
            if "_assert" in fn and fn.endswith(".c") and not fn.startswith("_cseq_"):
                os.remove(os.path.join(dirpath, fn))
    n = split_tree(root)
    got = count_assert_files(root)
    print("%s: generated %d, found %d (expected %d)" % (root, n, got, expected))
    if got != expected:
        ok = False
if not ok:
    sys.exit(1)
PY
    echo -e "\033[1;32m===== [split] done =====\033[0m"
    echo ""
}

# ---------------------------------------------------------------------------
# run helpers
# ---------------------------------------------------------------------------
run_one_config() {
    local ignore_flag="$1"
    local root="$2"
    local name src_c basesrc extra found_any

    extra=""
    if [[ "$ignore_flag" == "1" ]]; then
        extra="--ignore-masking"
        echo -e "\033[1;36m===== UnicSeq $MODE --ignore-masking (unwind=$UNWIND --loopAbs) =====\033[0m"
        echo "suite: $root"
    else
        echo -e "\033[1;36m===== UnicSeq $MODE default masking encoding (unwind=$UNWIND --loopAbs) =====\033[0m"
        echo "suite: $root"
    fi

    shopt -s nullglob
    for name in $(list_programs "$root"); do
        found_any=0
        for src_c in "$root/$name"/*_assert*.c; do
            basesrc="$(basename "$src_c")"
            if [[ "$basesrc" == _cseq_* ]]; then
                continue
            fi
            found_any=1
            echo -e "\033[1;35m========== UnicSeq Checking ($MODE): $src_c ==========\033[0m"
            python3 "$UNICSEQ" --input "$src_c" --cbmc-unwinding "$UNWIND" \
                --timelimit "$TIMELIMIT" --mode "$MODE" --RespCount "$RESPCOUNT" \
                --loopAbs $extra
            echo
        done
        if [[ "$found_any" -eq 0 ]]; then
            echo "No _assertN.c files found in $root/$name, skipping."
        fi
    done
    shopt -u nullglob
}

with_logfile() {
    local logfile="$1"
    local header="$2"
    shift 2

    {
        echo "$header"
        echo "========================================"
    } > "$logfile"

    exec {FD_STDOUT}>&1
    exec > >(tee -a "$logfile") 2>&1
    "$@"
    exec 1>&${FD_STDOUT}
    exec {FD_STDOUT}>&-
}

stage_run_ignore() {
    echo -e "\033[1;32m===== [run_ignore] UnicSeq $MODE with --ignore-masking =====\033[0m"
    with_logfile "$LOG_IGNORE" \
        "$START_TIME, $CMD_LINE, tool=unicseq mode=$MODE unwind=$UNWIND RespCount=$RESPCOUNT --loopAbs --ignore-masking" \
        run_one_config 1 "$SUBSET_NOMASK"
    echo -e "\033[1;32m===== [run_ignore] done =====\033[0m"
    echo "  $LOG_IGNORE"
    echo ""
}

stage_run_mask() {
    echo -e "\033[1;32m===== [run_mask] UnicSeq $MODE (masking encoded) =====\033[0m"
    with_logfile "$LOG_MASK" \
        "$START_TIME, $CMD_LINE, tool=unicseq mode=$MODE unwind=$UNWIND RespCount=$RESPCOUNT --loopAbs" \
        run_one_config 0 "$SUBSET_MASK"
    echo -e "\033[1;32m===== [run_mask] done =====\033[0m"
    echo "  $LOG_MASK"
    echo ""
}

# ---------------------------------------------------------------------------
# table (Python 3; per-program TP/FP/TN/FN from ground_th.csv)
# ---------------------------------------------------------------------------
stage_table() {
    echo -e "\033[1;32m===== [table] generating masking ablation table =====\033[0m"
    if [[ ! -f "$GROUND_CSV" ]]; then
        echo "error: missing $GROUND_CSV"
        exit 1
    fi
    python3 - "$SUBSET_MASK" "$INFO_TXT" "$GROUND_CSV" "$LOG_IGNORE" "$LOG_MASK" "$TABLE_TEX" <<'PY'
import csv
import os
import re
import sys
from collections import defaultdict

subset_mask, info_path, ground_csv, log_ignore, log_mask, out_tex = sys.argv[1:]

ANSI_RE = re.compile(r"\x1b\[[0-9;]*m")
INFO_ROW_RE = re.compile(
    r"^\|\s*(svp_simple_\d+)\s*\|\s*(\d+)\s*\|\s*(\d+)\s*\|\s*([^|]+)\|\s*([^|]+)\|"
)
FILE_RE = re.compile(r"UnicSeq Checking(?:\s+\([^)]+\))?\s*:\s+([^\s=]+)")
RES_RE = re.compile(r"Final verification results:\s*([A-Z]+)")
TIME_RE = re.compile(r"Total running time:\s*([0-9.]+)")


def strip_ansi(text):
    return ANSI_RE.sub("", text)


def latex_escape(text):
    return text.replace("_", r"\_")


def parse_info(path):
    info = {}
    with open(path, "r", encoding="utf-8", errors="ignore") as f:
        for line in f:
            m = INFO_ROW_RE.match(line)
            if not m:
                continue
            info[m.group(1)] = int(m.group(2))
    return info


def parse_ground(path):
    """basename -> (program, TRUE/FALSE)"""
    gt = {}
    with open(path, "r", encoding="utf-8", newline="") as f:
        reader = csv.DictReader(f)
        for row in reader:
            fn = os.path.basename(row["file"].strip())
            gt[fn] = (row["program"].strip(), row["ground_truth"].strip().upper())
    if not gt:
        raise ValueError("no rows in %s" % path)
    return gt


def parse_unicseq_log(log_path):
    """basename -> (verdict, time)"""
    by_base = {}
    if not os.path.isfile(log_path):
        print("[WARN] missing log: %s" % log_path, file=sys.stderr)
        return by_base
    with open(log_path, "r", encoding="utf-8", errors="ignore") as f:
        lines = f.readlines()
    current = None
    for idx, line in enumerate(lines):
        text = strip_ansi(line)
        mfile = FILE_RE.search(text)
        if mfile:
            current = os.path.basename(mfile.group(1).strip())
            continue
        mres = RES_RE.search(text)
        if mres and current:
            result = mres.group(1).strip().upper()
            used_time = 0.0
            for j in range(1, 10):
                if idx + j < len(lines):
                    mtime = TIME_RE.search(strip_ansi(lines[idx + j]))
                    if mtime:
                        used_time = float(mtime.group(1))
                        break
            by_base[current] = (result, used_time)
            current = None
    return by_base


def classify(gt, result):
    r = (result or "").upper()
    g = (gt or "").upper()
    if r in ("TIMEOUT", "UNKNOWN", "ERROR", "") or g not in ("TRUE", "FALSE"):
        return None
    if g == "FALSE" and r == "FALSE":
        return "tp"
    if g == "TRUE" and r == "FALSE":
        return "fp"
    if g == "TRUE" and r == "TRUE":
        return "tn"
    if g == "FALSE" and r == "TRUE":
        return "fn"
    return None


def fmt_time(t, have):
    if not have:
        return "--"
    return "%.1f" % t


def empty_stat():
    return {"tp": 0, "fp": 0, "tn": 0, "fn": 0, "time": 0.0, "have_time": False, "asserts": 0}


gt_map = parse_ground(ground_csv)
isr_map = parse_info(info_path)
ignore_map = parse_unicseq_log(log_ignore)
mask_map = parse_unicseq_log(log_mask)

programs = []
seen = set()
for _fn, (prog, _gt) in sorted(gt_map.items()):
    if prog not in seen:
        seen.add(prog)
        programs.append(prog)

ign_stats = defaultdict(empty_stat)
msk_stats = defaultdict(empty_stat)

for fn, (prog, gt) in gt_map.items():
    for stats, logmap, label in (
        (ign_stats, ignore_map, "ignore-masking"),
        (msk_stats, mask_map, "default-masking"),
    ):
        st = stats[prog]
        st["asserts"] += 1
        if fn not in logmap:
            print("[WARN] no %s verdict for %s" % (label, fn), file=sys.stderr)
            continue
        result, used_time = logmap[fn]
        st["time"] += used_time
        st["have_time"] = True
        cls = classify(gt, result)
        if cls:
            st[cls] += 1
        elif result not in ("TRUE", "FALSE"):
            print("[WARN] %s %s verdict=%s (not counted in TP/FP/TN/FN)" % (label, fn, result), file=sys.stderr)


def row_cells(st):
    return (
        st["tp"], st["fp"], st["tn"], st["fn"],
        fmt_time(st["time"], st["have_time"]),
    )


rows = []
tot_isr = tot_ass = 0
tot_ign = empty_stat()
tot_msk = empty_stat()

for name in programs:
    n_isr = isr_map.get(name, 0)
    n_ass = ign_stats[name]["asserts"] or msk_stats[name]["asserts"]
    ic = row_cells(ign_stats[name])
    mc = row_cells(msk_stats[name])
    rows.append((latex_escape(name), n_isr, n_ass) + ic + mc)
    tot_isr += n_isr
    tot_ass += n_ass
    for key in ("tp", "fp", "tn", "fn"):
        tot_ign[key] += ign_stats[name][key]
        tot_msk[key] += msk_stats[name][key]
    tot_ign["time"] += ign_stats[name]["time"]
    tot_msk["time"] += msk_stats[name]["time"]
    tot_ign["have_time"] = tot_ign["have_time"] or ign_stats[name]["have_time"]
    tot_msk["have_time"] = tot_msk["have_time"] or msk_stats[name]["have_time"]

tot_ign_t = fmt_time(tot_ign["time"], tot_ign["have_time"])
tot_msk_t = fmt_time(tot_msk["time"], tot_msk["have_time"])

with open(out_tex, "w") as f:
    f.write(r"""\begin{table*}[ht]
\centering
\caption{Ablation of interrupt-masking encoding on the Racebench~2.1 masking-sensitive subset. UNI-CSeq runs CBMC and CPAchecker in parallel.}
\label{tab:masking_ablation}
\setlength{\tabcolsep}{8pt}
\resizebox{\textwidth}{!}{
\begin{tabular}{l
      S[table-format=2.0]
      S[table-format=2.0]
      S[table-format=1.0]
      S[table-format=1.0]
      S[table-format=1.0]
      S[table-format=1.0]
      S[table-format=2.1]
      S[table-format=1.0]
      S[table-format=1.0]
      S[table-format=1.0]
      S[table-format=1.0]
      S[table-format=2.1]
      }
""")
    f.write(r"""        \toprule[1pt]
      \multicolumn{1}{l}{\multirow{2}{*}{Name}} & \multicolumn{1}{c}{\multirow{2}{*}{ISRs}} & \multicolumn{1}{c}{\multirow{2}{*}{Assertions}} &\multicolumn{5}{c}{\multirow{1}{*}{UNI-CSeq (ignore masking)}} &\multicolumn{5}{c}{\multirow{1}{*}{UNI-CSeq}}\\ \cmidrule(lr){4-8} \cmidrule(lr){9-13}
    
       & & & \multicolumn{1}{c}{TP} & \multicolumn{1}{c}{FP} & \multicolumn{1}{c}{TN} & \multicolumn{1}{c}{FN} & \multicolumn{1}{c}{Time (s)} & \multicolumn{1}{c}{TP} & \multicolumn{1}{c}{FP} & \multicolumn{1}{c}{TN} & \multicolumn{1}{c}{FN} & \multicolumn{1}{c}{Time (s)}\\ \midrule
""")
    for row in rows:
        f.write("{} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {}\\\\\n".format(*row))
    f.write(r"""\midrule
""")
    f.write("Total & {} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {}\\\\\n".format(
        tot_isr, tot_ass,
        tot_ign["tp"], tot_ign["fp"], tot_ign["tn"], tot_ign["fn"], tot_ign_t,
        tot_msk["tp"], tot_msk["fp"], tot_msk["tn"], tot_msk["fn"], tot_msk_t,
    ))
    f.write(r"""        \bottomrule[1pt]
\end{tabular}
}
\end{table*}
""")

print("[INFO] wrote %s" % out_tex)
PY
    echo -e "\033[1;32m===== [table] done =====\033[0m"
    echo "  $TABLE_TEX"
    echo ""
}

# ---------------------------------------------------------------------------
# main
# ---------------------------------------------------------------------------
if should_run_stage clean; then
    stage_clean
fi
if should_run_stage split; then
    stage_split
fi
if should_run_stage run_ignore; then
    stage_run_ignore
fi
if should_run_stage run_mask; then
    stage_run_mask
fi
if should_run_stage table; then
    stage_table
fi

echo -e "\033[1;33m===== masking ablation runner finished (until=$UNTIL_STAGE) =====\033[0m"
