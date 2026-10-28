
// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }



int g; 
// priority 1
void svp_simple_627_001_isr_1() {
  // pthread_mutex_lock(&D);
  // pthread_mutex_lock(&A);
  g = 1;
  // pthread_mutex_unlock(&A);
  g = 2;
  assert(g == 2);
  // pthread_mutex_unlock(&D);
  // return NULL;
}

int main(void) {
  // pthread_t id;
  // pthread_create(&id, NULL, t_fun, NULL);

  // pthread_mutex_lock(&D);
  // pthread_mutex_lock(&A);
  // pthread_mutex_unlock(&D);
  g = 2; 
  
  return 0;
}
