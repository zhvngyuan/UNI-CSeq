typedef int pthread_t;

extern int __VERIFIER_nondet_int();

int myglobal;


void sr_fun(void) {
  int i = __VERIFIER_nondet_int();
  int tmp;
  tmp = myglobal+1;
  myglobal=tmp; 
  // myglobal=myglobal+1; 
}
// priority 1
void *svp_simple_505_001_isr_1(void *arg) {
  myglobal = 0;
  // myglobal=myglobal+1; 
  int tmp = myglobal+1;
  myglobal = tmp; 

  sr_fun();
  assert(myglobal == 2);

}

void *main_task(void *arg) {
  myglobal = 0;
  // myglobal=myglobal+1;
  int tmp = myglobal+1;
  myglobal=tmp; 


  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_505_001_isr_1, 0);
}
