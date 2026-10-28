#!/bin/bash
# 用法：./run_scripts/run_icbmc_reproduce.sh <timelimit_in_seconds>
# 功能：用各目录内 ./cbmc --mm irq --unwind 2 复现 iCBMC 注释循环实验。
#       不修改原始 main.c；工作副本与日志写在 <dir>/_icbmc_repro/。
#
# 仅在 Linux 上运行（依赖 timeout 与目录内的 cbmc 二进制）。

if [ $# -lt 1 ]; then
    echo "Usage: $0 <timelimit_in_seconds>"
    exit 1
fi

TIMELIMIT="$1"
UNWIND=2
MAX_ROUNDS=80

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."
BASE_DIR="$PROJECT_ROOT/Experiments/icbmc"
REALWORLD_DIRS="$BASE_DIR/realworld18dirs.sh"
LOGFILE="$BASE_DIR/run_icbmc.log"
SUMMARY="$BASE_DIR/_icbmc_repro_summary.csv"
COMMENT_HELPER="$SCRIPT_DIR/icbmc_comment_assert.py"

if [ ! -f "$COMMENT_HELPER" ]; then
    echo "error: missing $COMMENT_HELPER"
    exit 1
fi

if command -v python3 >/dev/null 2>&1; then
    PYTHON=python3
elif command -v python >/dev/null 2>&1; then
    PYTHON=python
else
    echo "error: python3/python not found"
    exit 1
fi

if ! command -v timeout >/dev/null 2>&1; then
    echo "error: timeout not found (this script must run on Linux)"
    exit 1
fi

START_TIME=$(date "+%Y年%-m月%-d日%H:%M" 2>/dev/null || date "+%Y-%m-%d %H:%M")
CMD_LINE="$0 $*"

{
    echo "$START_TIME, $CMD_LINE"
    echo "unwind=$UNWIND  timelimit=$TIMELIMIT"
    echo "========================================"
} > "$LOGFILE"

exec > >(tee -a "$LOGFILE") 2>&1

source "$REALWORLD_DIRS"

parse_real_seconds() {
    local f="$1"
    local line
    line=$(grep -E '^real' "$f" 2>/dev/null | tail -1)
    if [ -z "$line" ]; then
        echo "0"
        return
    fi
    # bash time: real	0m0.290s
    echo "$line" | tr "m" " " | tr "s" " " | awk '{
        if (NF >= 3) printf "%.3f", ($2 * 60) + $3;
        else if (NF == 2) printf "%.3f", $2;
        else print 0;
    }'
}

