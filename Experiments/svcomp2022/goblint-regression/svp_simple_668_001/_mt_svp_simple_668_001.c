typedef int pthread_t;
int g1,g2;
// priority 1
void *svp_simple_668_001_isr_1(void *arg) {

  // access(g1);
  g1++;
  g1--;
  // access(g2);
  g2++;
  g2--;
}

void *main_task(void *arg) {
  g1 = 0;
  g2 = 0;

  // assert_racefree(g1);
  disable_isr(1);
  assert(g1 == 0);
  assert(g2 == 0);
  enable_isr(1);

  // assert_racefree(g1);
  // assert_racefree(g2);


  // assert_racefree(g1);


  return 0;
}
int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_668_001_isr_1, 0);
}
