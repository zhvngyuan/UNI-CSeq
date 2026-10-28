extern int __VERIFIER_nondet_int();
// extern void abort(void);
// void assume_abort_if_not(int cond) {
//   if(!cond) {abort();}
// }


int data;

// priority 1
void svp_simple_560_001_isr_1() {
 
  int tmp;
  tmp = data+1;
	data = tmp;

  // data++; 

}

int main() {
  data = 0;
  int i = __VERIFIER_nondet_int();
  if(0 <= i && i < 10){
  int tmp;
  tmp = data+1;
	data = tmp;
  }
  assert(data == 1);
  // data++; 
 
  return 0;
}

