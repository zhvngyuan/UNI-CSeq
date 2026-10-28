
// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }



int g;

// priority 1
void svp_simple_696_001_isr_1() {

  g = 2;
  assert(g == 2);
}

int main(void) {
  int x, y;
  g = 1;
//   assert(g == 1);

  int tmp;
  tmp = g-x;
  int tmp1;
  tmp1 = tmp -g;
  g = tmp1;

  return 0;
}
