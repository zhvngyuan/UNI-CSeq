typedef int pthread_t;

int myglobal;


// priority 1
void *svp_simple_511_001_isr_1(void *arg) {
  // lock();
  myglobal++; 
  // unlock();

}


void *main_task(void *arg) {
  // pthread_t id;
  // pthread_create(&id, NULL, t_fun, NULL);
  // lock();
  disable_isr(1);
  myglobal = 0;
  myglobal++; 
  assert(myglobal == 1);
  enable_isr(1);
  // unlock();
  // pthread_join (id, NULL);
  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_511_001_isr_1, 0);
}
