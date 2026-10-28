typedef int pthread_t;
extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }


int A;
int B;

// priority 1
void *generate_isr_1(void *arg) {
  int i;
  for (i=1; i<100; i++) {

    A = i;
    A = 5;

    // sleep(1);
  }
}

// priority 2
void *process_isr_2(void *arg) {
  while (1) {

    if (A > 0) {
      A++;
      B = A;
      B--;
      A--;
    }
    // else
    // sleep(2);
  }
}

// priority 3
void *dispose_isr_3(void *arg) {
  int p;
  while (1) {
    if (B > 0) {
      p = B;
      assert(p == 5);
    }
    // else
    // sleep(5);
  }
}

void *main_task(void *arg) {
  int i, j;
  A = 5;
  B = 5;

  for (i=0; i<10; i++) {
    j = i;
    assert(A == B);
    // pthread_mutex_unlock(&mutex_B);
    // pthread_mutex_unlock(&mutex_A);
    // sleep(3);
  }
  return 0;
}

int main(){
  pthread_t t0, t1, t2, t3;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, generate_isr_1, 0);
  pthread_create(&t2, 0, process_isr_2, 0);
  pthread_create(&t3, 0, dispose_isr_3, 0);
}
