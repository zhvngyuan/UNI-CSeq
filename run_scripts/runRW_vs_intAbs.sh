#!/bin/bash
# 用法：./runRW_vs_intAbs.sh <timelimit_in_seconds> [backend]
# 参数解析
if [ $# -lt 1 ]; then
    echo "Usage: $0 <timelimit_in_seconds> [backend]"
    exit 1
fi

TIMELIMIT="$1"
BACKEND="${2:-cpachecker}"  # 如果未指定，默认为cpachecker


SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."
UNICHECKER="$PROJECT_ROOT/unichecker.py"

if [ "$BACKEND" = "cbmc" ]; then
    BASE_DIR="$PROJECT_ROOT/Experiments/compare_with_intAbs_cbmc"
else
    BASE_DIR="$PROJECT_ROOT/Experiments/compare_with_intAbs_cpachecker"
    # BASE_DIR="$PROJECT_ROOT/Experiments/compare_with_intAbs_cpa_false"
fi


REALWORLD_DIRS="$BASE_DIR/testdirs.sh" # run 18 programs
# REALWORLD_DIRS="$BASE_DIR/testdirs1.sh"
LOGFILE="$BASE_DIR/runExp.log"

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
    # SEQ_C="$BASE_DIR/$DIR/_cseq_main_n.c"
    # LOG_C="$BASE_DIR/$DIR/_cseq_main_n.c.cpachecker.log"

    if [ -f "$MAIN_C" ]; then
        echo -e "\033[1;35m========== Checking directory: $DIR ==========\033[0m" # color pink blod
        echo "File path: $MAIN_C"
        echo "********Execute Analysis with $BACKEND:"
        if [ "$BACKEND" = "cpachecker" ]; then
            python2 "$UNICHECKER" -i "$MAIN_C" -b "$BACKEND" --timelimit "$TIMELIMIT" --RespCount 2
        else
            python2 "$UNICHECKER" -i "$MAIN_C" -b "$BACKEND" -u 2 --timelimit "$TIMELIMIT" --RespCount 2
        fi
        
    else
        echo "Warning: $MAIN_C does not exist, skipping."
    fi
done