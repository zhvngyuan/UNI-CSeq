// Main task
unsigned __CPROVER_bitvector[3] __cs_pc_0;
// Timer_A_isr_1
unsigned __CPROVER_bitvector[3] __cs_pc_1;
// Timer_B_isr_2
unsigned __CPROVER_bitvector[3] __cs_pc_2;
// Timer_C_isr_3
unsigned __CPROVER_bitvector[3] __cs_pc_3;
// Timer_Force_isr_4
unsigned __CPROVER_bitvector[1] __cs_pc_4;
// Timer_Reset_isr_5
unsigned __CPROVER_bitvector[2] __cs_pc_5;
unsigned __CPROVER_bitvector[2] __cs_simulate;
/* Predefined functions type 1 */
#define __VERIFIER_assume(X) __CPROVER_assume(X)
#define assume(X) __CPROVER_assume(X)
#define __VERIFIER_nondet_int() nondet_int()
int nondet_int();

#define __VERIFIER_nondet_uint() nondet_uint()
unsigned int nondet_uint();

#define __VERIFIER_nondet_bool() nondet_bool()
_Bool nondet_bool();

char nondet_char();
unsigned char nondet_uchar();

/* Predefined functions type 2 */
//void * __cs_safe_malloc(size_t size)
//{
//    void * ptr = malloc(size);
//    __VERIFIER_assume(ptr);
//    return ptr;
//}

//void * __cs_unsafe_malloc(size_t size)
//{
//    if(__VERIFIER_nondet_bool())
//        return 0;
//    return malloc(size);
//}

void __cs_init_scalar(void *var, unsigned int size)
{
    if (size == sizeof(int))
        *(int *)var = __VERIFIER_nondet_int();
    else {
        char * ptr = (char *)var;
        // size_t j;
        //for (j=0; j<size; j++)
        //  ptr[j] = __cs_nondet_char();
    }
}

