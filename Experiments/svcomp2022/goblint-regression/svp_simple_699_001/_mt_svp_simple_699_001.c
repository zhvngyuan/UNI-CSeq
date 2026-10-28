typedef int pthread_t;

extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

extern int __VERIFIER_nondet_int();


int g; 
// priority 1
void *svp_simple_699_001_isr_1(void *arg) {

  g = 42;
}

void *main_task(void *arg) {
  g = 42;
  int r = __VERIFIER_nondet_int(); 
  int t;
  if (r) {
    g = 17;

  }

  t = g;
  assert(t == 17);

  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_699_001_isr_1, 0);
}
