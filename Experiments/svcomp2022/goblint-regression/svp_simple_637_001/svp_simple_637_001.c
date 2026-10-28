extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

int g;
// priority 1
void svp_simple_637_001_isr_1() {
  int tmp;
  tmp = 1;

}

int main() {

  g = 0;
  g = 1;
  // pthread_mutex_unlock(&A); // singlethreaded mode unlock

  g = 2;

  // pthread_mutex_lock(&A);

  // pthread_t id;
  // pthread_create(&id, NULL, t_fun, NULL); // enter multithreaded mode with nonempty lockset

  g = 3; // write under mutex which was locked during singlethreaded mode
  assert(g == 3);
  return 0;
}
