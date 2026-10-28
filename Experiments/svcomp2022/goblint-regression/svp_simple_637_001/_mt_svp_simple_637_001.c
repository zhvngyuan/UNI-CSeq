typedef int pthread_t;
extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

int g;
// priority 1
void *svp_simple_637_001_isr_1(void *arg) {
  int tmp;
  tmp = 1;

}

void *main_task(void *arg) {

  g = 0;
  g = 1;
  // pthread_mutex_unlock(&A); // singlethreaded mode unlock

  g = 2;

  // pthread_mutex_lock(&A);

  // pthread_t id;
  // pthread_create(&id, NULL, t_fun, NULL); // enter multithreaded mode with nonempty lockset

  g = 3; 
  assert(g == 3);
  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_637_001_isr_1, 0);
}
