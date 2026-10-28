// Main task
unsigned __CPROVER_bitvector[1] __cs_pc_0;
// req1_isr_1
unsigned __CPROVER_bitvector[4] __cs_pc_1;
// req2_isr_2
unsigned __CPROVER_bitvector[4] __cs_pc_2;
// req3_isr_3
unsigned __CPROVER_bitvector[4] __cs_pc_3;
// req4_isr_4
unsigned __CPROVER_bitvector[4] __cs_pc_4;
// req5_isr_5
unsigned __CPROVER_bitvector[4] __cs_pc_5;
// req6_isr_6
unsigned __CPROVER_bitvector[2] __cs_pc_6;
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
int __cs_disable_isr_6;
/* Global variables */
int global_clock;
int irq;
int global_id;
int global_dev;
int cnt1;
int cnt2;
int cnt3;
int cnt4;
int cnt5;
int cnt6;
void req1();
void req2();
void req3();
void req4();
void req5();
void req6();
/* Simulate req3_isr_3 */
void req3_isr_3()
{
    if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else    {
            irq = 3;
    }}
    {
        if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;} else        {
                global_id = 3;
        }}
        if (__cs_simulate == 0 && __cs_pc_3 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 2; __cs_simulate = 2;} else        {
                global_dev = 3;
        }}
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 3; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_3 <= 4) || (__cs_simulate == 1 && (global_dev != 3)))
    {
                if (__cs_simulate == 0 && __cs_pc_3 == 4) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 4; __cs_simulate = 2;} else                {
                        assert(0);
                }}
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 5; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_3 <= 7) || (__cs_simulate == 1 && (irq > (-1))))
    {
                if (__cs_simulate == 0 && __cs_pc_3 == 6) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 6; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_3 <= 7) || (__cs_simulate == 1 && (global_id != 3)))
                {
                            if (__cs_simulate == 0 && __cs_pc_3 == 7) __cs_simulate = 1;
                            if (__cs_simulate == 1){
                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 7; __cs_simulate = 2;} else                            {
                                    assert(0);
                            }}
                }
    }
    {
        if (__cs_simulate == 0 && __cs_pc_3 == 8) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 8; __cs_simulate = 2;} else        {
                global_id = -1;
        }}
        if (__cs_simulate == 0 && __cs_pc_3 == 9) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 9; __cs_simulate = 2;} else        {
                global_dev = -1;
        }}
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 10) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 10; __cs_simulate = 2;} else    {
            cnt3++;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 11))
    {
        __cs_pc_3 = 11;
        __cs_simulate = 2;
    }
}
/* Simulate req1_isr_1 */
void req1_isr_1()
{
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            irq = 1;
    }}
    {
        if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;} else        {
                global_id = 1;
        }}
        if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;} else        {
                global_dev = 1;
        }}
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_1 <= 4) || (__cs_simulate == 1 && (global_dev != 1)))
    {
                if (__cs_simulate == 0 && __cs_pc_1 == 4) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 4; __cs_simulate = 2;} else                {
                        assert(0);
                }}
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 5; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_1 <= 7) || (__cs_simulate == 1 && (irq > (-1))))
    {
                if (__cs_simulate == 0 && __cs_pc_1 == 6) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 6; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_1 <= 7) || (__cs_simulate == 1 && (global_id != 1)))
                {
                            if (__cs_simulate == 0 && __cs_pc_1 == 7) __cs_simulate = 1;
                            if (__cs_simulate == 1){
                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 7; __cs_simulate = 2;} else                            {
                                    assert(0);
                            }}
                }
    }
    {
        if (__cs_simulate == 0 && __cs_pc_1 == 8) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 8; __cs_simulate = 2;} else        {
                global_id = -1;
        }}
        if (__cs_simulate == 0 && __cs_pc_1 == 9) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 9; __cs_simulate = 2;} else        {
                global_dev = -1;
        }}
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 10) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 10; __cs_simulate = 2;} else    {
            cnt1++;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 11))
    {
        __cs_pc_1 = 11;
        __cs_simulate = 2;
    }
}
/* Simulate req6_isr_6 */
void req6_isr_6()
{
    if (__cs_simulate == 0 && __cs_pc_6 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 0; __cs_simulate = 2;} else    {
            irq = -1;
    }}
    if (__cs_simulate == 0 && __cs_pc_6 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 1; __cs_simulate = 2;} else    {
            cnt6++;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_6 == 2))
    {
        __cs_pc_6 = 2;
        __cs_simulate = 2;
    }
}
/* Simulate req5_isr_5 */
void req5_isr_5()
{
        if (__cs_simulate == 0 && __cs_pc_5 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 0; __cs_simulate = 2;} else 
{
                    irq = 0;
    {
                        global_id = 5;
                        global_dev = 5;
    }
                    if (global_dev != 5)
    {
                        assert(0);
    }
                    if (irq > (-1))
    {
                                                if (global_id != 5)
                {
                                    assert(0);
                }
    }
    {
                        global_id = -1;
                        global_dev = -1;
    }
                    cnt5++;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_5 == 11))
    {
        __cs_pc_5 = 11;
        __cs_simulate = 2;
    }
}
/* Simulate req2_isr_2 */
void req2_isr_2()
{
    if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else    {
            irq = 2;
    }}
    {
        if (__cs_simulate == 0 && __cs_pc_2 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 1; __cs_simulate = 2;} else        {
                global_id = 2;
        }}
        if (__cs_simulate == 0 && __cs_pc_2 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 2; __cs_simulate = 2;} else        {
                global_dev = 2;
        }}
    }
    if (__cs_simulate == 0 && __cs_pc_2 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 3; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_2 <= 4) || (__cs_simulate == 1 && (global_dev != 2)))
    {
                if (__cs_simulate == 0 && __cs_pc_2 == 4) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 4; __cs_simulate = 2;} else                {
                        assert(0);
                }}
    }
    if (__cs_simulate == 0 && __cs_pc_2 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 5; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_2 <= 7) || (__cs_simulate == 1 && (irq > (-1))))
    {
                if (__cs_simulate == 0 && __cs_pc_2 == 6) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 6; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_2 <= 7) || (__cs_simulate == 1 && (global_id != 2)))
                {
                            if (__cs_simulate == 0 && __cs_pc_2 == 7) __cs_simulate = 1;
                            if (__cs_simulate == 1){
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 7; __cs_simulate = 2;} else                            {
                                    assert(0);
                            }}
                }
    }
    {
        if (__cs_simulate == 0 && __cs_pc_2 == 8) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 8; __cs_simulate = 2;} else        {
                global_id = -1;
        }}
        if (__cs_simulate == 0 && __cs_pc_2 == 9) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 9; __cs_simulate = 2;} else        {
                global_dev = -1;
        }}
    }
    if (__cs_simulate == 0 && __cs_pc_2 == 10) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 10; __cs_simulate = 2;} else    {
            cnt2++;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 11))
    {
        __cs_pc_2 = 11;
        __cs_simulate = 2;
    }
}
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            cnt1 = 1;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 1))
    {
        __cs_pc_0 = 1;
        __cs_simulate = 2;
    }
}
/* Simulate req4_isr_4 */
void req4_isr_4()
{
    if (__cs_simulate == 0 && __cs_pc_4 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 0; __cs_simulate = 2;} else    {
            irq = 0;
    }}
    {
        if (__cs_simulate == 0 && __cs_pc_4 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 1; __cs_simulate = 2;} else        {
                global_id = 4;
        }}
        if (__cs_simulate == 0 && __cs_pc_4 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 2; __cs_simulate = 2;} else        {
                global_dev = 4;
        }}
    }
    if (__cs_simulate == 0 && __cs_pc_4 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 3; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_4 <= 4) || (__cs_simulate == 1 && (global_dev != 4)))
    {
                if (__cs_simulate == 0 && __cs_pc_4 == 4) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 4; __cs_simulate = 2;} else                {
                        assert(0);
                }}
    }
    if (__cs_simulate == 0 && __cs_pc_4 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 5; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_4 <= 7) || (__cs_simulate == 1 && (irq > (-1))))
    {
                if (__cs_simulate == 0 && __cs_pc_4 == 6) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 6; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_4 <= 7) || (__cs_simulate == 1 && (global_id != 4)))
                {
                            if (__cs_simulate == 0 && __cs_pc_4 == 7) __cs_simulate = 1;
                            if (__cs_simulate == 1){
                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 7; __cs_simulate = 2;} else                            {
                                    assert(0);
                            }}
                }
    }
    {
        if (__cs_simulate == 0 && __cs_pc_4 == 8) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 8; __cs_simulate = 2;} else        {
                global_id = -1;
        }}
        if (__cs_simulate == 0 && __cs_pc_4 == 9) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 9; __cs_simulate = 2;} else        {
                global_dev = -1;
        }}
    }
    if (__cs_simulate == 0 && __cs_pc_4 == 10) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 10; __cs_simulate = 2;} else    {
            cnt4++;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 11))
    {
        __cs_pc_4 = 11;
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
  __cs_pc_6 = 0;
  __cs_disable_isr_0 = 0;
  __cs_disable_isr_1 = 0;
  __cs_disable_isr_2 = 0;
  __cs_disable_isr_3 = 0;
  __cs_disable_isr_4 = 0;
  __cs_disable_isr_5 = 0;
  __cs_disable_isr_6 = 0;
  while (1)
  {
    __cs_simulate = 0;
    if ((__cs_pc_6 == 0 || __cs_pc_6 == 2)&&(__cs_pc_4 == 0 || __cs_pc_4 == 11)&&(__cs_pc_3 == 0 || __cs_pc_3 == 11)&&(__cs_pc_2 == 0 || __cs_pc_2 == 11)&&(__cs_pc_1 == 0 || __cs_pc_1 == 11)) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_6 == 0 || __cs_pc_6 == 2)&&(__cs_pc_4 == 0 || __cs_pc_4 == 11)&&(__cs_pc_3 == 0 || __cs_pc_3 == 11)&&(__cs_pc_2 == 0 || __cs_pc_2 == 11)&&__cs_disable_isr_1 != 1) {
        req1_isr_1();
        if (__cs_pc_1 == 11) __cs_pc_1 = 0;
    }
    __cs_simulate = 0;
    if ((__cs_pc_4 == 0 || __cs_pc_4 == 11)&&(__cs_pc_3 == 0 || __cs_pc_3 == 11)&&__cs_disable_isr_2 != 1) {
        req2_isr_2();
        if (__cs_pc_2 == 11) __cs_pc_2 = 0;
    }
    __cs_simulate = 0;
    if ((__cs_pc_4 == 0 || __cs_pc_4 == 11)&&__cs_disable_isr_3 != 1) {
        req3_isr_3();
        if (__cs_pc_3 == 11) __cs_pc_3 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_4 != 1) {
        req4_isr_4();
        if (__cs_pc_4 == 11) __cs_pc_4 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_5 != 1) {
        req5_isr_5();
        if (__cs_pc_5 == 11) __cs_pc_5 = 0;
    }
    __cs_simulate = 0;
    if ((__cs_pc_4 == 0 || __cs_pc_4 == 11)&&(__cs_pc_3 == 0 || __cs_pc_3 == 11)&&(__cs_pc_2 == 0 || __cs_pc_2 == 11)&&(__cs_pc_1 == 0 || __cs_pc_1 == 11)&&__cs_disable_isr_6 != 1) {
        req6_isr_6();
        if (__cs_pc_6 == 2) __cs_pc_6 = 0;
    }
  }
}
