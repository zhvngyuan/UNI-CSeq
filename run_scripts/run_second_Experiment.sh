#!/bin/bash
# 用法:
#   ./run_scripts/run_second_Experiment.sh
#   ./run_scripts/run_second_Experiment.sh 900
#   ./run_scripts/run_second_Experiment.sh 900 --until run
#   ./run_scripts/run_second_Experiment.sh --from run_nic --until table
#   ./run_scripts/run_second_Experiment.sh --from run --until table
#
# 功能:
#   实验二 UNI-CSeq（CBMC）与 NIChecker 一键复现。
#   阶段: clean -> run -> run_nic -> table
#   一次覆盖 5 个包，UNI-CSeq unwind 与实验三 run_third_Experiment.sh 一致：
#   goblint-regression / pthread / racebench2.1 为 3；Idv-races / rw_benchmark 为 2。
#   NIChecker unwind 与 UNI-CSeq 相同，仅 racebench2.1 为 2。
#   仅 racebench2.1 加 --loopAbs（UNI-CSeq）与 --LA（NIChecker）。
#   rw_benchmark 即实验一 CBMC 目录（compare_with_intAbs_cbmc 的 main_n.c）。
#   UNI-CSeq 后端固定 CBMC。NIChecker rounds 固定为 2。

usage() {
    cat <<'EOF'
Usage: ./run_scripts/run_second_Experiment.sh [timelimit] [--from STAGE] [--until STAGE]

Stages (in order): clean, run, run_nic, table
  --from STAGE    start from this stage (default: clean)
  --until STAGE   stop after this stage (default: table)
  timelimit       seconds for unichecker / NIChecker (default: 900)

Examples:
  ./run_scripts/run_second_Experiment.sh
  ./run_scripts/run_second_Experiment.sh 900
  ./run_scripts/run_second_Experiment.sh 900 --until run
  ./run_scripts/run_second_Experiment.sh --from run_nic --until table
  ./run_scripts/run_second_Experiment.sh --from run --until table
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
        run) echo 1 ;;
        run_nic) echo 2 ;;
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
TABLE_DIR="$PROJECT_ROOT/Experiments/genTable_scripts"
NICHECKER="${NICHECKER:-}"
# nichecker.py does os.chdir(cwd+"/Cseq"); must run from its install dir
if [[ -n "$NICHECKER" ]]; then
    NICHECKER_DIR="$(cd "$(dirname "$NICHECKER")" 2>/dev/null && pwd)"
else
    NICHECKER_DIR=""
fi

BACKEND="cbmc"
RESPCOUNT="2"
NIC_ROUNDS="2"
PACKAGES=("Idv-races" "pthread" "goblint-regression" "racebench2.1" "rw_benchmark")

pkg_dir() {
    case "$1" in
        racebench2.1) echo "$PROJECT_ROOT/Experiments/racebench2.1" ;;
        rw_benchmark) echo "$PROJECT_ROOT/Experiments/compare_with_intAbs_cbmc" ;;
        *) echo "$PROJECT_ROOT/Experiments/svcomp2022/$1" ;;
    esac
}

# svcomp / racebench: <dir>/<dir>.c ；rw_benchmark: <dir>/main_n.c（与 runRW_vs_intAbs.sh 的 CBMC 路径一致）
pkg_src_file() {
    local pkg_name="$1"
    local pkg_dir="$2"
    local dir="$3"
    if [[ "$pkg_name" == "rw_benchmark" ]]; then
        echo "$pkg_dir/$dir/main_n.c"
    else
        echo "$pkg_dir/$dir/${dir}.c"
    fi
}

# svcomp / racebench: output_cbmc.log ；rw_benchmark: runExp.log（与 runRW_vs_intAbs.sh 一致）
pkg_logfile() {
    local pkg_name="$1"
    local pkg_dir="$2"
    if [[ "$pkg_name" == "rw_benchmark" ]]; then
        echo "$pkg_dir/runExp.log"
    else
        echo "$pkg_dir/output_cbmc.log"
    fi
}

# UNI-CSeq unwind: same as run_third_Experiment.sh
#   goblint-regression / pthread / racebench2.1 -> 3
#   Idv-races / rw_benchmark -> 2
unwind_for_pkg() {
    case "$1" in
        goblint-regression|pthread) echo 3 ;;
        racebench2.1) echo 3 ;;
        *) echo 2 ;;
    esac
}

# NIChecker unwind: same as UNI-CSeq, except racebench2.1 -> 2
nic_unwind_for_pkg() {
    if [[ "$1" == "racebench2.1" ]]; then
        echo 2
    else
        unwind_for_pkg "$1"
    fi
}

# --loopAbs (UNI-CSeq) / --LA (NIChecker): racebench2.1 only
loopabs_args_for_pkg() {
    if [[ "$1" == "racebench2.1" ]]; then
        echo "--loopAbs"
    fi
}

