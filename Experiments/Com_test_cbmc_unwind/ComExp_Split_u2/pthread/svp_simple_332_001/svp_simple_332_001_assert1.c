
extern void abort(void);
// void reach_error() { assert(0); }

int i, j, test;

#define NUM 20
#define LIMIT (2*NUM+6)


// priority 1
void svp_simple_332_001_isr_1() {
  for (int k = 0; k < NUM; k++) {
    i = j + 1;
  }
  test = 10;
  assert(test == 10);
  test = 0;

}
// priority 2
void svp_simple_332_001_isr_2() {
  for (int k = 0; k < NUM; k++) {
    j = i + 1;
  }
  
}

int main() {

  i = 3;
  j = 6;
  test++;

  return 0;

}