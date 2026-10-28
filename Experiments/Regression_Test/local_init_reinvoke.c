/* Regression (reviewer failure mode 1: initialized ISR-local on re-dispatch).
   A completed isr_1 may be dispatched again (use RespCount >= 2).  Automatic
   locals must be re-established at the declaration point: static storage is
   only for resumption, not a once-per-program C initializer.

   isr_1 is int cnt = 0; cnt++; assert(cnt == 1).  Sequentialization should
   emit a static declaration without an initializer and a runtime cnt = 0
   on every dispatch, so the assert holds on the second response.  Leaving
   static int cnt = 0 (initialized once) makes the second response start
   from cnt == 1; cnt++ then yields 2 and the assert fails (false alarm). */

int g;
int x;

// priority 1
void isr_1() {
    int cnt = 0; 
    cnt++;
    assert(cnt == 1);   
}

int main(void) { x = 0; return 0; }