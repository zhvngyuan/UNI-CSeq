typedef int pthread_t;
int myglobal;
// priority 1
void *svp_simple_504_001_isr_1(void *arg) {
  myglobal = 0;
  int tmp;
  tmp = myglobal+1;
  myglobal=tmp;
  assert(myglobal == 1); 
  // myglobal = myglobal+1
}

void *main_task(void *arg) {
  int tmp = myglobal+1;
  myglobal=tmp; 
  //myglobal = myglobal+1
  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_504_001_isr_1, 0);
}
