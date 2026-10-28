// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

int g; 
// priority 1
void svp_simple_621_001_isr_1() {
  g = 42;
}

int main(void) {
  g = 2;
  assert(g == 2);
  return 0;
}
