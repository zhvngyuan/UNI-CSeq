extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }

int g;
// priority 1
void svp_simple_634_001_isr_1() {
  g = 1;
}

int main() {
  g = 0;
  if (g == 1){ 
    assert(g == 1);
    g = 1;
  }else{
    assert(!(g == 1));
    g = 0;
  }

  // if (g) 
  //   assert(g);
  // else
  //   assert(!g);

  return 0;
}
