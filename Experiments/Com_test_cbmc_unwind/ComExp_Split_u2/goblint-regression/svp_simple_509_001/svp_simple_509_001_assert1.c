

int myglobal;


void munge() {
  int tmp = myglobal+1;
  myglobal=tmp; 
  // myglobal=myglobal+1; // RACE!

}
void sr_munge() {
  int tmp = myglobal+1;
  myglobal=tmp; 
  // myglobal=myglobal+1; // RACE!

}
// priority 1
void svp_simple_509_001_isr_1() {
  myglobal = 0;
  sr_munge();
  assert(myglobal == 1);
  // return NULL;
}


int main(void) {
  myglobal = 0;

  munge();
  return 0;
}
