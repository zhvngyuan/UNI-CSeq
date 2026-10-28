// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }


int A;
int B;

// priority 1
void generate_isr_1() {
  int i;
  for (i=1; i<100; i++) {

    A = i;
    A = 5;

    // sleep(1);
  }
}

// priority 2
void process_isr_2() {
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
void dispose_isr_3() {
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

int main() {
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
