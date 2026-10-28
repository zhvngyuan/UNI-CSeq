// Main task
unsigned int __cs_pc_0;
// closer1_isr_1
unsigned int __cs_pc_1;
// closer2_isr_2
unsigned int __cs_pc_2;
// writer1_isr_3
unsigned int __cs_pc_3;
// writer2_isr_4
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
unsigned char seconds_to_ticks(int);
void tco_timer_keepalive(void);
int tco_timer_set_heartbeat(int);
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
int cnt1;
int cnt2;
int cnt3;
int cnt4;
int cnt5;
/* Simulate closer2_isr_2 */
void closer2_isr_2()
{
    if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else    {
            tco_write_buf = 'V';
    }}
    {
        static int __cs_l_i8xx_tco_write_len;
        if (__cs_simulate == 1)
        {
                __cs_l_i8xx_tco_write_len = 1;
        }
        if (__cs_simulate == 0 && __cs_pc_2 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 1; __cs_simulate = 2;}
        if ((__cs_simulate == 0 && __cs_pc_2 <= 5) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
        {
                    if (__cs_simulate == 0 && __cs_pc_2 == 2) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 2; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_2 <= 5) || (__cs_simulate == 1 && (!nowayout)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_2 == 3) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 3; __cs_simulate = 2;} else                                {
                                        tco_expect_close = 0;
                                }}
                                if (__cs_simulate == 0 && __cs_pc_2 == 4) __cs_simulate = 1;
                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 4; __cs_simulate = 2;}
                                if ((__cs_simulate == 0 && __cs_pc_2 <= 5) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                {
                                            if (__cs_simulate == 0 && __cs_pc_2 == 5) __cs_simulate = 1;
                                            if (__cs_simulate == 1){
                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 5; __cs_simulate = 2;} else                                            {
                                                    tco_expect_close = 42;
                                            }}
                                }
                    }
        }
        {
            {
                static int __cs_l_outb_v;
                if (__cs_simulate == 1)
                {
                        __cs_l_outb_v = 0x01;
                }
                static int __cs_l_outb_l;
                if (__cs_simulate == 0 && __cs_pc_2 == 6) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 6; __cs_simulate = 2;} else                {
                        __cs_l_outb_l = tco1_rld;
                }}
                if (__cs_simulate == 1)
                {
                        __cs_l_outb_l = __cs_l_outb_v;
                }
                __exit__outb_3:;
            }
            __exit__tco_timer_keepalive_3:;
        }
        __exit__i8xx_tco_write_2:;
    }
    if (__cs_simulate == 0 && __cs_pc_2 == 7) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 7; __cs_simulate = 2;} else    {
            tco_expect_close = 42;
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 8) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 8; __cs_simulate = 2;} else    {
            if (!(tco_expect_close == 42)) __cseq_error();
    }}
    {
        {
            {
                static int __cs_l_outb_v;
                if (__cs_simulate == 1)
                {
                        __cs_l_outb_v = 0x01;
                }
                static int __cs_l_outb_l;
                if (__cs_simulate == 0 && __cs_pc_2 == 9) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 9; __cs_simulate = 2;} else                {
                        __cs_l_outb_l = tco1_rld;
                }}
                if (__cs_simulate == 1)
                {
                        __cs_l_outb_l = __cs_l_outb_v;
                }
                __exit__outb_4:;
            }
            __exit__tco_timer_keepalive_4:;
        }
        {
            static int __cs_l_clear_bit_unused;
            if (__cs_simulate == 1)
            {
                    __cs_l_clear_bit_unused = 0;
            }
            static int __cs_l_clear_bit_v;
            if (__cs_simulate == 0 && __cs_pc_2 == 10) __cs_simulate = 1;
            if (__cs_simulate == 1){
            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 10; __cs_simulate = 2;} else            {
                    __cs_l_clear_bit_v = timer_alive;
            }}
            if (__cs_simulate == 1)
            {
                    __cs_l_clear_bit_v = 0;
            }
            __exit__clear_bit_2:;
        }
        if (__cs_simulate == 0 && __cs_pc_2 == 11) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 11; __cs_simulate = 2;} else        {
                tco_expect_close = 0;
        }}
        __exit__i8xx_tco_release_2:;
    }
    if (__cs_simulate == 0 && __cs_pc_2 == 12) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 12; __cs_simulate = 2;} else    {
            cnt2++;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 13))
    {
        __cs_pc_2 = 13;
        __cs_simulate = 2;
    }
}
/* Simulate writer1_isr_3 */
void writer1_isr_3()
{
    {
        static int __cs_l_i8xx_tco_write_len;
        if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else        {
                __cs_l_i8xx_tco_write_len = 0;
        }}
        if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;}
        if ((__cs_simulate == 0 && __cs_pc_3 <= 5) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
        {
                    if (__cs_simulate == 0 && __cs_pc_3 == 2) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 2; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_3 <= 5) || (__cs_simulate == 1 && (!nowayout)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_3 == 3) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 3; __cs_simulate = 2;} else                                {
                                        tco_expect_close = 0;
                                }}
                                if (__cs_simulate == 0 && __cs_pc_3 == 4) __cs_simulate = 1;
                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 4; __cs_simulate = 2;}
                                if ((__cs_simulate == 0 && __cs_pc_3 <= 5) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                {
                                            if (__cs_simulate == 0 && __cs_pc_3 == 5) __cs_simulate = 1;
                                            if (__cs_simulate == 1){
                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 5; __cs_simulate = 2;} else                                            {
                                                    tco_expect_close = 42;
                                            }}
                                }
                    }
        }
        {
            {
                static int __cs_l_outb_v;
                if (__cs_simulate == 1)
                {
                        __cs_l_outb_v = 0x01;
                }
                static int __cs_l_outb_l;
                if (__cs_simulate == 0 && __cs_pc_3 == 6) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 6; __cs_simulate = 2;} else                {
                        __cs_l_outb_l = tco1_rld;
                }}
                if (__cs_simulate == 1)
                {
                        __cs_l_outb_l = __cs_l_outb_v;
                }
                __exit__outb_5:;
            }
            __exit__tco_timer_keepalive_5:;
        }
        __exit__i8xx_tco_write_3:;
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 7) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 7; __cs_simulate = 2;} else    {
            cnt3++;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 8))
    {
        __cs_pc_3 = 8;
        __cs_simulate = 2;
    }
}
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            tco_expect_close = 0;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 1))
    {
        __cs_pc_0 = 1;
        __cs_simulate = 2;
    }
}
/* Simulate closer1_isr_1 */
void closer1_isr_1()
{
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            tco_write_buf = 'V';
    }}
    {
        static int __cs_l_i8xx_tco_write_len;
        if (__cs_simulate == 1)
        {
                __cs_l_i8xx_tco_write_len = 1;
        }
        if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;}
        if ((__cs_simulate == 0 && __cs_pc_1 <= 5) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
        {
                    if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_1 <= 5) || (__cs_simulate == 1 && (!nowayout)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;} else                                {
                                        tco_expect_close = 0;
                                }}
                                if (__cs_simulate == 0 && __cs_pc_1 == 4) __cs_simulate = 1;
                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 4; __cs_simulate = 2;}
                                if ((__cs_simulate == 0 && __cs_pc_1 <= 5) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                {
                                            if (__cs_simulate == 0 && __cs_pc_1 == 5) __cs_simulate = 1;
                                            if (__cs_simulate == 1){
                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 5; __cs_simulate = 2;} else                                            {
                                                    tco_expect_close = 42;
                                            }}
                                }
                    }
        }
        {
            {
                static int __cs_l_outb_v;
                if (__cs_simulate == 1)
                {
                        __cs_l_outb_v = 0x01;
                }
                static int __cs_l_outb_l;
                if (__cs_simulate == 0 && __cs_pc_1 == 6) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 6; __cs_simulate = 2;} else                {
                        __cs_l_outb_l = tco1_rld;
                }}
                if (__cs_simulate == 1)
                {
                        __cs_l_outb_l = __cs_l_outb_v;
                }
                __exit__outb_1:;
            }
            __exit__tco_timer_keepalive_1:;
        }
        __exit__i8xx_tco_write_1:;
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 7) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 7; __cs_simulate = 2;} else    {
            tco_expect_close = 42;
    }}
    {
        {
            {
                static int __cs_l_outb_v;
                if (__cs_simulate == 1)
                {
                        __cs_l_outb_v = 0x01;
                }
                static int __cs_l_outb_l;
                if (__cs_simulate == 0 && __cs_pc_1 == 8) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 8; __cs_simulate = 2;} else                {
                        __cs_l_outb_l = tco1_rld;
                }}
                if (__cs_simulate == 1)
                {
                        __cs_l_outb_l = __cs_l_outb_v;
                }
                __exit__outb_2:;
            }
            __exit__tco_timer_keepalive_2:;
        }
        {
            static int __cs_l_clear_bit_unused;
            if (__cs_simulate == 1)
            {
                    __cs_l_clear_bit_unused = 0;
            }
            static int __cs_l_clear_bit_v;
            if (__cs_simulate == 0 && __cs_pc_1 == 9) __cs_simulate = 1;
            if (__cs_simulate == 1){
            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 9; __cs_simulate = 2;} else            {
                    __cs_l_clear_bit_v = timer_alive;
            }}
            if (__cs_simulate == 1)
            {
                    __cs_l_clear_bit_v = 0;
            }
            __exit__clear_bit_1:;
        }
        if (__cs_simulate == 0 && __cs_pc_1 == 10) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 10; __cs_simulate = 2;} else        {
                tco_expect_close = 0;
        }}
        __exit__i8xx_tco_release_1:;
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 11) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 11; __cs_simulate = 2;} else    {
            cnt1++;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 12))
    {
        __cs_pc_1 = 12;
        __cs_simulate = 2;
    }
}
/* Simulate writer2_isr_4 */
void writer2_isr_4()
{
        if (__cs_simulate == 0 && __cs_pc_4 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 0; __cs_simulate = 2;} else 
{
    {
                        static int __cs_l_i8xx_tco_write_len;
                        __cs_l_i8xx_tco_write_len = 0;
                                if (__cs_l_i8xx_tco_write_len)
        {
                                                            if (!nowayout)
                    {
                                tco_expect_close = 0;
                                                                                        if (tco_write_buf == 'V')
                                {
                                    tco_expect_close = 42;
                                }
                    }
        }
        {
            {
                                static int __cs_l_outb_v;
                                __cs_l_outb_v = 0x01;
                                static int __cs_l_outb_l;
                                __cs_l_outb_l = tco1_rld;
                                __cs_l_outb_l = __cs_l_outb_v;
                                __exit__outb_6:
;
                                ;;
            }
                            __exit__tco_timer_keepalive_6:
;
                            ;;
        }
                        __exit__i8xx_tco_write_4:
;
                        ;;
    }
                    cnt4++;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 8))
    {
        __cs_pc_4 = 8;
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
  __cs_disable_isr_0 = 0;
  __cs_disable_isr_1 = 0;
  __cs_disable_isr_2 = 0;
  __cs_disable_isr_3 = 0;
  __cs_disable_isr_4 = 0;
  while (1)
  {
    __cs_simulate = 0;
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 12)&&(__cs_pc_3 == 0 || __cs_pc_3 == 8)&&(__cs_pc_2 == 0 || __cs_pc_2 == 13)) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 8)&&(__cs_pc_2 == 0 || __cs_pc_2 == 13)&&__cs_disable_isr_1 != 1) {
        closer1_isr_1();
        if (__cs_pc_1 == 12) __cs_pc_1 = 0;
    }
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 8)&&__cs_disable_isr_2 != 1) {
        closer2_isr_2();
        if (__cs_pc_2 == 13) __cs_pc_2 = 0;
    }
    __cs_simulate = 0;
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 13)&&__cs_disable_isr_3 != 1) {
        writer1_isr_3();
        if (__cs_pc_3 == 8) __cs_pc_3 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_4 != 1) {
        writer2_isr_4();
        if (__cs_pc_4 == 8) __cs_pc_4 = 0;
    }
  }
}
