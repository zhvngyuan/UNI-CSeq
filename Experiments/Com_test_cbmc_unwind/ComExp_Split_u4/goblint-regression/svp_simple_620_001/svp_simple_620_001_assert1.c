// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

int g;
// priority 1
void svp_simple_620_001_isr_1() {

  g = 5;

  g = 0;

}

int main(void) {
  g = 0;
  assert(g == 0);

//   assert(g == 0);

  return 0;
}
