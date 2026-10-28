extern void abort(void);
// void reach_error() { assert(0); }

int data;


// priority 1
void svp_simple_304_001_isr_1()
{
  int tmp = data +1;
  data = tmp;

}

// priority 2
void svp_simple_304_001_isr_2()
{
  int tmp = data + 2;
  data = tmp;
}

// priority 3
void svp_simple_304_001_isr_3()
{
  int tmp1;
  tmp1 ++;
  assert(data < 3);
}

int main()
{
  data = 0;
  return 0;
}

