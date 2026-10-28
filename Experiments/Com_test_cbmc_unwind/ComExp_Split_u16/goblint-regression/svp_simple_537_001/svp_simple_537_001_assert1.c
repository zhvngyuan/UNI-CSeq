int g1, g2;
// priority 1
void svp_simple_537_001_isr_1() {
  int tmp1 = g1+1;
  g1 = tmp1;
  // g1++; 

  int tmp2 = g2+1;
  g2 = tmp2;
  // g2++; 

}

int main(void) {
  g1 = 0;
  g2 = 0;
  g1 = g2 + 1; // NORACE
  assert(g2 == 1);

  return 0;
}

