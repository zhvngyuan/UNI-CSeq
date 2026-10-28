// Main task
unsigned __CPROVER_bitvector[6] __cs_pc_0;
// svp_simple_003_001_isr_1
unsigned __CPROVER_bitvector[3] __cs_pc_1;
// svp_simple_003_001_isr_2
unsigned __CPROVER_bitvector[1] __cs_pc_2;
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
int svp_simple_003_001_global_var1 = 0;
int svp_simple_003_001_global_var2 = 0;
int svp_simple_003_001_global_flag = 1;
int svp_simple_003_001_global_flag1 = 0;
/* Simulate original main */
void main_task()
{
    static int __cs_l_main_reader1_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_reader1_1, sizeof(int));
    }}
    static int __cs_l_main_reader2_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_reader2_1, sizeof(int));
    }}
    static int __cs_l_main_reader3_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_reader3_1, sizeof(int));
    }}
    static int __cs_l_main_reader4_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_reader4_1, sizeof(int));
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;} else    {
            /*disable_isr(1);*/
            __cs_disable_isr_1 = 1;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else    {
            /*disable_isr(2);*/
            __cs_disable_isr_2 = 1;
    }}
    static int __cs_l_main_i_1;
    if (__cs_simulate == 1)
    {
            __cs_l_main_i_1 = 0;
    }
    __begin_main_loop_0:;
    int loop_1_IOVar1;
    int loop_1_block_2;
    int t_1 = 0;
    if (__cs_simulate == 0 && __cs_pc_0 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 6; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_0 <= 10) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_main_i_1 < 10))))
    {
                if (__cs_simulate == 1)
                {
                        loop_1_IOVar1 = __cs_l_main_i_1;
                }
                if (__cs_simulate == 1)
                {
                        loop_1_block_2 = __VERIFIER_nondet_int();
                }
                if (__cs_simulate == 1)
                {
                        __cs_l_main_i_1 = loop_1_IOVar1 + (1 * loop_1_block_2);
                }
                if (__cs_simulate == 0 && __cs_pc_0 == 7) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 7; __cs_simulate = 2;} else                {
                        __CPROVER_assume(loop_1_block_2 >= 0);
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 8) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 8; __cs_simulate = 2;} else                {
                        __CPROVER_assume(__cs_l_main_i_1 < 10);
                }}
                {
                    if (__cs_simulate == 0 && __cs_pc_0 == 9) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 9; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_0 <= 10) || (__cs_simulate == 1 && (__cs_l_main_i_1 == 9)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_0 == 10) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 10; __cs_simulate = 2;} else                                {
                                        __cs_l_main_reader3_1 = svp_simple_003_001_global_var2;
                                }}
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_main_i_1++;
                    }
                }
                if (__cs_simulate == 1)
                {
                        t_1++;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 11) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 11; __cs_simulate = 2;} else    {
            __CPROVER_assume(!(__cs_l_main_i_1 < 10));
    }}
    __end_main_loop_0:;
    static int __cs_l_main_j_1;
    if (__cs_simulate == 1)
    {
            __cs_l_main_j_1 = 10;
    }
    __begin_main_loop_1:;
    if (__cs_simulate == 0 && __cs_pc_0 == 12) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 12; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 15) || (__cs_simulate == 1 && (__cs_l_main_j_1 > 0)))
    {
                {
                    if (__cs_simulate == 0 && __cs_pc_0 == 13) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 13; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_0 <= 15) || (__cs_simulate == 1 && (__cs_l_main_j_1 == 9)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_0 == 14) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 14; __cs_simulate = 2;} else                                {
                                        __cs_l_main_reader4_1 = svp_simple_003_001_global_var2;
                                }}
                                if (__cs_simulate == 0 && __cs_pc_0 == 15) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 15; __cs_simulate = 2;} else                                {
                                        assert(svp_simple_003_001_global_var2 == 0);
                                }}
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_main_j_1--;
                    }
                }
    }
    int loop_2_IOVar1;
    int loop_2_block_2;
    int t_2 = 0;
    if (__cs_simulate == 0 && __cs_pc_0 == 16) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 16; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_0 <= 21) || ((__cs_simulate == 1) && ((t_2 < 2) && (__cs_l_main_j_1 > 0))))
    {
                if (__cs_simulate == 1)
                {
                        loop_2_IOVar1 = __cs_l_main_j_1;
                }
                if (__cs_simulate == 1)
                {
                        loop_2_block_2 = __VERIFIER_nondet_int();
                }
                if (__cs_simulate == 1)
                {
                        __cs_l_main_j_1 = loop_2_IOVar1 - (1 * loop_2_block_2);
                }
                if (__cs_simulate == 0 && __cs_pc_0 == 17) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 17; __cs_simulate = 2;} else                {
                        __CPROVER_assume(loop_2_block_2 >= 0);
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 18) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 18; __cs_simulate = 2;} else                {
                        __CPROVER_assume(__cs_l_main_j_1 > 0);
                }}
                {
                    if (__cs_simulate == 0 && __cs_pc_0 == 19) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 19; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_0 <= 21) || (__cs_simulate == 1 && (__cs_l_main_j_1 == 9)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_0 == 20) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 20; __cs_simulate = 2;} else                                {
                                        __cs_l_main_reader4_1 = svp_simple_003_001_global_var2;
                                }}
                                if (__cs_simulate == 0 && __cs_pc_0 == 21) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 21; __cs_simulate = 2;} else                                {
                                        __CPROVER_assume(svp_simple_003_001_global_var2 == 0);
                                }}
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_main_j_1--;
                    }
                }
                if (__cs_simulate == 1)
                {
                        t_2++;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 22) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 22; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 25) || (__cs_simulate == 1 && (__cs_l_main_j_1 > 0)))
    {
                {
                    if (__cs_simulate == 0 && __cs_pc_0 == 23) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 23; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_0 <= 25) || (__cs_simulate == 1 && (__cs_l_main_j_1 == 9)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_0 == 24) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 24; __cs_simulate = 2;} else                                {
                                        __cs_l_main_reader4_1 = svp_simple_003_001_global_var2;
                                }}
                                if (__cs_simulate == 0 && __cs_pc_0 == 25) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 25; __cs_simulate = 2;} else                                {
                                        assert(svp_simple_003_001_global_var2 == 0);
                                }}
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_main_j_1--;
                    }
                }
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 26) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 26; __cs_simulate = 2;} else    {
            __CPROVER_assume(!(__cs_l_main_j_1 > 0));
    }}
    __end_main_loop_1:;
    if (__cs_simulate == 0 && __cs_pc_0 == 27) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 27; __cs_simulate = 2;} else    {
            /*enable_isr(1);*/
            __cs_disable_isr_1 = 0;
    }}
    static int __cs_l_main_i1_1;
    if (__cs_simulate == 1)
    {
            __cs_l_main_i1_1 = 0;
    }
    __begin_main_loop_2:;
    int loop_3_IOVar1;
    int loop_3_block_2;
    int t_3 = 0;
    if (__cs_simulate == 0 && __cs_pc_0 == 28) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 28; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_0 <= 32) || ((__cs_simulate == 1) && ((t_3 < 2) && (__cs_l_main_i1_1 < 10))))
    {
                if (__cs_simulate == 1)
                {
                        loop_3_IOVar1 = __cs_l_main_i1_1;
                }
                if (__cs_simulate == 1)
                {
                        loop_3_block_2 = __VERIFIER_nondet_int();
                }
                if (__cs_simulate == 1)
                {
                        __cs_l_main_i1_1 = loop_3_IOVar1 + (1 * loop_3_block_2);
                }
                if (__cs_simulate == 0 && __cs_pc_0 == 29) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 29; __cs_simulate = 2;} else                {
                        __CPROVER_assume(loop_3_block_2 >= 0);
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 30) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 30; __cs_simulate = 2;} else                {
                        __CPROVER_assume(__cs_l_main_i1_1 < 10);
                }}
                {
                    if (__cs_simulate == 0 && __cs_pc_0 == 31) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 31; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_0 <= 32) || (__cs_simulate == 1 && (__cs_l_main_i1_1 == 9)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_0 == 32) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 32; __cs_simulate = 2;} else                                {
                                        __cs_l_main_reader1_1 = svp_simple_003_001_global_var1;
                                }}
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_main_i1_1++;
                    }
                }
                if (__cs_simulate == 1)
                {
                        t_3++;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 33) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 33; __cs_simulate = 2;} else    {
            __CPROVER_assume(!(__cs_l_main_i1_1 < 10));
    }}
    __end_main_loop_2:;
    static int __cs_l_main_j1_1;
    if (__cs_simulate == 1)
    {
            __cs_l_main_j1_1 = 10;
    }
    __begin_main_loop_3:;
    int loop_4_IOVar1;
    int loop_4_block_2;
    int t_4 = 0;
    if (__cs_simulate == 0 && __cs_pc_0 == 34) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 34; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_0 <= 38) || ((__cs_simulate == 1) && ((t_4 < 2) && (__cs_l_main_j1_1 > 0))))
    {
                if (__cs_simulate == 1)
                {
                        loop_4_IOVar1 = __cs_l_main_j1_1;
                }
                if (__cs_simulate == 1)
                {
                        loop_4_block_2 = __VERIFIER_nondet_int();
                }
                if (__cs_simulate == 1)
                {
                        __cs_l_main_j1_1 = loop_4_IOVar1 - (1 * loop_4_block_2);
                }
                if (__cs_simulate == 0 && __cs_pc_0 == 35) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 35; __cs_simulate = 2;} else                {
                        __CPROVER_assume(loop_4_block_2 >= 0);
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 36) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 36; __cs_simulate = 2;} else                {
                        __CPROVER_assume(__cs_l_main_j1_1 > 0);
                }}
                {
                    if (__cs_simulate == 0 && __cs_pc_0 == 37) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 37; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_0 <= 38) || (__cs_simulate == 1 && (__cs_l_main_j1_1 == 9)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_0 == 38) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 38; __cs_simulate = 2;} else                                {
                                        __cs_l_main_reader2_1 = svp_simple_003_001_global_var1;
                                }}
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_main_j1_1--;
                    }
                }
                if (__cs_simulate == 1)
                {
                        t_4++;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 39) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 39; __cs_simulate = 2;} else    {
            __CPROVER_assume(!(__cs_l_main_j1_1 > 0));
    }}
    __end_main_loop_3:;
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 40))
    {
        __cs_pc_0 = 40;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_003_001_isr_2 */
void svp_simple_003_001_isr_2()
{
        if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else 
{
                    svp_simple_003_001_global_flag = 1;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 1))
    {
        __cs_pc_2 = 1;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_003_001_isr_1 */
void svp_simple_003_001_isr_1()
{
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            /*enable_isr(2);*/
            __cs_disable_isr_2 = 0;
    }}
    if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;} else    {
            svp_simple_003_001_global_var2 = 999;
    }}
    if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_1 <= 3) || (__cs_simulate == 1 && (svp_simple_003_001_global_flag == 1)))
    {
                if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;} else                {
                        svp_simple_003_001_global_var1 = 999;
                }}
    }
    else
if ((__cs_simulate == 0 && __cs_pc_1 <= 5) || (__cs_simulate == 1))    {
                if (__cs_simulate == 0 && __cs_pc_1 == 4) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 4; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_1 <= 5) || (__cs_simulate == 1 && (svp_simple_003_001_global_flag1 == 2)))
                {
                            if (__cs_simulate == 0 && __cs_pc_1 == 5) __cs_simulate = 1;
                            if (__cs_simulate == 1){
                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 5; __cs_simulate = 2;} else                            {
                                    svp_simple_003_001_global_var1 = 888;
                            }}
                }
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 6))
    {
        __cs_pc_1 = 6;
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
  __cs_disable_isr_0 = 0;
  __cs_disable_isr_1 = 0;
  __cs_disable_isr_2 = 0;
  while (1)
  {
    __cs_simulate = 0;
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 6)) main_task();
    __cs_simulate = 0;
    if (__cs_disable_isr_1 != 1) {
        svp_simple_003_001_isr_1();
        if (__cs_pc_1 == 6) __cs_pc_1 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_2 != 1) {
        svp_simple_003_001_isr_2();
        if (__cs_pc_2 == 1) __cs_pc_2 = 0;
    }
  }
}
