#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 <timelimit_in_seconds> [backend]"
    exit 1
fi

TIMELIMIT="$1"
BACKEND="${2:-cpachecker}"  # 默认cpachecker


SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."
UNICHECKER="$PROJECT_ROOT/unichecker.py"


# 执行一次脚本检测如下路径中的所有程序
BASE_DIRS=(
    # "$PROJECT_ROOT/Experiments/svcomp2022/Idv-races"
    # "$PROJECT_ROOT/Experiments/svcomp2022/pthread"
    # "$PROJECT_ROOT/Experiments/svcomp2022/goblint-regression"
    "$PROJECT_ROOT/Experiments/racebench2.1"
)

for BASE_DIR in "${BASE_DIRS[@]}"
do
    REALWORLD_DIRS="$BASE_DIR/testdirs.sh"
    LOGFILE="$BASE_DIR/output_${BACKEND}.log"

    START_TIME=$(date "+%Y年%-m月%-d日%H:%M")
    CMD_LINE="$0 $*"

    {
        echo "$START_TIME, $CMD_LINE"
        echo "========================================"
    } > "$LOGFILE"

    exec > >(tee -a "$LOGFILE") 2>&1

    # 检查 testdirs.sh 是否存在
    if [ ! -f "$REALWORLD_DIRS" ]; then
        echo "Warning: $REALWORLD_DIRS not found, skipping $BASE_DIR."
        continue
    fi

    source "$REALWORLD_DIRS"

    for DIR in $TEST_DIRS
    do
        MAIN_C="$BASE_DIR/$DIR/${DIR}.c"

        if [ -f "$MAIN_C" ]; then
            echo -e "\033[1;35m========== Checking directory: $DIR ==========\033[0m"
            echo "File path: $MAIN_C"
            echo "********Execute Analysis with $BACKEND:"
            if [ "$BACKEND" = "cpachecker" ]; then
                python2 "$UNICHECKER" -i "$MAIN_C" --timelimit "$TIMELIMIT" --RespCount 2 #--loopAbs
            else
                python2 "$UNICHECKER" -i "$MAIN_C" -b "$BACKEND" -u 3 --timelimit "$TIMELIMIT" --RespCount 2 --loopAbs
            fi
            echo
        else
            echo "Warning: $MAIN_C does not exist, skipping."
        fi
    done
done