// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

int glob1;
// priority 1
void svp_simple_609_001_isr_1() {

  glob1 = 5;

  glob1 = 0;

}

int main(void) {
  glob1 = 0;
  assert(!(glob1 == 0));

  return 0;
}
