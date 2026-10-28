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

if [ "$BACKEND" = "cbmc" ]; then
    BASE_DIR="$PROJECT_ROOT/Experiments/icbmc"
else
    BASE_DIR="$PROJECT_ROOT/Experiments/Testrealpro_safe_cpa"
fi

REALWORLD_DIRS="$BASE_DIR/realworld18dirs.sh"
LOGFILE="$BASE_DIR/runRW.log"

# 获取当前时间和命令
START_TIME=$(date "+%Y年%-m月%-d日%H:%M")
CMD_LINE="$0 $*"

# 初始化并写入日志头
{
    echo "$START_TIME, $CMD_LINE"
    echo "========================================"
} > "$LOGFILE"

# 将后续所有输出重定向到日志和终端
exec > >(tee -a "$LOGFILE") 2>&1

# 加载目录列表
source "$REALWORLD_DIRS"

for DIR in $TEST_DIRS
do
    MAIN_C="$BASE_DIR/$DIR/main_n.c"
    SEQ_C="$BASE_DIR/$DIR/_cseq_main.c"
    LOG_C="$BASE_DIR/$DIR/_cseq_main.c.cpachecker.log"

    if [ -f "$MAIN_C" ]; then
        echo -e "\033[1;35m========== Checking directory: $DIR ==========\033[0m"
        echo "File path: $MAIN_C"
        [ -f "$SEQ_C" ] && rm -f "$SEQ_C"
        [ -f "$LOG_C" ] && rm -f "$LOG_C"
        echo "********Execute Analysis with $BACKEND:"
        if [ "$BACKEND" = "cpachecker" ]; then
            python2 "$UNICHECKER" -i "$MAIN_C" --timelimit "$TIMELIMIT" --RespCount 2
        else
            python2 "$UNICHECKER" -i "$MAIN_C" -b "$BACKEND" -u 2 --timelimit "$TIMELIMIT" --RespCount 2
        fi
        echo
    else
        echo "Warning: $MAIN_C does not exist, skipping."
    fi
done