
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
  //  disable_isr(2);
   
   for (int i = 0; i < 10; i++) {     g_array[i] = 1; }

   for (int i = 0; i < 10; i++) { g_array[8] = 1;}

  x = 5;
  assert(x == 5);
   z = 4;
   g_var = 1;
  
}

// priority 2
void isr_2() {
  y = 5;
  x = 6;
  g_var = 2;
  reader1 = 1;
}

void main() {
  // disable_isr(2);

  x = 1;
  g_var = 1;

}
