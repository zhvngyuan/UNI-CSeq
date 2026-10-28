
int myglobal;
// priority 1
void svp_simple_524_001_isr_1() {
  int tmp;
  tmp = myglobal + 1;
  myglobal = tmp;
  // myglobal=myglobal+1; // RACE!

}

int main(void) {
  myglobal = 0;
  assert(myglobal == 0);
  // scanf("%d", &myglobal); // RACE!
  return 0;
}

