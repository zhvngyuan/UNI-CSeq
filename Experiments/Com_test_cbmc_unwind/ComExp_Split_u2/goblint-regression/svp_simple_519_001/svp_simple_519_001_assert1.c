
int myglobal;

// priority 1
void svp_simple_519_001_isr_1() {
  myglobal=myglobal+1; // NORACE
  assert(myglobal <=2);
}

int add1 (int x) {
  return x+1;
}

int main(void) {
  myglobal = 0;

  // printf("myglobal equals %dn",myglobal); // NORACE
//   assert(myglobal == 0);

  add1(myglobal); // NORACE
//   assert(myglobal == 1);

  return 0;
}
