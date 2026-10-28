// #include <stdlib.h>
// Main task
unsigned int __cs_pc_9;
// req1_isr_1 thread
unsigned int __cs_pc_1;
// req2_isr_2 thread
unsigned int __cs_pc_2;
// req3_isr_3 thread
unsigned int __cs_pc_3;
// req4_isr_4 thread
unsigned int __cs_pc_4;
// req5_isr_5 thread
unsigned int __cs_pc_5;
// req6_isr_6 thread
unsigned int __cs_pc_6;
// req7_isr_7 thread
unsigned int __cs_pc_7;
// req8_isr_8 thread
unsigned int __cs_pc_8;
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
int __cs_disable_isr[9];
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
int cnt7;
int cnt8;
int test_global_array[10000];
int test_global_var1;
int test_global_var2;
int test_global_var3;
int test_global_condition1;
int test_global_condition2;
int test_global_condition3;
int test_global_condition4;
void JudgeCondi(void);
/* Simulate req7_isr_7 */
void req7_isr_7(void)
{
    if (__cs_simulate == 0 && __cs_pc_7 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 0; __cs_simulate = 2;} else    {
            irq = 0;
    }
    {
        static int __cs_l_pca_isa_init_dev;
        if (__cs_simulate == 1)
        {
                __cs_l_pca_isa_init_dev = 7;
        }
        static int __cs_l_pca_isa_init_id;
        if (__cs_simulate == 1)
        {
                __cs_l_pca_isa_init_id = 7;
        }
        if (__cs_simulate == 0 && __cs_pc_7 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 1; __cs_simulate = 2;} else        {
                global_id = __cs_l_pca_isa_init_id;
        }
        if (__cs_simulate == 0 && __cs_pc_7 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 2; __cs_simulate = 2;} else        {
                global_dev = __cs_l_pca_isa_init_dev;
        }
        __exit__pca_isa_init_6:;
    }
    {
        if (__cs_simulate == 0 && __cs_pc_7 == 3) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 3; __cs_simulate = 2;} else        {
                global_id = -1;
        }
        if (__cs_simulate == 0 && __cs_pc_7 == 4) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 4; __cs_simulate = 2;} else        {
                global_dev = -1;
        }
        __exit__pca_isa_exit_6:;
    }
    if (__cs_simulate == 0 && __cs_pc_7 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 5; __cs_simulate = 2;} else    {
            cnt7++;
    }
    static int __cs_l_req7_isr_7_i = 0;
    static int __cs_l_req7_isr_7_maxnum;
    if (__cs_simulate == 0 && __cs_pc_7 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 6; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_req7_isr_7_maxnum, sizeof(int));
    }
    static int __cs_l_req7_isr_7_mininum;
    if (__cs_simulate == 0 && __cs_pc_7 == 7) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 7; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_req7_isr_7_mininum, sizeof(int));
    }
    if (__cs_simulate == 1)
    {
            __cs_l_req7_isr_7_i = 0;
    }
    __begin_req7_isr_7_loop_0:;
    if (__cs_simulate == 0 && __cs_pc_7 == 8) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_7 = 8; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_7 <= 12) || ((__cs_simulate == 1) && (__cs_l_req7_isr_7_i < 10000)))
    {
                if (__cs_simulate == 0 && __cs_pc_7 == 9) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_7 = 9; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_7 <= 10) || (__cs_simulate == 1 && (__cs_l_req7_isr_7_i == 9000)))
                {
                            if (__cs_simulate == 0 && __cs_pc_7 == 10) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 10; __cs_simulate = 2;} else                            {
                                    test_global_array[9000] = 1;
                            }
                }
                if (__cs_simulate == 0 && __cs_pc_7 == 11) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_7 = 11; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_7 <= 12) || (__cs_simulate == 1 && (__cs_l_req7_isr_7_i == 10001)))
                {
                            if (__cs_simulate == 0 && __cs_pc_7 == 12) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 12; __cs_simulate = 2;} else                            {
                                    test_global_array[9000] = 1;
                            }
                }
                if (__cs_simulate == 1)
                {
                        __cs_l_req7_isr_7_i++;
                }
    }
    __end_req7_isr_7_loop_0:;
    if (__cs_simulate == 0 && __cs_pc_7 == 13) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 13; __cs_simulate = 2;} else    {
            __cs_l_req7_isr_7_mininum = test_global_array[9000] - 10;
    }
    if (__cs_simulate == 0 && __cs_pc_7 == 14) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 14; __cs_simulate = 2;} else    {
            __cs_l_req7_isr_7_maxnum = test_global_array[0] + 10;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_7 == 15))
    {
        __cs_pc_7 = 15;
        __cs_simulate = 2;
    }
}
/* Simulate req3_isr_3 */
void req3_isr_3(void)
{
    if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else    {
            irq = 0;
    }
    {
        static int __cs_l_pca_isa_init_dev;
        if (__cs_simulate == 1)
        {
                __cs_l_pca_isa_init_dev = 3;
        }
        static int __cs_l_pca_isa_init_id;
        if (__cs_simulate == 1)
        {
                __cs_l_pca_isa_init_id = 3;
        }
        if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;} else        {
                global_id = __cs_l_pca_isa_init_id;
        }
        if (__cs_simulate == 0 && __cs_pc_3 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 2; __cs_simulate = 2;} else        {
                global_dev = __cs_l_pca_isa_init_dev;
        }
        __exit__pca_isa_init_3:;
    }
    {
        if (__cs_simulate == 0 && __cs_pc_3 == 3) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 3; __cs_simulate = 2;} else        {
                global_id = -1;
        }
        if (__cs_simulate == 0 && __cs_pc_3 == 4) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 4; __cs_simulate = 2;} else        {
                global_dev = -1;
        }
        __exit__pca_isa_exit_3:;
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 5; __cs_simulate = 2;} else    {
            cnt3++;
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 6; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_3 <= 7) || (__cs_simulate == 1 && (global_id == (-1))))
    {
                if (__cs_simulate == 0 && __cs_pc_3 == 7) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 7; __cs_simulate = 2;} else                {
                        test_global_var1 = 0x11;
                }
    }
    else
