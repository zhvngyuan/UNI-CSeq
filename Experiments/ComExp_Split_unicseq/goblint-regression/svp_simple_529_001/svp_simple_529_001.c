

int x;
// priority 1
void svp_simple_529_001_isr_1() {
  x = 0;
  int tmp = x+1;
  x = tmp;
  assert(x == 1);
  // x++; // RACE!

}

int main() {
  x = 0;
  return 0;
}
