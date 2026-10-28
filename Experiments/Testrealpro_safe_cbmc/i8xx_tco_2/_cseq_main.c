// Main task
unsigned __CPROVER_bitvector[5] __cs_pc_5;
// closer1_isr_1
unsigned __CPROVER_bitvector[7] __cs_pc_1;
// closer2_isr_2
unsigned __CPROVER_bitvector[7] __cs_pc_2;
// writer1_isr_3
unsigned __CPROVER_bitvector[7] __cs_pc_3;
// writer2_isr_4
unsigned __CPROVER_bitvector[7] __cs_pc_4;
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
/* Simulate closer2_isr_2 */
void closer2_isr_2(void)
{
    if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else    {
            tco_write_buf = 'V';
    }
    {
        static int __cs_l_i8xx_tco_write_len;
        if (__cs_simulate == 1)
        {
                __cs_l_i8xx_tco_write_len = 1;
        }
        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_8 = 0;
        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_2:;
        int loop_15_IOVar1;
        int loop_15_block_3;
        int t_15 = 0;
        if (__cs_simulate == 0 && __cs_pc_2 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 1; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_2 <= 31) || ((__cs_simulate == 1) && ((t_15 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_8 < 1))))
        {
                    if (__cs_simulate == 1)
                    {
                            loop_15_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_8;
                    }
                    if (__cs_simulate == 1)
                    {
                            loop_15_block_3 = nondet_int();
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_8 = loop_15_IOVar1 + (1 * loop_15_block_3);
                    }
                    if (__cs_simulate == 0 && __cs_pc_2 == 2) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 2; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(loop_15_block_3 >= 0);
                    }
                    if (__cs_simulate == 0 && __cs_pc_2 == 3) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 3; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_8 < 1);
                    }
                    {
                        if (__cs_simulate == 0 && __cs_pc_2 == 4) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 4; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_2 <= 8) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                        {
                                    if (__cs_simulate == 0 && __cs_pc_2 == 5) __cs_simulate = 1;
                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 5; __cs_simulate = 2;}
                                    if ((__cs_simulate == 0 && __cs_pc_2 <= 8) || (__cs_simulate == 1 && (!nowayout)))
                                    {
                                                if (__cs_simulate == 0 && __cs_pc_2 == 6) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 6; __cs_simulate = 2;} else                                                {
                                                        tco_expect_close = 0;
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_2 == 7) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 7; __cs_simulate = 2;}
                                                if ((__cs_simulate == 0 && __cs_pc_2 <= 8) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 8) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 8; __cs_simulate = 2;} else                                                            {
                                                                    tco_expect_close = 42;
                                                            }
                                                }
                                    }
                        }
                        {
                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = 0;
                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_3:;
                            int loop_16_IOVar1;
                            int loop_16_block_2;
                            int t_16 = 0;
                            if (__cs_simulate == 0 && __cs_pc_2 == 9) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 9; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_2 <= 19) || ((__cs_simulate == 1) && ((t_16 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_16_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_16_block_2 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = loop_16_IOVar1 + (1 * loop_16_block_2);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_2 == 10) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 10; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_16_block_2 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_2 == 11) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 11; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1);
                                        }
                                        {
                                            {
                                                static int __cs_l_outb_v;
                                                if (__cs_simulate == 1)
                                                {
                                                        __cs_l_outb_v = 0x01;
                                                }
                                                static int __cs_l_outb_l;
                                                if (__cs_simulate == 0 && __cs_pc_2 == 12) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 12; __cs_simulate = 2;} else                                                {
                                                        __cs_l_outb_l = tco1_rld;
                                                }
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_5:;
                                                int loop_17_IOVar1;
                                                int loop_17_block_1;
                                                int t_17 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_2 == 13) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 13; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 15) || ((__cs_simulate == 1) && ((t_17 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_17_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_17_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_17_IOVar1 + (1 * loop_17_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 14) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 14; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_17_block_1 >= 0);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 15) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 15; __cs_simulate = 2;} else                                                            {
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
                                                                    t_17++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_2 == 16) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 16; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_5:;
                                                __begin_outb_loop_1_outb_5:;
                                                int t_18 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_2 == 17) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 17; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 18) || ((__cs_simulate == 1) && ((t_18 < 1) && 0)))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 18) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 18; __cs_simulate = 2;} else                                                            {
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
                                                                    t_18++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_2 == 19) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 19; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!0);
                                                }
                                                __end_outb_loop_1_outb_5:;
                                                __exit__outb_5:;
                                            }
                                            if (__cs_simulate == 1)
                                            {
                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6++;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_16++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_2 == 20) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 20; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1));
                            }
                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_3:;
                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_3:;
                            int t_19 = 0;
                            if (__cs_simulate == 0 && __cs_pc_2 == 21) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 21; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_2 <= 30) || ((__cs_simulate == 1) && ((t_19 < 2) && 0)))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_2 == 22) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 22; __cs_simulate = 2;} else                                        {
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
                                                if (__cs_simulate == 0 && __cs_pc_2 == 23) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 23; __cs_simulate = 2;} else                                                {
                                                        __cs_l_outb_l = tco1_rld;
                                                }
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_6:;
                                                int loop_20_IOVar1;
                                                int loop_20_block_1;
                                                int t_20 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_2 == 24) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 24; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 26) || ((__cs_simulate == 1) && ((t_20 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_20_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_20_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_20_IOVar1 + (1 * loop_20_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 25) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 25; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_20_block_1 >= 0);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 26) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 26; __cs_simulate = 2;} else                                                            {
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
                                                                    t_20++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_2 == 27) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 27; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_6:;
                                                __begin_outb_loop_1_outb_6:;
                                                int t_21 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_2 == 28) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 28; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 29) || ((__cs_simulate == 1) && ((t_21 < 1) && 0)))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 29) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 29; __cs_simulate = 2;} else                                                            {
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
                                                                    t_21++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_2 == 30) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 30; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!0);
                                                }
                                                __end_outb_loop_1_outb_6:;
                                                __exit__outb_6:;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_19++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_2 == 31) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 31; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!0);
                            }
                            __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_3:;
                            __exit__tco_timer_keepalive_3:;
                        }
                        if (__cs_simulate == 1)
                        {
                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_8++;
                        }
                    }
                    if (__cs_simulate == 1)
                    {
                            t_15++;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_2 == 32) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 32; __cs_simulate = 2;} else        {
                __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_8 < 1));
        }
        __end_i8xx_tco_write_loop_0_i8xx_tco_write_2:;
        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_2:;
        int t_22 = 0;
        if (__cs_simulate == 0 && __cs_pc_2 == 33) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 33; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_2 <= 62) || ((__cs_simulate == 1) && ((t_22 < 1) && 0)))
        {
                    if (__cs_simulate == 0 && __cs_pc_2 == 34) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 34; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(0);
                    }
                    {
                        if (__cs_simulate == 0 && __cs_pc_2 == 35) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 35; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_2 <= 39) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                        {
                                    if (__cs_simulate == 0 && __cs_pc_2 == 36) __cs_simulate = 1;
                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 36; __cs_simulate = 2;}
                                    if ((__cs_simulate == 0 && __cs_pc_2 <= 39) || (__cs_simulate == 1 && (!nowayout)))
                                    {
                                                if (__cs_simulate == 0 && __cs_pc_2 == 37) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 37; __cs_simulate = 2;} else                                                {
                                                        tco_expect_close = 0;
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_2 == 38) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 38; __cs_simulate = 2;}
                                                if ((__cs_simulate == 0 && __cs_pc_2 <= 39) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 39) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 39; __cs_simulate = 2;} else                                                            {
                                                                    tco_expect_close = 42;
                                                            }
                                                }
                                    }
                        }
                        {
                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = 0;
                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_4:;
                            int loop_23_IOVar1;
                            int loop_23_block_2;
                            int t_23 = 0;
                            if (__cs_simulate == 0 && __cs_pc_2 == 40) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 40; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_2 <= 50) || ((__cs_simulate == 1) && ((t_23 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_23_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_23_block_2 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = loop_23_IOVar1 + (1 * loop_23_block_2);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_2 == 41) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 41; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_23_block_2 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_2 == 42) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 42; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1);
                                        }
                                        {
                                            {
                                                static int __cs_l_outb_v;
                                                if (__cs_simulate == 1)
                                                {
                                                        __cs_l_outb_v = 0x01;
                                                }
                                                static int __cs_l_outb_l;
                                                if (__cs_simulate == 0 && __cs_pc_2 == 43) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 43; __cs_simulate = 2;} else                                                {
                                                        __cs_l_outb_l = tco1_rld;
                                                }
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_7:;
                                                int loop_24_IOVar1;
                                                int loop_24_block_1;
                                                int t_24 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_2 == 44) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 44; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 46) || ((__cs_simulate == 1) && ((t_24 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_24_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_24_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_24_IOVar1 + (1 * loop_24_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 45) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 45; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_24_block_1 >= 0);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 46) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 46; __cs_simulate = 2;} else                                                            {
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
                                                                    t_24++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_2 == 47) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 47; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_7:;
                                                __begin_outb_loop_1_outb_7:;
                                                int t_25 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_2 == 48) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 48; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 49) || ((__cs_simulate == 1) && ((t_25 < 1) && 0)))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 49) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 49; __cs_simulate = 2;} else                                                            {
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
                                                                    t_25++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_2 == 50) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 50; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!0);
                                                }
                                                __end_outb_loop_1_outb_7:;
                                                __exit__outb_7:;
                                            }
                                            if (__cs_simulate == 1)
                                            {
                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6++;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_23++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_2 == 51) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 51; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1));
                            }
                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_4:;
                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_4:;
                            int t_26 = 0;
                            if (__cs_simulate == 0 && __cs_pc_2 == 52) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 52; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_2 <= 61) || ((__cs_simulate == 1) && ((t_26 < 2) && 0)))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_2 == 53) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 53; __cs_simulate = 2;} else                                        {
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
                                                if (__cs_simulate == 0 && __cs_pc_2 == 54) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 54; __cs_simulate = 2;} else                                                {
                                                        __cs_l_outb_l = tco1_rld;
                                                }
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_8:;
                                                int loop_27_IOVar1;
                                                int loop_27_block_1;
                                                int t_27 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_2 == 55) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 55; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 57) || ((__cs_simulate == 1) && ((t_27 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_27_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_27_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_27_IOVar1 + (1 * loop_27_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 56) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 56; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_27_block_1 >= 0);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 57) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 57; __cs_simulate = 2;} else                                                            {
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
                                                                    t_27++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_2 == 58) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 58; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_8:;
                                                __begin_outb_loop_1_outb_8:;
                                                int t_28 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_2 == 59) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 59; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 60) || ((__cs_simulate == 1) && ((t_28 < 1) && 0)))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 60) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 60; __cs_simulate = 2;} else                                                            {
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
                                                                    t_28++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_2 == 61) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 61; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!0);
                                                }
                                                __end_outb_loop_1_outb_8:;
                                                __exit__outb_8:;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_26++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_2 == 62) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 62; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!0);
                            }
                            __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_4:;
                            __exit__tco_timer_keepalive_4:;
                        }
                    }
                    if (__cs_simulate == 1)
                    {
                            t_22++;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_2 == 63) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 63; __cs_simulate = 2;} else        {
                __CPROVER_assume(!0);
        }
        __end_i8xx_tco_write_loop_1_i8xx_tco_write_2:;
        __exit__i8xx_tco_write_2:;
    }
    if (__cs_simulate == 0 && __cs_pc_2 == 64) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 64; __cs_simulate = 2;} else    {
            tco_expect_close = 42;
    }
    {
        static int __cs_l_i8xx_tco_release___cs_dowhile_onetime_7 = 0;
        __begin_i8xx_tco_release_loop_0_i8xx_tco_release_1:;
        int loop_29_IOVar1;
        int loop_29_block_2;
        int t_29 = 0;
        if (__cs_simulate == 0 && __cs_pc_2 == 65) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 65; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_2 <= 77) || ((__cs_simulate == 1) && ((t_29 < 4) && (__cs_l_i8xx_tco_release___cs_dowhile_onetime_7 < 1))))
        {
                    if (__cs_simulate == 1)
                    {
                            loop_29_IOVar1 = __cs_l_i8xx_tco_release___cs_dowhile_onetime_7;
                    }
                    if (__cs_simulate == 1)
                    {
                            loop_29_block_2 = nondet_int();
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_i8xx_tco_release___cs_dowhile_onetime_7 = loop_29_IOVar1 + (1 * loop_29_block_2);
                    }
                    if (__cs_simulate == 0 && __cs_pc_2 == 66) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 66; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(loop_29_block_2 >= 0);
                    }
                    if (__cs_simulate == 0 && __cs_pc_2 == 67) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 67; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(__cs_l_i8xx_tco_release___cs_dowhile_onetime_7 < 1);
                    }
                    {
                        if (__cs_simulate == 0 && __cs_pc_2 == 68) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 68; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_2 <= 68) || (__cs_simulate == 1 && (tco_expect_close != 42)))
                        {
                        }
                        else
