#!/bin/bash
# 用法: ./run_ComExp.sh <timelimit_in_seconds>
# 例如: ./run_ComExp.sh 900

# 
#     功能:
#         这是主验证实验批处理脚本, 用于在不同模型检测后端(cbmc、cpachecker、uautomizer)下, 
#          自动批量运行unichecker.py, 对各类并发C程序进行模型检测.

#     主要流程:
#     1 参数1为时间限制(秒), 如900.
#     2 遍历所有BACKEND(cbmc、cpachecker、uautomizer).
#     3 每个后端有独立的日志文件results_${BACKEND}.log.
#     4 对每个SUBFOLDER(Idv-races、pthread、racebench2.1、rw_benchmark):
#         加载当前子目录下的testdirs.sh,读取TEST_DIRS
#     5 对每个测试子目录，查找所有*_assert*.c(或rw_benchmark为main_n_assert*.c)源文件. 
#     6 跳过以_cseq_开头的文件。
#     7 调用python2 unichecker.py, 指定后端和时间限制, 运行模型检测.
#     8 结果写入日志并输出到终端.
# 

if [ $# -lt 1 ]; then
    echo "Usage: $0 <timelimit_in_seconds>"
    exit 1
fi

TIMELIMIT="$1"

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."
UNICHECKER="$PROJECT_ROOT/unichecker.py"
BASE_DIR="$PROJECT_ROOT/Experiments_tests/ComExp_Split"


# BACKENDS=("cbmc" "cpachecker" "uautomizer")
BACKENDS=("uautomizer")
SUBFOLDERS=("Idv-races" "pthread" "racebench2.1" "rw_benchmark")

START_TIME=$(date "+%Y年%-m月%-d日%H:%M")
CMD_LINE="$0 $*"

for BACKEND in "${BACKENDS[@]}"
do
    LOGFILE="$BASE_DIR/results_${BACKEND}.log"
    {
        echo "$START_TIME, $CMD_LINE, backend=$BACKEND"
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

        echo -e "\033[1;36m===== Checking $SUBFOLDER =====\033[0m"

        if [[ "$SUBFOLDER" == "Idv-races" || "$SUBFOLDER" == "pthread" || "$SUBFOLDER" == "racebench2.1" ]]; then
            for DIR in $TEST_DIRS
            do
                CUR_CASE_DIR="$CUR_DIR/$DIR"
                found_any=0
                for SRC_C in "$CUR_CASE_DIR/"*_assert*.c
                do
                     # 跳过_cseq_生成的文件
                    baseSRC=$(basename "$SRC_C")
                    if [[ "$baseSRC" == _cseq_* ]]; then
                        continue
                    fi
                    if [ -f "$SRC_C" ]; then
                        found_any=1
                        echo -e "\033[1;35m========== Checking: $SRC_C ==========\033[0m"
                        if [ "$BACKEND" = "cpachecker" ]; then
                            python2 "$UNICHECKER" -i "$SRC_C" -b "$BACKEND" --timelimit "$TIMELIMIT" --RespCount 2
                        else
                            python2 "$UNICHECKER" -i "$SRC_C" -b "$BACKEND" -u 2 --timelimit "$TIMELIMIT" --RespCount 2
                        fi
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
                     # 跳过_cseq_生成的文件
                    baseSRC=$(basename "$SRC_C")
                    if [[ "$baseSRC" == _cseq_* ]]; then
                        continue
                    fi
                    if [ -f "$SRC_C" ]; then
                        found_any=1
                        echo -e "\033[1;35m========== Checking: $SRC_C ==========\033[0m"
                        if [ "$BACKEND" = "cpachecker" ]; then
                             python2 "$UNICHECKER" -i "$SRC_C" -b "$BACKEND" --timelimit "$TIMELIMIT" --RespCount 2
                        else
                             python2 "$UNICHECKER" -i "$SRC_C" -b "$BACKEND" -u 2 --timelimit "$TIMELIMIT" --RespCount 2
                        fi
                    fi
                done
                if [ $found_any -eq 0 ]; then
                    echo "No main_n_assertN.c files found in $CUR_CASE_DIR, skipping."
                fi
            done
        fi
    done

    # 恢复stdout（退出本轮输出重定向）
    exec 1>&${FD_STDOUT}
    exec {FD_STDOUT}>&-
done