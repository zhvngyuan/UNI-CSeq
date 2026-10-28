
int myglobal;

// priority 1
void svp_simple_508_001_isr_1() {
  myglobal = myglobal + 1; // NORACE

}

int main(void) {
  myglobal = 0;
  myglobal = myglobal + 1; // NORACE
  assert(myglobal <= 2);

  return 0;
}
