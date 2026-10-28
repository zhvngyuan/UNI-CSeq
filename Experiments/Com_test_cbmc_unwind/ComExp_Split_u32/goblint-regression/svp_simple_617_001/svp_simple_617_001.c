// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

int g2;
// priority 1
void svp_simple_617_001_isr_1() {

  int tmp3, tmp4;
  tmp3 = g2 + 1;
  g2 = tmp3;
  // g2++;

  tmp4 = g2 - 1;
  g2 = tmp4;
  // g2--;

}

int main(void) {
  g2 = 0;
  
  assert(0 <= g2);
  assert(g2 <= 1);
 
  assert(g2 == 0);

  return 0;
}