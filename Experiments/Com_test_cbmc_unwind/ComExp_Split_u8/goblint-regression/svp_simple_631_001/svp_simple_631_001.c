
// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }



int g; 
// priority 1
void svp_simple_631_001_isr_1() {

  g = 1;

  g = 2;

  g = 3;

}

int main(void) {
  g = 3;
  assert(g == 3);

  // assert(g == 3);
  return 0;
}
