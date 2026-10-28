

int myglobal;


void munge() {

  myglobal=myglobal+1; // NORACE

}
// priority 1
void svp_simple_510_001_isr_1() {
  myglobal = 0;
  munge();

}


int main(void) {
  myglobal = 0;

  munge();
  assert(myglobal == 1);

  return 0;
}
