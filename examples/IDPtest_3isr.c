// extern void __VERIFIER_error() __attribute__ ((__noreturn__));

// typedef int pthread_t;

volatile int  g_var;
volatile int  g_array[10];
volatile int  g_flag;
volatile int  x;
volatile int  y;
volatile int  z;




//priority 1
void isr_1() {
  // int m1;
  // m1 = 0;
  // while(m1 < 10){
  g_flag = 1;
  //  for (int i = 0; i < 10; i++) {
  //     if(i == 3) reader1 = x;
  //  }
  y ++;
  z = 4;
  g_var = 1;
//   m1 ++;
// }
// x = 2;
// enable_isr(2);

}



//priority 2
void isr_2() {
  // int reader1, reader2, reader3;
  // z = 5;
  y = 5;
  // y = 10;
  // x = 6;
  // g_var = 1;
}

//priority 3
void isr_3() {
  y = 1;
  x = 2;
}



void main() {
  // disable_isr(2);
  
  // disable_isr(2);
  x = 1;

  if(y >= 250){
    z = 1;
    assert(z == 1);
  }
  // assert(z == 1);
  // disable_isr(2);
}