if ((__cs_simulate == 0 && __cs_pc_2 <= 68) || (__cs_simulate == 1))                        {
                        }
                        {
                            static int __cs_l_clear_bit_unused;
                            if (__cs_simulate == 1)
                            {
                                    __cs_l_clear_bit_unused = 0;
                            }
                            static int __cs_l_clear_bit_v;
                            if (__cs_simulate == 0 && __cs_pc_2 == 69) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 69; __cs_simulate = 2;} else                            {
                                    __cs_l_clear_bit_v = timer_alive;
                            }
                            static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                            __begin_clear_bit_loop_0_clear_bit_1:;
                            int loop_30_IOVar1;
                            int loop_30_block_1;
                            int t_30 = 0;
                            if (__cs_simulate == 0 && __cs_pc_2 == 70) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 70; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_2 <= 72) || ((__cs_simulate == 1) && ((t_30 < 2) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_30_IOVar1 = __cs_l_clear_bit___cs_dowhile_onetime_4;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_30_block_1 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_clear_bit___cs_dowhile_onetime_4 = loop_30_IOVar1 + (1 * loop_30_block_1);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_2 == 71) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 71; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_30_block_1 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_2 == 72) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 72; __cs_simulate = 2;} else                                        {
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
                                                t_30++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_2 == 73) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 73; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1));
                            }
                            __end_clear_bit_loop_0_clear_bit_1:;
                            __begin_clear_bit_loop_1_clear_bit_1:;
                            int t_31 = 0;
                            if (__cs_simulate == 0 && __cs_pc_2 == 74) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 74; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_2 <= 75) || ((__cs_simulate == 1) && ((t_31 < 1) && 0)))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_2 == 75) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 75; __cs_simulate = 2;} else                                        {
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
                                                t_31++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_2 == 76) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 76; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!0);
                            }
                            __end_clear_bit_loop_1_clear_bit_1:;
                            __exit__clear_bit_1:;
                        }
                        if (__cs_simulate == 0 && __cs_pc_2 == 77) __cs_simulate = 1;
                        if (__cs_simulate == 1)
                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 77; __cs_simulate = 2;} else                        {
                                tco_expect_close = 0;
                        }
                        if (__cs_simulate == 1)
                        {
                                __cs_l_i8xx_tco_release___cs_dowhile_onetime_7++;
                        }
                    }
                    if (__cs_simulate == 1)
                    {
                            t_29++;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_2 == 78) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 78; __cs_simulate = 2;} else        {
                __CPROVER_assume(!(__cs_l_i8xx_tco_release___cs_dowhile_onetime_7 < 1));
        }
        __end_i8xx_tco_release_loop_0_i8xx_tco_release_1:;
        __begin_i8xx_tco_release_loop_1_i8xx_tco_release_1:;
        int t_32 = 0;
        if (__cs_simulate == 0 && __cs_pc_2 == 79) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 79; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_2 <= 90) || ((__cs_simulate == 1) && ((t_32 < 3) && 0)))
        {
                    if (__cs_simulate == 0 && __cs_pc_2 == 80) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 80; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(0);
                    }
                    {
                        if (__cs_simulate == 0 && __cs_pc_2 == 81) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 81; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_2 <= 81) || (__cs_simulate == 1 && (tco_expect_close != 42)))
                        {
                        }
                        else
