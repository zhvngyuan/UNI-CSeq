typedef int pthread_t;
extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

extern int __VERIFIER_nondet_int();


int glob1;
// priority 1
void *svp_simple_605_001_isr_1(void *arg) {
  int t = __VERIFIER_nondet_int();

  if(t == 42) {
      glob1 = 1;
  }
  t = glob1;

  assert(t == 0);


  glob1 = 0;

}

void *main_task(void *arg) {
  glob1 = 0;

  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_605_001_isr_1, 0);
}
