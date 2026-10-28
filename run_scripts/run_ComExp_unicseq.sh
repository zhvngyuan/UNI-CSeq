#!/bin/bash
# 用法: ./run_ComExp_unicseq.sh [timelimit_in_seconds]
# 例如: ./run_ComExp_unicseq.sh 900

    # 功能:
    #     批量跑 unicseq.py（默认 parallel：CBMC+CPAchecker），覆盖 ComExp_Split_unicseq 下五组测试集。
    #     跑前按实验三口径拆断言；CBMC unwind 统一为 2；仅 racebench2.1 追加 --loopAbs。

    # 主要流程:
    #     1 可接受一个时间限制参数（默认60秒）。
    #     2 BASE_DIR 为 ComExp_Split_unicseq。
    #     3 清掉该树旧 *_assert*.c / _cseq_* 后调用 split_asserts.py，并校验 271 个单断言。
    #     4 对每个 SUBFOLDER：加载 testdirs.sh，按子目录找拆分后的断言文件（跳过 _cseq_）。
    #     5 调用 python3 unicseq.py：--cbmc-unwinding 2 --RespCount 2；racebench2.1 再加 --loopAbs。
    #     6 日志和终端同时输出到 results_unicseq.log。


if [ $# -ge 1 ]; then
    TIMELIMIT="$1"
else
    TIMELIMIT="60"
fi

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."
UNICSEQ="$PROJECT_ROOT/unicseq.py"
BASE_DIR="$PROJECT_ROOT/Experiments/ComExp_Split_unicseq"
SUBFOLDERS=("Idv-races" "pthread" "racebench2.1" "rw_benchmark" "goblint-regression")
CBMC_UNWINDING=2
TIMEFORMAT=$'WALLTIME %R'

EXPECTED_IDV=20
EXPECTED_PTHREAD=10
EXPECTED_RACE=53
EXPECTED_RW=78
EXPECTED_GOBLINT=110

# --loopAbs: racebench2.1 only (passed to every backend unicseq launches)
loopabs_args_for_pkg() {
    if [[ "$1" == "racebench2.1" ]]; then
        echo "--loopAbs"
    fi
}

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

verify_split_tree() {
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
        echo "error: expected per-package counts: Idv-races=$EXPECTED_IDV pthread=$EXPECTED_PTHREAD racebench2.1=$EXPECTED_RACE rw_benchmark=$EXPECTED_RW goblint-regression=$EXPECTED_GOBLINT"
        return 1
    fi
    return 0
}

stage_split() {
    echo -e "\033[1;32m===== [split] splitting asserts in $BASE_DIR =====\033[0m"
    if [[ ! -d "$BASE_DIR" ]]; then
        echo "error: missing $BASE_DIR"
        exit 1
    fi
    echo "purging old *_assert*.c and _cseq_* under $BASE_DIR"
    find "$BASE_DIR" -type f \( -name '*_assert*.c' -o -name '_cseq_*' \) -delete
    if [[ ! -f "$BASE_DIR/split_asserts.py" ]]; then
        echo "error: missing $BASE_DIR/split_asserts.py"
        exit 1
    fi
    echo "splitting $BASE_DIR"
    if ! python3 "$BASE_DIR/split_asserts.py"; then
        echo "error: split_asserts.py failed in $BASE_DIR"
        exit 1
    fi

    echo -e "\033[1;32m===== [split] verifying counts =====\033[0m"
    if ! verify_split_tree "$BASE_DIR"; then
        exit 1
    fi
    echo -e "\033[1;32m===== [split] done =====\033[0m"
    echo ""
}

run_one_case() {
    local src_c="$1"
    local pkg="$2"
    local loopabs_args

    loopabs_args="$(loopabs_args_for_pkg "$pkg")"
    echo -e "\033[1;35m========== UnicSeq Checking: $src_c ==========\033[0m"
    time python3 "$UNICSEQ" --input "$src_c" --cbmc-unwinding "$CBMC_UNWINDING" --timelimit "$TIMELIMIT" --RespCount 2 $loopabs_args
}

run_packages() {
    local subfolder testdirs_sh dir cur_case_dir src_c basesrc found_any

    shopt -s nullglob
    for subfolder in "${SUBFOLDERS[@]}"; do
        testdirs_sh="$BASE_DIR/$subfolder/testdirs.sh"
        if [[ ! -f "$testdirs_sh" ]]; then
            echo "Warning: $testdirs_sh does not exist, skipping $subfolder."
            continue
        fi
        # shellcheck disable=SC1090
        source "$testdirs_sh"

        echo -e "\033[1;36m===== Checking $subfolder =====\033[0m"

        for dir in $TEST_DIRS; do
            cur_case_dir="$BASE_DIR/$subfolder/$dir"
            found_any=0
            if [[ "$subfolder" == "rw_benchmark" ]]; then
                for src_c in "$cur_case_dir"/main_n_assert*.c; do
                    basesrc="$(basename "$src_c")"
                    if [[ "$basesrc" == _cseq_* ]]; then
                        continue
                    fi
                    if [[ -f "$src_c" ]]; then
                        found_any=1
                        run_one_case "$src_c" "$subfolder"
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
                        run_one_case "$src_c" "$subfolder"
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

stage_split

START_TIME=$(date "+%Y年%-m月%-d日%H:%M")
CMD_LINE="$0 $*"

LOGFILE="$BASE_DIR/results_unicseq.log"
{
    echo "$START_TIME, $CMD_LINE, tool=unicseq"
    echo "========================================"
} > "$LOGFILE"

# 保存当前stdout文件描述符
exec {FD_STDOUT}>&1

# 将后续所有输出同时定向到 log 和终端
exec > >(tee -a "$LOGFILE") 2>&1

run_packages

# 恢复stdout（退出本轮输出重定向）
exec 1>&${FD_STDOUT}
exec {FD_STDOUT}>&-
