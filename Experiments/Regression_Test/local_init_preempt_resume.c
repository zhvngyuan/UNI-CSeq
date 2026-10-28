/* Regression (reviewer resumption of ISR-locals, plus the cnt fragment).
   static locals must keep the state of a preempted flow.  The initializer
   is emitted as an assignment at the declaration point and is not a
   preemption point (no __VERIFIER_nondet_bool suspend on cnt = 0).

   isr_1 contains int cnt=0; cnt++; assert(cnt==1).  Higher-priority isr_2
   may preempt isr_1 only at visible statements (here, the assert).  On
   resume, cnt must still be 0 after the increment's preceding init, so
   assert(cnt == 1) holds.  With RespCount >= 2 this also covers a second
   dispatch of isr_1. */

int g;
int x;

// priority 1
void isr_1() {
    int cnt = 0;
    cnt++;
    assert(cnt == 1);
}

// priority 2
void isr_2() {
    g = 1;
}

int main(void) {
    x = 0;
    return 0;
}