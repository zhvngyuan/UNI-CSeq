#!/bin/bash
# 用法:
#   ./run_scripts/run_third_Experiment.sh
#   ./run_scripts/run_third_Experiment.sh 900
#   ./run_scripts/run_third_Experiment.sh 900 --until split
#   ./run_scripts/run_third_Experiment.sh 900 --until run
#   ./run_scripts/run_third_Experiment.sh --from run --until table
#
# 功能:
#   实验三主表一键复现（不含 Com_test_cbmc_unwind 配图，不含 sequential / ComExp_Split_unicseq_SEQ）。
#   阶段: clean -> split -> run -> table
#   一次覆盖 5 个包；portfolio 仅跑并行 cbmc-cpachecker。日志仍按出表脚本拆成「4 包」与 goblint 两套文件。

usage() {
    cat <<'EOF'
Usage: ./run_scripts/run_third_Experiment.sh [timelimit] [--from STAGE] [--until STAGE]

Stages (in order): clean, split, run, table
  --from STAGE    start from this stage (default: clean)
  --until STAGE   stop after this stage (default: table)
  timelimit       seconds for unichecker/unicseq (default: 900)

Examples:
  ./run_scripts/run_third_Experiment.sh
  ./run_scripts/run_third_Experiment.sh 900 --until split
  ./run_scripts/run_third_Experiment.sh 900 --until run
  ./run_scripts/run_third_Experiment.sh --from run --until table
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
        run) echo 2 ;;
        table) echo 3 ;;
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
UNICHECKER="$PROJECT_ROOT/unichecker.py"
UNICSEQ="$PROJECT_ROOT/unicseq.py"
SPLIT_BASE="$PROJECT_ROOT/Experiments/ComExp_Split"
CC_BASE="$PROJECT_ROOT/Experiments/ComExp_Split_unicseq_CC"
TABLE_DIR="$PROJECT_ROOT/Experiments/genTable_scripts"

PACKAGES_FOUR=("Idv-races" "pthread" "racebench2.1" "rw_benchmark")
PACKAGES_GOBLINT=("goblint-regression")
TREES=("$SPLIT_BASE" "$CC_BASE")

EXPECTED_IDV=20
EXPECTED_PTHREAD=10
EXPECTED_RACE=53
EXPECTED_RW=78
EXPECTED_GOBLINT=110

START_TIME="$(date "+%Y年%-m月%-d日%H:%M")"
CMD_LINE="$0 $ORIG_ARGS"

echo -e "\033[1;33m===== UNI-CSeq Experiment 3 runner =====\033[0m"
echo "project: $PROJECT_ROOT"
echo "timelimit: $TIMELIMIT"
echo "from: $FROM_STAGE  until: $UNTIL_STAGE"
echo ""

# ---------------------------------------------------------------------------
# clean
# ---------------------------------------------------------------------------
stage_clean() {
    echo -e "\033[1;32m===== [clean] removing old split files and run artifacts =====\033[0m"
    local tree
    for tree in "${TREES[@]}"; do
        if [[ ! -x "$tree/clean.sh" && ! -f "$tree/clean.sh" ]]; then
            echo "error: missing $tree/clean.sh"
            exit 1
        fi
        echo "cleaning $tree"
        (cd "$tree" && sh ./clean.sh)
    done
    echo -e "\033[1;32m===== [clean] done =====\033[0m"
    echo ""
}

# ---------------------------------------------------------------------------
# split + checks
# ---------------------------------------------------------------------------
count_assert_files() {
    local pkg_dir="$1"
    if [[ ! -d "$pkg_dir" ]]; then
        echo 0
        return
    fi
    find "$pkg_dir" -type f -name '*_assert*.c' ! -name '_cseq_*' | wc -l | tr -d ' '
}

find_nested_assert_files() {
    local tree="$1"
    find "$tree" -type f -name '*_assert*_assert*.c' ! -name '_cseq_*' 2>/dev/null
}

verify_one_tree() {
    local tree="$1"
    local nested
    local ok=1
    local got

    echo "verifying $tree"

    nested="$(find_nested_assert_files "$tree")"
    if [[ -n "$nested" ]]; then
        echo "error: nested split files found (clean was incomplete):"
        echo "$nested"
        ok=0
    fi

    got="$(count_assert_files "$tree/Idv-races")"
    echo "  Idv-races: $got (expected $EXPECTED_IDV)"
    [[ "$got" -eq "$EXPECTED_IDV" ]] || ok=0

    got="$(count_assert_files "$tree/pthread")"
    echo "  pthread: $got (expected $EXPECTED_PTHREAD)"
    [[ "$got" -eq "$EXPECTED_PTHREAD" ]] || ok=0

    got="$(count_assert_files "$tree/racebench2.1")"
    echo "  racebench2.1: $got (expected $EXPECTED_RACE)"
    [[ "$got" -eq "$EXPECTED_RACE" ]] || ok=0

    got="$(count_assert_files "$tree/rw_benchmark")"
    echo "  rw_benchmark: $got (expected $EXPECTED_RW)"
    [[ "$got" -eq "$EXPECTED_RW" ]] || ok=0

    got="$(count_assert_files "$tree/goblint-regression")"
    echo "  goblint-regression: $got (expected $EXPECTED_GOBLINT)"
    [[ "$got" -eq "$EXPECTED_GOBLINT" ]] || ok=0

    if [[ "$ok" -ne 1 ]]; then
        echo "error: split verification failed for $tree"
        return 1
    fi
    return 0
}

