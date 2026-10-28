extern void abort(void);
// void reach_error() { assert(0); }

int  num;

// priority 1
void svp_simple_326_001_isr_1()
{

  while (num > 0) {
    assert(num > 0);
    num = num-1;
  } 
}

// priority 2
void svp_simple_326_001_isr_2()
{

  while (num == 0) {
    num = num-1;
  } 

}

int main()
{

  num = 1;

  return 0;
}
