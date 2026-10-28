#!/bin/bash
# 用法: ./run_ComExp_cbmc_unwind.sh <timelimit_in_seconds>
# 例如: ./run_ComExp_cbmc_unwind.sh 900

if [ $# -lt 1 ]; then
    echo "Usage: $0 <timelimit_in_seconds>"
    exit 1
fi

TIMELIMIT="$1"

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."
UNICHECKER="$PROJECT_ROOT/unichecker.py"


BASE_PARENT="$PROJECT_ROOT/Experiments/Com_test_cbmc_unwind"
UNWIND_DIRS=("ComExp_Split_u2" "ComExp_Split_u4" "ComExp_Split_u8" "ComExp_Split_u16" "ComExp_Split_u32")
SUBFOLDERS=("Idv-races" "pthread" "racebench2.1" "rw_benchmark" "goblint-regression")
BACKEND="cbmc"
TIMEFORMAT=$'WALLTIME %R'

# --loopAbs: racebench2.1 only (same as experiment-3 main table)
loopabs_args_for_pkg() {
    if [[ "$1" == "racebench2.1" ]]; then
        echo "--loopAbs"
    fi
}

START_TIME=$(date "+%Y年%-m月%-d日%H:%M")
CMD_LINE="$0 $*"

for UNWIND_DIR in "${UNWIND_DIRS[@]}"
do
    # 提取unwind参数N
    UNWIND=$(echo "$UNWIND_DIR" | sed -n 's/.*_u\([0-9]\+\)$/\1/p')
    BASE_DIR="$BASE_PARENT/$UNWIND_DIR"
    LOGFILE="$BASE_DIR/results_cbmc_unwind${UNWIND}.log"
    {
        echo "$START_TIME, $CMD_LINE, backend=cbmc, unwind=$UNWIND"
        echo "========================================"
    } > "$LOGFILE"

    # 保存当前stdout文件描述符
    exec {FD_STDOUT}>&1

    # 将后续所有输出同时定向到 log 和终端
    exec > >(tee -a "$LOGFILE") 2>&1

    for SUBFOLDER in "${SUBFOLDERS[@]}"
    do
        CUR_DIR="$BASE_DIR/$SUBFOLDER"
        TESTDIRS_SH="$CUR_DIR/testdirs.sh"

        if [ ! -f "$TESTDIRS_SH" ]; then
            echo "Warning: $TESTDIRS_SH does not exist, skipping $SUBFOLDER."
            continue
        fi

        # 加载 TEST_DIRS 环境变量
        source "$TESTDIRS_SH"

        echo -e "\033[1;36m===== Checking $SUBFOLDER (unwind=$UNWIND) =====\033[0m"
        LOOPABS_ARGS="$(loopabs_args_for_pkg "$SUBFOLDER")"

        if [[ "$SUBFOLDER" == "goblint-regression" || "$SUBFOLDER" == "Idv-races" || "$SUBFOLDER" == "pthread" || "$SUBFOLDER" == "racebench2.1" ]]; then
            for DIR in $TEST_DIRS
            do
                CUR_CASE_DIR="$CUR_DIR/$DIR"
                found_any=0
                for SRC_C in "$CUR_CASE_DIR/"*_assert*.c
                do
                    baseSRC=$(basename "$SRC_C")
                    if [[ "$baseSRC" == _cseq_* ]]; then
                        continue
                    fi
                    if [ -f "$SRC_C" ]; then
                        found_any=1
                        echo -e "\033[1;35m========== Checking: $SRC_C ==========\033[0m"
                        time python2 "$UNICHECKER" -i "$SRC_C" -b "$BACKEND" -u "$UNWIND" --timelimit "$TIMELIMIT" --RespCount 2 $LOOPABS_ARGS
                    fi
                done
                if [ $found_any -eq 0 ]; then
                    echo "No _assertN.c files found in $CUR_CASE_DIR, skipping."
                fi
            done

        elif [[ "$SUBFOLDER" == "rw_benchmark" ]]; then
            for DIR in $TEST_DIRS
            do
                CUR_CASE_DIR="$CUR_DIR/$DIR"
                found_any=0
                for SRC_C in "$CUR_CASE_DIR"/main_n_assert*.c
                do
                    baseSRC=$(basename "$SRC_C")
                    if [[ "$baseSRC" == _cseq_* ]]; then
                        continue
                    fi
                    if [ -f "$SRC_C" ]; then
                        found_any=1
                        echo -e "\033[1;35m========== Checking: $SRC_C ==========\033[0m"
                        time python2 "$UNICHECKER" -i "$SRC_C" -b "$BACKEND" -u "$UNWIND" --timelimit "$TIMELIMIT" --RespCount 2 $LOOPABS_ARGS
                    fi
                done
                if [ $found_any -eq 0 ]; then
                    echo "No main_n_assertN.c files found in $CUR_CASE_DIR, skipping."
                fi
            done
        fi
    done

    # 恢复stdout
    exec 1>&${FD_STDOUT}
    exec {FD_STDOUT}>&-
done