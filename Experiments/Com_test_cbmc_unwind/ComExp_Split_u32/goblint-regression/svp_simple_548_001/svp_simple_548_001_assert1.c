int data;
// priority 1
void svp_simple_548_001_isr_1()
{
  data = 0;
  data++; 
  assert(data == 1);
}

int main()
{
  data = 0;
  data++; 
  

  return 0;
}
