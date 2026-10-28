typedef int pthread_t;


extern int __VERIFIER_nondet_int();


int myglobal;

// priority 1
void *svp_simple_522_001_isr_1(void *arg) {
  int tmp;
  if (myglobal == 1) 
      tmp = 1;
    // printf("How do you do?n");
}

void *main_task(void *arg) {
  myglobal = 0;
  int k = __VERIFIER_nondet_int();
  myglobal = k;

  if (myglobal == 1)  
     assert(myglobal == 1);
    // printf("Hello!n");
  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_522_001_isr_1, 0);
}
