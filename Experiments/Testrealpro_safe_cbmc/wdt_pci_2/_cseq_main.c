// Main task
unsigned __CPROVER_bitvector[4] __cs_pc_7;
// closer1_isr_1
unsigned __CPROVER_bitvector[5] __cs_pc_1;
// closer2_isr_2
unsigned __CPROVER_bitvector[4] __cs_pc_2;
// closer3_isr_3
unsigned __CPROVER_bitvector[4] __cs_pc_3;
// writer1_isr_4
unsigned __CPROVER_bitvector[4] __cs_pc_4;
// writer2_isr_5
unsigned __CPROVER_bitvector[3] __cs_pc_5;
// writer3_isr_6
unsigned __CPROVER_bitvector[5] __cs_pc_6;
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
char wdtpci_write_buf;
char wdt_dc_port;
long jiffies;
void spin_lock(int);
void spin_unlock(int);
void outb(int, int);
void udelay(int);
void clear_bit(int, int);
void up(int);
void wdt_ctr_load(int, int);
void wdt_ctr_mode(int, int);
void wdtpci_stop(void);
void wdtpci_ping(void);
void wdtpci_write(int);
void wdtpci_release(void);
int dev_count;
unsigned open_sem;
int wdtpci_lock;
int expect_close;
int io;
int irq;
int heartbeat = 60;
int wd_heartbeat;
int nowayout = 0;
int count;
int buf;
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
int reader3;
int reader4;
void JudgeCondi(void);
/* Simulate writer3_isr_6 */
void writer3_isr_6(void)
{
    if (__cs_simulate == 0 && __cs_pc_6 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 0; __cs_simulate = 2;} else    {
            count = 0;
    }
    if (__cs_simulate == 0 && __cs_pc_6 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 1; __cs_simulate = 2;} else    {
            expect_close = 0;
    }
    if (__cs_simulate == 0 && __cs_pc_6 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_6 = 2; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_6 <= 5) || (__cs_simulate == 1 && (count)))
    {
                if (__cs_simulate == 0 && __cs_pc_6 == 3) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_6 = 3; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_6 <= 5) || (__cs_simulate == 1 && (!nowayout)))
                {
                            if (__cs_simulate == 0 && __cs_pc_6 == 4) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_6 = 4; __cs_simulate = 2;}
                            if ((__cs_simulate == 0 && __cs_pc_6 <= 5) || (__cs_simulate == 1 && (wdtpci_write_buf != 'V')))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_6 == 5) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 5; __cs_simulate = 2;} else                                        {
                                                expect_close = 0;
                                        }
                            }
                }
    }
    static int __cs_l_writer3_isr_6_i = 0;
    static int __cs_l_writer3_isr_6_maxnum;
    if (__cs_simulate == 0 && __cs_pc_6 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 6; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_writer3_isr_6_maxnum, sizeof(int));
    }
    static int __cs_l_writer3_isr_6_mininum;
    if (__cs_simulate == 0 && __cs_pc_6 == 7) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 7; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_writer3_isr_6_mininum, sizeof(int));
    }
    if (__cs_simulate == 1)
    {
            __cs_l_writer3_isr_6_i = 0;
    }
    __begin_writer3_isr_6_loop_0:;
    int loop_1_IOVar1;
    int loop_1_block_3;
    int t_1 = 0;
    if (__cs_simulate == 0 && __cs_pc_6 == 8) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_6 = 8; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_6 <= 14) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_writer3_isr_6_i < 10000))))
    {
                if (__cs_simulate == 1)
                {
                        loop_1_IOVar1 = __cs_l_writer3_isr_6_i;
                }
                if (__cs_simulate == 1)
                {
                        loop_1_block_3 = nondet_int();
                }
                if (__cs_simulate == 1)
                {
                        __cs_l_writer3_isr_6_i = loop_1_IOVar1 + (1 * loop_1_block_3);
                }
                if (__cs_simulate == 0 && __cs_pc_6 == 9) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 9; __cs_simulate = 2;} else                {
                        __CPROVER_assume(loop_1_block_3 >= 0);
                }
                if (__cs_simulate == 0 && __cs_pc_6 == 10) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 10; __cs_simulate = 2;} else                {
                        __CPROVER_assume(__cs_l_writer3_isr_6_i < 10000);
                }
                {
                    if (__cs_simulate == 0 && __cs_pc_6 == 11) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_6 = 11; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_6 <= 12) || (__cs_simulate == 1 && (__cs_l_writer3_isr_6_i == 9000)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_6 == 12) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 12; __cs_simulate = 2;} else                                {
                                        test_global_array[9000] = 1;
                                }
                    }
                    if (__cs_simulate == 0 && __cs_pc_6 == 13) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_6 = 13; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_6 <= 14) || (__cs_simulate == 1 && (__cs_l_writer3_isr_6_i == 10001)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_6 == 14) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 14; __cs_simulate = 2;} else                                {
                                        test_global_array[9000] = 1;
                                }
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_writer3_isr_6_i++;
                    }
                }
                if (__cs_simulate == 1)
                {
                        t_1++;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_6 == 15) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 15; __cs_simulate = 2;} else    {
            __CPROVER_assume(!(__cs_l_writer3_isr_6_i < 10000));
    }
    __end_writer3_isr_6_loop_0:;
    if (__cs_simulate == 0 && __cs_pc_6 == 16) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 16; __cs_simulate = 2;} else    {
            __cs_l_writer3_isr_6_mininum = test_global_array[9000] - 10;
    }
    if (__cs_simulate == 0 && __cs_pc_6 == 17) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 17; __cs_simulate = 2;} else    {
            __cs_l_writer3_isr_6_maxnum = test_global_array[0] + 10;
    }
    if (__cs_simulate == 0 && __cs_pc_6 == 18) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 18; __cs_simulate = 2;} else    {
            test_global_array[0] = __cs_l_writer3_isr_6_maxnum;
    }
    if (__cs_simulate == 0 && __cs_pc_6 == 19) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_6 = 19; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_6 <= 20) || (__cs_simulate == 1 && (test_global_array[0] != 11)))
    {
                if (__cs_simulate == 0 && __cs_pc_6 == 20) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 20; __cs_simulate = 2;} else                {
                        assert(0);
                }
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_6 == 21))
    {
        __cs_pc_6 = 21;
        __cs_simulate = 2;
    }
}
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_7 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 0; __cs_simulate = 2;} else    {
            /*disable_isr(-1);*/
            __cs_disable_isr_0 = 1;
            __cs_disable_isr_6 = 1;
            __cs_disable_isr_1 = 1;
            __cs_disable_isr_3 = 1;
            __cs_disable_isr_4 = 1;
            __cs_disable_isr_2 = 1;
            __cs_disable_isr_5 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_7 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 1; __cs_simulate = 2;} else    {
            count = 0;
    }
    if (__cs_simulate == 0 && __cs_pc_7 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 2; __cs_simulate = 2;} else    {
            expect_close = 0;
    }
    if (__cs_simulate == 0 && __cs_pc_7 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 3; __cs_simulate = 2;} else    {
            test_global_condition1 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_7 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 4; __cs_simulate = 2;} else    {
            test_global_condition2 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_7 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 5; __cs_simulate = 2;} else    {
            test_global_condition3 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_7 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 6; __cs_simulate = 2;} else    {
            test_global_condition4 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_7 == 7) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 7; __cs_simulate = 2;} else    {
            /*enable_isr(-1);*/
            __cs_disable_isr_0 = 0;
            __cs_disable_isr_6 = 0;
            __cs_disable_isr_1 = 0;
            __cs_disable_isr_3 = 0;
            __cs_disable_isr_4 = 0;
            __cs_disable_isr_2 = 0;
            __cs_disable_isr_5 = 0;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_7 == 8))
    {
        __cs_pc_7 = 8;
        __cs_simulate = 2;
    }
}
/* Simulate closer1_isr_1 */
void closer1_isr_1(void)
{
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            wdtpci_write_buf = 'V';
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;} else    {
            expect_close = 42;
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;} else    {
            count = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_1 <= 16) || (__cs_simulate == 1 && (count)))
    {
                if (__cs_simulate == 0 && __cs_pc_1 == 4) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 4; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_1 <= 6) || (__cs_simulate == 1 && (!nowayout)))
                {
                            if (__cs_simulate == 0 && __cs_pc_1 == 5) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 5; __cs_simulate = 2;}
                            if ((__cs_simulate == 0 && __cs_pc_1 <= 6) || (__cs_simulate == 1 && (wdtpci_write_buf != 'V')))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_1 == 6) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 6; __cs_simulate = 2;} else                                        {
                                                expect_close = 0;
                                        }
                            }
                }
                {
                    if (__cs_simulate == 0 && __cs_pc_1 == 7) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 7; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_1 <= 8) || (__cs_simulate == 1 && (test_global_condition1 == 1)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_1 == 8) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 8; __cs_simulate = 2;} else                                {
                                        reader1 = test_global_var1;
                                }
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 9) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 9; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_1 <= 10) || (__cs_simulate == 1 && (test_global_condition2 == 1)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_1 == 10) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 10; __cs_simulate = 2;} else                                {
                                        reader2 = test_global_var1;
                                }
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 11) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 11; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_1 <= 12) || (__cs_simulate == 1 && (reader1 != reader2)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_1 == 12) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 12; __cs_simulate = 2;} else                                {
                                        assert(0);
                                }
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 13) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 13; __cs_simulate = 2;} else                    {
                            reader3 = test_global_var2;
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 14) __cs_simulate = 1;
                    if (__cs_simulate == 1)
                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 14; __cs_simulate = 2;} else                    {
                            reader4 = test_global_var2;
                    }
                    if (__cs_simulate == 0 && __cs_pc_1 == 15) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 15; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_1 <= 16) || (__cs_simulate == 1 && (reader3 != reader4)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_1 == 16) __cs_simulate = 1;
                                if (__cs_simulate == 1)
                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 16; __cs_simulate = 2;} else                                {
                                        assert(0);
                                }
                    }
                    __exit__JudgeCondi_1:;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 17) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 17; __cs_simulate = 2;} else    {
            expect_close = 0;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 18))
    {
        __cs_pc_1 = 18;
        __cs_simulate = 2;
    }
}
/* Simulate closer3_isr_3 */
void closer3_isr_3(void)
{
        if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else {
                    wdtpci_write_buf = 'V';
                    expect_close = 42;
                    count = 1;
                    if (count)
                                                if (!nowayout)
                                                                            if (wdtpci_write_buf != 'V')
                                expect_close = 0;
                    expect_close = 0;
                    test_global_array[9000] = 999;
        }
                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 9))
                            {
                                __cs_pc_3 = 9;
                                __cs_simulate = 2;
                            }
}
/* Simulate writer1_isr_4 */
void writer1_isr_4(void)
{
        if (__cs_simulate == 0 && __cs_pc_4 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 0; __cs_simulate = 2;} else {
                    count = 0;
                    expect_close = 0;
                                                                    if (count)
                                                                                                if (!nowayout)
                                                                                                                            if (wdtpci_write_buf != 'V')
                                expect_close = 0;
                                                                                                                    if (test_global_condition3 == 0)
                        test_global_var1 = 0x99;
                                                                                                                                    if (test_global_condition4 == 0)
                        test_global_var2 = 0x99;
        }
                                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 10))
                                                                    {
                                                                        __cs_pc_4 = 10;
                                                                        __cs_simulate = 2;
                                                                    }
}
/* Simulate closer2_isr_2 */
void closer2_isr_2(void)
                                                                {
                                                                    if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else                                                                    {
                                                                            wdtpci_write_buf = 'V';
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_2 == 1) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 1; __cs_simulate = 2;} else                                                                    {
                                                                            expect_close = 42;
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_2 == 2) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 2; __cs_simulate = 2;} else                                                                    {
                                                                            count = 1;
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_2 == 3) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 3; __cs_simulate = 2;}
                                                                    if ((__cs_simulate == 0 && __cs_pc_2 <= 6) || (__cs_simulate == 1 && (count)))
                                                                    {
                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 4) __cs_simulate = 1;
                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 4; __cs_simulate = 2;}
                                                                                if ((__cs_simulate == 0 && __cs_pc_2 <= 6) || (__cs_simulate == 1 && (!nowayout)))
                                                                                {
                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 5) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 5; __cs_simulate = 2;}
                                                                                            if ((__cs_simulate == 0 && __cs_pc_2 <= 6) || (__cs_simulate == 1 && (wdtpci_write_buf != 'V')))
                                                                                            {
                                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 6) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 6; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                expect_close = 0;
                                                                                                        }
                                                                                            }
                                                                                }
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_2 == 7) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 7; __cs_simulate = 2;}
                                                                    if ((__cs_simulate == 0 && __cs_pc_2 <= 7) || (__cs_simulate == 1 && (expect_close != 42)))
                                                                    {
                                                                    }
                                                                    else
