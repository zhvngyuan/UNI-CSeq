
extern void __VERIFIER_atomic_begin();
extern void __VERIFIER_atomic_end();

extern void abort(void);

// void reach_error() { assert(0); }

int i, j;

#define NUM 5
#define LIMIT (2*NUM+6)

// priority 1
void svp_simple_327_001_isr_1() {
  for (int k = 0; k < NUM; k++) {
    i = j + 2;
  }

}
// priority 2
void svp_simple_327_001_isr_2() {
  for (int k = 0; k < NUM; k++) {
    j = i + 2;
  }
  assert(j == LIMIT);

}

int main() {

  i = 3;
  j = 6;
  
  return 0;

}


