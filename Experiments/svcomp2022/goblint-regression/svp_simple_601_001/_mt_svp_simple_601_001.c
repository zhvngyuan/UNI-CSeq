typedef int pthread_t;

int x;
// priority 1
void *svp_simple_601_001_isr_1(void *arg)
{

  if (x == 1)
  { 
    x = 0;
    assert(x == 0);
  }

  x = -1; 
}

void *main_task(void *arg)
{
  x = 1;
  assert(x == 1);

  x = 0; 
  assert(x == 0);
  x = 1; 

  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_601_001_isr_1, 0);
}
