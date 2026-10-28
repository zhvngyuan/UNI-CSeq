typedef int pthread_t;

extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

extern int nondet_int();


int g;
// priority 1
void *svp_simple_697_001_isr_1(void *arg) {
    g=1;
}

void *main_task(void *arg) {
  int x = __VERIFIER_nondet_int(); 
  int y = __VERIFIER_nondet_int(); 
  int r = __VERIFIER_nondet_int(); 

  g = r;

  x = g;
  y = g;
  assert(x == y);
  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_697_001_isr_1, 0);
}