/* ISR Masking variables */
int __cs_disable_isr_0;
int __cs_disable_isr_1;
int __cs_disable_isr_2;
int __cs_disable_isr_3;
int __cs_disable_isr_4;
int __cs_disable_isr_5;
/* Global variables */
unsigned int timerCount = 0;
int P1OUT;
int LED_0;
int LED_1;
int WDTCLT;
int WDTPW;
int WDTCTL;
int WDTHOLD;
int LED_DIR;
int LED_OUT;
int CCTL0;
int CCIE;
int TACTL;
int TASSEL_2;
int MC_2;
int cnt1;
int cnt2;
int cnt3;
int cnt4;
int cnt5;
/* Simulate Timer_Reset_isr_5 */
void Timer_Reset_isr_5()
{
        if (__cs_simulate == 0 && __cs_pc_5 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 0; __cs_simulate = 2;} else 
{
                    timerCount = 0;
                    if (timerCount != 0)
    {
                        assert(0);
    }
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_5 == 3))
    {
        __cs_pc_5 = 3;
        __cs_simulate = 2;
    }
}
/* Simulate Timer_Force_isr_4 */
void Timer_Force_isr_4()
{
    if (__cs_simulate == 0 && __cs_pc_4 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 0; __cs_simulate = 2;} else    {
            timerCount++;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 1))
    {
        __cs_pc_4 = 1;
        __cs_simulate = 2;
    }
}
/* Simulate Timer_C_isr_3 */
void Timer_C_isr_3()
{
    if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else    {
            timerCount = 1;
    }}
    if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_3 <= 2) || (__cs_simulate == 1 && (timerCount != 0)))
    {
                if (__cs_simulate == 0 && __cs_pc_3 == 2) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 2; __cs_simulate = 2;} else                {
                        assert(0);
                }}
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 3; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_3 <= 4) || (__cs_simulate == 1 && (timerCount == 0)))
    {
                if (__cs_simulate == 0 && __cs_pc_3 == 4) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 4; __cs_simulate = 2;} else                {
                        P1OUT = LED_0;
                }}
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 5))
    {
        __cs_pc_3 = 5;
        __cs_simulate = 2;
    }
}
/* Simulate Timer_B_isr_2 */
void Timer_B_isr_2()
{
    if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else    {
            timerCount = 1;
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 1; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_2 <= 2) || (__cs_simulate == 1 && (timerCount != 0)))
    {
                if (__cs_simulate == 0 && __cs_pc_2 == 2) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 2; __cs_simulate = 2;} else                {
                        assert(0);
                }}
    }
    if (__cs_simulate == 0 && __cs_pc_2 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 3; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_2 <= 4) || (__cs_simulate == 1 && (timerCount == 0)))
    {
                if (__cs_simulate == 0 && __cs_pc_2 == 4) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 4; __cs_simulate = 2;} else                {
                        P1OUT = LED_0;
                }}
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 5))
    {
        __cs_pc_2 = 5;
        __cs_simulate = 2;
    }
}
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            WDTCTL = WDTPW + WDTHOLD;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else    {
            LED_DIR = LED_0 + LED_1;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else    {
            LED_OUT = 1 + (LED_0 + LED_1);
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else    {
            CCTL0 = CCIE;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;} else    {
            TACTL = TASSEL_2 + MC_2;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else    {
            timerCount = 0;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 6))
    {
        __cs_pc_0 = 6;
        __cs_simulate = 2;
    }
}
/* Simulate Timer_A_isr_1 */
void Timer_A_isr_1()
{
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            timerCount = 1;
    }}
    if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_1 <= 2) || (__cs_simulate == 1 && (timerCount != 0)))
    {
                if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;} else                {
                        assert(0);
                }}
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_1 <= 4) || (__cs_simulate == 1 && (timerCount == 0)))
    {
                if (__cs_simulate == 0 && __cs_pc_1 == 4) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 4; __cs_simulate = 2;} else                {
                        P1OUT = LED_0 + LED_1;
                }}
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 5))
    {
        __cs_pc_1 = 5;
        __cs_simulate = 2;
    }
}
/* main function (scheduler) */
int main()
{
  __cs_simulate = 0;
  __cs_pc_0 = 0;
  __cs_pc_1 = 0;
  __cs_pc_2 = 0;
  __cs_pc_3 = 0;
  __cs_pc_4 = 0;
  __cs_pc_5 = 0;
  __cs_disable_isr_0 = 0;
  __cs_disable_isr_1 = 0;
  __cs_disable_isr_2 = 0;
  __cs_disable_isr_3 = 0;
  __cs_disable_isr_4 = 0;
  __cs_disable_isr_5 = 0;
  while (1)
  {
    __cs_simulate = 0;
    if ((__cs_pc_4 == 0 || __cs_pc_4 == 1)&&(__cs_pc_3 == 0 || __cs_pc_3 == 5)&&(__cs_pc_2 == 0 || __cs_pc_2 == 5)&&(__cs_pc_1 == 0 || __cs_pc_1 == 5)) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_4 == 0 || __cs_pc_4 == 1)&&(__cs_pc_3 == 0 || __cs_pc_3 == 5)&&(__cs_pc_2 == 0 || __cs_pc_2 == 5)&&__cs_disable_isr_1 != 1) {
        Timer_A_isr_1();
        if (__cs_pc_1 == 5) __cs_pc_1 = 0;
    }
    __cs_simulate = 0;
    if ((__cs_pc_4 == 0 || __cs_pc_4 == 1)&&(__cs_pc_3 == 0 || __cs_pc_3 == 5)&&(__cs_pc_1 == 0 || __cs_pc_1 == 5)&&__cs_disable_isr_2 != 1) {
        Timer_B_isr_2();
        if (__cs_pc_2 == 5) __cs_pc_2 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_3 != 1) {
        Timer_C_isr_3();
        if (__cs_pc_3 == 5) __cs_pc_3 = 0;
    }
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 5)&&__cs_disable_isr_4 != 1) {
        Timer_Force_isr_4();
        if (__cs_pc_4 == 1) __cs_pc_4 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_5 != 1) {
        Timer_Reset_isr_5();
        if (__cs_pc_5 == 3) __cs_pc_5 = 0;
    }
  }
}
