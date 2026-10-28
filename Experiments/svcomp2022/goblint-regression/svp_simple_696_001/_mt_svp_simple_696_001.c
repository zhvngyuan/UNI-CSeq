typedef int pthread_t;

// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }



int g;

// priority 1
void *svp_simple_696_001_isr_1(void *arg) {

  g = 2;
  assert(g == 2);
}

void *main_task(void *arg) {
  int x, y;
  g = 1;
  assert(g == 1);

  int tmp;
  tmp = g-x;
  int tmp1;
  tmp1 = tmp -g;
  g = tmp1;

  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_696_001_isr_1, 0);
}
