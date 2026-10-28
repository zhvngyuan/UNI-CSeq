

int myglobal;
// priority 1
void svp_simple_598_001_isr_1() {
  myglobal = 42; 
  assert(myglobal == 42);

}

int main(void) {
  myglobal = 0;
  

  return 0;
}
