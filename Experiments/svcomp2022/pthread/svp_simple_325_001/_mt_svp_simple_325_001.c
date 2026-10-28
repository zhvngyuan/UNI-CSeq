typedef int pthread_t;

extern void abort(void);

// void reach_error() { assert(0); }

int data1, data2;


// priority 1
void *svp_simple_325_001_isr_1(void *arg)
{  
  data1 = data1+1;
  data2 = data2+1;
 
}

// priority 2
void *svp_simple_325_001_isr_2(void *arg)
{  
  data1 = data1+5;
  data2 = data2-6;
}

void *main_task(void *arg)
{

  data1 = 10;
  data2 = 10;
  if (data1 == 16) { assert(data2 <= 16); }
  
  return 0;
}




int main(){
  pthread_t t0, t1, t2;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_325_001_isr_1, 0);
  pthread_create(&t2, 0, svp_simple_325_001_isr_2, 0);
}
