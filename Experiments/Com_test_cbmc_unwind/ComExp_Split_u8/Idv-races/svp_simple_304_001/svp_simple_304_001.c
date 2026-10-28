
extern void abort(void); 

// void reach_error() { assert(0); }
int __VERIFIER_nondet_int(void);
// void ldv_assert(int expression) { if (!expression) { ERROR: {reach_error();abort();}}; return; }

int pdev;

// priority 1
void svp_simple_304_001_isr_1() {

   pdev = 6;

}

int module_init() {
   pdev = 1;
   assert(pdev==1);
   if(__VERIFIER_nondet_int()) {
      return 0;
   }
   pdev = 3;
   assert(pdev==3);
   return -1;
}

void module_exit() {
   void *status;
   pdev = 4;
   assert(pdev==4);
   pdev = 5;
   assert(pdev==5);
}

int main(void) {
    if(module_init()!=0){
      module_exit();
      }
    module_exit();
    module_exit();
    return 0;
}


