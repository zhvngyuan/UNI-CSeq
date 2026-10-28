int myglobal;
// priority 1
void svp_simple_504_001_isr_1() {
  myglobal = 0;
  int tmp;
  tmp = myglobal+1;
  myglobal=tmp;
  assert(myglobal == 1); 
  // myglobal = myglobal+1
}

int main(void) {
  int tmp = myglobal+1;
  myglobal=tmp; 
  //myglobal = myglobal+1
  return 0;
}
