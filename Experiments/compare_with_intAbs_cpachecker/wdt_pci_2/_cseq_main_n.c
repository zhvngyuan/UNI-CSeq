// Main task
unsigned int __cs_pc_7;
// closer1_isr_1
unsigned int __cs_pc_1;
// closer2_isr_2
unsigned int __cs_pc_2;
// closer3_isr_3
unsigned int __cs_pc_3;
// writer1_isr_4
unsigned int __cs_pc_4;
// writer2_isr_5
unsigned int __cs_pc_5;
// writer3_isr_6
unsigned int __cs_pc_6;
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

#define __CPROVER_assume(X) __VERIFIER_assume(X)
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
int cnt1;
int cnt2;
int cnt3;
int cnt4;
int cnt5;
int cnt6;
int count;
int buf;
/* Simulate writer3_isr_6 */
void writer3_isr_6()
{
        if (__cs_simulate == 0 && __cs_pc_6 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 0; __cs_simulate = 2;} else {
                    count = 0;
                    expect_close = 0;
                    if (count)
                                                if (!nowayout)
                                                                            if (wdtpci_write_buf != 'V')
                                expect_close = 0;
                    cnt6++;
        }
                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_6 == 7))
                            {
                                __cs_pc_6 = 7;
                                __cs_simulate = 2;
                            }
}
/* Simulate original main */
int main_task()
                        {
                            if (__cs_simulate == 0 && __cs_pc_7 == 0) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 0; __cs_simulate = 2;} else                            {
                                    cnt1 = 1;
                            }
                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_7 == 1))
                            {
                                __cs_pc_7 = 1;
                                __cs_simulate = 2;
                            }
                        }
/* Simulate closer1_isr_1 */
void closer1_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else {
                    wdtpci_write_buf = 'V';
                    expect_close = 42;
                    count = 1;
                                                                    if (count)
                                                                                                if (!nowayout)
                                                                                                                            if (wdtpci_write_buf != 'V')
                                expect_close = 0;
                                                                                                                    if (expect_close != 42)
                                                                        if (!(0)) __cseq_error();
                    else;
                    expect_close = 0;
                    cnt1++;
        }
                                                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 11))
                                                            {
                                                                __cs_pc_1 = 11;
                                                                __cs_simulate = 2;
                                                            }
}
/* Simulate closer3_isr_3 */
void closer3_isr_3()
                                                        {
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else                                                            {
                                                                    wdtpci_write_buf = 'V';
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;} else                                                            {
                                                                    expect_close = 42;
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 2) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 2; __cs_simulate = 2;} else                                                            {
                                                                    count = 1;
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 3) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 3; __cs_simulate = 2;}
                                                            if ((__cs_simulate == 0 && __cs_pc_3 <= 6) || (__cs_simulate == 1 && (count)))
                                                            {
                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 4) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 4; __cs_simulate = 2;}
                                                                        if ((__cs_simulate == 0 && __cs_pc_3 <= 6) || (__cs_simulate == 1 && (!nowayout)))
                                                                        {
                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 5) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 5; __cs_simulate = 2;}
                                                                                    if ((__cs_simulate == 0 && __cs_pc_3 <= 6) || (__cs_simulate == 1 && (wdtpci_write_buf != 'V')))
                                                                                    {
                                                                                                if (__cs_simulate == 0 && __cs_pc_3 == 6) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 6; __cs_simulate = 2;} else                                                                                                {
                                                                                                        expect_close = 0;
                                                                                                }
                                                                                    }
                                                                        }
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 7) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 7; __cs_simulate = 2;} else                                                            {
                                                                    expect_close = 0;
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 8) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 8; __cs_simulate = 2;} else                                                            {
                                                                    cnt5++;
                                                            }
                                                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 9))
                                                            {
                                                                __cs_pc_3 = 9;
                                                                __cs_simulate = 2;
                                                            }
                                                        }
