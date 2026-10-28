typedef int pthread_t;

int myglobal;
// pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
// priority 1
void *svp_simple_518_001_isr_1(void *arg) {
  myglobal = 0;
  int tmp = myglobal+1;
  myglobal = tmp;
  // myglobal=myglobal+1; // RACE!
  assert(myglobal == 0);

}

int add1 (int x) {
  return x+1;
}

void *main_task(void *arg) {
  myglobal = 0;
  // printf("myglobal equals %dn",myglobal); // RACE!
  assert(myglobal == 0);

  add1(myglobal); 

  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_518_001_isr_1, 0);
}
