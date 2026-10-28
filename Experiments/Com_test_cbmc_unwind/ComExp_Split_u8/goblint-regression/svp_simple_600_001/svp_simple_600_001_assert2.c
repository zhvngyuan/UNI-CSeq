// extern void abort(void);
// void reach_error() { assert(0); }


// void __VERIFIER_assert(int cond)
// {
//   if (!(cond))
//   {
//   ERROR:
//   {
//     reach_error();
//     abort();
//   }
//   }
// }

int glob1 = 5;



// priority 1
void svp_simple_600_001_isr_1()
{
  int t;
  t = glob1;
//   assert(t == 5);
  glob1 = -10;
  assert(glob1 == -10);
  glob1 = t;
}

int main(void)
{

//   assert(glob1 == 5);
  int tmp = glob1 + 1;
  glob1 = tmp;
  // glob1++;
//   assert(glob1 == 6);
  int tmp1 = glob1 - 1;
  glob1 = tmp1;
  // glob1--;

  return 0;
}

