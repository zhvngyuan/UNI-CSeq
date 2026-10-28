/* Regression: a local declared inside a loop is re-initialized on every
   iteration (not only once as a C static).

   isr_1 runs while (k < 5) with int t = 0; t++; assert(t == 1) in the body.
   Sequentialization should emit a static declaration of t without an
   initializer and a runtime t = 0 on each iteration (and the same for k
   at each dispatch; use RespCount >= 2).  Treating t as static int t = 0
   initializes it only once: later iterations accumulate and the assert
   fails (false alarm).  A sound encoding reports VERIFICATION SUCCESSFUL. */

int g;
int x;

// priority 1
void isr_1() {
    int k = 0;
    while (k < 5) {
        int t = 0;
        t++;
        g = k;
        assert(t == 1);
        k++;
    }
    
    
}

int main(void) {
    x = 0;
    return 0;
}