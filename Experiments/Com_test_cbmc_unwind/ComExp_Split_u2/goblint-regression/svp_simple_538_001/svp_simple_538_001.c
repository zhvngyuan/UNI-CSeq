int myglobal;
int debug;
// priority 1
void svp_simple_538_001_isr_1() {
  int tmp;
  tmp=myglobal+1;
  myglobal = tmp;
  // myglobal=myglobal+1; // NORACE

  debug = 3;  // add

}

int main(void) {
  myglobal = 0;
  debug = 0; // NORACE

  int tmp;
  tmp=myglobal+1;
  myglobal = tmp;
  assert(myglobal == 1);
  // myglobal=myglobal+1; // NORACE

  int tmp1;
  tmp1=debug+1;
  debug = tmp1;
  // debug++; // NORACE
  return 0;
}
