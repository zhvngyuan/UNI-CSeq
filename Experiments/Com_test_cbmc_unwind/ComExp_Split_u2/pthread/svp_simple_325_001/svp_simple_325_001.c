
extern void abort(void);

// void reach_error() { assert(0); }

int data1, data2;


// priority 1
void svp_simple_325_001_isr_1()
{  
  data1 = data1+1;
  data2 = data2+1;
 
}

// priority 2
void svp_simple_325_001_isr_2()
{  
  data1 = data1+5;
  data2 = data2-6;
}

int main()
{

  data1 = 10;
  data2 = 10;
  if (data1 == 16) { assert(data2 <= 16); }
  
  return 0;
}



