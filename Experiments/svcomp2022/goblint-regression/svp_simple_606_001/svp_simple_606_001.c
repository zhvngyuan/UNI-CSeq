extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

extern int __VERIFIER_nondet_int();



int glob1;
// priority 1
void svp_simple_606_001_isr_1() {
  int t = __VERIFIER_nondet_int();

  if(t == 42) {
      glob1 = 1;
  }
  t = glob1;

  assert(!(t == 1));

  glob1 = 0;

}

int main(void) {
  glob1 = 0;

  return 0;
}