la_args_for_pkg() {
    if [[ "$1" == "racebench2.1" ]]; then
        echo "--LA"
    fi
}

pkg_nic_logfile() {
    local pkg_dir="$1"
    echo "$pkg_dir/output_NIChecker.log"
}

START_TIME="$(date "+%Y年%-m月%-d日%H:%M")"
CMD_LINE="$0 $ORIG_ARGS"

echo -e "\033[1;33m===== UNI-CSeq Experiment 2 runner =====\033[0m"
echo "project: $PROJECT_ROOT"
echo "backend: $BACKEND"
echo "unwind: goblint/pthread/racebench=3, Idv-races/rw_benchmark=2 (same as Experiment 3)"
echo "NIChecker unwind: same as UNI-CSeq, except racebench2.1=2"
echo "RespCount: $RESPCOUNT"
echo "NIChecker rounds: $NIC_ROUNDS"
echo "NIChecker: $NICHECKER"
echo "NIChecker cwd: $NICHECKER_DIR"
echo "timelimit: $TIMELIMIT"
echo "loopAbs / --LA: racebench2.1 only"
echo "rw_benchmark: Experiments/compare_with_intAbs_cbmc (main_n.c, unwind=2)"
echo "from: $FROM_STAGE  until: $UNTIL_STAGE"
echo ""

# ---------------------------------------------------------------------------
# clean: UNI-CSeq/CBMC artifacts only (keep NIChecker logs)
# ---------------------------------------------------------------------------
stage_clean() {
    echo -e "\033[1;32m===== [clean] removing UNI-CSeq/CBMC artifacts (keep NIChecker logs) =====\033[0m"
    local pkg pkg_dir
    for pkg in "${PACKAGES[@]}"; do
        pkg_dir="$(pkg_dir "$pkg")"
        if [[ ! -d "$pkg_dir" ]]; then
            echo "error: missing package directory $pkg_dir"
            exit 1
        fi
        echo "cleaning $pkg_dir"
        find "$pkg_dir" -type f \( -name '_cseq_cbmc_*' -o -name '*.c.cbmc.log' \) -delete
        rm -f "$pkg_dir/output_cbmc.log" "$pkg_dir/runExp.log"
    done
    echo -e "\033[1;32m===== [clean] done =====\033[0m"
    echo ""
}

# ---------------------------------------------------------------------------
# run helpers
# ---------------------------------------------------------------------------
run_one_package() {
    local pkg_name="$1"
    local pkg_dir="$2"
    local testdirs_sh="$pkg_dir/testdirs.sh"
    local dir main_c loopabs_args unwind

    if [[ ! -f "$testdirs_sh" ]]; then
        echo "error: missing $testdirs_sh"
        exit 1
    fi
    # shellcheck disable=SC1090
    source "$testdirs_sh"

    unwind="$(unwind_for_pkg "$pkg_name")"
    loopabs_args="$(loopabs_args_for_pkg "$pkg_name")"
    echo -e "\033[1;36m===== Checking $pkg_name (unwind=$unwind $loopabs_args) =====\033[0m"

    for dir in $TEST_DIRS; do
        main_c="$(pkg_src_file "$pkg_name" "$pkg_dir" "$dir")"
        if [[ -f "$main_c" ]]; then
            echo -e "\033[1;35m========== Checking directory: $dir ==========\033[0m"
            echo "File path: $main_c"
            echo "********Execute Analysis with $BACKEND:"
            python2 "$UNICHECKER" -i "$main_c" -b "$BACKEND" -u "$unwind" --timelimit "$TIMELIMIT" --RespCount "$RESPCOUNT" $loopabs_args
            echo
        else
            echo "Warning: $main_c does not exist, skipping."
        fi
    done
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
    echo -e "\033[1;32m===== [run] UNI-CSeq + CBMC on 5 packages =====\033[0m"

    local pkg pkg_dir logfile loopabs_args unwind
    for pkg in "${PACKAGES[@]}"; do
        pkg_dir="$(pkg_dir "$pkg")"
        logfile="$(pkg_logfile "$pkg" "$pkg_dir")"
        unwind="$(unwind_for_pkg "$pkg")"
        loopabs_args="$(loopabs_args_for_pkg "$pkg")"
        echo -e "\033[1;32m===== $pkg -> $logfile =====\033[0m"
        with_logfile "$logfile" \
            "$START_TIME, $CMD_LINE, backend=$BACKEND unwind=$unwind RespCount=$RESPCOUNT $loopabs_args pkg=$pkg" \
            run_one_package "$pkg" "$pkg_dir"
    done

    echo -e "\033[1;32m===== [run] done =====\033[0m"
    echo "Logs:"
    for pkg in "${PACKAGES[@]}"; do
        pkg_dir="$(pkg_dir "$pkg")"
        echo "  $(pkg_logfile "$pkg" "$pkg_dir")"
    done
    echo ""
}

