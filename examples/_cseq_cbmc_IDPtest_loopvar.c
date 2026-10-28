// Main task
unsigned __CPROVER_bitvector[2] __cs_pc_3;
// isr_1
unsigned __CPROVER_bitvector[4] __cs_pc_1;
// isr_2
unsigned __CPROVER_bitvector[3] __cs_pc_2;
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
/* Global variables */
int g_var;
int g_array[10];
int g_flag;
int x;
int y;
int z;
int reader1;
int reader2;
int reader3;
/* Simulate original main */
void main_task()
{
    if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else    {
            x = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;} else    {
            g_var = 1;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 2))
    {
        __cs_pc_3 = 2;
        __cs_simulate = 2;
    }
}
/* Simulate isr_2 */
void isr_2()
{
        if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else 
{
                    y = 5;
                    x = 6;
                    g_var = 2;
                    reader1 = 1;
        }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 4))
    {
        __cs_pc_2 = 4;
        __cs_simulate = 2;
    }
}
/* Simulate isr_1 */
void isr_1()
{
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            g_flag = 1;
    }
    static int __cs_l_isr_1_i_1 = 0;
    __begin_isr_1_loop_0:;
    if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_1 <= 2) || ((__cs_simulate == 1) && (__cs_l_isr_1_i_1 < 10)))
    {
                if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;} else                {
                        g_array[__cs_l_isr_1_i_1] = 1;
                }
                if (__cs_simulate == 1)
                {
                        __cs_l_isr_1_i_1++;
                }
    }
    __end_isr_1_loop_0:;
    static int __cs_l_isr_1_i_2 = 0;
    __begin_isr_1_loop_1:;
    if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_1 <= 4) || ((__cs_simulate == 1) && (__cs_l_isr_1_i_2 < 10)))
    {
                if (__cs_simulate == 0 && __cs_pc_1 == 4) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 4; __cs_simulate = 2;} else                {
                        g_array[8] = 1;
                }
                if (__cs_simulate == 1)
                {
                        __cs_l_isr_1_i_2++;
                }
    }
    __end_isr_1_loop_1:;
    if (__cs_simulate == 0 && __cs_pc_1 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 5; __cs_simulate = 2;} else    {
            x = 5;
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 6; __cs_simulate = 2;} else    {
            assert(x == 5);
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 7) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 7; __cs_simulate = 2;} else    {
            z = 4;
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 8) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 8; __cs_simulate = 2;} else    {
            g_var = 1;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 9))
    {
        __cs_pc_1 = 9;
        __cs_simulate = 2;
    }
}
/* main function (scheduler) */
int main()
{
  __cs_simulate = 0;
  __cs_pc_3 = 0;
  __cs_pc_1 = 0;
  __cs_pc_2 = 0;
  __cs_disable_isr_0 = 0;
  __cs_disable_isr_1 = 0;
  __cs_disable_isr_2 = 0;
  while (1)
  {
    __cs_simulate = 0;
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 9)&&__cs_disable_isr_0 != 1) main_task();
    __cs_simulate = 0;
    if (__cs_disable_isr_1 != 1) isr_1();
    __cs_simulate = 0;
    if (__cs_disable_isr_2 != 1) isr_2();
  }
}