stage_split() {
    echo -e "\033[1;32m===== [split] splitting asserts in two trees =====\033[0m"
    local tree
    for tree in "${TREES[@]}"; do
        echo "purging old *_assert*.c and _cseq_* under $tree"
        find "$tree" -type f \( -name '*_assert*.c' -o -name '_cseq_*' \) -delete
        if [[ ! -f "$tree/split_asserts.py" ]]; then
            echo "error: missing $tree/split_asserts.py"
            exit 1
        fi
        echo "splitting $tree"
        if ! python3 "$tree/split_asserts.py"; then
            echo "error: split_asserts.py failed in $tree"
            exit 1
        fi
    done

    echo -e "\033[1;32m===== [split] verifying counts =====\033[0m"
    local failed=0
    for tree in "${TREES[@]}"; do
        if ! verify_one_tree "$tree"; then
            failed=1
        fi
    done
    if [[ "$failed" -ne 0 ]]; then
        echo "error: expected per-package counts: Idv-races=$EXPECTED_IDV pthread=$EXPECTED_PTHREAD racebench2.1=$EXPECTED_RACE rw_benchmark=$EXPECTED_RW goblint-regression=$EXPECTED_GOBLINT"
        exit 1
    fi
    echo -e "\033[1;32m===== [split] done =====\033[0m"
    echo ""
}

# ---------------------------------------------------------------------------
# run helpers
# ---------------------------------------------------------------------------
# CBMC unwind: goblint-regression/pthread=3, racebench2.1=3, else 2
# --loopAbs: racebench2.1 only (both CBMC and CPAchecker)
unwind_for_pkg() {
    case "$1" in
        goblint-regression|pthread) echo 3 ;;
        racebench2.1) echo 3 ;;
        *) echo 2 ;;
    esac
}

loopabs_args_for_pkg() {
    if [[ "$1" == "racebench2.1" ]]; then
        echo "--loopAbs"
    fi
}

run_one_case() {
    local kind="$1"
    local src_c="$2"
    local backend_or_mode="$3"
    local pkg="$4"
    local unwind loopabs_args

    unwind="$(unwind_for_pkg "$pkg")"
    loopabs_args="$(loopabs_args_for_pkg "$pkg")"

    if [[ "$kind" == "unichecker" ]]; then
        echo -e "\033[1;35m========== Checking: $src_c ==========\033[0m"
        if [[ "$backend_or_mode" == "cpachecker" ]]; then
            python2 "$UNICHECKER" -i "$src_c" -b "$backend_or_mode" --timelimit "$TIMELIMIT" --RespCount 2 $loopabs_args
        else
            python2 "$UNICHECKER" -i "$src_c" -b "$backend_or_mode" -u "$unwind" --timelimit "$TIMELIMIT" --RespCount 2 $loopabs_args
        fi
    else
        echo -e "\033[1;35m========== UnicSeq Checking ($backend_or_mode): $src_c ==========\033[0m"
        python3 "$UNICSEQ" --input "$src_c" --cbmc-unwinding "$unwind" --timelimit "$TIMELIMIT" --mode "$backend_or_mode" --RespCount 2 $loopabs_args
    fi
}