extract_violated_line() {
    local f="$1"
    local line
    line=$(awk '
        /Violated property:/ { grab=1; next }
        grab && /line [0-9]+/ {
            if (match($0, /line [0-9]+/)) {
                s=substr($0, RSTART, RLENGTH)
                sub(/line /, "", s)
                print s
                exit
            }
        }
    ' "$f")
    if [ -z "$line" ]; then
        line=$(grep -E 'file .+ line [0-9]+' "$f" | tail -1 | sed -E 's/.* line ([0-9]+).*/\1/')
    fi
    echo "$line"
}

echo "Name,rounds,Vio,Val,Time,last_result,commented_lines" > "$SUMMARY"

for DIR in $TEST_DIRS
do
    PROG_DIR="$BASE_DIR/$DIR"
    MAIN_C="$PROG_DIR/main.c"
    WORK_DIR="$PROG_DIR/_icbmc_repro"
    WORK_C="$WORK_DIR/main.c"

    echo -e "\033[1;35m========== Checking directory: $DIR ==========\033[0m"
    echo "File path: $MAIN_C"

    if [ ! -f "$MAIN_C" ]; then
        echo "Warning: $MAIN_C does not exist, skipping."
        echo "$DIR,0,0,0,0,ERROR,missing_main_c" >> "$SUMMARY"
        echo
        continue
    fi
    if [ ! -x "$PROG_DIR/cbmc" ]; then
        echo "Warning: $PROG_DIR/cbmc is missing or not executable, skipping."
        echo "$DIR,0,0,0,0,ERROR,missing_cbmc" >> "$SUMMARY"
        echo
        continue
    fi

    rm -rf "$WORK_DIR"
    mkdir -p "$WORK_DIR"
    cp "$MAIN_C" "$WORK_C"

    commented_lines=""
    vio=0
    last_result="ERROR"
    total_time="0"
    round=0

    (
        cd "$PROG_DIR" || exit 1
        for k in $(seq 1 "$MAX_ROUNDS"); do
            out="_icbmc_repro/runtime${k}.out"
            echo "******** round $k: ./cbmc --mm irq --unwind $UNWIND _icbmc_repro/main.c"
            timeout "$TIMELIMIT" bash -c "time ./cbmc --mm irq --unwind $UNWIND \"_icbmc_repro/main.c\"" > "$out" 2>&1
            rc=$?

            if [ "$rc" -eq 124 ] || [ "$rc" -eq 137 ]; then
                echo "TIMEOUT round=$k"
                echo "TIMEOUT" > "_icbmc_repro/_last_result"
                echo "$k" > "_icbmc_repro/_rounds"
                echo "$vio" > "_icbmc_repro/_vio"
                echo "$commented_lines" > "_icbmc_repro/_commented"
                exit 0
            fi

            if grep -q "VERIFICATION SUCCESSFUL" "$out"; then
                echo "SUCCESS"
                echo "SUCCESS" > "_icbmc_repro/_last_result"
                echo "$k" > "_icbmc_repro/_rounds"
                echo "$vio" > "_icbmc_repro/_vio"
                echo "$commented_lines" > "_icbmc_repro/_commented"
                exit 0
            fi

            if grep -q "VERIFICATION FAILED" "$out"; then
                line=$(extract_violated_line "$out")
                if [ -z "$line" ]; then
                    echo "ERROR: FAILED but could not parse violated line (round $k)"
                    echo "ERROR" > "_icbmc_repro/_last_result"
                    echo "$k" > "_icbmc_repro/_rounds"
                    echo "$vio" > "_icbmc_repro/_vio"
                    echo "$commented_lines" > "_icbmc_repro/_commented"
                    exit 0
                fi
                echo "FAILED line=$line"
                "$PYTHON" "$COMMENT_HELPER" "_icbmc_repro/main.c" "$line"
                helper_rc=$?
                if [ "$helper_rc" -ne 0 ]; then
                    echo "ERROR: failed to comment assert at line $line"
                    echo "ERROR" > "_icbmc_repro/_last_result"
                    echo "$k" > "_icbmc_repro/_rounds"
                    echo "$vio" > "_icbmc_repro/_vio"
                    echo "$commented_lines" > "_icbmc_repro/_commented"
                    exit 0
                fi
                vio=$((vio + 1))
                if [ -z "$commented_lines" ]; then
                    commented_lines="$line"
                else
                    commented_lines="${commented_lines};$line"
                fi
                echo "$commented_lines" > "_icbmc_repro/_commented"
                echo "$vio" > "_icbmc_repro/_vio"
                continue
            fi

            echo "ERROR: no SUCCESS/FAILED in round $k (cbmc exit $rc)"
            echo "ERROR" > "_icbmc_repro/_last_result"
            echo "$k" > "_icbmc_repro/_rounds"
            echo "$vio" > "_icbmc_repro/_vio"
            echo "$commented_lines" > "_icbmc_repro/_commented"
            exit 0
        done

        echo "ERROR: reached max rounds ($MAX_ROUNDS)"
        echo "ERROR" > "_icbmc_repro/_last_result"
        echo "$MAX_ROUNDS" > "_icbmc_repro/_rounds"
        echo "$vio" > "_icbmc_repro/_vio"
        echo "$commented_lines" > "_icbmc_repro/_commented"
    )

    last_result="ERROR"
    [ -f "$WORK_DIR/_last_result" ] && last_result=$(cat "$WORK_DIR/_last_result")
    round=0
    [ -f "$WORK_DIR/_rounds" ] && round=$(cat "$WORK_DIR/_rounds")
    vio=0
    [ -f "$WORK_DIR/_vio" ] && vio=$(cat "$WORK_DIR/_vio")
    commented_lines=""
    [ -f "$WORK_DIR/_commented" ] && commented_lines=$(cat "$WORK_DIR/_commented")

    total_time=0
    if ls "$WORK_DIR"/runtime*.out >/dev/null 2>&1; then
        for rf in "$WORK_DIR"/runtime*.out; do
            sec=$(parse_real_seconds "$rf")
            total_time=$(awk -v a="$total_time" -v b="$sec" 'BEGIN { printf "%.3f", a + b }')
        done
    fi

    val=0
    if [ "$last_result" = "SUCCESS" ]; then
        val=1
    fi

    echo "$DIR,$round,$vio,$val,$total_time,$last_result,${commented_lines:-}" >> "$SUMMARY"
    echo "summary: rounds=$round Vio=$vio Val=$val Time=${total_time}s result=$last_result"
    echo
done

echo "========================================"
echo "Summary written to $SUMMARY"
echo "Log written to $LOGFILE"
