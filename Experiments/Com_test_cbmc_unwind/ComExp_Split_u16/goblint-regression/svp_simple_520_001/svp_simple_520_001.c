

extern int __VERIFIER_nondet_int();



int glob;

// priority 1
void svp_simple_520_001_isr_1() {
  glob++; 
  assert(glob < 5);

}

int main() {
  int i = __VERIFIER_nondet_int();
  glob = 0;
  glob++; 
  assert(glob == 1);
  

  return 0;
}
