typedef int pthread_t;
extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }



int glob1;
// priority 1
void *svp_simple_611_001_isr_1(void *arg) {

  glob1 = 5;



  glob1 = 0;


}

void *main_task(void *arg) {
  // pthread_t id;
  // pthread_create(&id, NULL, t_fun, NULL);
  // pthread_mutex_lock(&mutex2);
  glob1 = 0;
  assert(!(glob1 == 5));
  // pthread_mutex_unlock(&mutex2);
  // pthread_join (id, NULL);
  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_611_001_isr_1, 0);
}
