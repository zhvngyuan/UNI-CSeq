int global;
// priority 1
void svp_simple_644_001_isr_1() {

  // access(global);
  global++;
  global--;

}

int main(void) {

  disable_isr(1);
  global = 0;
  assert(global == 0);
  enable_isr(1);
  // assert_racefree(global);  

  return 0;
}