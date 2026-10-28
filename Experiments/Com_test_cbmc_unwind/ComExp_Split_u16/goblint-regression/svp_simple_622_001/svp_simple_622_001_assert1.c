// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

extern int __VERIFIER_nondet_int();

int g;
// priority 1
void svp_simple_622_001_isr_1()
{

  g = 15;

  g = 42;
}

int main(void)
{
  g = 42;
  assert(g == 42);
  return 0;
}
