typedef int pthread_t;
int myglobal;
int debug;
// priority 1
void *svp_simple_538_001_isr_1(void *arg) {
  int tmp;
  tmp=myglobal+1;
  myglobal = tmp;
  // myglobal=myglobal+1; // NORACE

  debug = 3;  

}

void *main_task(void *arg) {
  myglobal = 0;
  debug = 0; 

  int tmp;
  tmp=myglobal+1;
  myglobal = tmp;
  assert(myglobal == 1);
  // myglobal=myglobal+1; // NORACE

  int tmp1;
  tmp1=debug+1;
  debug = tmp1;
  // debug++; // NORACE
  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_538_001_isr_1, 0);
}
