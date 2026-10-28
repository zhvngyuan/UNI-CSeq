// Main task
unsigned __CPROVER_bitvector[3] __cs_pc_4;
// closer2_isr_1
unsigned __CPROVER_bitvector[7] __cs_pc_1;
// closer1_isr_2
unsigned __CPROVER_bitvector[7] __cs_pc_2;
// writer1_isr_3
unsigned __CPROVER_bitvector[7] __cs_pc_3;
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
/* Global variables */
unsigned int ACPIBASE;
int tco_lock;
unsigned long timer_alive;
char tco_expect_close;
char tco_write_buf;
char tco1_rld;
void spin_lock(int);
void spin_unlock(int);
void outb(int, int);
void clear_bit(int, int);
void tco_timer_keepalive(void);
void i8xx_tco_release(void);
void i8xx_tco_write(int);
int tco1_cnt_b0;
int tco1_cnt_b1;
int tco1_cnt_b2;
int tco1_cnt_b3;
int tco1_cnt_b4;
int tco1_cnt_b5;
int tco1_cnt_b6;
int tco1_cnt_b7;
int heartbeat = 30;
int nowayout = 0;
int test_global_array[10000];
int test_global_var1;
int test_global_var2;
int test_global_var3;
int test_global_condition1;
int test_global_condition2;
int test_global_condition3;
int test_global_condition4;
int reader1;
int reader2;
void JudgeCondi(void);
/* Simulate closer2_isr_1 */
void closer2_isr_1(void)
{
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            tco_write_buf = 'V';
    }
    {
        static int __cs_l_i8xx_tco_write_len;
        if (__cs_simulate == 1)
        {
                __cs_l_i8xx_tco_write_len = 1;
        }
        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_7 = 0;
        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_1:;
        int loop_1_IOVar1;
        int loop_1_block_3;
        int t_1 = 0;
        if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_1 <= 31) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_7 < 1))))
        {
                    if (__cs_simulate == 1)
                    {
                            loop_1_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_7;
                    }
                    if (__cs_simulate == 1)
                    {
                            loop_1_block_3 = nondet_int();
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_7 = loop_1_IOVar1 + (1 * loop_1_block_3);
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(loop_1_block_3 >= 0);
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_7 < 1);
                    }
                    {
                        if (__cs_simulate == 0 && __cs_pc_1 == 4) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 4; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_1 <= 8) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                        {
                                    if (__cs_simulate == 0 && __cs_pc_1 == 5) __cs_simulate = 1;
                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 5; __cs_simulate = 2;}
                                    if ((__cs_simulate == 0 && __cs_pc_1 <= 8) || (__cs_simulate == 1 && (!nowayout)))
                                    {
                                                if (__cs_simulate == 0 && __cs_pc_1 == 6) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 6; __cs_simulate = 2;} else                                                {
                                                        tco_expect_close = 0;
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_1 == 7) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 7; __cs_simulate = 2;}
                                                if ((__cs_simulate == 0 && __cs_pc_1 <= 8) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 8) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 8; __cs_simulate = 2;} else                                                            {
                                                                    tco_expect_close = 42;
                                                            }
                                                }
                                    }
                        }
                        {
                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_1:;
                            int loop_2_IOVar1;
                            int loop_2_block_2;
                            int t_2 = 0;
                            if (__cs_simulate == 0 && __cs_pc_1 == 9) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 9; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_1 <= 19) || ((__cs_simulate == 1) && ((t_2 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_2_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_2_block_2 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_2_IOVar1 + (1 * loop_2_block_2);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_1 == 10) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 10; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_2_block_2 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_1 == 11) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 11; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1);
                                        }
                                        {
                                            {
                                                static int __cs_l_outb_v;
                                                if (__cs_simulate == 1)
                                                {
                                                        __cs_l_outb_v = 0x01;
                                                }
                                                static int __cs_l_outb_l;
                                                if (__cs_simulate == 0 && __cs_pc_1 == 12) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 12; __cs_simulate = 2;} else                                                {
                                                        __cs_l_outb_l = tco1_rld;
                                                }
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_1:;
                                                int loop_3_IOVar1;
                                                int loop_3_block_1;
                                                int t_3 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_1 == 13) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 13; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_1 <= 15) || ((__cs_simulate == 1) && ((t_3 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_3_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_3_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_3_IOVar1 + (1 * loop_3_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 14) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 14; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_3_block_1 >= 0);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 15) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 15; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_3++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_1 == 16) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 16; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_1:;
                                                __begin_outb_loop_1_outb_1:;
                                                int t_4 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_1 == 17) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 17; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_1 <= 18) || ((__cs_simulate == 1) && ((t_4 < 1) && 0)))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 18) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 18; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(0);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_4++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_1 == 19) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 19; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!0);
                                                }
                                                __end_outb_loop_1_outb_1:;
                                                __exit__outb_1:;
                                            }
                                            if (__cs_simulate == 1)
                                            {
                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_2++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_1 == 20) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 20; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                            }
                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_1:;
                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_1:;
                            int t_5 = 0;
                            if (__cs_simulate == 0 && __cs_pc_1 == 21) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 21; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_1 <= 30) || ((__cs_simulate == 1) && ((t_5 < 2) && 0)))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_1 == 22) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 22; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(0);
                                        }
                                        {
                                            {
                                                static int __cs_l_outb_v;
                                                if (__cs_simulate == 1)
                                                {
                                                        __cs_l_outb_v = 0x01;
                                                }
                                                static int __cs_l_outb_l;
                                                if (__cs_simulate == 0 && __cs_pc_1 == 23) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 23; __cs_simulate = 2;} else                                                {
                                                        __cs_l_outb_l = tco1_rld;
                                                }
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_2:;
                                                int loop_6_IOVar1;
                                                int loop_6_block_1;
                                                int t_6 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_1 == 24) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 24; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_1 <= 26) || ((__cs_simulate == 1) && ((t_6 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_6_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_6_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_6_IOVar1 + (1 * loop_6_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 25) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 25; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_6_block_1 >= 0);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 26) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 26; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_6++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_1 == 27) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 27; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_2:;
                                                __begin_outb_loop_1_outb_2:;
                                                int t_7 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_1 == 28) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 28; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_1 <= 29) || ((__cs_simulate == 1) && ((t_7 < 1) && 0)))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 29) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 29; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(0);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_7++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_1 == 30) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 30; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!0);
                                                }
                                                __end_outb_loop_1_outb_2:;
                                                __exit__outb_2:;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_5++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_1 == 31) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 31; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!0);
                            }
                            __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_1:;
                            __exit__tco_timer_keepalive_1:;
                        }
                        if (__cs_simulate == 1)
                        {
                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_7++;
                        }
                    }
                    if (__cs_simulate == 1)
                    {
                            t_1++;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_1 == 32) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 32; __cs_simulate = 2;} else        {
                __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_7 < 1));
        }
        __end_i8xx_tco_write_loop_0_i8xx_tco_write_1:;
        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_1:;
        int t_8 = 0;
        if (__cs_simulate == 0 && __cs_pc_1 == 33) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 33; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_1 <= 62) || ((__cs_simulate == 1) && ((t_8 < 1) && 0)))
        {
                    if (__cs_simulate == 0 && __cs_pc_1 == 34) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 34; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(0);
                    }
                    {
                        if (__cs_simulate == 0 && __cs_pc_1 == 35) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 35; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_1 <= 39) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                        {
                                    if (__cs_simulate == 0 && __cs_pc_1 == 36) __cs_simulate = 1;
                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 36; __cs_simulate = 2;}
                                    if ((__cs_simulate == 0 && __cs_pc_1 <= 39) || (__cs_simulate == 1 && (!nowayout)))
                                    {
                                                if (__cs_simulate == 0 && __cs_pc_1 == 37) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 37; __cs_simulate = 2;} else                                                {
                                                        tco_expect_close = 0;
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_1 == 38) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 38; __cs_simulate = 2;}
                                                if ((__cs_simulate == 0 && __cs_pc_1 <= 39) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 39) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 39; __cs_simulate = 2;} else                                                            {
                                                                    tco_expect_close = 42;
                                                            }
                                                }
                                    }
                        }
                        {
                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_2:;
                            int loop_9_IOVar1;
                            int loop_9_block_2;
                            int t_9 = 0;
                            if (__cs_simulate == 0 && __cs_pc_1 == 40) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 40; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_1 <= 50) || ((__cs_simulate == 1) && ((t_9 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_9_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_9_block_2 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_9_IOVar1 + (1 * loop_9_block_2);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_1 == 41) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 41; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_9_block_2 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_1 == 42) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 42; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1);
                                        }
                                        {
                                            {
                                                static int __cs_l_outb_v;
                                                if (__cs_simulate == 1)
                                                {
                                                        __cs_l_outb_v = 0x01;
                                                }
                                                static int __cs_l_outb_l;
                                                if (__cs_simulate == 0 && __cs_pc_1 == 43) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 43; __cs_simulate = 2;} else                                                {
                                                        __cs_l_outb_l = tco1_rld;
                                                }
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_3:;
                                                int loop_10_IOVar1;
                                                int loop_10_block_1;
                                                int t_10 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_1 == 44) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 44; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_1 <= 46) || ((__cs_simulate == 1) && ((t_10 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_10_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_10_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_10_IOVar1 + (1 * loop_10_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 45) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 45; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_10_block_1 >= 0);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 46) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 46; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_10++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_1 == 47) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 47; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_3:;
                                                __begin_outb_loop_1_outb_3:;
                                                int t_11 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_1 == 48) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 48; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_1 <= 49) || ((__cs_simulate == 1) && ((t_11 < 1) && 0)))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 49) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 49; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(0);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_11++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_1 == 50) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 50; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!0);
                                                }
                                                __end_outb_loop_1_outb_3:;
                                                __exit__outb_3:;
                                            }
                                            if (__cs_simulate == 1)
                                            {
                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_9++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_1 == 51) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 51; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                            }
                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_2:;
                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_2:;
                            int t_12 = 0;
                            if (__cs_simulate == 0 && __cs_pc_1 == 52) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 52; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_1 <= 61) || ((__cs_simulate == 1) && ((t_12 < 2) && 0)))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_1 == 53) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 53; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(0);
                                        }
                                        {
                                            {
                                                static int __cs_l_outb_v;
                                                if (__cs_simulate == 1)
                                                {
                                                        __cs_l_outb_v = 0x01;
                                                }
                                                static int __cs_l_outb_l;
                                                if (__cs_simulate == 0 && __cs_pc_1 == 54) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 54; __cs_simulate = 2;} else                                                {
                                                        __cs_l_outb_l = tco1_rld;
                                                }
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_4:;
                                                int loop_13_IOVar1;
                                                int loop_13_block_1;
                                                int t_13 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_1 == 55) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 55; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_1 <= 57) || ((__cs_simulate == 1) && ((t_13 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_13_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_13_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_13_IOVar1 + (1 * loop_13_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 56) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 56; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_13_block_1 >= 0);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 57) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 57; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_13++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_1 == 58) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 58; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_4:;
                                                __begin_outb_loop_1_outb_4:;
                                                int t_14 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_1 == 59) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 59; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_1 <= 60) || ((__cs_simulate == 1) && ((t_14 < 1) && 0)))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 60) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 60; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(0);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_14++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_1 == 61) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 61; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!0);
                                                }
                                                __end_outb_loop_1_outb_4:;
                                                __exit__outb_4:;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_12++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_1 == 62) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 62; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!0);
                            }
                            __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_2:;
                            __exit__tco_timer_keepalive_2:;
                        }
                    }
                    if (__cs_simulate == 1)
                    {
                            t_8++;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_1 == 63) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 63; __cs_simulate = 2;} else        {
                __CPROVER_assume(!0);
        }
        __end_i8xx_tco_write_loop_1_i8xx_tco_write_1:;
        __exit__i8xx_tco_write_1:;
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 64) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 64; __cs_simulate = 2;} else    {
            tco_expect_close = 42;
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 65) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 65; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_1 <= 75) || (__cs_simulate == 1 && (tco_expect_close == 42)))
    {
                {
                    static int __cs_l_JudgeCondi_reader3;
                    if (__cs_simulate == 0 && __cs_pc_1 == 66) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 66; __cs_simulate = 2;} else                    {
                            __cs_init_scalar(&__cs_l_JudgeCondi_reader3, sizeof(int));
                    }
                    static int __cs_l_JudgeCondi_reader4;
                    if (__cs_simulate == 0 && __cs_pc_1 == 67) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 67; __cs_simulate = 2;} else                    {
                            __cs_init_scalar(&__cs_l_JudgeCondi_reader4, sizeof(int));
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 68) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 68; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_1 <= 69) || (__cs_simulate == 1 && (test_global_condition1 == 1)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_1 == 69) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 69; __cs_simulate = 2;} else                                {
                                        reader1 = test_global_var1;
                                }
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 70) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 70; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_1 <= 71) || (__cs_simulate == 1 && (test_global_condition2 == 1)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_1 == 71) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 71; __cs_simulate = 2;} else                                {
                                        reader2 = test_global_var1;
                                }
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 72) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 72; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_1 <= 73) || (__cs_simulate == 1 && (reader1 != reader2)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_1 == 73) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 73; __cs_simulate = 2;} else                                {
                                        assert(0);
                                }
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 74) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 74; __cs_simulate = 2;} else                    {
                            __cs_l_JudgeCondi_reader3 = test_global_var2;
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 75) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 75; __cs_simulate = 2;} else                    {
                            __cs_l_JudgeCondi_reader4 = test_global_var2;
                    }
                    __exit__JudgeCondi_1:;
                }
    }
    {
        static int __cs_l_i8xx_tco_release___cs_dowhile_onetime_6 = 0;
        __begin_i8xx_tco_release_loop_0_i8xx_tco_release_1:;
        int loop_15_IOVar1;
        int loop_15_block_2;
        int t_15 = 0;
        if (__cs_simulate == 0 && __cs_pc_1 == 76) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 76; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_1 <= 87) || ((__cs_simulate == 1) && ((t_15 < 4) && (__cs_l_i8xx_tco_release___cs_dowhile_onetime_6 < 1))))
        {
                    if (__cs_simulate == 1)
                    {
                            loop_15_IOVar1 = __cs_l_i8xx_tco_release___cs_dowhile_onetime_6;
                    }
                    if (__cs_simulate == 1)
                    {
                            loop_15_block_2 = nondet_int();
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_i8xx_tco_release___cs_dowhile_onetime_6 = loop_15_IOVar1 + (1 * loop_15_block_2);
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 77) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 77; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(loop_15_block_2 >= 0);
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 78) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 78; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(__cs_l_i8xx_tco_release___cs_dowhile_onetime_6 < 1);
                    }
                    {
                        {
                            static int __cs_l_clear_bit_unused;
                            if (__cs_simulate == 1)
                            {
                                    __cs_l_clear_bit_unused = 0;
                            }
                            static int __cs_l_clear_bit_v;
                            if (__cs_simulate == 0 && __cs_pc_1 == 79) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 79; __cs_simulate = 2;} else                            {
                                    __cs_l_clear_bit_v = timer_alive;
                            }
                            static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                            __begin_clear_bit_loop_0_clear_bit_1:;
                            int loop_16_IOVar1;
                            int loop_16_block_1;
                            int t_16 = 0;
                            if (__cs_simulate == 0 && __cs_pc_1 == 80) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 80; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_1 <= 82) || ((__cs_simulate == 1) && ((t_16 < 2) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_16_IOVar1 = __cs_l_clear_bit___cs_dowhile_onetime_4;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_16_block_1 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_clear_bit___cs_dowhile_onetime_4 = loop_16_IOVar1 + (1 * loop_16_block_1);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_1 == 81) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 81; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_16_block_1 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_1 == 82) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 82; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1);
                                        }
                                        {
                                            if (__cs_simulate == 1)
                                            {
                                                    __cs_l_clear_bit_v = 0;
                                            }
                                            if (__cs_simulate == 1)
                                            {
                                                    __cs_l_clear_bit___cs_dowhile_onetime_4++;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_16++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_1 == 83) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 83; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1));
                            }
                            __end_clear_bit_loop_0_clear_bit_1:;
                            __begin_clear_bit_loop_1_clear_bit_1:;
                            int t_17 = 0;
                            if (__cs_simulate == 0 && __cs_pc_1 == 84) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 84; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_1 <= 85) || ((__cs_simulate == 1) && ((t_17 < 1) && 0)))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_1 == 85) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 85; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(0);
                                        }
                                        {
                                            if (__cs_simulate == 1)
                                            {
                                                    __cs_l_clear_bit_v = 0;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_17++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_1 == 86) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 86; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!0);
                            }
                            __end_clear_bit_loop_1_clear_bit_1:;
                            __exit__clear_bit_1:;
                        }
                        if (__cs_simulate == 0 && __cs_pc_1 == 87) __cs_simulate = 1;
                        if (__cs_simulate == 1)
                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 87; __cs_simulate = 2;} else                        {
                                tco_expect_close = 0;
                        }
                        if (__cs_simulate == 1)
                        {
                                __cs_l_i8xx_tco_release___cs_dowhile_onetime_6++;
                        }
                    }
                    if (__cs_simulate == 1)
                    {
                            t_15++;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_1 == 88) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 88; __cs_simulate = 2;} else        {
                __CPROVER_assume(!(__cs_l_i8xx_tco_release___cs_dowhile_onetime_6 < 1));
        }
        __end_i8xx_tco_release_loop_0_i8xx_tco_release_1:;
        __begin_i8xx_tco_release_loop_1_i8xx_tco_release_1:;
        int t_18 = 0;
        if (__cs_simulate == 0 && __cs_pc_1 == 89) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 89; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_1 <= 99) || ((__cs_simulate == 1) && ((t_18 < 3) && 0)))
        {
                    if (__cs_simulate == 0 && __cs_pc_1 == 90) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 90; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(0);
                    }
                    {
                        {
                            static int __cs_l_clear_bit_unused;
                            if (__cs_simulate == 1)
                            {
                                    __cs_l_clear_bit_unused = 0;
                            }
                            static int __cs_l_clear_bit_v;
                            if (__cs_simulate == 0 && __cs_pc_1 == 91) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 91; __cs_simulate = 2;} else                            {
                                    __cs_l_clear_bit_v = timer_alive;
                            }
                            static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                            __begin_clear_bit_loop_0_clear_bit_2:;
                            int loop_19_IOVar1;
                            int loop_19_block_1;
                            int t_19 = 0;
                            if (__cs_simulate == 0 && __cs_pc_1 == 92) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 92; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_1 <= 94) || ((__cs_simulate == 1) && ((t_19 < 2) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_19_IOVar1 = __cs_l_clear_bit___cs_dowhile_onetime_4;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_19_block_1 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_clear_bit___cs_dowhile_onetime_4 = loop_19_IOVar1 + (1 * loop_19_block_1);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_1 == 93) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 93; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_19_block_1 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_1 == 94) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 94; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1);
                                        }
                                        {
                                            if (__cs_simulate == 1)
                                            {
                                                    __cs_l_clear_bit_v = 0;
                                            }
                                            if (__cs_simulate == 1)
                                            {
                                                    __cs_l_clear_bit___cs_dowhile_onetime_4++;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_19++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_1 == 95) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 95; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1));
                            }
                            __end_clear_bit_loop_0_clear_bit_2:;
                            __begin_clear_bit_loop_1_clear_bit_2:;
                            int t_20 = 0;
                            if (__cs_simulate == 0 && __cs_pc_1 == 96) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 96; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_1 <= 97) || ((__cs_simulate == 1) && ((t_20 < 1) && 0)))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_1 == 97) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 97; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(0);
                                        }
                                        {
                                            if (__cs_simulate == 1)
                                            {
                                                    __cs_l_clear_bit_v = 0;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_20++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_1 == 98) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 98; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!0);
                            }
                            __end_clear_bit_loop_1_clear_bit_2:;
                            __exit__clear_bit_2:;
                        }
                        if (__cs_simulate == 0 && __cs_pc_1 == 99) __cs_simulate = 1;
                        if (__cs_simulate == 1)
                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 99; __cs_simulate = 2;} else                        {
                                tco_expect_close = 0;
                        }
                    }
                    if (__cs_simulate == 1)
                    {
                            t_18++;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_1 == 100) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 100; __cs_simulate = 2;} else        {
                __CPROVER_assume(!0);
        }
        __end_i8xx_tco_release_loop_1_i8xx_tco_release_1:;
        __exit__i8xx_tco_release_1:;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 101))
    {
        __cs_pc_1 = 101;
        __cs_simulate = 2;
    }
}
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_4 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 0; __cs_simulate = 2;} else    {
            /*disable_isr(-1);*/
            __cs_disable_isr_0 = 1;
            __cs_disable_isr_1 = 1;
            __cs_disable_isr_3 = 1;
            __cs_disable_isr_2 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_4 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 1; __cs_simulate = 2;} else    {
            test_global_condition1 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_4 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 2; __cs_simulate = 2;} else    {
            test_global_condition2 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_4 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 3; __cs_simulate = 2;} else    {
            test_global_condition3 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_4 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 4; __cs_simulate = 2;} else    {
            test_global_condition4 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_4 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 5; __cs_simulate = 2;} else    {
            tco_expect_close = 0;
    }
    if (__cs_simulate == 0 && __cs_pc_4 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 6; __cs_simulate = 2;} else    {
            /*enable_isr(-1);*/
            __cs_disable_isr_0 = 0;
            __cs_disable_isr_1 = 0;
            __cs_disable_isr_3 = 0;
            __cs_disable_isr_2 = 0;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 7))
    {
        __cs_pc_4 = 7;
        __cs_simulate = 2;
    }
}
/* Simulate writer1_isr_3 */
void writer1_isr_3(void)
{
    {
        static int __cs_l_i8xx_tco_write_len;
        if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else        {
                __cs_l_i8xx_tco_write_len = 0;
        }
        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_7 = 0;
        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_3:;
        int loop_41_IOVar1;
        int loop_41_block_3;
        int t_41 = 0;
        if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_3 <= 31) || ((__cs_simulate == 1) && ((t_41 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_7 < 1))))
        {
                    if (__cs_simulate == 1)
                    {
                            loop_41_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_7;
                    }
                    if (__cs_simulate == 1)
                    {
                            loop_41_block_3 = nondet_int();
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_7 = loop_41_IOVar1 + (1 * loop_41_block_3);
                    }
                    if (__cs_simulate == 0 && __cs_pc_3 == 2) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 2; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(loop_41_block_3 >= 0);
                    }
                    if (__cs_simulate == 0 && __cs_pc_3 == 3) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 3; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_7 < 1);
                    }
                    {
                        if (__cs_simulate == 0 && __cs_pc_3 == 4) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 4; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_3 <= 8) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                        {
                                    if (__cs_simulate == 0 && __cs_pc_3 == 5) __cs_simulate = 1;
                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 5; __cs_simulate = 2;}
                                    if ((__cs_simulate == 0 && __cs_pc_3 <= 8) || (__cs_simulate == 1 && (!nowayout)))
                                    {
                                                if (__cs_simulate == 0 && __cs_pc_3 == 6) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 6; __cs_simulate = 2;} else                                                {
                                                        tco_expect_close = 0;
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 7) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 7; __cs_simulate = 2;}
                                                if ((__cs_simulate == 0 && __cs_pc_3 <= 8) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 8) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 8; __cs_simulate = 2;} else                                                            {
                                                                    tco_expect_close = 42;
                                                            }
                                                }
                                    }
                        }
                        {
                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_5:;
                            int loop_42_IOVar1;
                            int loop_42_block_2;
                            int t_42 = 0;
                            if (__cs_simulate == 0 && __cs_pc_3 == 9) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 9; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_3 <= 19) || ((__cs_simulate == 1) && ((t_42 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_42_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_42_block_2 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_42_IOVar1 + (1 * loop_42_block_2);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_3 == 10) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 10; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_42_block_2 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_3 == 11) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 11; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1);
                                        }
                                        {
                                            {
                                                static int __cs_l_outb_v;
                                                if (__cs_simulate == 1)
                                                {
                                                        __cs_l_outb_v = 0x01;
                                                }
                                                static int __cs_l_outb_l;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 12) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 12; __cs_simulate = 2;} else                                                {
                                                        __cs_l_outb_l = tco1_rld;
                                                }
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_9:;
                                                int loop_43_IOVar1;
                                                int loop_43_block_1;
                                                int t_43 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 13) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 13; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 15) || ((__cs_simulate == 1) && ((t_43 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_43_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_43_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_43_IOVar1 + (1 * loop_43_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 14) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 14; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_43_block_1 >= 0);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 15) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 15; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_43++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 16) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 16; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_9:;
                                                __begin_outb_loop_1_outb_9:;
                                                int t_44 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 17) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 17; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 18) || ((__cs_simulate == 1) && ((t_44 < 1) && 0)))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 18) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 18; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(0);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_44++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 19) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 19; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!0);
                                                }
                                                __end_outb_loop_1_outb_9:;
                                                __exit__outb_9:;
                                            }
                                            if (__cs_simulate == 1)
                                            {
                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_42++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_3 == 20) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 20; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                            }
                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_5:;
                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_5:;
                            int t_45 = 0;
                            if (__cs_simulate == 0 && __cs_pc_3 == 21) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 21; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_3 <= 30) || ((__cs_simulate == 1) && ((t_45 < 2) && 0)))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_3 == 22) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 22; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(0);
                                        }
                                        {
                                            {
                                                static int __cs_l_outb_v;
                                                if (__cs_simulate == 1)
                                                {
                                                        __cs_l_outb_v = 0x01;
                                                }
                                                static int __cs_l_outb_l;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 23) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 23; __cs_simulate = 2;} else                                                {
                                                        __cs_l_outb_l = tco1_rld;
                                                }
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_10:;
                                                int loop_46_IOVar1;
                                                int loop_46_block_1;
                                                int t_46 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 24) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 24; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 26) || ((__cs_simulate == 1) && ((t_46 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_46_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_46_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_46_IOVar1 + (1 * loop_46_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 25) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 25; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_46_block_1 >= 0);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 26) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 26; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_46++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 27) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 27; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_10:;
                                                __begin_outb_loop_1_outb_10:;
                                                int t_47 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 28) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 28; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 29) || ((__cs_simulate == 1) && ((t_47 < 1) && 0)))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 29) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 29; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(0);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_47++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 30) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 30; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!0);
                                                }
                                                __end_outb_loop_1_outb_10:;
                                                __exit__outb_10:;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_45++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_3 == 31) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 31; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!0);
                            }
                            __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_5:;
                            __exit__tco_timer_keepalive_5:;
                        }
                        if (__cs_simulate == 1)
                        {
                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_7++;
                        }
                    }
                    if (__cs_simulate == 1)
                    {
                            t_41++;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_3 == 32) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 32; __cs_simulate = 2;} else        {
                __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_7 < 1));
        }
        __end_i8xx_tco_write_loop_0_i8xx_tco_write_3:;
        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_3:;
        int t_48 = 0;
        if (__cs_simulate == 0 && __cs_pc_3 == 33) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 33; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_3 <= 62) || ((__cs_simulate == 1) && ((t_48 < 1) && 0)))
        {
                    if (__cs_simulate == 0 && __cs_pc_3 == 34) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 34; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(0);
                    }
                    {
                        if (__cs_simulate == 0 && __cs_pc_3 == 35) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 35; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_3 <= 39) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                        {
                                    if (__cs_simulate == 0 && __cs_pc_3 == 36) __cs_simulate = 1;
                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 36; __cs_simulate = 2;}
                                    if ((__cs_simulate == 0 && __cs_pc_3 <= 39) || (__cs_simulate == 1 && (!nowayout)))
                                    {
                                                if (__cs_simulate == 0 && __cs_pc_3 == 37) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 37; __cs_simulate = 2;} else                                                {
                                                        tco_expect_close = 0;
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 38) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 38; __cs_simulate = 2;}
                                                if ((__cs_simulate == 0 && __cs_pc_3 <= 39) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 39) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 39; __cs_simulate = 2;} else                                                            {
                                                                    tco_expect_close = 42;
                                                            }
                                                }
                                    }
                        }
                        {
                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_6:;
                            int loop_49_IOVar1;
                            int loop_49_block_2;
                            int t_49 = 0;
                            if (__cs_simulate == 0 && __cs_pc_3 == 40) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 40; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_3 <= 50) || ((__cs_simulate == 1) && ((t_49 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_49_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_49_block_2 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_49_IOVar1 + (1 * loop_49_block_2);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_3 == 41) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 41; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_49_block_2 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_3 == 42) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 42; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1);
                                        }
                                        {
                                            {
                                                static int __cs_l_outb_v;
                                                if (__cs_simulate == 1)
                                                {
                                                        __cs_l_outb_v = 0x01;
                                                }
                                                static int __cs_l_outb_l;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 43) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 43; __cs_simulate = 2;} else                                                {
                                                        __cs_l_outb_l = tco1_rld;
                                                }
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_11:;
                                                int loop_50_IOVar1;
                                                int loop_50_block_1;
                                                int t_50 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 44) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 44; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 46) || ((__cs_simulate == 1) && ((t_50 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_50_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_50_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_50_IOVar1 + (1 * loop_50_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 45) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 45; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_50_block_1 >= 0);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 46) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 46; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_50++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 47) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 47; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_11:;
                                                __begin_outb_loop_1_outb_11:;
                                                int t_51 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 48) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 48; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 49) || ((__cs_simulate == 1) && ((t_51 < 1) && 0)))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 49) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 49; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(0);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_51++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 50) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 50; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!0);
                                                }
                                                __end_outb_loop_1_outb_11:;
                                                __exit__outb_11:;
                                            }
                                            if (__cs_simulate == 1)
                                            {
                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_49++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_3 == 51) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 51; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                            }
                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_6:;
                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_6:;
                            int t_52 = 0;
                            if (__cs_simulate == 0 && __cs_pc_3 == 52) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 52; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_3 <= 61) || ((__cs_simulate == 1) && ((t_52 < 2) && 0)))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_3 == 53) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 53; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(0);
                                        }
                                        {
                                            {
                                                static int __cs_l_outb_v;
                                                if (__cs_simulate == 1)
                                                {
                                                        __cs_l_outb_v = 0x01;
                                                }
                                                static int __cs_l_outb_l;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 54) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 54; __cs_simulate = 2;} else                                                {
                                                        __cs_l_outb_l = tco1_rld;
                                                }
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_12:;
                                                int loop_53_IOVar1;
                                                int loop_53_block_1;
                                                int t_53 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 55) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 55; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 57) || ((__cs_simulate == 1) && ((t_53 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_53_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_53_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_53_IOVar1 + (1 * loop_53_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 56) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 56; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_53_block_1 >= 0);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 57) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 57; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_53++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 58) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 58; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_12:;
                                                __begin_outb_loop_1_outb_12:;
                                                int t_54 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 59) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 59; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 60) || ((__cs_simulate == 1) && ((t_54 < 1) && 0)))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 60) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 60; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(0);
                                                            }
                                                            {
                                                                if (__cs_simulate == 1)
                                                                {
                                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                                }
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    t_54++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 61) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 61; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!0);
                                                }
                                                __end_outb_loop_1_outb_12:;
                                                __exit__outb_12:;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_52++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_3 == 62) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 62; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!0);
                            }
                            __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_6:;
                            __exit__tco_timer_keepalive_6:;
                        }
                    }
                    if (__cs_simulate == 1)
                    {
                            t_48++;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_3 == 63) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 63; __cs_simulate = 2;} else        {
                __CPROVER_assume(!0);
        }
        __end_i8xx_tco_write_loop_1_i8xx_tco_write_3:;
        __exit__i8xx_tco_write_3:;
    }
    static int __cs_l_writer1_isr_3_i = 0;
    static int __cs_l_writer1_isr_3_maxnum;
    if (__cs_simulate == 0 && __cs_pc_3 == 64) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 64; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_writer1_isr_3_maxnum, sizeof(int));
    }
    static int __cs_l_writer1_isr_3_mininum;
    if (__cs_simulate == 0 && __cs_pc_3 == 65) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 65; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_writer1_isr_3_mininum, sizeof(int));
    }
    if (__cs_simulate == 1)
    {
            __cs_l_writer1_isr_3_i = 0;
    }
    __begin_writer1_isr_3_loop_0:;
    int loop_55_IOVar1;
    int loop_55_block_3;
    int t_55 = 0;
    if (__cs_simulate == 0 && __cs_pc_3 == 66) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 66; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_3 <= 72) || ((__cs_simulate == 1) && ((t_55 < 2) && (__cs_l_writer1_isr_3_i < 10000))))
    {
                if (__cs_simulate == 1)
                {
                        loop_55_IOVar1 = __cs_l_writer1_isr_3_i;
                }
                if (__cs_simulate == 1)
                {
                        loop_55_block_3 = nondet_int();
                }
                if (__cs_simulate == 1)
                {
                        __cs_l_writer1_isr_3_i = loop_55_IOVar1 + (1 * loop_55_block_3);
                }
                if (__cs_simulate == 0 && __cs_pc_3 == 67) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 67; __cs_simulate = 2;} else                {
                        __CPROVER_assume(loop_55_block_3 >= 0);
                }
                if (__cs_simulate == 0 && __cs_pc_3 == 68) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 68; __cs_simulate = 2;} else                {
                        __CPROVER_assume(__cs_l_writer1_isr_3_i < 10000);
                }
                {
                    if (__cs_simulate == 0 && __cs_pc_3 == 69) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 69; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_3 <= 70) || (__cs_simulate == 1 && (__cs_l_writer1_isr_3_i == 9000)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_3 == 70) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 70; __cs_simulate = 2;} else                                {
                                        test_global_array[9000] = 1;
                                }
                    }
                    if (__cs_simulate == 0 && __cs_pc_3 == 71) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 71; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_3 <= 72) || (__cs_simulate == 1 && (__cs_l_writer1_isr_3_i == 10001)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_3 == 72) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 72; __cs_simulate = 2;} else                                {
                                        test_global_array[9000] = 1;
                                }
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_writer1_isr_3_i++;
                    }
                }
                if (__cs_simulate == 1)
                {
                        t_55++;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 73) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 73; __cs_simulate = 2;} else    {
            __CPROVER_assume(!(__cs_l_writer1_isr_3_i < 10000));
    }
    __end_writer1_isr_3_loop_0:;
    if (__cs_simulate == 0 && __cs_pc_3 == 74) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 74; __cs_simulate = 2;} else    {
            __cs_l_writer1_isr_3_mininum = test_global_array[9000] - 10;
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 75) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 75; __cs_simulate = 2;} else    {
            __cs_l_writer1_isr_3_maxnum = test_global_array[0] + 10;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 76))
    {
        __cs_pc_3 = 76;
        __cs_simulate = 2;
    }
}
/* Simulate closer1_isr_2 */
void closer1_isr_2(void)
{
        if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else {
                    if (test_global_condition3 == 0)
                        test_global_var1 = 0x11;
                    else;
                        test_global_var2 = 0x22;
                    tco_write_buf = 'V';
                        static int __cs_l_i8xx_tco_write_len;
                        __cs_l_i8xx_tco_write_len = 1;
                        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_7 = 0;
                        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_2:
;
                        ;;
                        int loop_21_IOVar1;
                        int loop_21_block_3;
                        int t_21 = 0;
                    while ((t_21 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_7 < 1)){
                            loop_21_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_7;
                            loop_21_block_3 = nondet_int();
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_7 = loop_21_IOVar1 + (1 * loop_21_block_3);
                            __CPROVER_assume(loop_21_block_3 >= 0);
                            __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_7 < 1);
                                                                        if (__cs_l_i8xx_tco_write_len)
                                                                                                    if (!nowayout)
                                        tco_expect_close = 0;
                                                                                                                                if (tco_write_buf == 'V')
                                            tco_expect_close = 42;
                                    static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                    __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_3:
;
                                    ;;
                                    int loop_22_IOVar1;
                                    int loop_22_block_2;
                                    int t_22 = 0;
                                while ((t_22 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)){
                                        loop_22_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                        loop_22_block_2 = nondet_int();
                                        __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_22_IOVar1 + (1 * loop_22_block_2);
                                                                __CPROVER_assume(loop_22_block_2 >= 0);
                                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_5:
;
                                                ;;
                                                int loop_23_IOVar1;
                                                int loop_23_block_1;
                                                int t_23 = 0;
                                            while ((t_23 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_23_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_23_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_23_IOVar1 + (1 * loop_23_block_1);
                                                                            __CPROVER_assume(loop_23_block_1 >= 0);
                                                                            __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_23++;
                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_5:
;
                                                ;;
                                                __begin_outb_loop_1_outb_5:
;
                                                ;;
                                                int t_24 = 0;
                                            while ((t_24 < 1) && 0){
                                                                            __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_24++;
                                                                        __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_5:
;
                                                ;;
                                                __exit__outb_5:
;
                                                ;;
                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                        t_22++;
                                                            __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                }
                                    __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_3:
;
                                    ;;
                                    __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_3:
;
                                    ;;
                                    int t_25 = 0;
                                while ((t_25 < 2) && 0){
                                                                __CPROVER_assume(0);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_6:
;
                                                ;;
                                                int loop_26_IOVar1;
                                                int loop_26_block_1;
                                                int t_26 = 0;
                                            while ((t_26 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_26_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_26_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_26_IOVar1 + (1 * loop_26_block_1);
                                                                            __CPROVER_assume(loop_26_block_1 >= 0);
                                                                            __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_26++;
                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_6:
;
                                                ;;
                                                __begin_outb_loop_1_outb_6:
;
                                                ;;
                                                int t_27 = 0;
                                            while ((t_27 < 1) && 0){
                                                                            __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_27++;
                                                                        __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_6:
;
                                                ;;
                                                __exit__outb_6:
;
                                                ;;
                                        t_25++;
                                                            __CPROVER_assume(!0);
                                }
                                    __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_3:
;
                                    ;;
                                    __exit__tco_timer_keepalive_3:
;
                                    ;;
                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_7++;
                            t_21++;
                                                __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_7 < 1));
                    }
                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_2:
;
                        ;;
                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_2:
;
                        ;;
                        int t_28 = 0;
                    while ((t_28 < 1) && 0){
                                                    __CPROVER_assume(0);
                                                                                                                        if (__cs_l_i8xx_tco_write_len)
                                                                                                                                                    if (!nowayout)
                                        tco_expect_close = 0;
                                                                                                                                                                                if (tco_write_buf == 'V')
                                            tco_expect_close = 42;
                                    static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                    __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_4:
;
                                    ;;
                                    int loop_29_IOVar1;
                                    int loop_29_block_2;
                                    int t_29 = 0;
                                while ((t_29 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)){
                                        loop_29_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                        loop_29_block_2 = nondet_int();
                                        __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_29_IOVar1 + (1 * loop_29_block_2);
                                                                                        __CPROVER_assume(loop_29_block_2 >= 0);
                                                                                        __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_7:
;
                                                ;;
                                                int loop_30_IOVar1;
                                                int loop_30_block_1;
                                                int t_30 = 0;
                                            while ((t_30 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_30_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_30_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_30_IOVar1 + (1 * loop_30_block_1);
                                                                                                    __CPROVER_assume(loop_30_block_1 >= 0);
                                                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_30++;
                                                                                                __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_7:
;
                                                ;;
                                                __begin_outb_loop_1_outb_7:
;
                                                ;;
                                                int t_31 = 0;
                                            while ((t_31 < 1) && 0){
                                                                                                    __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_31++;
                                                                                                __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_7:
;
                                                ;;
                                                __exit__outb_7:
;
                                                ;;
                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                        t_29++;
                                                                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                }
                                    __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_4:
;
                                    ;;
                                    __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_4:
;
                                    ;;
                                    int t_32 = 0;
                                while ((t_32 < 2) && 0){
                                                                                        __CPROVER_assume(0);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_8:
;
                                                ;;
                                                int loop_33_IOVar1;
                                                int loop_33_block_1;
                                                int t_33 = 0;
                                            while ((t_33 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_33_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_33_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_33_IOVar1 + (1 * loop_33_block_1);
                                                                                                    __CPROVER_assume(loop_33_block_1 >= 0);
                                                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_33++;
                                                                                                __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_8:
;
                                                ;;
                                                __begin_outb_loop_1_outb_8:
;
                                                ;;
                                                int t_34 = 0;
                                            while ((t_34 < 1) && 0){
                                                                                                    __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_34++;
                                                                                                __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_8:
;
                                                ;;
                                                __exit__outb_8:
;
                                                ;;
                                        t_32++;
                                                                                    __CPROVER_assume(!0);
                                }
                                    __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_4:
;
                                    ;;
                                    __exit__tco_timer_keepalive_4:
;
                                    ;;
                            t_28++;
                                                                        __CPROVER_assume(!0);
                    }
                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_2:
;
                        ;;
                        __exit__i8xx_tco_write_2:
;
                        ;;
                    tco_expect_close = 42;
                        static int __cs_l_i8xx_tco_release___cs_dowhile_onetime_6 = 0;
                        __begin_i8xx_tco_release_loop_0_i8xx_tco_release_2:
;
                        ;;
                        int loop_35_IOVar1;
                        int loop_35_block_2;
                        int t_35 = 0;
                    while ((t_35 < 4) && (__cs_l_i8xx_tco_release___cs_dowhile_onetime_6 < 1)){
                            loop_35_IOVar1 = __cs_l_i8xx_tco_release___cs_dowhile_onetime_6;
                            loop_35_block_2 = nondet_int();
                            __cs_l_i8xx_tco_release___cs_dowhile_onetime_6 = loop_35_IOVar1 + (1 * loop_35_block_2);
                                                                            __CPROVER_assume(loop_35_block_2 >= 0);
                                                                            __CPROVER_assume(__cs_l_i8xx_tco_release___cs_dowhile_onetime_6 < 1);
                                    static int __cs_l_clear_bit_unused;
                                    __cs_l_clear_bit_unused = 0;
                                    static int __cs_l_clear_bit_v;
                                    __cs_l_clear_bit_v = timer_alive;
                                    static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                                    __begin_clear_bit_loop_0_clear_bit_3:
;
                                    ;;
                                    int loop_36_IOVar1;
                                    int loop_36_block_1;
                                    int t_36 = 0;
                                while ((t_36 < 2) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1)){
                                        loop_36_IOVar1 = __cs_l_clear_bit___cs_dowhile_onetime_4;
                                        loop_36_block_1 = nondet_int();
                                        __cs_l_clear_bit___cs_dowhile_onetime_4 = loop_36_IOVar1 + (1 * loop_36_block_1);
                                                                                        __CPROVER_assume(loop_36_block_1 >= 0);
                                                                                        __CPROVER_assume(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1);
                                            __cs_l_clear_bit_v = 0;
                                            __cs_l_clear_bit___cs_dowhile_onetime_4++;
                                        t_36++;
                                                                                    __CPROVER_assume(!(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1));
                                }
                                    __end_clear_bit_loop_0_clear_bit_3:
;
                                    ;;
                                    __begin_clear_bit_loop_1_clear_bit_3:
;
                                    ;;
                                    int t_37 = 0;
                                while ((t_37 < 1) && 0){
                                                                                        __CPROVER_assume(0);
                                            __cs_l_clear_bit_v = 0;
                                        t_37++;
                                                                                    __CPROVER_assume(!0);
                                }
                                    __end_clear_bit_loop_1_clear_bit_3:
;
                                    ;;
                                    __exit__clear_bit_3:
;
                                    ;;
                                tco_expect_close = 0;
                                __cs_l_i8xx_tco_release___cs_dowhile_onetime_6++;
                            t_35++;
                                                                        __CPROVER_assume(!(__cs_l_i8xx_tco_release___cs_dowhile_onetime_6 < 1));
                    }
                        __end_i8xx_tco_release_loop_0_i8xx_tco_release_2:
;
                        ;;
                        __begin_i8xx_tco_release_loop_1_i8xx_tco_release_2:
;
                        ;;
                        int t_38 = 0;
                    while ((t_38 < 3) && 0){
                                                                            __CPROVER_assume(0);
                                    static int __cs_l_clear_bit_unused;
                                    __cs_l_clear_bit_unused = 0;
                                    static int __cs_l_clear_bit_v;
                                    __cs_l_clear_bit_v = timer_alive;
                                    static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                                    __begin_clear_bit_loop_0_clear_bit_4:
;
                                    ;;
                                    int loop_39_IOVar1;
                                    int loop_39_block_1;
                                    int t_39 = 0;
                                while ((t_39 < 2) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1)){
                                        loop_39_IOVar1 = __cs_l_clear_bit___cs_dowhile_onetime_4;
                                        loop_39_block_1 = nondet_int();
                                        __cs_l_clear_bit___cs_dowhile_onetime_4 = loop_39_IOVar1 + (1 * loop_39_block_1);
                                                                                        __CPROVER_assume(loop_39_block_1 >= 0);
                                                                                        __CPROVER_assume(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1);
                                            __cs_l_clear_bit_v = 0;
                                            __cs_l_clear_bit___cs_dowhile_onetime_4++;
                                        t_39++;
                                                                                    __CPROVER_assume(!(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1));
                                }
                                    __end_clear_bit_loop_0_clear_bit_4:
;
                                    ;;
                                    __begin_clear_bit_loop_1_clear_bit_4:
;
                                    ;;
                                    int t_40 = 0;
                                while ((t_40 < 1) && 0){
                                                                                        __CPROVER_assume(0);
                                            __cs_l_clear_bit_v = 0;
                                        t_40++;
                                                                                    __CPROVER_assume(!0);
                                }
                                    __end_clear_bit_loop_1_clear_bit_4:
;
                                    ;;
                                    __exit__clear_bit_4:
;
                                    ;;
                                tco_expect_close = 0;
                            t_38++;
                                                                        __CPROVER_assume(!0);
                    }
                        __end_i8xx_tco_release_loop_1_i8xx_tco_release_2:
;
                        ;;
                        __exit__i8xx_tco_release_2:
;
                        ;;
                                                                                                                                    if (test_global_condition4 == 1)
                        test_global_array[9000] = 999;
                                                                                                                                                    if (test_global_array[9000] != 999)
                                                                                        assert(0);
        }
                                                                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 97))
                                                                            {
                                                                                __cs_pc_2 = 97;
                                                                                __cs_simulate = 2;
                                                                            }
}
/* main function (scheduler) */
int main()
{
  __cs_simulate = 0;
  __cs_pc_4 = 0;
  __cs_pc_1 = 0;
  __cs_pc_2 = 0;
  __cs_pc_3 = 0;
  __cs_disable_isr_0 = 0;
  __cs_disable_isr_1 = 0;
  __cs_disable_isr_2 = 0;
  __cs_disable_isr_3 = 0;
  while (1)
  {
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 76)&&(__cs_pc_1 == 0 || __cs_pc_1 == 101)&&__cs_disable_isr_0 != 1) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 76)&&__cs_disable_isr_1 != 1) closer2_isr_1();
    __cs_simulate = 0;
    if (__cs_disable_isr_2 != 1) closer1_isr_2();
    __cs_simulate = 0;
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 101)&&__cs_disable_isr_3 != 1) writer1_isr_3();
  }
}
