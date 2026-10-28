typedef int pthread_t;
int g1, g2;
// priority 1
void *svp_simple_537_001_isr_1(void *arg) {
  int tmp1 = g1+1;
  g1 = tmp1;
  // g1++; 

  int tmp2 = g2+1;
  g2 = tmp2;
  // g2++; 

}

void *main_task(void *arg) {
  g1 = 0;
  g2 = 0;
  g1 = g2 + 1; 
  assert(g2 == 1);

  return 0;
}


int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_537_001_isr_1, 0);
}
