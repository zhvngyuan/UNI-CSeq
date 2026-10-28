int myglobal;
// priority 1
void svp_simple_597_001_isr_1() {
  myglobal = 40; // NORACE
  assert(myglobal == 40);

}

int main(void) {
  myglobal = 0;
  return 0;
}
