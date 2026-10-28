

extern void exit (int status);

int glob;


void f() {
  int tmp;
  tmp = glob+1;
  glob = glob+1;
  // glob++; 

  exit(0);
}
// priority 1
void svp_simple_506_001_isr_1() {
  int tmp = glob+1;
  glob=glob+1;
  // glob++;

}

int main(void) {
  glob = 0;
  // while () {
  //   f();
  // }
  f();
//   assert(glob == 0);
  
  glob = 8;
  assert(glob == 8);
  return 0;
}
