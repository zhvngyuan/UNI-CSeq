typedef int pthread_t;
extern void abort(void);
// void reach_error() { assert(0); }

int  num;

// priority 1
void *svp_simple_326_001_isr_1(void *arg)
{

  while (num > 0) {
    assert(num > 0);
    num = num-1;
  } 
}

// priority 2
void *svp_simple_326_001_isr_2(void *arg)
{

  while (num == 0) {
    num = num-1;
  } 

}

void *main_task(void *arg)
{

  num = 1;

  return 0;
}

int main(){
  pthread_t t0, t1, t2;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_326_001_isr_1, 0);
  pthread_create(&t2, 0, svp_simple_326_001_isr_2, 0);
}
