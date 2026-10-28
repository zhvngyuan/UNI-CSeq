
extern int __VERIFIER_nondet_int();

int myglobal;


void sr_fun(void) {
  int i = __VERIFIER_nondet_int();
  int tmp;
  tmp = myglobal+1;
  myglobal=tmp; 
  // myglobal=myglobal+1; 
}
// priority 1
void svp_simple_505_001_isr_1() {
  myglobal = 0;
  // myglobal=myglobal+1; 
  int tmp = myglobal+1;
  myglobal = tmp; 

  sr_fun();
  assert(myglobal == 2);

}

int main(void) {
  myglobal = 0;
  // myglobal=myglobal+1;
  int tmp = myglobal+1;
  myglobal=tmp; 


  return 0;
}
