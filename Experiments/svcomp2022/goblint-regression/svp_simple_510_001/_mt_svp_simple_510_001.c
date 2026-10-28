typedef int pthread_t;


int myglobal;


void munge() {

  myglobal=myglobal+1; 

}
// priority 1
void *svp_simple_510_001_isr_1(void *arg) {
  myglobal = 0;
  munge();

}


void *main_task(void *arg) {
  myglobal = 0;

  munge();
  assert(myglobal == 1);

  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_510_001_isr_1, 0);
}