if ((__cs_simulate == 0 && __cs_pc_3 <= 8) || (__cs_simulate == 1))    {
                if (__cs_simulate == 0 && __cs_pc_3 == 8) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 8; __cs_simulate = 2;} else                {
                        test_global_var2 = 0x22;
                }
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 9))
    {
        __cs_pc_3 = 9;
        __cs_simulate = 2;
    }
}
/* Simulate req1_isr_1 */
void req1_isr_1(void)
{
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            irq = 0;
    }
    {
        static int __cs_l_pca_isa_init_dev;
        if (__cs_simulate == 1)
        {
                __cs_l_pca_isa_init_dev = 1;
        }
        static int __cs_l_pca_isa_init_id;
        if (__cs_simulate == 1)
        {
                __cs_l_pca_isa_init_id = 1;
        }
        if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;} else        {
                global_id = __cs_l_pca_isa_init_id;
        }
        if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;} else        {
                global_dev = __cs_l_pca_isa_init_dev;
        }
        __exit__pca_isa_init_1:;
    }
    {
        if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;} else        {
                global_id = -1;
        }
        if (__cs_simulate == 0 && __cs_pc_1 == 4) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 4; __cs_simulate = 2;} else        {
                global_dev = -1;
        }
        __exit__pca_isa_exit_1:;
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 5; __cs_simulate = 2;} else    {
            cnt1++;
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 6; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_1 <= 16) || (__cs_simulate == 1 && (irq == 0)))
    {
                {
                    static int __cs_l_JudgeCondi_reader1;
                    if (__cs_simulate == 0 && __cs_pc_1 == 7) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 7; __cs_simulate = 2;} else                    {
                            __cs_init_scalar(&__cs_l_JudgeCondi_reader1, sizeof(int));
                    }
                    static int __cs_l_JudgeCondi_reader2;
                    if (__cs_simulate == 0 && __cs_pc_1 == 8) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 8; __cs_simulate = 2;} else                    {
                            __cs_init_scalar(&__cs_l_JudgeCondi_reader2, sizeof(int));
                    }
                    static int __cs_l_JudgeCondi_reader3;
                    if (__cs_simulate == 0 && __cs_pc_1 == 9) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 9; __cs_simulate = 2;} else                    {
                            __cs_init_scalar(&__cs_l_JudgeCondi_reader3, sizeof(int));
                    }
                    static int __cs_l_JudgeCondi_reader4;
                    if (__cs_simulate == 0 && __cs_pc_1 == 10) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 10; __cs_simulate = 2;} else                    {
                            __cs_init_scalar(&__cs_l_JudgeCondi_reader4, sizeof(int));
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 11) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 11; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_1 <= 12) || (__cs_simulate == 1 && (test_global_condition1 == 1)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_1 == 12) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 12; __cs_simulate = 2;} else                                {
                                        __cs_l_JudgeCondi_reader1 = test_global_var1;
                                }
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 13) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 13; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_1 <= 14) || (__cs_simulate == 1 && (test_global_condition2 == 1)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_1 == 14) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 14; __cs_simulate = 2;} else                                {
                                        __cs_l_JudgeCondi_reader2 = test_global_var1;
                                }
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 15) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 15; __cs_simulate = 2;} else                    {
                            __cs_l_JudgeCondi_reader3 = test_global_var2;
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 16) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 16; __cs_simulate = 2;} else                    {
                            __cs_l_JudgeCondi_reader4 = test_global_var2;
                    }
                    __exit__JudgeCondi_1:;
                }
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 17))
    {
        __cs_pc_1 = 17;
        __cs_simulate = 2;
    }
}
/* Simulate req6_isr_6 */
void req6_isr_6(void)
{
    if (__cs_simulate == 0 && __cs_pc_6 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 0; __cs_simulate = 2;} else    {
            irq = -1;
    }
    if (__cs_simulate == 0 && __cs_pc_6 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_6 = 1; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_6 <= 2) || (__cs_simulate == 1 && (irq == (-1))))
    {
                if (__cs_simulate == 0 && __cs_pc_6 == 2) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 2; __cs_simulate = 2;} else                {
                        test_global_var3 = 0x33;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_6 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 3; __cs_simulate = 2;} else    {
            cnt6++;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_6 == 4))
    {
        __cs_pc_6 = 4;
        __cs_simulate = 2;
    }
}
/* Simulate req5_isr_5 */
void req5_isr_5(void)
{
    if (__cs_simulate == 0 && __cs_pc_5 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 0; __cs_simulate = 2;} else    {
            irq = 0;
    }
    {
        static int __cs_l_pca_isa_init_dev;
        if (__cs_simulate == 1)
        {
                __cs_l_pca_isa_init_dev = 5;
        }
        static int __cs_l_pca_isa_init_id;
        if (__cs_simulate == 1)
        {
                __cs_l_pca_isa_init_id = 5;
        }
        if (__cs_simulate == 0 && __cs_pc_5 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 1; __cs_simulate = 2;} else        {
                global_id = __cs_l_pca_isa_init_id;
        }
        if (__cs_simulate == 0 && __cs_pc_5 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 2; __cs_simulate = 2;} else        {
                global_dev = __cs_l_pca_isa_init_dev;
        }
        __exit__pca_isa_init_5:;
    }
    {
        if (__cs_simulate == 0 && __cs_pc_5 == 3) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 3; __cs_simulate = 2;} else        {
                global_id = -1;
        }
        if (__cs_simulate == 0 && __cs_pc_5 == 4) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 4; __cs_simulate = 2;} else        {
                global_dev = -1;
        }
        __exit__pca_isa_exit_5:;
    }
    if (__cs_simulate == 0 && __cs_pc_5 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 5; __cs_simulate = 2;} else    {
            cnt5++;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_5 == 6))
    {
        __cs_pc_5 = 6;
        __cs_simulate = 2;
    }
}
/* Simulate req2_isr_2 */
void req2_isr_2(void)
{
    if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else    {
            irq = 0;
    }
    {
        static int __cs_l_pca_isa_init_dev;
        if (__cs_simulate == 1)
        {
                __cs_l_pca_isa_init_dev = 2;
        }
        static int __cs_l_pca_isa_init_id;
        if (__cs_simulate == 1)
        {
                __cs_l_pca_isa_init_id = 2;
        }
        if (__cs_simulate == 0 && __cs_pc_2 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 1; __cs_simulate = 2;} else        {
                global_id = __cs_l_pca_isa_init_id;
        }
        if (__cs_simulate == 0 && __cs_pc_2 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 2; __cs_simulate = 2;} else        {
                global_dev = __cs_l_pca_isa_init_dev;
        }
        __exit__pca_isa_init_2:;
    }
    {
        if (__cs_simulate == 0 && __cs_pc_2 == 3) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 3; __cs_simulate = 2;} else        {
                global_id = -1;
        }
        if (__cs_simulate == 0 && __cs_pc_2 == 4) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 4; __cs_simulate = 2;} else        {
                global_dev = -1;
        }
        __exit__pca_isa_exit_2:;
    }
    if (__cs_simulate == 0 && __cs_pc_2 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 5; __cs_simulate = 2;} else    {
            cnt2++;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 6))
    {
        __cs_pc_2 = 6;
        __cs_simulate = 2;
    }
}
/* Simulate req8_isr_8 */
void req8_isr_8(void)
{
        if (__cs_simulate == 0 && __cs_pc_8 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_8 = 0; __cs_simulate = 2;} else {
                    irq = 0;
                        static int __cs_l_pca_isa_init_dev;
                        __cs_l_pca_isa_init_dev = 8;
                        static int __cs_l_pca_isa_init_id;
                        __cs_l_pca_isa_init_id = 8;
                        global_id = __cs_l_pca_isa_init_id;
                        global_dev = __cs_l_pca_isa_init_dev;
                        __exit__pca_isa_init_7:
;
                        ;;
                        static int __cs_l_pca_isa_probe_dev;
                        __cs_l_pca_isa_probe_dev = 8;
                        static int __cs_l_pca_isa_probe_id;
                        __cs_l_pca_isa_probe_id = 8;
                                if (global_dev != __cs_l_pca_isa_probe_dev)
                                                if (irq > (-1))
                                                                            if (global_id != __cs_l_pca_isa_probe_id)
                        __exit__pca_isa_probe_1:
;
                        ;;
                        global_id = -1;
                        global_dev = -1;
                        __exit__pca_isa_exit_7:
;
                        ;;
                    cnt8++;
                    test_global_array[9000] = 999;
        }
                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_8 == 10))
                            {
                                __cs_pc_8 = 10;
                                __cs_simulate = 2;
                            }
}
/* Simulate original main */
int main_task()
                        {
                            if (__cs_simulate == 0 && __cs_pc_9 == 0) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_9 = 0; __cs_simulate = 2;} else                            {
                                    /*disable_isr(-1);*/
                                    __cs_disable_isr[0] = 1;
                                    __cs_disable_isr[7] = 1;
                                    __cs_disable_isr[3] = 1;
                                    __cs_disable_isr[1] = 1;
                                    __cs_disable_isr[6] = 1;
                                    __cs_disable_isr[5] = 1;
                                    __cs_disable_isr[2] = 1;
                                    __cs_disable_isr[8] = 1;
                                    __cs_disable_isr[4] = 1;
                            }
                            if (__cs_simulate == 0 && __cs_pc_9 == 1) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_9 = 1; __cs_simulate = 2;} else                            {
                                    test_global_condition1 = 1;
                            }
                            if (__cs_simulate == 0 && __cs_pc_9 == 2) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_9 = 2; __cs_simulate = 2;} else                            {
                                    test_global_condition2 = 1;
                            }
                            if (__cs_simulate == 0 && __cs_pc_9 == 3) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_9 = 3; __cs_simulate = 2;} else                            {
                                    test_global_condition3 = 1;
                            }
                            if (__cs_simulate == 0 && __cs_pc_9 == 4) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_9 = 4; __cs_simulate = 2;} else                            {
                                    test_global_condition4 = 1;
                            }
                            if (__cs_simulate == 0 && __cs_pc_9 == 5) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_9 = 5; __cs_simulate = 2;} else                            {
                                    /*enable_isr(-1);*/
                                    __cs_disable_isr[0] = 0;
                                    __cs_disable_isr[7] = 0;
                                    __cs_disable_isr[3] = 0;
                                    __cs_disable_isr[1] = 0;
                                    __cs_disable_isr[6] = 0;
                                    __cs_disable_isr[5] = 0;
                                    __cs_disable_isr[2] = 0;
                                    __cs_disable_isr[8] = 0;
                                    __cs_disable_isr[4] = 0;
                            }
                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_9 == 6))
                            {
                                __cs_pc_9 = 6;
                                __cs_simulate = 2;
                            }
                        }
