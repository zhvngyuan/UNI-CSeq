
extern int __VERIFIER_nondet_int();


int glob;
// priority 1
void svp_simple_513_001_isr_1() {

  glob++; // NORACE

}

int main() {
  glob == 0;
  int i = __VERIFIER_nondet_int();

  // if (i)
  // printf("Now we do the work..n");
  if (i == 1){
    glob++; 
    assert(glob == 1);
  }
  // printf("Work is completed...");

  return 0;
}
