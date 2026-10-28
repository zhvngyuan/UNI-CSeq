typedef int pthread_t;


int x;
// priority 1
void *svp_simple_529_001_isr_1(void *arg) {
  x = 0;
  int tmp = x+1;
  x = tmp;
  assert(x == 1);
  // x++; // RACE!

}

void *main_task(void *arg) {
  x = 0;
  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_529_001_isr_1, 0);
}
