/* Regression: main-task double-read of a shared counter vs ISR increment.
   The two reads of isr_count are not atomic.  After the first snapshot
   equals 1, isr_1 may increment before the second read, so the inner
   check can fail.

   The original scratch used threshold 200 (unreachable under RespCount=2)
   and if (isr_count > 200) then if (isr_count != 200), which is always
   true without an interrupt.  The bound here is 1 so the race is
   reachable.  A sound sequentialization should report a failed assertion
   (VERIFICATION FAILED). */

volatile int isr_count = 0;

// priority 1
void isr_1() {
    isr_count++;
}

int main(void) {
    if (isr_count == 1) {
        if (isr_count != 1) {
            assert(0);
        }
        isr_count = 0;
    }
    return 0;
}