if ((__cs_simulate == 0 && __cs_pc_2 <= 81) || (__cs_simulate == 1))                        {
                        }
                        {
                            static int __cs_l_clear_bit_unused;
                            if (__cs_simulate == 1)
                            {
                                    __cs_l_clear_bit_unused = 0;
                            }
                            static int __cs_l_clear_bit_v;
                            if (__cs_simulate == 0 && __cs_pc_2 == 82) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 82; __cs_simulate = 2;} else                            {
                                    __cs_l_clear_bit_v = timer_alive;
                            }
                            static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                            __begin_clear_bit_loop_0_clear_bit_2:;
                            int loop_33_IOVar1;
                            int loop_33_block_1;
                            int t_33 = 0;
                            if (__cs_simulate == 0 && __cs_pc_2 == 83) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 83; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_2 <= 85) || ((__cs_simulate == 1) && ((t_33 < 2) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_33_IOVar1 = __cs_l_clear_bit___cs_dowhile_onetime_4;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_33_block_1 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_clear_bit___cs_dowhile_onetime_4 = loop_33_IOVar1 + (1 * loop_33_block_1);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_2 == 84) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 84; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_33_block_1 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_2 == 85) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 85; __cs_simulate = 2;} else                                        {
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
                                                t_33++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_2 == 86) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 86; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1));
                            }
                            __end_clear_bit_loop_0_clear_bit_2:;
                            __begin_clear_bit_loop_1_clear_bit_2:;
                            int t_34 = 0;
                            if (__cs_simulate == 0 && __cs_pc_2 == 87) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 87; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_2 <= 88) || ((__cs_simulate == 1) && ((t_34 < 1) && 0)))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_2 == 88) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 88; __cs_simulate = 2;} else                                        {
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
                                                t_34++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_2 == 89) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 89; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!0);
                            }
                            __end_clear_bit_loop_1_clear_bit_2:;
                            __exit__clear_bit_2:;
                        }
                        if (__cs_simulate == 0 && __cs_pc_2 == 90) __cs_simulate = 1;
                        if (__cs_simulate == 1)
                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 90; __cs_simulate = 2;} else                        {
                                tco_expect_close = 0;
                        }
                    }
                    if (__cs_simulate == 1)
                    {
                            t_32++;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_2 == 91) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 91; __cs_simulate = 2;} else        {
                __CPROVER_assume(!0);
        }
        __end_i8xx_tco_release_loop_1_i8xx_tco_release_1:;
        __exit__i8xx_tco_release_1:;
    }
    if (__cs_simulate == 0 && __cs_pc_2 == 92) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 92; __cs_simulate = 2;} else    {
            test_global_var1 = 0x11;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 93))
    {
        __cs_pc_2 = 93;
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
        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_8 = 0;
        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_3:;
        int loop_35_IOVar1;
        int loop_35_block_3;
        int t_35 = 0;
        if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_3 <= 31) || ((__cs_simulate == 1) && ((t_35 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_8 < 1))))
        {
                    if (__cs_simulate == 1)
                    {
                            loop_35_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_8;
                    }
                    if (__cs_simulate == 1)
                    {
                            loop_35_block_3 = nondet_int();
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_8 = loop_35_IOVar1 + (1 * loop_35_block_3);
                    }
                    if (__cs_simulate == 0 && __cs_pc_3 == 2) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 2; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(loop_35_block_3 >= 0);
                    }
                    if (__cs_simulate == 0 && __cs_pc_3 == 3) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 3; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_8 < 1);
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
                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = 0;
                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_5:;
                            int loop_36_IOVar1;
                            int loop_36_block_2;
                            int t_36 = 0;
                            if (__cs_simulate == 0 && __cs_pc_3 == 9) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 9; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_3 <= 19) || ((__cs_simulate == 1) && ((t_36 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_36_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_36_block_2 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = loop_36_IOVar1 + (1 * loop_36_block_2);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_3 == 10) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 10; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_36_block_2 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_3 == 11) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 11; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1);
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
                                                int loop_37_IOVar1;
                                                int loop_37_block_1;
                                                int t_37 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 13) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 13; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 15) || ((__cs_simulate == 1) && ((t_37 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_37_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_37_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_37_IOVar1 + (1 * loop_37_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 14) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 14; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_37_block_1 >= 0);
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
                                                                    t_37++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 16) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 16; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_9:;
                                                __begin_outb_loop_1_outb_9:;
                                                int t_38 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 17) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 17; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 18) || ((__cs_simulate == 1) && ((t_38 < 1) && 0)))
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
                                                                    t_38++;
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
                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6++;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_36++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_3 == 20) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 20; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1));
                            }
                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_5:;
                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_5:;
                            int t_39 = 0;
                            if (__cs_simulate == 0 && __cs_pc_3 == 21) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 21; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_3 <= 30) || ((__cs_simulate == 1) && ((t_39 < 2) && 0)))
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
                                                int loop_40_IOVar1;
                                                int loop_40_block_1;
                                                int t_40 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 24) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 24; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 26) || ((__cs_simulate == 1) && ((t_40 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_40_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_40_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_40_IOVar1 + (1 * loop_40_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 25) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 25; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_40_block_1 >= 0);
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
                                                                    t_40++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 27) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 27; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_10:;
                                                __begin_outb_loop_1_outb_10:;
                                                int t_41 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 28) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 28; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 29) || ((__cs_simulate == 1) && ((t_41 < 1) && 0)))
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
                                                                    t_41++;
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
                                                t_39++;
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
                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_8++;
                        }
                    }
                    if (__cs_simulate == 1)
                    {
                            t_35++;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_3 == 32) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 32; __cs_simulate = 2;} else        {
                __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_8 < 1));
        }
        __end_i8xx_tco_write_loop_0_i8xx_tco_write_3:;
        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_3:;
        int t_42 = 0;
        if (__cs_simulate == 0 && __cs_pc_3 == 33) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 33; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_3 <= 62) || ((__cs_simulate == 1) && ((t_42 < 1) && 0)))
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
                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = 0;
                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_6:;
                            int loop_43_IOVar1;
                            int loop_43_block_2;
                            int t_43 = 0;
                            if (__cs_simulate == 0 && __cs_pc_3 == 40) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 40; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_3 <= 50) || ((__cs_simulate == 1) && ((t_43 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_43_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_43_block_2 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = loop_43_IOVar1 + (1 * loop_43_block_2);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_3 == 41) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 41; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_43_block_2 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_3 == 42) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 42; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1);
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
                                                int loop_44_IOVar1;
                                                int loop_44_block_1;
                                                int t_44 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 44) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 44; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 46) || ((__cs_simulate == 1) && ((t_44 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_44_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_44_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_44_IOVar1 + (1 * loop_44_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 45) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 45; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_44_block_1 >= 0);
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
                                                                    t_44++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 47) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 47; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_11:;
                                                __begin_outb_loop_1_outb_11:;
                                                int t_45 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 48) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 48; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 49) || ((__cs_simulate == 1) && ((t_45 < 1) && 0)))
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
                                                                    t_45++;
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
                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6++;
                                            }
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                t_43++;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_3 == 51) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 51; __cs_simulate = 2;} else                            {
                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1));
                            }
                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_6:;
                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_6:;
                            int t_46 = 0;
                            if (__cs_simulate == 0 && __cs_pc_3 == 52) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 52; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_3 <= 61) || ((__cs_simulate == 1) && ((t_46 < 2) && 0)))
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
                                                int loop_47_IOVar1;
                                                int loop_47_block_1;
                                                int t_47 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 55) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 55; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 57) || ((__cs_simulate == 1) && ((t_47 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                {
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_47_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    loop_47_block_1 = nondet_int();
                                                            }
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_47_IOVar1 + (1 * loop_47_block_1);
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 56) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 56; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(loop_47_block_1 >= 0);
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
                                                                    t_47++;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 58) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 58; __cs_simulate = 2;} else                                                {
                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                }
                                                __end_outb_loop_0_outb_12:;
                                                __begin_outb_loop_1_outb_12:;
                                                int t_48 = 0;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 59) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 59; __cs_simulate = 2;}
                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 60) || ((__cs_simulate == 1) && ((t_48 < 1) && 0)))
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
                                                                    t_48++;
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
                                                t_46++;
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
                            t_42++;
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
    if (__cs_simulate == 0 && __cs_pc_3 == 64) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 64; __cs_simulate = 2;} else    {
            test_global_condition3 = 0;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 65))
    {
        __cs_pc_3 = 65;
        __cs_simulate = 2;
    }
}
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_5 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 0; __cs_simulate = 2;} else    {
            /*disable_isr(-1);*/
            __cs_disable_isr_0 = 1;
            __cs_disable_isr_2 = 1;
            __cs_disable_isr_3 = 1;
            __cs_disable_isr_1 = 1;
            __cs_disable_isr_4 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_5 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 1; __cs_simulate = 2;} else    {
            test_global_condition1 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_5 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 2; __cs_simulate = 2;} else    {
            test_global_condition2 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_5 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 3; __cs_simulate = 2;} else    {
            test_global_condition3 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_5 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 4; __cs_simulate = 2;} else    {
            test_global_condition4 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_5 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 5; __cs_simulate = 2;} else    {
            tco_expect_close = 0;
    }
    if (__cs_simulate == 0 && __cs_pc_5 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 6; __cs_simulate = 2;} else    {
            /*enable_isr(-1);*/
            __cs_disable_isr_0 = 0;
            __cs_disable_isr_2 = 0;
            __cs_disable_isr_3 = 0;
            __cs_disable_isr_1 = 0;
            __cs_disable_isr_4 = 0;
    }
    if (__cs_simulate == 0 && __cs_pc_5 == 7) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 7; __cs_simulate = 2;} else    {
            /*disable_isr(2);*/
            __cs_disable_isr_2 = 1;
    }
    {
        static int __cs_l_JudgeCondi_reader3;
        if (__cs_simulate == 0 && __cs_pc_5 == 8) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 8; __cs_simulate = 2;} else        {
                __cs_init_scalar(&__cs_l_JudgeCondi_reader3, sizeof(int));
        }
        static int __cs_l_JudgeCondi_reader4;
        if (__cs_simulate == 0 && __cs_pc_5 == 9) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 9; __cs_simulate = 2;} else        {
                __cs_init_scalar(&__cs_l_JudgeCondi_reader4, sizeof(int));
        }
        if (__cs_simulate == 0 && __cs_pc_5 == 10) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 10; __cs_simulate = 2;}
        if ((__cs_simulate == 0 && __cs_pc_5 <= 11) || (__cs_simulate == 1 && (test_global_condition1 == 1)))
        {
                    if (__cs_simulate == 0 && __cs_pc_5 == 11) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 11; __cs_simulate = 2;} else                    {
                            reader1 = test_global_var1;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_5 == 12) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 12; __cs_simulate = 2;}
        if ((__cs_simulate == 0 && __cs_pc_5 <= 13) || (__cs_simulate == 1 && (test_global_condition2 == 1)))
        {
                    if (__cs_simulate == 0 && __cs_pc_5 == 13) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 13; __cs_simulate = 2;} else                    {
                            reader2 = test_global_var1;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_5 == 14) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 14; __cs_simulate = 2;}
        if ((__cs_simulate == 0 && __cs_pc_5 <= 15) || (__cs_simulate == 1 && (reader1 != reader2)))
        {
                    if (__cs_simulate == 0 && __cs_pc_5 == 15) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 15; __cs_simulate = 2;} else                    {
                            assert(0);
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_5 == 16) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 16; __cs_simulate = 2;} else        {
                __cs_l_JudgeCondi_reader3 = test_global_var2;
        }
        if (__cs_simulate == 0 && __cs_pc_5 == 17) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 17; __cs_simulate = 2;} else        {
                __cs_l_JudgeCondi_reader4 = test_global_var2;
        }
        __exit__JudgeCondi_1:;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_5 == 18))
    {
        __cs_pc_5 = 18;
        __cs_simulate = 2;
    }
}
/* Simulate closer1_isr_1 */
void closer1_isr_1(void)
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
        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_8 = 0;
        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_1:;
        int loop_1_IOVar1;
        int loop_1_block_3;
        int t_1 = 0;
        if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_1 <= 31) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_8 < 1))))
        {
                    if (__cs_simulate == 1)
                    {
                            loop_1_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_8;
                    }
                    if (__cs_simulate == 1)
                    {
                            loop_1_block_3 = nondet_int();
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_8 = loop_1_IOVar1 + (1 * loop_1_block_3);
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(loop_1_block_3 >= 0);
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_8 < 1);
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
                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = 0;
                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_1:;
                            int loop_2_IOVar1;
                            int loop_2_block_2;
                            int t_2 = 0;
                            if (__cs_simulate == 0 && __cs_pc_1 == 9) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 9; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_1 <= 19) || ((__cs_simulate == 1) && ((t_2 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_2_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_2_block_2 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = loop_2_IOVar1 + (1 * loop_2_block_2);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_1 == 10) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 10; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_2_block_2 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_1 == 11) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 11; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1);
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
                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6++;
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
                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1));
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
                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_8++;
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
                __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_8 < 1));
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
                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = 0;
                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_2:;
                            int loop_9_IOVar1;
                            int loop_9_block_2;
                            int t_9 = 0;
                            if (__cs_simulate == 0 && __cs_pc_1 == 40) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 40; __cs_simulate = 2;}
                            while ((__cs_simulate == 0 && __cs_pc_1 <= 50) || ((__cs_simulate == 1) && ((t_9 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1))))
                            {
                                        if (__cs_simulate == 1)
                                        {
                                                loop_9_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6;
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                loop_9_block_2 = nondet_int();
                                        }
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = loop_9_IOVar1 + (1 * loop_9_block_2);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_1 == 41) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 41; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(loop_9_block_2 >= 0);
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_1 == 42) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 42; __cs_simulate = 2;} else                                        {
                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1);
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
                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6++;
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
                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1));
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
    if ((__cs_simulate == 0 && __cs_pc_1 <= 66) || (__cs_simulate == 1 && (tco_expect_close == 42)))
    {
                if (__cs_simulate == 0 && __cs_pc_1 == 66) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 66; __cs_simulate = 2;} else                {
                        test_global_var3++;
                }
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 67))
    {
        __cs_pc_1 = 67;
        __cs_simulate = 2;
    }
}
/* Simulate writer2_isr_4 */
void writer2_isr_4(void)
{
        if (__cs_simulate == 0 && __cs_pc_4 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 0; __cs_simulate = 2;} else {
                        static int __cs_l_i8xx_tco_write_len;
                        __cs_l_i8xx_tco_write_len = 0;
                        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_8 = 0;
                        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_4:
;
                        ;;
                        int loop_49_IOVar1;
                        int loop_49_block_3;
                        int t_49 = 0;
                    while ((t_49 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_8 < 1)){
                            loop_49_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_8;
                            loop_49_block_3 = nondet_int();
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_8 = loop_49_IOVar1 + (1 * loop_49_block_3);
                    __CPROVER_assume(loop_49_block_3 >= 0);
                    __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_8 < 1);
                                                        if (__cs_l_i8xx_tco_write_len)
                                                                                    if (!nowayout)
                                        tco_expect_close = 0;
                                                                                                                if (tco_write_buf == 'V')
                                            tco_expect_close = 42;
                                    static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = 0;
                                    __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_7:
;
                                    ;;
                                    int loop_50_IOVar1;
                                    int loop_50_block_2;
                                    int t_50 = 0;
                                while ((t_50 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1)){
                                        loop_50_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6;
                                        loop_50_block_2 = nondet_int();
                                        __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = loop_50_IOVar1 + (1 * loop_50_block_2);
                                                        __CPROVER_assume(loop_50_block_2 >= 0);
                                                        __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_13:
;
                                                ;;
                                                int loop_51_IOVar1;
                                                int loop_51_block_1;
                                                int t_51 = 0;
                                            while ((t_51 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_51_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_51_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_51_IOVar1 + (1 * loop_51_block_1);
                                                                    __CPROVER_assume(loop_51_block_1 >= 0);
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_51++;
                                                                __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_13:
;
                                                ;;
                                                __begin_outb_loop_1_outb_13:
;
                                                ;;
                                                int t_52 = 0;
                                            while ((t_52 < 1) && 0){
                                                                    __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_52++;
                                                                __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_13:
;
                                                ;;
                                                __exit__outb_13:
;
                                                ;;
                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6++;
                                        t_50++;
                                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1));
                                }
                                    __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_7:
;
                                    ;;
                                    __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_7:
;
                                    ;;
                                    int t_53 = 0;
                                while ((t_53 < 2) && 0){
                                                        __CPROVER_assume(0);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_14:
;
                                                ;;
                                                int loop_54_IOVar1;
                                                int loop_54_block_1;
                                                int t_54 = 0;
                                            while ((t_54 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_54_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_54_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_54_IOVar1 + (1 * loop_54_block_1);
                                                                    __CPROVER_assume(loop_54_block_1 >= 0);
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_54++;
                                                                __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_14:
;
                                                ;;
                                                __begin_outb_loop_1_outb_14:
;
                                                ;;
                                                int t_55 = 0;
                                            while ((t_55 < 1) && 0){
                                                                    __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_55++;
                                                                __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_14:
;
                                                ;;
                                                __exit__outb_14:
;
                                                ;;
                                        t_53++;
                                                    __CPROVER_assume(!0);
                                }
                                    __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_7:
;
                                    ;;
                                    __exit__tco_timer_keepalive_7:
;
                                    ;;
                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_8++;
                            t_49++;
                                        __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_8 < 1));
                    }
                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_4:
;
                        ;;
                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_4:
;
                        ;;
                        int t_56 = 0;
                    while ((t_56 < 1) && 0){
                                            __CPROVER_assume(0);
                                                                                                        if (__cs_l_i8xx_tco_write_len)
                                                                                                                                    if (!nowayout)
                                        tco_expect_close = 0;
                                                                                                                                                                if (tco_write_buf == 'V')
                                            tco_expect_close = 42;
                                    static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = 0;
                                    __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_8:
;
                                    ;;
                                    int loop_57_IOVar1;
                                    int loop_57_block_2;
                                    int t_57 = 0;
                                while ((t_57 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1)){
                                        loop_57_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6;
                                        loop_57_block_2 = nondet_int();
                                        __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 = loop_57_IOVar1 + (1 * loop_57_block_2);
                                                                                __CPROVER_assume(loop_57_block_2 >= 0);
                                                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_15:
;
                                                ;;
                                                int loop_58_IOVar1;
                                                int loop_58_block_1;
                                                int t_58 = 0;
                                            while ((t_58 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_58_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_58_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_58_IOVar1 + (1 * loop_58_block_1);
                                                                                            __CPROVER_assume(loop_58_block_1 >= 0);
                                                                                            __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_58++;
                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_15:
;
                                                ;;
                                                __begin_outb_loop_1_outb_15:
;
                                                ;;
                                                int t_59 = 0;
                                            while ((t_59 < 1) && 0){
                                                                                            __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_59++;
                                                                                        __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_15:
;
                                                ;;
                                                __exit__outb_15:
;
                                                ;;
                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_6++;
                                        t_57++;
                                                                            __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_6 < 1));
                                }
                                    __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_8:
;
                                    ;;
                                    __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_8:
;
                                    ;;
                                    int t_60 = 0;
                                while ((t_60 < 2) && 0){
                                                                                __CPROVER_assume(0);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_16:
;
                                                ;;
                                                int loop_61_IOVar1;
                                                int loop_61_block_1;
                                                int t_61 = 0;
                                            while ((t_61 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_61_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_61_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_61_IOVar1 + (1 * loop_61_block_1);
                                                                                            __CPROVER_assume(loop_61_block_1 >= 0);
                                                                                            __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_61++;
                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_16:
;
                                                ;;
                                                __begin_outb_loop_1_outb_16:
;
                                                ;;
                                                int t_62 = 0;
                                            while ((t_62 < 1) && 0){
                                                                                            __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_62++;
                                                                                        __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_16:
;
                                                ;;
                                                __exit__outb_16:
;
                                                ;;
                                        t_60++;
                                                                            __CPROVER_assume(!0);
                                }
                                    __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_8:
;
                                    ;;
                                    __exit__tco_timer_keepalive_8:
;
                                    ;;
                            t_56++;
                                                                __CPROVER_assume(!0);
                    }
                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_4:
;
                        ;;
                        __exit__i8xx_tco_write_4:
;
                        ;;
                                                                                                                    if (test_global_condition3 == 1)
                        test_global_var2 = 0x22;
        }
                                                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 66))
                                                            {
                                                                __cs_pc_4 = 66;
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
  __cs_disable_isr_0 = 0;
  __cs_disable_isr_1 = 0;
  __cs_disable_isr_2 = 0;
  __cs_disable_isr_3 = 0;
  __cs_disable_isr_4 = 0;
  while (1)
  {
    __cs_simulate = 0;
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 67)&&(__cs_pc_3 == 0 || __cs_pc_3 == 65)&&(__cs_pc_2 == 0 || __cs_pc_2 == 93)&&__cs_disable_isr_0 != 1) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 65)&&(__cs_pc_2 == 0 || __cs_pc_2 == 93)&&__cs_disable_isr_1 != 1) closer1_isr_1();
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 65)&&__cs_disable_isr_2 != 1) closer2_isr_2();
    __cs_simulate = 0;
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 93)&&__cs_disable_isr_3 != 1) writer1_isr_3();
    __cs_simulate = 0;
    if (__cs_disable_isr_4 != 1) writer2_isr_4();
  }
}
