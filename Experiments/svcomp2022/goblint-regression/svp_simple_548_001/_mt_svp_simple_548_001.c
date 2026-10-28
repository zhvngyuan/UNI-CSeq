typedef int pthread_t;
int data;
// priority 1
void *svp_simple_548_001_isr_1(void *arg)
{
  data = 0;
  data++; 
  assert(data == 1);
}

void *main_task(void *arg)
{
  data = 0;
  data++; 
  

  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_548_001_isr_1, 0);
}
