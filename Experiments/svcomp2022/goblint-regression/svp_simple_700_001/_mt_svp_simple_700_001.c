typedef int pthread_t;

extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

extern int __VERIFIER_nondet_int();



int g;
int h;

// priority 1
void *svp_simple_700_001_isr_1(void *arg) {
  int x = __VERIFIER_nondet_int(); 
  if (x > -1000) { 
    g = x;
    h = x - 17;
   
    h = x;
   
  }
 
}
// priority 2
void *svp_simple_700_001_isr_2(void *arg) {
  int x = __VERIFIER_nondet_int(); 
  int y = __VERIFIER_nondet_int(); 
 
  x = g;
  y = h;
  
  assert(y <= x);
 
}
// priority 3
void *svp_simple_700_001_isr_3(void *arg) {
  int x = __VERIFIER_nondet_int(); 
  int y = __VERIFIER_nondet_int(); 
 
  x = g;
  y = h;

  assert(y == x);

}

void *main_task(void *arg) {
  g = 42;
  h = 42;
  int x = __VERIFIER_nondet_int(); 
  int y = __VERIFIER_nondet_int(); 

 
  x = g;
  y = h;
 
  assert(y == x);

  assert(y == x);
  return 0;
}

int main(){
  pthread_t t0, t1, t2, t3;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_700_001_isr_1, 0);
  pthread_create(&t2, 0, svp_simple_700_001_isr_2, 0);
  pthread_create(&t3, 0, svp_simple_700_001_isr_3, 0);
}
