#!/bin/bash
# 用法:
#   ./run_scripts/run_masking_ablation_all.sh
#   ./run_scripts/run_masking_ablation_all.sh 900
#   ./run_scripts/run_masking_ablation_all.sh 900 --until split
#   ./run_scripts/run_masking_ablation_all.sh --from table --until table
#
# 功能:
#   中断屏蔽消融：完整 Racebench 2.1（31 个程序）。
#     racebench2.1            默认编码
#     racebench2.1_nomasking  --ignore-masking
#   阶段: clean -> split -> run_ignore -> run_mask -> table
#   split 按实验三口径生成 *_assertN.c（期望 53 个单断言）。
#   检测用 unicseq.py --mode cbmc-cpachecker（实验三 parallel portfolio）：
#     run_ignore  nomasking + --ignore-masking -> output_cbmc_all_ignore_masking.log
#     run_mask    racebench2.1，不加该参数     -> output_cbmc_all.log
#   unwind=3，RespCount=2，CBMC 与 CPAchecker 均 --loopAbs。
#   表格 31 行，按程序汇总 Violations/Proofs/FP/Unknown；时间对同名程序全部断言求和。
#   另写 masking_ablation_differing_cases.tex（仅 FP 非 0 的程序）。

usage() {
    cat <<'EOF'
Usage: ./run_scripts/run_masking_ablation_all.sh [timelimit] [--from STAGE] [--until STAGE]

Stages (in order): clean, split, run_ignore, run_mask, table
  --from STAGE    start from this stage (default: clean)
  --until STAGE   stop after this stage (default: table)
  timelimit       seconds for unicseq (default: 900)

run_ignore  scans racebench2.1_nomasking with --ignore-masking
run_mask    scans racebench2.1 without --ignore-masking
table       scores Violations/Proofs/FP/Unknown from GT_rachench21.csv;
            writes masking_ablation_all_table.tex and
            masking_ablation_differing_cases.tex

Examples:
  ./run_scripts/run_masking_ablation_all.sh
  ./run_scripts/run_masking_ablation_all.sh 900
  ./run_scripts/run_masking_ablation_all.sh 900 --until split
  ./run_scripts/run_masking_ablation_all.sh --from table --until table
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
SUBSET_MASK="$MASKING_DIR/racebench2.1"
SUBSET_NOMASK="$MASKING_DIR/racebench2.1_nomasking"
GROUND_CSV="$MASKING_DIR/GT_rachench21.csv"
LOG_IGNORE="$MASKING_DIR/output_cbmc_all_ignore_masking.log"
LOG_MASK="$MASKING_DIR/output_cbmc_all.log"
TABLE_TEX="$MASKING_DIR/masking_ablation_all_table.tex"
TABLE_DIFF_TEX="$MASKING_DIR/masking_ablation_differing_cases.tex"

MODE="cbmc-cpachecker"
UNWIND="3"
RESPCOUNT="2"
EXPECTED_ASSERT="53"

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

echo -e "\033[1;33m===== UNI-CSeq masking ablation runner (full racebench2.1) =====\033[0m"
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
    rm -f "$LOG_IGNORE" "$LOG_MASK" "$TABLE_TEX" "$TABLE_DIFF_TEX"
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
# table (Python 3; 31 programs, Violations/Proofs/FP/Unknown from GT_rachench21.csv)
# ---------------------------------------------------------------------------
stage_table() {
    echo -e "\033[1;32m===== [table] generating full racebench2.1 masking ablation table =====\033[0m"
    if [[ ! -f "$GROUND_CSV" ]]; then
        echo "error: missing $GROUND_CSV"
        exit 1
    fi
    python3 - "$SUBSET_MASK" "$GROUND_CSV" "$LOG_IGNORE" "$LOG_MASK" "$TABLE_TEX" "$TABLE_DIFF_TEX" <<'PY'
import csv
import os
import re
import sys
from collections import defaultdict

subset_mask, ground_csv, log_ignore, log_mask, out_tex, out_diff = sys.argv[1:]

ANSI_RE = re.compile(r"\x1b\[[0-9;]*m")
ISR_RE = re.compile(r"\bvoid\s+\w*_isr_\d+\s*\(")
FILE_RE = re.compile(r"UnicSeq Checking(?:\s+\([^)]+\))?\s*:\s+([^\s=]+)")
RES_RE = re.compile(r"Final verification results:\s*([A-Z]+)")
TIME_RE = re.compile(r"Total running time:\s*([0-9.]+)")
INCONCLUSIVE = ("TIMEOUT", "UNKNOWN", "ERROR", "")
LOC_MAP = {
    "svp_simple_001": 65,
    "svp_simple_002": 46,
    "svp_simple_003": 74,
    "svp_simple_004": 69,
    "svp_simple_005": 47,
    "svp_simple_006": 54,
    "svp_simple_007": 51,
    "svp_simple_008": 53,
    "svp_simple_009": 48,
    "svp_simple_010": 54,
    "svp_simple_011": 44,
    "svp_simple_012": 35,
    "svp_simple_013": 67,
    "svp_simple_014": 60,
    "svp_simple_015": 41,
    "svp_simple_016": 34,
    "svp_simple_017": 42,
    "svp_simple_018": 65,
    "svp_simple_019": 72,
    "svp_simple_020": 55,
    "svp_simple_021": 81,
    "svp_simple_022": 67,
    "svp_simple_023": 40,
    "svp_simple_024": 65,
    "svp_simple_025": 39,
    "svp_simple_026": 44,
    "svp_simple_027": 49,
    "svp_simple_028": 54,
    "svp_simple_029": 95,
    "svp_simple_030": 57,
    "svp_simple_031": 92,
}


def strip_ansi(text):
    return ANSI_RE.sub("", text)


def latex_escape(text):
    return text.replace("_", r"\_")


def count_isrs(root, name):
    src = os.path.join(root, name, name + ".c")
    if not os.path.isfile(src):
        return 0
    with open(src, "r", encoding="utf-8", errors="ignore") as f:
        return len(ISR_RE.findall(f.read()))


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
    """TRUE/FALSE vs GT only. Inconclusive verdicts are Unknown, never TP/FP/TN/FN."""
    r = (result or "").upper()
    g = (gt or "").upper()
    if r in INCONCLUSIVE or g not in ("TRUE", "FALSE"):
        return "unk"
    if g == "FALSE" and r == "FALSE":
        return "tp"
    if g == "TRUE" and r == "FALSE":
        return "fp"
    if g == "TRUE" and r == "TRUE":
        return "tn"
    if g == "FALSE" and r == "TRUE":
        return "fn"
    return "unk"


def fmt_time(t, have):
    if not have:
        return "--"
    return "%.1f" % t


def empty_stat():
    return {
        "tp": 0, "fp": 0, "tn": 0, "fn": 0, "unk": 0,
        "time": 0.0, "have_time": False, "asserts": 0,
    }


def add_stat(dst, src):
    for key in ("tp", "fp", "tn", "fn", "unk"):
        dst[key] += src[key]
    dst["time"] += src["time"]
    dst["have_time"] = dst["have_time"] or src["have_time"]
    dst["asserts"] += src["asserts"]


gt_map = parse_ground(ground_csv)
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
            print("[WARN] no %s verdict for %s (counted as Unknown)" % (label, fn), file=sys.stderr)
            st["unk"] += 1
            continue
        result, used_time = logmap[fn]
        st["time"] += used_time
        st["have_time"] = True
        cls = classify(gt, result)
        st[cls] += 1
        if cls == "unk":
            print("[WARN] %s %s verdict=%s (counted as Unknown)" % (label, fn, result), file=sys.stderr)


def row_cells_all(st):
    return (
        st["tp"], st["tn"], st["fp"], st["unk"],
        fmt_time(st["time"], st["have_time"]),
    )


def row_cells_diff(st):
    return (
        st["tp"], st["tn"], st["fp"],
        fmt_time(st["time"], st["have_time"]),
    )


rows = []
diff_rows = []
tot_loc = tot_isr = tot_ass = 0
tot_ign = empty_stat()
tot_msk = empty_stat()

for name in programs:
    n_loc = LOC_MAP.get(name, 0)
    if name not in LOC_MAP:
        print("[WARN] no hardcoded LOC for %s" % name, file=sys.stderr)
    n_isr = count_isrs(subset_mask, name)
    n_ass = ign_stats[name]["asserts"] or msk_stats[name]["asserts"]
    ic = row_cells_all(ign_stats[name])
    mc = row_cells_all(msk_stats[name])
    rows.append((latex_escape(name), n_loc, n_isr, n_ass) + ic + mc)
    tot_loc += n_loc
    tot_isr += n_isr
    tot_ass += n_ass
    add_stat(tot_ign, ign_stats[name])
    add_stat(tot_msk, msk_stats[name])
    if ign_stats[name]["fp"] or msk_stats[name]["fp"]:
        diff_rows.append(
            (latex_escape(name), n_loc, n_isr, n_ass)
            + row_cells_diff(ign_stats[name])
            + row_cells_diff(msk_stats[name])
        )

tot_ign_t = fmt_time(tot_ign["time"], tot_ign["have_time"])
tot_msk_t = fmt_time(tot_msk["time"], tot_msk["have_time"])

with open(out_tex, "w") as f:
    f.write(r"""\begin{table*}[ht]
\centering
\caption{Ablation of interrupt-masking encoding on the complete Racebench~2.1 suite (31 programs). UNI-CSeq runs CBMC and CPAchecker in parallel.}
\label{tab:masking_ablation_all}
\setlength{\tabcolsep}{8pt}
\resizebox{\textwidth}{!}{
\begin{tabular}{l
      S[table-format=4.0]
      S[table-format=2.0]
      S[table-format=2.0]
      S[table-format=2.0]
      S[table-format=2.0]
      S[table-format=2.0]
      S[table-format=2.0]
      S[table-format=4.1]
      S[table-format=2.0]
      S[table-format=2.0]
      S[table-format=2.0]
      S[table-format=2.0]
      S[table-format=4.1]
      }
""")
    f.write(r"""        \toprule[1pt]
      \multicolumn{1}{l}{\multirow{2}{*}{Name}} & \multicolumn{1}{c}{\multirow{2}{*}{LOC}} & \multicolumn{1}{c}{\multirow{2}{*}{ISRs}} & \multicolumn{1}{c}{\multirow{2}{*}{Assertions}} &\multicolumn{5}{c}{\multirow{1}{*}{UNI-CSeq (ignore masking)}} &\multicolumn{5}{c}{\multirow{1}{*}{UNI-CSeq}}\\ \cmidrule(lr){5-9} \cmidrule(lr){10-14}
    
       && & & \multicolumn{1}{c}{Violations} & \multicolumn{1}{c}{Proofs} & \multicolumn{1}{c}{FP} & \multicolumn{1}{c}{Unknown} & \multicolumn{1}{c}{Time (s)} & \multicolumn{1}{c}{Violations} & \multicolumn{1}{c}{Proofs} & \multicolumn{1}{c}{FP} & \multicolumn{1}{c}{Unknown} & \multicolumn{1}{c}{Time (s)}\\ \midrule
""")
    for row in rows:
        f.write("{} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {}\\\\\n".format(*row))
    f.write(r"""\midrule
""")
    f.write("Total & {} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {}\\\\\n".format(
        tot_loc, tot_isr, tot_ass,
        tot_ign["tp"], tot_ign["tn"], tot_ign["fp"], tot_ign["unk"], tot_ign_t,
        tot_msk["tp"], tot_msk["tn"], tot_msk["fp"], tot_msk["unk"], tot_msk_t,
    ))
    f.write(r"""        \bottomrule[1pt]
\end{tabular}
}
\end{table*}
""")

print("[INFO] wrote %s" % out_tex)

diff_tot_loc = diff_tot_isr = diff_tot_ass = 0
diff_tot_ign = empty_stat()
diff_tot_msk = empty_stat()
for name in programs:
    if not (ign_stats[name]["fp"] or msk_stats[name]["fp"]):
        continue
    diff_tot_loc += LOC_MAP.get(name, 0)
    diff_tot_isr += count_isrs(subset_mask, name)
    diff_tot_ass += ign_stats[name]["asserts"] or msk_stats[name]["asserts"]
    add_stat(diff_tot_ign, ign_stats[name])
    add_stat(diff_tot_msk, msk_stats[name])

diff_ign_t = fmt_time(diff_tot_ign["time"], diff_tot_ign["have_time"])
diff_msk_t = fmt_time(diff_tot_msk["time"], diff_tot_msk["have_time"])

with open(out_diff, "w") as f:
    f.write(r"""\begin{table*}[ht]
\centering
\caption{Differing cases in the interrupt-masking ablation on \texttt{racebench~2.1}. UNI-CSeq was run on all 31 programs; the table reports only the two programs whose results differ when interrupt masking is ignored. Complete per-program results are provided in the artifact.}
\label{tab:masking_ablation_diff}
\setlength{\tabcolsep}{8pt}
\resizebox{0.95\textwidth}{!}{
\begin{tabular}{l
      S[table-format=2.0]
      S[table-format=1.0]
      S[table-format=1.0]
      S[table-format=1.0]
      S[table-format=1.0]
      S[table-format=1.0]
      S[table-format=2.1]
      S[table-format=1.0]
      S[table-format=1.0]
      S[table-format=1.0]
      S[table-format=2.1]
      }
        \toprule[1pt]
      \multicolumn{1}{l}{\multirow{2}{*}{Name}} &\multicolumn{1}{c}{\multirow{2}{*}{LOC}} & \multicolumn{1}{c}{\multirow{2}{*}{ISRs}} & \multicolumn{1}{c}{\multirow{2}{*}{Assertions}} &\multicolumn{4}{c}{\multirow{1}{*}{UNI-CSeq (ignore masking)}} &\multicolumn{4}{c}{\multirow{1}{*}{UNI-CSeq}}\\ \cmidrule(lr){5-8} \cmidrule(lr){9-12}
    
       && & & \multicolumn{1}{c}{Violations} & \multicolumn{1}{c}{Proofs} & \multicolumn{1}{c}{FP} & \multicolumn{1}{c}{Time (s)} & \multicolumn{1}{c}{Violations} & \multicolumn{1}{c}{Proofs} & \multicolumn{1}{c}{FP} & \multicolumn{1}{c}{Time (s)}\\ \midrule
""")
    for row in diff_rows:
        f.write("{} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {}\\\\\n".format(*row))
    f.write(r"""\midrule
""")
    f.write("Total & {} & {} & {} & {} & {} & {} & {} & {} & {} & {} & {}\\\\\n".format(
        diff_tot_loc, diff_tot_isr, diff_tot_ass,
        diff_tot_ign["tp"], diff_tot_ign["tn"], diff_tot_ign["fp"], diff_ign_t,
        diff_tot_msk["tp"], diff_tot_msk["tn"], diff_tot_msk["fp"], diff_msk_t,
    ))
    f.write(r"""        \bottomrule[1pt]
\end{tabular}
}
\end{table*}
""")

print("[INFO] wrote %s (%d differing programs)" % (out_diff, len(diff_rows)))
print("[INFO] programs=%d assertions=%d" % (len(programs), tot_ass))
PY
    echo -e "\033[1;32m===== [table] done =====\033[0m"
    echo "  $TABLE_TEX"
    echo "  $TABLE_DIFF_TEX"
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

echo -e "\033[1;33m===== masking ablation (full racebench2.1) finished (until=$UNTIL_STAGE) =====\033[0m"
