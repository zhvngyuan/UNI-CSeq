

extern int __VERIFIER_nondet_int();


int myglobal;

// priority 1
void svp_simple_522_001_isr_1() {
  int tmp;
  if (myglobal == 1) // NORACE
      tmp = 1;
    // printf("How do you do?n");
}

int main(void) {
  myglobal = 0;
  int k = __VERIFIER_nondet_int();
  myglobal = k;

  if (myglobal == 1)  // NORACE
     assert(myglobal == 1);
    // printf("Hello!n");
  return 0;
}
