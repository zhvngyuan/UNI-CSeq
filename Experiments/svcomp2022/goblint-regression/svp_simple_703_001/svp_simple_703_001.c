extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

extern int __VERIFIER_nondet_int();


// priority 1
void svp_simple_703_001_isr_1() {
  int x;
  x = __VERIFIER_nondet_int(); 
  assert(!(x == 3));

}

int main(void) {

  int x;
  x = 3;

  return 0;
}
