extern void abort(void);
// void reach_error() { assert(0); }

int i, j;

#define NUM 20
#define LIMIT (2*NUM+6)

// priority 1
void svp_simple_330_001_isr_1() {
  for (int k = 0; k < NUM; k++) {
    i = j + 2;
  }
  
}
// priority 2
void svp_simple_330_001_isr_2() {
  for (int k = 0; k < NUM; k++) {
    j = i + 2;
  }
}

int main() {

  
  disable_isr(1);
  i = 3;
  assert(i == 3);
  disable_isr(1);
  j = 6;
  

  return 0;
}
