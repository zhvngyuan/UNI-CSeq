typedef int pthread_t;
int global;
// priority 1
void *svp_simple_644_001_isr_1(void *arg) {

  // access(global);
  global++;
  global--;

}

void *main_task(void *arg) {

  disable_isr(1);
  global = 0;
  assert(global == 0);
  enable_isr(1);
  // assert_racefree(global);  

  return 0;
}
int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_644_001_isr_1, 0);
}
