
volatile int  g_var;
volatile int  g_array[10];
volatile int  g_flag;
volatile int  x;
volatile int  y;
volatile int  z;

int reader1, reader2, reader3;

// priority 1
void isr_1() {

   g_flag = 1;
   disable_isr(2);
   x = 5;
   for (int i = 0; i < 10; i++) {
      // if(i == 3) reader1 = x;
      g_array[i] = 1;
      // assert(g_array[i] == 1);
   }
  assert(g_array[5] == 1); 
  // assert(reader2 == 1);
  reader1 = x;
  // assert(reader1 == 5);
  //  if(reader1!=5){
  //   ERROR: __VERIFIER_error();
  //  }
   z = 4;
   g_var = 1;
  //  assert(g_var == 1);
  //  if(g_var!=1){
  //     ERROR: __VERIFIER_error();
  //     ;
  //  }
  
}

// priority 2
void isr_2() {
  // int reader1, reader2, reader3;
  // z = 5;
  y = 5;
  x = 6;
  g_var = 2;
  reader1 = 1;
}

// int main(){
//   pthread_t t0, t1, t2;
//   pthread_create(&t0, 0, main_task, 0);
//   pthread_create(&t1, 0, isr_1, 0);
//   pthread_create(&t2, 0, isr_2, 0);
// }
void main() {
  // disable_isr(2);
  
  // for (int i = 0; i < 10; i++)  g_array[8] = 0;
  // g_array[8] = 1;
  x = 1;
  g_var = 1;

}