/* Simulate req4_isr_4 */
void req4_isr_4(void)
                        {
                            if (__cs_simulate == 0 && __cs_pc_4 == 0) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 0; __cs_simulate = 2;} else                            {
                                    irq = 0;
                            }
                            {
                                static int __cs_l_pca_isa_init_dev;
                                if (__cs_simulate == 1)
                                {
                                        __cs_l_pca_isa_init_dev = 4;
                                }
                                static int __cs_l_pca_isa_init_id;
                                if (__cs_simulate == 1)
                                {
                                        __cs_l_pca_isa_init_id = 4;
                                }
                                if (__cs_simulate == 0 && __cs_pc_4 == 1) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 1; __cs_simulate = 2;} else                                {
                                        global_id = __cs_l_pca_isa_init_id;
                                }
                                if (__cs_simulate == 0 && __cs_pc_4 == 2) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 2; __cs_simulate = 2;} else                                {
                                        global_dev = __cs_l_pca_isa_init_dev;
                                }
                                __exit__pca_isa_init_4:;
                            }
                            {
                                if (__cs_simulate == 0 && __cs_pc_4 == 3) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 3; __cs_simulate = 2;} else                                {
                                        global_id = -1;
                                }
                                if (__cs_simulate == 0 && __cs_pc_4 == 4) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 4; __cs_simulate = 2;} else                                {
                                        global_dev = -1;
                                }
                                __exit__pca_isa_exit_4:;
                            }
                            if (__cs_simulate == 0 && __cs_pc_4 == 5) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 5; __cs_simulate = 2;} else                            {
                                    cnt4++;
                            }
                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 6))
                            {
                                __cs_pc_4 = 6;
                                __cs_simulate = 2;
                            }
                        }
