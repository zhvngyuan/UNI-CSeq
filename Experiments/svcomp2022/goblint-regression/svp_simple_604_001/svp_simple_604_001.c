extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

extern int __VERIFIER_nondet_int();


int glob1;
// priority 1
void svp_simple_604_001_isr_1() {
  int t = __VERIFIER_nondet_int();

  if(t == 42) {
      glob1 = 1;
  }
  t = glob1;


  glob1 = t;
}

int main(void) {
  glob1 = 0;
  assert(glob1 == 0);
  return 0;
}
