typedef int pthread_t;

extern int __VERIFIER_nondet_int();


int glob;
// priority 1
void *svp_simple_513_001_isr_1(void *arg) {

  glob++; 

}

void *main_task(void *arg) {
  glob == 0;
  int i = __VERIFIER_nondet_int();

  // if (i)
  // printf("Now we do the work..n");
  if (i == 1){
    glob++; 
    assert(glob == 1);
  }
  // printf("Work is completed...");

  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_513_001_isr_1, 0);
}
