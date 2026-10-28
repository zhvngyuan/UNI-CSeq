#!/bin/bash
# Run the ISR-local regression tests (re-dispatch init / uninit havoc / resume / loop-local).
# Usage: ./run_local_regression_test.sh [timelimit_in_seconds] [unwind]
# Output: this directory's test_result.txt (terminal is also shown).

if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    echo "Usage: $0 [timelimit_in_seconds] [unwind]"
    echo "  timelimit  default 60"
    echo "  unwind     default 8  (scheduler while(1) needs >1; local_init_loop needs >=5)"
    echo "Requires python2 (conda env py27) and cbmc on PATH."
    exit 0
fi

TIMELIMIT="${1:-60}"
UNWIND="${2:-8}"
BACKEND="cbmc"
RESPCOUNT=2

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
UNICHECKER="$PROJECT_ROOT/unichecker.py"
RESULT_FILE="$SCRIPT_DIR/test_result.txt"

if [ ! -f "$UNICHECKER" ]; then
    echo "error: unichecker.py not found at $UNICHECKER"
    exit 1
fi

START_TIME=$(date "+%Y年%-m月%-d日%H:%M")
CMD_LINE="$0 $*"

# Rewrite the result file, then duplicate stdout/stderr to it.
{
    echo "$START_TIME, $CMD_LINE"
    echo "PROJECT_ROOT=$PROJECT_ROOT"
    echo "backend=$BACKEND unwind=$UNWIND timelimit=$TIMELIMIT RespCount=$RESPCOUNT"
    echo "========================================"
} > "$RESULT_FILE"
exec > >(tee -a "$RESULT_FILE") 2>&1

PASS_COUNT=0
FAIL_COUNT=0
declare -a SUMMARY_NAMES
declare -a SUMMARY_STATUS
declare -a SUMMARY_REASON

seqfile_for() {
    local src="$1"
    local base
    base="$(basename "$src")"
    echo "$SCRIPT_DIR/_cseq_${BACKEND}_${base}"
}

log_for() {
    echo "$(seqfile_for "$1").${BACKEND}.log"
}

# Return 0 if any of the N lines before the first match of PATTERN contain needle.
lines_before_match_contain() {
    local file="$1"
    local pattern="$2"
    local needle="$3"
    local n="${4:-4}"
    local lineno start
    lineno=$(grep -n -E "$pattern" "$file" 2>/dev/null | head -1 | cut -d: -f1)
    if [ -z "$lineno" ]; then
        return 2
    fi
    start=$((lineno - n))
    if [ "$start" -lt 1 ]; then
        start=1
    fi
    sed -n "${start},${lineno}p" "$file" | grep -q -E "$needle"
}

# Return 0 if any of the N lines before LINENO contain needle.
lines_before_lineno_contain() {
    local file="$1"
    local lineno="$2"
    local needle="$3"
    local n="${4:-4}"
    local start
    if [ -z "$lineno" ]; then
        return 2
    fi
    start=$((lineno - n))
    if [ "$start" -lt 1 ]; then
        start=1
    fi
    sed -n "${start},${lineno}p" "$file" | grep -q -E "$needle"
}

