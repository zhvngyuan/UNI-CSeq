#include <stdlib.h>
// Main task
unsigned int __cs_pc_5;
// req1_isr_1 thread
unsigned int __cs_pc_1;
// req2_isr_2 thread
unsigned int __cs_pc_2;
// req3_isr_3 thread
unsigned int __cs_pc_3;
// req4_isr_4 thread
unsigned int __cs_pc_4;
int __cs_simulate;
/* Predefined functions type 1 */
void __cseq_error()
{
    ERROR: goto ERROR;
}

void __VERIFIER_assume(int i)
{
    while (!i);
    return;
}

_Bool __VERIFIER_nondet_bool()
{
    _Bool i;
    return i;
}

char __VERIFIER_nondet_char()
{
    char i;
    return i;
}

int __VERIFIER_nondet_int()
{
    int i;
    return i;
}

unsigned int __VERIFIER_nondet_uint()
{
    unsigned int i; __VERIFIER_assume(i>=0);
    return i;
}

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

/* Global variables */
int __cs_disable_isr[5];
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
int test_global_var1;
int test_global_var2;
int test_global_var3;
int test_global_condition1;
int test_global_condition2;
int test_global_condition3;
int test_global_condition4;
void JudgeCondi(void);
/* Simulate req2_isr_2 */
void req2_isr_2(void)
{
        if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else {
                    irq = 2;
                        static int __cs_l_pca_isa_init_dev;
                        __cs_l_pca_isa_init_dev = 2;
                        static int __cs_l_pca_isa_init_id;
                        __cs_l_pca_isa_init_id = 2;
                        global_id = __cs_l_pca_isa_init_id;
                        global_dev = __cs_l_pca_isa_init_dev;
                        __exit__pca_isa_init_2:
;
                        ;;
                        static int __cs_l_pca_isa_probe_dev;
                        __cs_l_pca_isa_probe_dev = 2;
                        static int __cs_l_pca_isa_probe_id;
                        __cs_l_pca_isa_probe_id = 2;
                                if (global_dev != __cs_l_pca_isa_probe_dev)
                                                if (irq > (-1))
                                                                            if (global_id != __cs_l_pca_isa_probe_id)
                        __exit__pca_isa_probe_2:
;
                        ;;
                        global_id = -1;
                        global_dev = -1;
                        __exit__pca_isa_exit_2:
;
                        ;;
                    cnt2++;
                    static int __cs_l_req2_isr_2_reader;
                                    __cs_init_scalar(&__cs_l_req2_isr_2_reader, sizeof(int));
                    __cs_l_req2_isr_2_reader = test_global_var3;
        }
                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 11))
                            {
                                __cs_pc_2 = 11;
                                __cs_simulate = 2;
                            }
}
/* Simulate req3_isr_3 */
void req3_isr_3(void)
{
        if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else {
                    irq = 3;
                                                                    if (irq == 3)
                                                                                                if (test_global_condition4 == 0)
                            test_global_var2 = 0x22;
                        static int __cs_l_pca_isa_init_dev;
                        __cs_l_pca_isa_init_dev = 3;
                        static int __cs_l_pca_isa_init_id;
                        __cs_l_pca_isa_init_id = 3;
                        global_id = __cs_l_pca_isa_init_id;
                        global_dev = __cs_l_pca_isa_init_dev;
                        __exit__pca_isa_init_3:
;
                        ;;
                        static int __cs_l_pca_isa_probe_dev;
                        __cs_l_pca_isa_probe_dev = 3;
                        static int __cs_l_pca_isa_probe_id;
                        __cs_l_pca_isa_probe_id = 3;
                                                                                                                if (global_dev != __cs_l_pca_isa_probe_dev)
                                                                                                                                if (irq > (-1))
                                                                                                                                                            if (global_id != __cs_l_pca_isa_probe_id)
                        __exit__pca_isa_probe_3:
;
                        ;;
                        global_id = -1;
                        global_dev = -1;
                        __exit__pca_isa_exit_3:
;
                        ;;
                    cnt3++;
        }
                                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 12))
                                                                    {
                                                                        __cs_pc_3 = 12;
                                                                        __cs_simulate = 2;
                                                                    }
}
/* Simulate req4_isr_4 */
void req4_isr_4(void)
{
        if (__cs_simulate == 0 && __cs_pc_4 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 0; __cs_simulate = 2;} else {
                    irq = -1;
                                                                                                                                                    if (irq == (-1))
                                                                                                                                                                                if (test_global_condition3 == 1)
                            test_global_var1 = 0x11;
                    cnt4++;
        }
                                                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 5))
                                                                                    {
                                                                                        __cs_pc_4 = 5;
                                                                                        __cs_simulate = 2;
                                                                                    }
}
/* Simulate original main */
int main_task()
                                                                                {
                                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 0) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1)
                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 0; __cs_simulate = 2;} else                                                                                    {
                                                                                            /*disable_isr(-1);*/
                                                                                            __cs_disable_isr[2] = 1;
                                                                                            __cs_disable_isr[3] = 1;
                                                                                            __cs_disable_isr[4] = 1;
                                                                                            __cs_disable_isr[1] = 1;
                                                                                            __cs_disable_isr[0] = 1;
                                                                                    }
                                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 1) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1)
                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 1; __cs_simulate = 2;} else                                                                                    {
                                                                                            test_global_condition1 = 1;
                                                                                    }
                                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 2) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1)
                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 2; __cs_simulate = 2;} else                                                                                    {
                                                                                            test_global_condition2 = 1;
                                                                                    }
                                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 3) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1)
                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 3; __cs_simulate = 2;} else                                                                                    {
                                                                                            test_global_condition3 = 1;
                                                                                    }
                                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 4) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1)
                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 4; __cs_simulate = 2;} else                                                                                    {
                                                                                            test_global_condition4 = 1;
                                                                                    }
                                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 5) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1)
                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 5; __cs_simulate = 2;} else                                                                                    {
                                                                                            /*enable_isr(-1);*/
                                                                                            __cs_disable_isr[2] = 0;
                                                                                            __cs_disable_isr[3] = 0;
                                                                                            __cs_disable_isr[4] = 0;
                                                                                            __cs_disable_isr[1] = 0;
                                                                                            __cs_disable_isr[0] = 0;
                                                                                    }
                                                                                    {
                                                                                        static int __cs_l_JudgeCondi_reader1;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 6) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 6; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_init_scalar(&__cs_l_JudgeCondi_reader1, sizeof(int));
                                                                                        }
                                                                                        static int __cs_l_JudgeCondi_reader2;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 7) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 7; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_init_scalar(&__cs_l_JudgeCondi_reader2, sizeof(int));
                                                                                        }
                                                                                        static int __cs_l_JudgeCondi_reader3;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 8) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 8; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_init_scalar(&__cs_l_JudgeCondi_reader3, sizeof(int));
                                                                                        }
                                                                                        static int __cs_l_JudgeCondi_reader4;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 9) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 9; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_init_scalar(&__cs_l_JudgeCondi_reader4, sizeof(int));
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 10) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 10; __cs_simulate = 2;}
                                                                                        if ((__cs_simulate == 0 && __cs_pc_5 <= 11) || (__cs_simulate == 1 && (test_global_condition1 == 1)))
                                                                                        {
                                                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 11) __cs_simulate = 1;
                                                                                                    if (__cs_simulate == 1)
                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 11; __cs_simulate = 2;} else                                                                                                    {
                                                                                                            __cs_l_JudgeCondi_reader1 = test_global_var1;
                                                                                                    }
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 12) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 12; __cs_simulate = 2;}
                                                                                        if ((__cs_simulate == 0 && __cs_pc_5 <= 13) || (__cs_simulate == 1 && (test_global_condition2 == 1)))
                                                                                        {
                                                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 13) __cs_simulate = 1;
                                                                                                    if (__cs_simulate == 1)
                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 13; __cs_simulate = 2;} else                                                                                                    {
                                                                                                            __cs_l_JudgeCondi_reader2 = test_global_var1;
                                                                                                    }
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 14) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 14; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_JudgeCondi_reader3 = test_global_var2;
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 15) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 15; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_JudgeCondi_reader4 = test_global_var2;
                                                                                        }
                                                                                        __exit__JudgeCondi_1:;
                                                                                    }
                                                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_5 == 16))
                                                                                    {
                                                                                        __cs_pc_5 = 16;
                                                                                        __cs_simulate = 2;
                                                                                    }
                                                                                }
