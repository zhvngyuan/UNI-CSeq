
// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

extern int __VERIFIER_nondet_int();



int g;
int h;

// priority 1
void svp_simple_700_001_isr_1() {
  int x = __VERIFIER_nondet_int(); //rand
  if (x > -1000) { 
    g = x;
    h = x - 17;
   
    h = x;
   
  }
 
}
// priority 2
void svp_simple_700_001_isr_2() {
  int x = __VERIFIER_nondet_int(); 
  int y = __VERIFIER_nondet_int(); 
 
  x = g;
  y = h;
  
//   assert(y <= x);
 
}
// priority 3
void svp_simple_700_001_isr_3() {
  int x = __VERIFIER_nondet_int(); 
  int y = __VERIFIER_nondet_int(); 
 
  x = g;
  y = h;

  assert(y == x);

}

int main(void) {
  g = 42;
  h = 42;
  int x = __VERIFIER_nondet_int(); 
  int y = __VERIFIER_nondet_int(); 

 
  x = g;
  y = h;
 
//   assert(y == x);

//   assert(y == x);
  return 0;
}