# ---------------------------------------------------------------------------
# run_nic: NIChecker; unwind matches UNI-CSeq except racebench2.1=2; --LA only for racebench2.1
# ---------------------------------------------------------------------------
run_one_package_nic() {
    local pkg_name="$1"
    local pkg_dir="$2"
    local testdirs_sh="$pkg_dir/testdirs.sh"
    local dir main_c la_args unwind

    if [[ ! -f "$testdirs_sh" ]]; then
        echo "error: missing $testdirs_sh"
        exit 1
    fi
    # shellcheck disable=SC1090
    source "$testdirs_sh"

    unwind="$(nic_unwind_for_pkg "$pkg_name")"
    la_args="$(la_args_for_pkg "$pkg_name")"
    echo -e "\033[1;36m===== Checking $pkg_name with NIChecker (unwind=$unwind rounds=$NIC_ROUNDS $la_args) =====\033[0m"

    for dir in $TEST_DIRS; do
        main_c="$(pkg_src_file "$pkg_name" "$pkg_dir" "$dir")"
        if [[ -f "$main_c" ]]; then
            echo -e "\033[1;35m========== Checking directory: $dir ==========\033[0m"
            echo "File path: $main_c"
            echo "********Execute Analysis with NIChecker:"
            (
                cd "$NICHECKER_DIR" || exit 1
                python2 "$NICHECKER" -i "$main_c" --unwind "$unwind" --rounds "$NIC_ROUNDS" --timelimit "$TIMELIMIT" $la_args
            )
            echo
        else
            echo "Warning: $main_c does not exist, skipping."
        fi
    done
}

stage_run_nic() {
    echo -e "\033[1;32m===== [run_nic] NIChecker on 5 packages =====\033[0m"
    if [[ -z "$NICHECKER" ]]; then
        echo "error: NICHECKER is not set"
        echo "export NICHECKER to the path of nichecker.py"
        exit 1
    fi
    if [[ ! -f "$NICHECKER" ]]; then
        echo "error: missing NIChecker at $NICHECKER"
        echo "export NICHECKER to the path of nichecker.py"
        exit 1
    fi
    if [[ -z "$NICHECKER_DIR" || ! -d "$NICHECKER_DIR/Cseq" ]]; then
        echo "error: missing $NICHECKER_DIR/Cseq"
        echo "nichecker.py chdirs to ./Cseq relative to its working directory;"
        echo "set NICHECKER to nichecker.py inside the NIChecker install tree"
        exit 1
    fi

    local pkg pkg_dir logfile la_args unwind
    for pkg in "${PACKAGES[@]}"; do
        pkg_dir="$(pkg_dir "$pkg")"
        logfile="$(pkg_nic_logfile "$pkg_dir")"
        unwind="$(nic_unwind_for_pkg "$pkg")"
        la_args="$(la_args_for_pkg "$pkg")"
        echo -e "\033[1;32m===== $pkg -> $logfile =====\033[0m"
        with_logfile "$logfile" \
            "$START_TIME, $CMD_LINE, NIChecker unwind=$unwind rounds=$NIC_ROUNDS $la_args pkg=$pkg" \
            run_one_package_nic "$pkg" "$pkg_dir"
    done

    echo -e "\033[1;32m===== [run_nic] done =====\033[0m"
    echo "Logs:"
    for pkg in "${PACKAGES[@]}"; do
        pkg_dir="$(pkg_dir "$pkg")"
        echo "  $(pkg_nic_logfile "$pkg_dir")"
    done
    echo ""
}

# ---------------------------------------------------------------------------
# table
# ---------------------------------------------------------------------------
stage_table() {
    echo -e "\033[1;32m===== [table] generating Experiment 2 table =====\033[0m"
    if [[ ! -d "$TABLE_DIR" ]]; then
        echo "error: missing $TABLE_DIR"
        exit 1
    fi
    (
        cd "$TABLE_DIR" || exit 1
        python3 gen_compare_table.py || exit 1
    )
    echo -e "\033[1;32m===== [table] done =====\033[0m"
    echo "  $TABLE_DIR/compare_table.tex"
    echo ""
}

# ---------------------------------------------------------------------------
# main
# ---------------------------------------------------------------------------
if should_run_stage clean; then
    stage_clean
fi
if should_run_stage run; then
    stage_run
fi
if should_run_stage run_nic; then
    stage_run_nic
fi
if should_run_stage table; then
    stage_table
fi

echo -e "\033[1;33m===== Experiment 2 runner finished (until=$UNTIL_STAGE) =====\033[0m"
