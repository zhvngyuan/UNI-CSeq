typedef int pthread_t;
extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

int g2;
// priority 1
void *svp_simple_617_001_isr_1(void *arg) {

  int tmp3, tmp4;
  tmp3 = g2 + 1;
  g2 = tmp3;
  // g2++;

  tmp4 = g2 - 1;
  g2 = tmp4;
  // g2--;

}

void *main_task(void *arg) {
  g2 = 0;
  
  assert(0 <= g2);
  assert(g2 <= 1);
 
  assert(g2 == 0);

  return 0;
}
int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_617_001_isr_1, 0);
}
