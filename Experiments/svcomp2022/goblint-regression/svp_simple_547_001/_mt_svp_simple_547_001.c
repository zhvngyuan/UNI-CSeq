typedef int pthread_t;
int data;
// priority 1
void *svp_simple_547_001_isr_1(void *arg)
{
  int tmp = data + 1;
  data = tmp;
  // data++; // RACE!
}

void *main_task(void *arg)
{
  data = 0;
  assert(data == 0);
  int tmp = data + 1;
  data = tmp;
  // data++; // RACE!

  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_547_001_isr_1, 0);
}
