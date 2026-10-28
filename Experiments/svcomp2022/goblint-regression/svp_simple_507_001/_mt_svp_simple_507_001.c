typedef int pthread_t;


int myglobal;
// priority 1
void *svp_simple_507_001_isr_1(void *arg)
{
  int tmp = myglobal + 1;
  myglobal = tmp;
  // myglobal=myglobal+1; // RACE!
}

void *main_task(void *arg)
{
  myglobal = 0;
  int tmp = myglobal + 1;
  myglobal = tmp;
  assert(myglobal == 1);
  // myglobal=myglobal+1; // RACE!
}
int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_507_001_isr_1, 0);
}
