
extern int __VERIFIER_nondet_int();


int glob;

// priority 1
void svp_simple_512_001_isr_1() {
  glob = 0;
  int tmp = glob+1;
  glob = tmp;
  assert(glob == 1);
  // glob++; // RACE!

}

int main() {
  int i = __VERIFIER_nondet_int();
  // if (i)
  // printf("Now we do the work..n");
  if (i == 1)
  {
      int tmp = glob+1;
      glob = tmp;
      // glob++; // RACE!
  }
    
  // printf("Work is completed...");

  return 0;
}