/* Simulate writer1_isr_4 */
void writer1_isr_4()
                                                        {
                                                            if (__cs_simulate == 0 && __cs_pc_4 == 0) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 0; __cs_simulate = 2;} else                                                            {
                                                                    count = 0;
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_4 == 1) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 1; __cs_simulate = 2;} else                                                            {
                                                                    expect_close = 0;
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_4 == 2) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 2; __cs_simulate = 2;}
                                                            if ((__cs_simulate == 0 && __cs_pc_4 <= 5) || (__cs_simulate == 1 && (count)))
                                                            {
                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 3) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 3; __cs_simulate = 2;}
                                                                        if ((__cs_simulate == 0 && __cs_pc_4 <= 5) || (__cs_simulate == 1 && (!nowayout)))
                                                                        {
                                                                                    if (__cs_simulate == 0 && __cs_pc_4 == 4) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 4; __cs_simulate = 2;}
                                                                                    if ((__cs_simulate == 0 && __cs_pc_4 <= 5) || (__cs_simulate == 1 && (wdtpci_write_buf != 'V')))
                                                                                    {
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 5) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 5; __cs_simulate = 2;} else                                                                                                {
                                                                                                        expect_close = 0;
                                                                                                }
                                                                                    }
                                                                        }
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_4 == 6) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 6; __cs_simulate = 2;} else                                                            {
                                                                    cnt3++;
                                                            }
                                                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 7))
                                                            {
                                                                __cs_pc_4 = 7;
                                                                __cs_simulate = 2;
                                                            }
                                                        }
/* Simulate closer2_isr_2 */
void closer2_isr_2()
{
        if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else {
                    wdtpci_write_buf = 'V';
                    expect_close = 42;
                    count = 1;
                                                                                                                                    if (count)
                                                                                                                                                                if (!nowayout)
                                                                                                                                                                                            if (wdtpci_write_buf != 'V')
                                expect_close = 0;
                                                                                                                                                                                    if (expect_close != 42)
                                                                                                        if (!(0)) __cseq_error();
                    else;
                    expect_close = 0;
                    cnt2++;
        }
                                                                                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 11))
                                                                                            {
                                                                                                __cs_pc_2 = 11;
                                                                                                __cs_simulate = 2;
                                                                                            }
}
/* Simulate writer2_isr_5 */
void writer2_isr_5()
                                                                                        {
                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 0) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1)
                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 0; __cs_simulate = 2;} else                                                                                            {
                                                                                                    count = 0;
                                                                                            }
                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 1) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1)
                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 1; __cs_simulate = 2;} else                                                                                            {
                                                                                                    expect_close = 0;
                                                                                            }
                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 2) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 2; __cs_simulate = 2;}
                                                                                            if ((__cs_simulate == 0 && __cs_pc_5 <= 5) || (__cs_simulate == 1 && (count)))
                                                                                            {
                                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 3) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 3; __cs_simulate = 2;}
                                                                                                        if ((__cs_simulate == 0 && __cs_pc_5 <= 5) || (__cs_simulate == 1 && (!nowayout)))
                                                                                                        {
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 4) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 4; __cs_simulate = 2;}
                                                                                                                    if ((__cs_simulate == 0 && __cs_pc_5 <= 5) || (__cs_simulate == 1 && (wdtpci_write_buf != 'V')))
                                                                                                                    {
                                                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 5) __cs_simulate = 1;
                                                                                                                                if (__cs_simulate == 1)
                                                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 5; __cs_simulate = 2;} else                                                                                                                                {
                                                                                                                                        expect_close = 0;
                                                                                                                                }
                                                                                                                    }
                                                                                                        }
                                                                                            }
                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 6) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1)
                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 6; __cs_simulate = 2;} else                                                                                            {
                                                                                                    cnt4++;
                                                                                            }
                                                                                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_5 == 7))
                                                                                            {
                                                                                                __cs_pc_5 = 7;
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
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 9)&&(__cs_pc_4 == 0 || __cs_pc_4 == 7)&&(__cs_pc_5 == 0 || __cs_pc_5 == 7)&&__cs_disable_isr_0 != 1) main_task();
    __cs_simulate = 0;
    if (__cs_disable_isr_1 != 1) closer1_isr_1();
    __cs_simulate = 0;
    if (__cs_disable_isr_2 != 1) closer2_isr_2();
    __cs_simulate = 0;
    if ((__cs_pc_4 == 0 || __cs_pc_4 == 7)&&(__cs_pc_5 == 0 || __cs_pc_5 == 7)&&__cs_disable_isr_3 != 1) closer3_isr_3();
    __cs_simulate = 0;
    if ((__cs_pc_5 == 0 || __cs_pc_5 == 7)&&__cs_disable_isr_4 != 1) writer1_isr_4();
    __cs_simulate = 0;
    if ((__cs_pc_4 == 0 || __cs_pc_4 == 7)&&__cs_disable_isr_5 != 1) writer2_isr_5();
    __cs_simulate = 0;
    if (__cs_disable_isr_6 != 1) writer3_isr_6();
  }
}