if ((__cs_simulate == 0 && __cs_pc_2 <= 7) || (__cs_simulate == 1))                                                                    {
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_2 == 8) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 8; __cs_simulate = 2;} else                                                                    {
                                                                            expect_close = 0;
                                                                    }
                                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 9))
                                                                    {
                                                                        __cs_pc_2 = 9;
                                                                        __cs_simulate = 2;
                                                                    }
                                                                }
/* Simulate writer2_isr_5 */
void writer2_isr_5(void)
{
        if (__cs_simulate == 0 && __cs_pc_5 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 0; __cs_simulate = 2;} else {
                    count = 0;
                    expect_close = 0;
                                                                                                                                                    if (count)
                                                                                                                                                                                if (!nowayout)
                                                                                                                                                                                                            if (wdtpci_write_buf != 'V')
                                expect_close = 0;
        }
                                                                                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_5 == 6))
                                                                                            {
                                                                                                __cs_pc_5 = 6;
                                                                                                __cs_simulate = 2;
                                                                                            }
}
/* main function (scheduler) */
int main()
{
  __cs_simulate = 0;
  __cs_pc_7 = 0;
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
    if ((__cs_pc_6 == 0 || __cs_pc_6 == 21)&&(__cs_pc_1 == 0 || __cs_pc_1 == 18)&&(__cs_pc_2 == 0 || __cs_pc_2 == 9)&&__cs_disable_isr_0 != 1) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 9)&&__cs_disable_isr_1 != 1) closer1_isr_1();
    __cs_simulate = 0;
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 18)&&__cs_disable_isr_2 != 1) closer2_isr_2();
    __cs_simulate = 0;
    if (__cs_disable_isr_3 != 1) closer3_isr_3();
    __cs_simulate = 0;
    if (__cs_disable_isr_4 != 1) writer1_isr_4();
    __cs_simulate = 0;
    if (__cs_disable_isr_5 != 1) writer2_isr_5();
    __cs_simulate = 0;
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 18)&&(__cs_pc_2 == 0 || __cs_pc_2 == 9)&&__cs_disable_isr_6 != 1) writer3_isr_6();
  }
}
