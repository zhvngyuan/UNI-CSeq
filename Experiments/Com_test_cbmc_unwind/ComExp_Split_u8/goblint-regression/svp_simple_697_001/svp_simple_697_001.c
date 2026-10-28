
// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

extern int nondet_int();


int g;
// priority 1
void svp_simple_697_001_isr_1() {
    g=1;
}

int main(void) {
  int x = __VERIFIER_nondet_int(); // rand
  int y = __VERIFIER_nondet_int(); //rand
  int r = __VERIFIER_nondet_int(); //rand

  g = r;

  x = g;
  y = g;
  assert(x == y);
  return 0;
}