/* Simulate req1_isr_1 */
void req1_isr_1(void)
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else {
                    test_global_var3 = 0x33;
                    irq = 1;
                        static int __cs_l_pca_isa_init_dev;
                        __cs_l_pca_isa_init_dev = 1;
                        static int __cs_l_pca_isa_init_id;
                        __cs_l_pca_isa_init_id = 1;
                        global_id = __cs_l_pca_isa_init_id;
                        global_dev = __cs_l_pca_isa_init_dev;
                        __exit__pca_isa_init_1:
;
                        ;;
                        static int __cs_l_pca_isa_probe_dev;
                        __cs_l_pca_isa_probe_dev = 1;
                        static int __cs_l_pca_isa_probe_id;
                        __cs_l_pca_isa_probe_id = 1;
                                                                                                                                                                                                if (global_dev != __cs_l_pca_isa_probe_dev)
                                                                                                                                                                                                                if (irq > (-1))
                                                                                                                                                                                                                                            if (global_id != __cs_l_pca_isa_probe_id)
                        __exit__pca_isa_probe_1:
;
                        ;;
                        global_id = -1;
                        global_dev = -1;
                        __exit__pca_isa_exit_1:
;
                        ;;
                    cnt1++;
                    test_global_var3 = 0x44;
        }
                                                                                                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 11))
                                                                                                            {
                                                                                                                __cs_pc_1 = 11;
                                                                                                                __cs_simulate = 2;
                                                                                                            }
}
/* main function (scheduler) */
int main()
{
  __cs_simulate = 0;
  __cs_pc_5 = 0;
  __cs_pc_1 = 0;
  __cs_pc_2 = 0;
  __cs_pc_3 = 0;
  __cs_pc_4 = 0;
  while (1)
  {
    __cs_simulate = 0;
    if (__cs_disable_isr[0] != 1) main_task();
    __cs_simulate = 0;
    if (__cs_disable_isr[0] != 1) req1_isr_1();
    __cs_simulate = 0;
    if (__cs_disable_isr[1] != 1) req2_isr_2();
    __cs_simulate = 0;
    if (__cs_disable_isr[2] != 1) req3_isr_3();
    __cs_simulate = 0;
    if (__cs_disable_isr[3] != 1) req4_isr_4();
  }
}
