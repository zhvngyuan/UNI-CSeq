typedef int pthread_t;
extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}


extern int __VERIFIER_nondet_int();


int plus(int a, int b);
int sr_plus(int a, int b);

int g;
int h;
int i;

// priority 1
void *svp_simple_702_001_isr_1(void *arg) {
  int x = __VERIFIER_nondet_int(); 
  int y = __VERIFIER_nondet_int(); 
  int z = __VERIFIER_nondet_int(); 
  if (x < 1000) { 
    x = g;
    y = h;
    assert(y <= x);

    assert(x == y);

    i = plus(x, 31);
    z = i;
    assert(z >= x);

  }

}

void *main_task(void *arg) {
  g = 0;
  h = 0;
  i = 0;
  int x = __VERIFIER_nondet_int(); 
  if (x > -1000) { 

    i = 11;
    g = x;
    h = plus(x, - 17);
 
    h = x;

    i = 3;

  }
  return 0;
}

int plus(int a, int b) {
  assume_abort_if_not(b >= 0 || a >= -2147483648 - b);
  assume_abort_if_not(b <= 0 || a <= 2147483647 - b);
  return a + b;
}
int sr_plus(int a, int b) {
  assume_abort_if_not(b >= 0 || a >= -2147483648 - b);
  assume_abort_if_not(b <= 0 || a <= 2147483647 - b);
  return a + b;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_702_001_isr_1, 0);
}