run_packages() {
    local base_dir="$1"
    local kind="$2"
    local backend_or_mode="$3"
    shift 3
    local subfolders=("$@")
    local subfolder testdirs_sh dir cur_case_dir src_c basesrc found_any

    shopt -s nullglob
    for subfolder in "${subfolders[@]}"; do
        testdirs_sh="$base_dir/$subfolder/testdirs.sh"
        if [[ ! -f "$testdirs_sh" ]]; then
            echo "Warning: $testdirs_sh does not exist, skipping $subfolder."
            continue
        fi
        # shellcheck disable=SC1090
        source "$testdirs_sh"
        if [[ "$kind" == "unichecker" ]]; then
            echo -e "\033[1;36m===== Checking $subfolder =====\033[0m"
        else
            echo -e "\033[1;36m===== Checking $subfolder with mode: $backend_or_mode =====\033[0m"
        fi

        for dir in $TEST_DIRS; do
            cur_case_dir="$base_dir/$subfolder/$dir"
            found_any=0
            if [[ "$subfolder" == "rw_benchmark" ]]; then
                for src_c in "$cur_case_dir"/main_n_assert*.c; do
                    basesrc="$(basename "$src_c")"
                    if [[ "$basesrc" == _cseq_* ]]; then
                        continue
                    fi
                    if [[ -f "$src_c" ]]; then
                        found_any=1
                        run_one_case "$kind" "$src_c" "$backend_or_mode" "$subfolder"
                    fi
                done
                if [[ "$found_any" -eq 0 ]]; then
                    echo "No main_n_assertN.c files found in $cur_case_dir, skipping."
                fi
            else
                for src_c in "$cur_case_dir"/*_assert*.c; do
                    basesrc="$(basename "$src_c")"
                    if [[ "$basesrc" == _cseq_* ]]; then
                        continue
                    fi
                    if [[ -f "$src_c" ]]; then
                        found_any=1
                        run_one_case "$kind" "$src_c" "$backend_or_mode" "$subfolder"
                    fi
                done
                if [[ "$found_any" -eq 0 ]]; then
                    echo "No _assertN.c files found in $cur_case_dir, skipping."
                fi
            fi
        done
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

stage_run() {
    echo -e "\033[1;32m===== [run] single backends + parallel portfolio on 5 packages =====\033[0m"

    local backend logfile mode base_dir

    for backend in cbmc cpachecker; do
        logfile="$SPLIT_BASE/results_${backend}.log"
        echo -e "\033[1;32m===== single $backend (4 packages) -> $logfile =====\033[0m"
        with_logfile "$logfile" \
            "$START_TIME, $CMD_LINE, backend=$backend" \
            run_packages "$SPLIT_BASE" unichecker "$backend" "${PACKAGES_FOUR[@]}"

        logfile="$SPLIT_BASE/results_goblint-regression_${backend}.log"
        echo -e "\033[1;32m===== single $backend (goblint-regression) -> $logfile =====\033[0m"
        with_logfile "$logfile" \
            "$START_TIME, $CMD_LINE, backend=$backend" \
            run_packages "$SPLIT_BASE" unichecker "$backend" "${PACKAGES_GOBLINT[@]}"
    done

    mode="cbmc-cpachecker"
    base_dir="$CC_BASE"

    logfile="$base_dir/results_unicseq_${mode}.log"
    echo -e "\033[1;32m===== unicseq $mode (4 packages) -> $logfile =====\033[0m"
    with_logfile "$logfile" \
        "$START_TIME, $CMD_LINE, tool=unicseq, mode=$mode" \
        run_packages "$base_dir" unicseq "$mode" "${PACKAGES_FOUR[@]}"

    logfile="$base_dir/results_unicseq_goblint-regression_${mode}.log"
    echo -e "\033[1;32m===== unicseq $mode (goblint-regression) -> $logfile =====\033[0m"
    with_logfile "$logfile" \
        "$START_TIME, $CMD_LINE, tool=unicseq, mode=$mode" \
        run_packages "$base_dir" unicseq "$mode" "${PACKAGES_GOBLINT[@]}"

    echo -e "\033[1;32m===== [run] done =====\033[0m"
    echo "Logs:"
    echo "  $SPLIT_BASE/results_cbmc.log"
    echo "  $SPLIT_BASE/results_cpachecker.log"
    echo "  $SPLIT_BASE/results_goblint-regression_cbmc.log"
    echo "  $SPLIT_BASE/results_goblint-regression_cpachecker.log"
    echo "  $CC_BASE/results_unicseq_cbmc-cpachecker.log"
    echo "  $CC_BASE/results_unicseq_goblint-regression_cbmc-cpachecker.log"
    echo ""
}

# ---------------------------------------------------------------------------
# table
# ---------------------------------------------------------------------------
stage_table() {
    echo -e "\033[1;32m===== [table] generating Experiment 3 tables =====\033[0m"
    if [[ ! -d "$TABLE_DIR" ]]; then
        echo "error: missing $TABLE_DIR"
        exit 1
    fi
    (
        cd "$TABLE_DIR" || exit 1
        python3 score_table_all_correctness.py || exit 1
    )
    echo -e "\033[1;32m===== [table] done =====\033[0m"
    echo "  $TABLE_DIR/compare_two_table.txt"
    echo "  $TABLE_DIR/compare_correctness_table.txt"
    echo "  $TABLE_DIR/compare_correctness_detail.csv"
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
if should_run_stage run; then
    stage_run
fi
if should_run_stage table; then
    stage_table
fi

echo -e "\033[1;33m===== Experiment 3 runner finished (until=$UNTIL_STAGE) =====\033[0m"
