#!/bin/bash
# 用法: ./run_ComExp_unicseq_mix.sh [timelimit_in_seconds]
# 例如: ./run_ComExp_unicseq_mix.sh 900

# '''
#     功能:
#         这是对unicseq.py的两种模式批量验证的脚本，对比“cbmc-cpachecker”与“sequential”两种模式在不同测试集下的表现。

#     主要流程:
#         1 可接受时间限制参数（默认60秒）。
#         2 定义了两个EXPERIMENTS（路径与模式的映射），即ComExp_Split_unicseq_CC（cbmc-cpachecker）和ComExp_Split_unicseq_SEQ（sequential）。
#         3 对于每个模式，单独生成日志文件，启动独立的tee日志输出。
#         4 对每个SUBFOLDER及其TEST_DIRS，查找测试C文件并批量运行unicseq.py，指定--mode参数为对应模式。
#         5 日志更详细，有不同实验路径、模式的区分。
#         6 终端和日志均输出结果，最后统一打印结果文件路径。
#     用途：
#         对unicseq.py的不同顺序化模式或后端策略做定量对比实验，便于统计效果差异或性能差异。
# '''

if [ $# -ge 1 ]; then
    TIMELIMIT="$1"
else
    TIMELIMIT="60"
fi


SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."

UNICSEQ="$PROJECT_ROOT/unicseq.py"
SUBFOLDERS=("goblint-regression")

START_TIME=$(date "+%Y年%-m月%-d日%H:%M")
CMD_LINE="$0 $*"

# 定义两个实验路径和对应的验证模式
declare -A EXPERIMENTS
EXPERIMENTS["$PROJECT_ROOT/Experiments/ComExp_Split_unicseq_CC"]="cbmc-cpachecker"
EXPERIMENTS["$PROJECT_ROOT/Experiments/ComExp_Split_unicseq_SEQ"]="sequential"

# 为每个实验创建独立的日志文件
for BASE_DIR in "${!EXPERIMENTS[@]}"
do
    MODE="${EXPERIMENTS[$BASE_DIR]}"
    LOGFILE="$BASE_DIR/results_unicseq_goblint-regression_${MODE}.log"
    
    {
        echo "$START_TIME, $CMD_LINE, tool=unicseq, mode=$MODE"
        echo "========================================"
    } > "$LOGFILE"
    
    # 保存当前stdout文件描述符
    exec {FD_STDOUT}>&1
    
    # 将后续所有输出同时定向到 log 和终端
    exec > >(tee -a "$LOGFILE") 2>&1
    
    echo -e "\033[1;32m===== Starting verification with mode: $MODE =====\033[0m"
    echo -e "\033[1;32m===== Base directory: $BASE_DIR =====\033[0m"
    
    shopt -s nullglob  # 防止未匹配到文件时报错
    
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
        
        echo -e "\033[1;36m===== Checking $SUBFOLDER with mode: $MODE =====\033[0m"
        
        if [[ "$SUBFOLDER" == "goblint-regression" ]]; then
            for DIR in $TEST_DIRS
            do
                CUR_CASE_DIR="$CUR_DIR/$DIR"
                found_any=0
                for SRC_C in "$CUR_CASE_DIR"/*_assert*.c
                do
                    baseSRC=$(basename "$SRC_C")
                    # 跳过_cseq_生成的文件
                    if [[ "$baseSRC" == _cseq_* ]]; then
                        continue
                    fi
                    if [ -f "$SRC_C" ]; then
                        found_any=1
                        echo -e "\033[1;35m========== UnicSeq Checking ($MODE): $SRC_C ==========\033[0m"
                        python3 "$UNICSEQ" --input "$SRC_C" --cbmc-unwinding 2 --timelimit "$TIMELIMIT" --mode "$MODE" --RespCount 2
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
                    # 跳过_cseq_生成的文件
                    if [[ "$baseSRC" == _cseq_* ]]; then
                        continue
                    fi
                    if [ -f "$SRC_C" ]; then
                        found_any=1
                        echo -e "\033[1;35m========== UnicSeq Checking ($MODE): $SRC_C ==========\033[0m"
                        python3 "$UNICSEQ" --input "$SRC_C" --cbmc-unwinding 2 --timelimit "$TIMELIMIT" --mode "$MODE" --RespCount 2
                    fi
                done
                if [ $found_any -eq 0 ]; then
                    echo "No main_n_assertN.c files found in $CUR_CASE_DIR, skipping."
                fi
            done
        fi
    done
    
    shopt -u nullglob
    
    # 恢复stdout（退出本轮输出重定向）
    exec 1>&${FD_STDOUT}
    exec {FD_STDOUT}>&-
    
    echo -e "\033[1;32m===== Completed verification with mode: $MODE =====\033[0m"
    echo ""
done

echo -e "\033[1;33m===== All verifications completed =====\033[0m"
echo "Results saved in:"
for BASE_DIR in "${!EXPERIMENTS[@]}"
do
    MODE="${EXPERIMENTS[$BASE_DIR]}"
    echo "  - $BASE_DIR/results_unicseq_goblint-regression_${mode}.log"
done