extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond)
{
  if (!(cond))
  {
  ERROR:
  {
    reach_error();
    abort();
  }
  }
}

int g;
// priority 1
void svp_simple_636_001_isr_1()
{
  if (g == 1)
    g = 3;
}

int main()
{
  g = 0;
  g = 1;

  g = 2;

  assert(g == 2);
  return 0;
}
