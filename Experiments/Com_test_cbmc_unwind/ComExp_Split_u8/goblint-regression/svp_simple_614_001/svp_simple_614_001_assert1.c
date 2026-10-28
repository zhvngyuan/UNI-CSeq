// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

int g1,g2;
// priority 1
void svp_simple_614_001_isr_1()
{
  int tmp1 = g1 + 1;
  g1 = tmp1;
  // g1++;

  int tmp2 = g1 - 1;
  g1 = tmp2;
  // g1--;

  int tmp3 = g2 + 1;
  g2 = tmp3;
  // g2++;

  int tmp4 = g2 - 1;
  g2 = tmp4;
  // g2--;
}

int main(void)
{
  g1 = 0;
  assert(g1 == 0);
  g2 = 0;

  // assert(g1 == 0);
//   assert(g2 == 0);

  // assert(g1 == 0);

  return 0;
}
