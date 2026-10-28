typedef int pthread_t;
extern void abort(void);
// void reach_error() { assert(0); }

int data;


// priority 1
void *svp_simple_304_001_isr_1(void *arg)
{
  int tmp = data +1;
  data = tmp;

}

// priority 2
void *svp_simple_304_001_isr_2(void *arg)
{
  int tmp = data + 2;
  data = tmp;
}

// priority 3
void *svp_simple_304_001_isr_3(void *arg)
{
  int tmp1;
  tmp1 ++;
  assert(data < 3);
}

void *main_task(void *arg)
{
  data = 0;
  return 0;
}


int main(){
  pthread_t t0, t1, t2, t3;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_304_001_isr_1, 0);
  pthread_create(&t2, 0, svp_simple_304_001_isr_2, 0);
  pthread_create(&t3, 0, svp_simple_304_001_isr_3, 0);
}
