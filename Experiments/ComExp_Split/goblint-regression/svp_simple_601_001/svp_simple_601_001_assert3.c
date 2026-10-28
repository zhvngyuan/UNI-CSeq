
int x;
// priority 1
void svp_simple_601_001_isr_1()
{

  if (x == 1)
  { 
    x = 0;
//     assert(x == 0);
  }

  x = -1; 
}

int main(void)
{
  x = 1;
//   assert(x == 1);

  x = 0; 
  assert(x == 0);
  x = 1; 

  return 0;
}
