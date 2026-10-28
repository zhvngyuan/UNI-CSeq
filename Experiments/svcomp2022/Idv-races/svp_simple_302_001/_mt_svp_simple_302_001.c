typedef int pthread_t;
extern void abort(void);

void reach_error() { assert(0); }
int __VERIFIER_nondet_int(void);
// void ldv_assert(int expression) { if (!expression) { ERROR: {reach_error();abort();}}; return; }


int pdev;

void *main_task(void *arg) {
   if (module_init() != 0){
      module_exit();
   }
    module_exit();
    module_exit();
    return 0;
}
// priority 1
void *svp_simple_302_001_isr_1(void *arg) {
   pdev = 6;
}

int module_init() {
   pdev = 1;
   assert(pdev==1);
   if(__VERIFIER_nondet_int()) {
      pdev = 2;
      assert(pdev==2);
      return 0;
   }

   pdev = 3;
   assert(pdev==3);
   return -1;
}

void module_exit() {
   void *status;
   pdev = 5;
   assert(pdev==5);
}


int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_302_001_isr_1, 0);
}
