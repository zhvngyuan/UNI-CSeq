/* Regression (reviewer failure mode 2: uninitialized ISR-local on re-dispatch).
   int cnt has no initializer, so a fresh ISR instance must havoc cnt at the
   declaration point.  Sequentialized code should contain
   __cs_init_scalar(&cnt, ...) (or the renamed local) with no extra preemption
   nondet on that statement.

   if (cnt) assert(0) is reachable once cnt is havoc'd, so a sound encoding
   reports VERIFICATION FAILED.  The old encoding (static zero-init, or
   retaining the previous response's cnt) keeps cnt == 0, skips the assert,
   and yields a false-negative SUCCESSFUL. */


int x;

// priority 1
void isr_1() {
    int cnt;
    if(cnt) {
        assert(0);
    }
}

int main(void) {
    x = 0;
    return 0;
}