/* main function (scheduler) */
int main()
{
  __cs_simulate = 0;
  __cs_pc_9 = 0;
  __cs_pc_1 = 0;
  __cs_pc_2 = 0;
  __cs_pc_3 = 0;
  __cs_pc_4 = 0;
  __cs_pc_5 = 0;
  __cs_pc_6 = 0;
  __cs_pc_7 = 0;
  __cs_pc_8 = 0;
  while (1)
  {
    __cs_simulate = 0;
    if ((__cs_pc_7 == 0 || __cs_pc_7 == 15)&&(__cs_pc_3 == 0 || __cs_pc_3 == 9)&&(__cs_pc_1 == 0 || __cs_pc_1 == 17)&&(__cs_pc_6 == 0 || __cs_pc_6 == 4)&&(__cs_pc_5 == 0 || __cs_pc_5 == 6)&&(__cs_pc_2 == 0 || __cs_pc_2 == 6)&&(__cs_pc_4 == 0 || __cs_pc_4 == 6)&&__cs_disable_isr[0] != 1) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_7 == 0 || __cs_pc_7 == 15)&&(__cs_pc_3 == 0 || __cs_pc_3 == 9)&&(__cs_pc_6 == 0 || __cs_pc_6 == 4)&&(__cs_pc_5 == 0 || __cs_pc_5 == 6)&&(__cs_pc_2 == 0 || __cs_pc_2 == 6)&&(__cs_pc_4 == 0 || __cs_pc_4 == 6)&&__cs_disable_isr[0] != 1) req1_isr_1();
    __cs_simulate = 0;
    if ((__cs_pc_7 == 0 || __cs_pc_7 == 15)&&(__cs_pc_3 == 0 || __cs_pc_3 == 9)&&(__cs_pc_1 == 0 || __cs_pc_1 == 17)&&(__cs_pc_6 == 0 || __cs_pc_6 == 4)&&(__cs_pc_5 == 0 || __cs_pc_5 == 6)&&(__cs_pc_4 == 0 || __cs_pc_4 == 6)&&__cs_disable_isr[1] != 1) req2_isr_2();
    __cs_simulate = 0;
    if ((__cs_pc_7 == 0 || __cs_pc_7 == 15)&&(__cs_pc_6 == 0 || __cs_pc_6 == 4)&&(__cs_pc_5 == 0 || __cs_pc_5 == 6)&&(__cs_pc_4 == 0 || __cs_pc_4 == 6)&&__cs_disable_isr[2] != 1) req3_isr_3();
    __cs_simulate = 0;
    if ((__cs_pc_7 == 0 || __cs_pc_7 == 15)&&(__cs_pc_3 == 0 || __cs_pc_3 == 9)&&(__cs_pc_6 == 0 || __cs_pc_6 == 4)&&(__cs_pc_5 == 0 || __cs_pc_5 == 6)&&__cs_disable_isr[3] != 1) req4_isr_4();
    __cs_simulate = 0;
    if ((__cs_pc_7 == 0 || __cs_pc_7 == 15)&&__cs_disable_isr[4] != 1) req5_isr_5();
    __cs_simulate = 0;
    if ((__cs_pc_7 == 0 || __cs_pc_7 == 15)&&(__cs_pc_3 == 0 || __cs_pc_3 == 9)&&(__cs_pc_5 == 0 || __cs_pc_5 == 6)&&(__cs_pc_4 == 0 || __cs_pc_4 == 6)&&__cs_disable_isr[5] != 1) req6_isr_6();
    __cs_simulate = 0;
    if (__cs_disable_isr[6] != 1) req7_isr_7();
    __cs_simulate = 0;
    if (__cs_disable_isr[7] != 1) req8_isr_8();
  }
}
