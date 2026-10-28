typedef int pthread_t;
extern int __VERIFIER_nondet_int();
extern void abort(void);
void assume_abort_if_not(int cond) {
  if(!cond) {abort();}
}


int data;

// priority 1
void *svp_simple_560_001_isr_1(void *arg) {
 
  int tmp;
  tmp = data+1;
	data = tmp;

  // data++; 

}

void *main_task(void *arg) {
  data = 0;
  int i = __VERIFIER_nondet_int();
  assume_abort_if_not(0 <= i && i < 10);
  int tmp;
  tmp = data+1;
	data = tmp;
  assert(data == 1);
  // data++; 
 
  return 0;
}


int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_560_001_isr_1, 0);
}
