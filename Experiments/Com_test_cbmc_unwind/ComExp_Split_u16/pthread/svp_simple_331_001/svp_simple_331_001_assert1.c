
extern void abort(void);

// void reach_error() { assert(0); }

int i, j, test;

#define NUM 20
#define LIMIT (2*NUM+6)


// priority 1
void svp_simple_331_001_isr_1() {
  for (int k = 0; k < NUM; k++) {
    i = j + 3;
  }
  test++;

}
// priority 2
void svp_simple_331_001_isr_2() {
  for (int k = 0; k < NUM; k++) {
    j = i + 2;
  }
  test = 0;
  assert(test == 0);
}

int main() {

  i = 3;
  j = 6;

  return 0;
}
