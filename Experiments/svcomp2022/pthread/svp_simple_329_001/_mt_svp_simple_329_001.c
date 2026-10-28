typedef int pthread_t;

extern void abort(void);
// void reach_error() { assert(0); }

int i, j;


#define NUM 10
#define LIMIT (2*NUM+6)

// priority 1
void *svp_simple_329_001_isr_1(void *arg) {
  for (int k = 0; k < NUM; k++) {
    i = j + 2;
  }
}
// priority 2
void *svp_simple_329_001_isr_2(void *arg) {

  for (int k = 0; k < NUM; k++) {
    j = i + 2;
  }
  j = LIMIT;
  assert(j == LIMIT);
}
void *main_task(void *arg) {

  i = 3;
  j = 6;

  return 0;

}

int main(){
  pthread_t t0, t1, t2;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_329_001_isr_1, 0);
  pthread_create(&t2, 0, svp_simple_329_001_isr_2, 0);
}
