
int myglobal;

int f(int x) {
  return 5;
}
// priority 1
void svp_simple_542_001_isr_1() {
    int tmp;
    myglobal=f(myglobal);
    if(myglobal == 5){
          tmp = 1;
    }
}

int main(void) {
//  int tmp=myglobal+1;
//  myglobal = tmp;
  myglobal = 0;
  assert(myglobal == 0);
  myglobal = f(myglobal);
//   assert(myglobal == 5);
  myglobal = f(myglobal);
  return 0;
}