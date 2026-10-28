
extern int __VERIFIER_nondet_int();



int glob;

// priority 1
void svp_simple_521_001_isr_1() {

  glob++; 

}

int main() {
  int i;
  glob = 0;
  i = __VERIFIER_nondet_int();


  // printf("Do the work? ");

  // printf("Now we do the work..n");
  i++;
  if (i == 2){
    glob++; // NORACE
    assert(glob == 1);
  }
  // printf("Work is completed...");
  i--;


  return 0;
}