# Absolute line numbers of isr_1 payload statements (local ops / assert / error).
isr_1_payload_linenos() {
    local file="$1"
    awk '
        /^void isr_1\(/ { p=1 }
        p && /^}/ { exit }
        p && /static[[:space:]]/ { next }
        p && /__cs_init_scalar/ { next }
        p && /(__cs_l_isr_1_|assert\(|__cseq_error)/ { print NR }
    ' "$file"
}

record() {
    local name="$1"
    local status="$2"
    local reason="$3"
    SUMMARY_NAMES+=("$name")
    SUMMARY_STATUS+=("$status")
    SUMMARY_REASON+=("$reason")
    if [ "$status" = "PASS" ]; then
        PASS_COUNT=$((PASS_COUNT + 1))
        echo "[PASS] $name: $reason"
    else
        FAIL_COUNT=$((FAIL_COUNT + 1))
        echo "[FAIL] $name: $reason"
    fi
}

judge_common() {
    # Sets JUDGE_SEQ, JUDGE_LOG, JUDGE_REASON in the current shell.
    # Must NOT be called inside $() — that would run in a subshell and
    # leave JUDGE_SEQ / JUDGE_LOG empty in the caller (grep: : No such file).
    local src="$1"
    local rc="$2"
    JUDGE_REASON=""
    JUDGE_SEQ="$(seqfile_for "$src")"
    JUDGE_LOG="$(log_for "$src")"
    if [ "$rc" -ne 0 ]; then
        JUDGE_REASON="unichecker exit code $rc"
        return 1
    fi
    if [ ! -f "$JUDGE_SEQ" ]; then
        JUDGE_REASON="sequentialized file missing ($JUDGE_SEQ)"
        return 1
    fi
    if [ ! -f "$JUDGE_LOG" ]; then
        JUDGE_REASON="CBMC log missing ($JUDGE_LOG)"
        return 1
    fi
    if grep -q "PARSING ERROR" "$JUDGE_LOG"; then
        JUDGE_REASON="CBMC PARSING ERROR in $JUDGE_LOG"
        return 1
    fi
    return 0
}

run_and_get_rc() {
    local src="$1"
    python2 "$UNICHECKER" -i "$src" -b "$BACKEND" -u "$UNWIND" --timelimit "$TIMELIMIT" --RespCount "$RESPCOUNT"
    return $?
}

judge_reinvoke() {
    local src="$1"
    local rc="$2"
    local name
    name="$(basename "$src")"
    if ! judge_common "$src" "$rc"; then
        record "$name" "FAIL" "$JUDGE_REASON"
        return
    fi
    if ! grep -q "VERIFICATION SUCCESSFUL" "$JUDGE_LOG"; then
        record "$name" "FAIL" "CBMC log has no VERIFICATION SUCCESSFUL ($JUDGE_LOG)"
        return
    fi
    if grep -E 'static[[:space:]]+int[[:space:]]+[^;]*cnt[^;]*=[[:space:]]*0' "$JUDGE_SEQ" >/dev/null; then
        record "$name" "FAIL" "static cnt still has a declaration initializer"
        return
    fi
    if ! grep -E '__cs_l_isr_1_cnt_[0-9]+ = 0' "$JUDGE_SEQ" >/dev/null; then
        record "$name" "FAIL" "no runtime cnt = 0 assignment in sequentialized code"
        return
    fi
    record "$name" "PASS" "SUCCESSFUL; runtime cnt=0; static decl has no =0"
}

judge_uninit() {
    local src="$1"
    local rc="$2"
    local name
    name="$(basename "$src")"
    if ! judge_common "$src" "$rc"; then
        record "$name" "FAIL" "$JUDGE_REASON"
        return
    fi
    if grep -q "VERIFICATION SUCCESSFUL" "$JUDGE_LOG"; then
        record "$name" "FAIL" "SUCCESSFUL, but havoc'd cnt should make assert(0) reachable ($JUDGE_LOG)"
        return
    fi
    if ! grep -q "VERIFICATION FAILED" "$JUDGE_LOG"; then
        record "$name" "FAIL" "CBMC log has no VERIFICATION FAILED ($JUDGE_LOG)"
        return
    fi
    if ! grep -q "__cs_init_scalar" "$JUDGE_SEQ"; then
        record "$name" "FAIL" "sequentialized code has no __cs_init_scalar ($JUDGE_SEQ)"
        return
    fi
    if ! grep -E '__cs_init_scalar\(&__cs_l_isr_1_cnt_[0-9]+' "$JUDGE_SEQ" >/dev/null; then
        record "$name" "FAIL" "no __cs_init_scalar of cnt"
        return
    fi
    record "$name" "PASS" "FAILED as expected; __cs_init_scalar havoc of cnt"
}

judge_loop() {
    local src="$1"
    local rc="$2"
    local name
    name="$(basename "$src")"
    if ! judge_common "$src" "$rc"; then
        record "$name" "FAIL" "$JUDGE_REASON"
        return
    fi
    if ! grep -q "VERIFICATION SUCCESSFUL" "$JUDGE_LOG"; then
        record "$name" "FAIL" "CBMC log has no VERIFICATION SUCCESSFUL ($JUDGE_LOG)"
        return
    fi
    if grep -E 'static[[:space:]]+int[[:space:]]+[^;]*t[^;]*=[[:space:]]*0' "$JUDGE_SEQ" >/dev/null; then
        record "$name" "FAIL" "static t still has a declaration initializer"
        return
    fi
    if ! grep -E '__cs_l_isr_1_t_[0-9]+ = 0' "$JUDGE_SEQ" >/dev/null; then
        record "$name" "FAIL" "no runtime t = 0 assignment in sequentialized code"
        return
    fi
    if ! grep -E '__cs_l_isr_1_k_[0-9]+ = 0' "$JUDGE_SEQ" >/dev/null; then
        record "$name" "FAIL" "no runtime k = 0 assignment in sequentialized code"
        return
    fi
    record "$name" "PASS" "SUCCESSFUL; runtime t=0 each iteration; static decl has no =0"
}

judge_preempt_resume() {
    local src="$1"
    local rc="$2"
    local name
    name="$(basename "$src")"
    if ! judge_common "$src" "$rc"; then
        record "$name" "FAIL" "$JUDGE_REASON"
        return
    fi
    if ! grep -q "VERIFICATION SUCCESSFUL" "$JUDGE_LOG"; then
        record "$name" "FAIL" "CBMC log has no VERIFICATION SUCCESSFUL ($JUDGE_LOG)"
        return
    fi
    if ! grep -E '__cs_l_isr_1_cnt_[0-9]+ = 0' "$JUDGE_SEQ" >/dev/null; then
        record "$name" "FAIL" "no runtime cnt = 0 assignment"
        return
    fi
    # Local assignments may sit on a preemption probe when they are the first or
    # last statement of isr_1 (pc==0 means suspend-before-execute, which matches
    # nested-interrupt entry). A middle local op must not have nondet.
    local payloads first last ln assert_ln
    payloads="$(isr_1_payload_linenos "$JUDGE_SEQ")"
    if [ -z "$payloads" ]; then
        record "$name" "FAIL" "could not find isr_1 payload statements"
        return
    fi
    first=$(printf '%s\n' "$payloads" | head -1)
    last=$(printf '%s\n' "$payloads" | tail -1)
    while IFS= read -r ln; do
        [ -z "$ln" ] && continue
        if sed -n "${ln}p" "$JUDGE_SEQ" | grep -qE 'assert\(|__cseq_error'; then
            continue
        fi
        if [ "$ln" = "$first" ] || [ "$ln" = "$last" ]; then
            continue
        fi
        if lines_before_lineno_contain "$JUDGE_SEQ" "$ln" '__VERIFIER_nondet_bool' 4; then
            record "$name" "FAIL" "local op at line $ln is a middle statement but wrapped in a preemption nondet"
            return
        fi
    done <<< "$payloads"
    # Assert (or __cseq_error rewrite) inside isr_1 must remain a preemption point.
    assert_ln=$(awk '
        /^void isr_1\(/ { p=1 }
        p && /^}/ { exit }
        p && /(assert\(|__cseq_error)/ { print NR; exit }
    ' "$JUDGE_SEQ")
    if [ -z "$assert_ln" ]; then
        record "$name" "FAIL" "could not find assert in sequentialized isr_1"
        return
    fi
    if ! lines_before_lineno_contain "$JUDGE_SEQ" "$assert_ln" '__VERIFIER_nondet_bool' 4; then
        record "$name" "FAIL" "assert is not wrapped in a preemption nondet"
        return
    fi
    record "$name" "PASS" "SUCCESSFUL; middle local ops not preemptable; first/last stmt preempt OK; assert still preemptable"
}

echo "******** Execute Analysis with $BACKEND ********"

SRC1="$SCRIPT_DIR/local_init_reinvoke.c"
SRC2="$SCRIPT_DIR/local_uninit_reinvoke.c"
SRC3="$SCRIPT_DIR/local_init_preempt_resume.c"
SRC4="$SCRIPT_DIR/local_init_loop.c"

echo ""
echo "========== Checking $(basename "$SRC1") =========="
echo "File path: $SRC1"
run_and_get_rc "$SRC1"
RC1=$?
echo "(unichecker exit code: $RC1)"
judge_reinvoke "$SRC1" "$RC1"

echo ""
echo "========== Checking $(basename "$SRC2") =========="
echo "File path: $SRC2"
run_and_get_rc "$SRC2"
RC2=$?
echo "(unichecker exit code: $RC2)"
judge_uninit "$SRC2" "$RC2"

echo ""
echo "========== Checking $(basename "$SRC3") =========="
echo "File path: $SRC3"
run_and_get_rc "$SRC3"
RC3=$?
echo "(unichecker exit code: $RC3)"
judge_preempt_resume "$SRC3" "$RC3"

echo ""
echo "========== Checking $(basename "$SRC4") =========="
echo "File path: $SRC4"
run_and_get_rc "$SRC4"
RC4=$?
echo "(unichecker exit code: $RC4)"
judge_loop "$SRC4" "$RC4"

echo ""
echo "========================================"
echo "Summary: $PASS_COUNT/4 passed, $FAIL_COUNT failed"
i=0
while [ "$i" -lt "${#SUMMARY_NAMES[@]}" ]; do
    echo "  ${SUMMARY_STATUS[$i]}  ${SUMMARY_NAMES[$i]}  --  ${SUMMARY_REASON[$i]}"
    i=$((i + 1))
done
echo "Full transcript: $RESULT_FILE"

if [ "$FAIL_COUNT" -ne 0 ]; then
    exit 1
fi
exit 0