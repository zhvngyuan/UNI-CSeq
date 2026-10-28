typedef int pthread_t;


int myglobal;


void munge() {
  int tmp = myglobal+1;
  myglobal=tmp; 
  // myglobal=myglobal+1; // RACE!

}
void sr_munge() {
  int tmp = myglobal+1;
  myglobal=tmp; 
  // myglobal=myglobal+1; // RACE!

}
// priority 1
void *svp_simple_509_001_isr_1(void *arg) {
  myglobal = 0;
  sr_munge();
  assert(myglobal == 1);
  // return NULL;
}


void *main_task(void *arg) {
  myglobal = 0;

  munge();
  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_509_001_isr_1, 0);
}
