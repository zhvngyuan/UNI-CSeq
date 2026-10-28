// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

extern int __VERIFIER_nondet_int();



int g;
int h;
int i;

// priority 1
void svp_simple_701_001_isr_1() {
  int x = __VERIFIER_nondet_int(); //rand
  int y = __VERIFIER_nondet_int(); //rand
  int z = __VERIFIER_nondet_int(); //rand
  if (x < 1000) { 
    x = g;
    y = h;
    assert(y <= x);
    
//     assert(x == y);
   
    i = x + 31;
    z = i;
//     assert(z >= x);

  }

}

int main(void) {
  g = 0;
  h = 0;
  i = 0;
  int x = __VERIFIER_nondet_int(); 
  if (x > -1000) { 

    i = 11;
    g = x;
    h = x - 17;

    h = x;

    i = 3;

  }
  return 0;
}
