// Main task
unsigned __CPROVER_bitvector[1] __cs_pc_0;
// closer2_isr_1
unsigned __CPROVER_bitvector[6] __cs_pc_1;
// closer1_isr_2
unsigned __CPROVER_bitvector[6] __cs_pc_2;
// writer1_isr_3
unsigned __CPROVER_bitvector[5] __cs_pc_3;
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
/* Simulate closer2_isr_1 */
void closer2_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    tco_write_buf = 'V';
    {
                        static int __cs_l_i8xx_tco_write_len;
                        __cs_l_i8xx_tco_write_len = 1;
                        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_6_1;
                        __cs_l_i8xx_tco_write___cs_dowhile_onetime_6_1 = 0;
                        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_1:
;
                        ;;
                    while (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6_1 < 1)
        {
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
                                static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1;
                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1 = 0;
                                __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_1:
;
                                ;;
                            while (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1 < 1)
                        {
                                    {
                                        static int __cs_l_outb_v;
                                        __cs_l_outb_v = 0x01;
                                        static int __cs_l_outb_l;
                                        __cs_l_outb_l = tco1_rld;
                                        static int __cs_l_outb___cs_dowhile_onetime_3_1;
                                        __cs_l_outb___cs_dowhile_onetime_3_1 = 0;
                                        __begin_outb_loop_0_outb_1:
;
                                        ;;
                                    while (__cs_l_outb___cs_dowhile_onetime_3_1 < 1)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                            __cs_l_outb___cs_dowhile_onetime_3_1++;
                                        }
                                        __end_outb_loop_0_outb_1:
;
                                        ;;
                                        __begin_outb_loop_1_outb_1:
;
                                        ;;
                                    while (0)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                        }
                                        __end_outb_loop_1_outb_1:
;
                                        ;;
                                        __exit__outb_1:
;
                                        ;;
                                    }
                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1++;
                        }
                                __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_1:
;
                                ;;
                                __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_1:
;
                                ;;
                            while (0)
                        {
                                    {
                                        static int __cs_l_outb_v;
                                        __cs_l_outb_v = 0x01;
                                        static int __cs_l_outb_l;
                                        __cs_l_outb_l = tco1_rld;
                                        static int __cs_l_outb___cs_dowhile_onetime_3_1;
                                        __cs_l_outb___cs_dowhile_onetime_3_1 = 0;
                                        __begin_outb_loop_0_outb_2:
;
                                        ;;
                                    while (__cs_l_outb___cs_dowhile_onetime_3_1 < 1)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                            __cs_l_outb___cs_dowhile_onetime_3_1++;
                                        }
                                        __end_outb_loop_0_outb_2:
;
                                        ;;
                                        __begin_outb_loop_1_outb_2:
;
                                        ;;
                                    while (0)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                        }
                                        __end_outb_loop_1_outb_2:
;
                                        ;;
                                        __exit__outb_2:
;
                                        ;;
                                    }
                        }
                                __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_1:
;
                                ;;
                                __exit__tco_timer_keepalive_1:
;
                                ;;
                    }
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6_1++;
        }
                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_1:
;
                        ;;
                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_1:
;
                        ;;
                    while (0)
        {
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
                                static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1;
                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1 = 0;
                                __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_2:
;
                                ;;
                            while (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1 < 1)
                        {
                                    {
                                        static int __cs_l_outb_v;
                                        __cs_l_outb_v = 0x01;
                                        static int __cs_l_outb_l;
                                        __cs_l_outb_l = tco1_rld;
                                        static int __cs_l_outb___cs_dowhile_onetime_3_1;
                                        __cs_l_outb___cs_dowhile_onetime_3_1 = 0;
                                        __begin_outb_loop_0_outb_3:
;
                                        ;;
                                    while (__cs_l_outb___cs_dowhile_onetime_3_1 < 1)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                            __cs_l_outb___cs_dowhile_onetime_3_1++;
                                        }
                                        __end_outb_loop_0_outb_3:
;
                                        ;;
                                        __begin_outb_loop_1_outb_3:
;
                                        ;;
                                    while (0)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                        }
                                        __end_outb_loop_1_outb_3:
;
                                        ;;
                                        __exit__outb_3:
;
                                        ;;
                                    }
                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1++;
                        }
                                __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_2:
;
                                ;;
                                __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_2:
;
                                ;;
                            while (0)
                        {
                                    {
                                        static int __cs_l_outb_v;
                                        __cs_l_outb_v = 0x01;
                                        static int __cs_l_outb_l;
                                        __cs_l_outb_l = tco1_rld;
                                        static int __cs_l_outb___cs_dowhile_onetime_3_1;
                                        __cs_l_outb___cs_dowhile_onetime_3_1 = 0;
                                        __begin_outb_loop_0_outb_4:
;
                                        ;;
                                    while (__cs_l_outb___cs_dowhile_onetime_3_1 < 1)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                            __cs_l_outb___cs_dowhile_onetime_3_1++;
                                        }
                                        __end_outb_loop_0_outb_4:
;
                                        ;;
                                        __begin_outb_loop_1_outb_4:
;
                                        ;;
                                    while (0)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                        }
                                        __end_outb_loop_1_outb_4:
;
                                        ;;
                                        __exit__outb_4:
;
                                        ;;
                                    }
                        }
                                __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_2:
;
                                ;;
                                __exit__tco_timer_keepalive_2:
;
                                ;;
                    }
        }
                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_1:
;
                        ;;
                        __exit__i8xx_tco_write_1:
;
                        ;;
    }
                    tco_expect_close = 42;
    {
                                if (tco_expect_close != 42)
        {
                            assert(0);
        }
        {
                            static int __cs_l_clear_bit_unused;
                            __cs_l_clear_bit_unused = 0;
                            static int __cs_l_clear_bit_v;
                            __cs_l_clear_bit_v = timer_alive;
                            static int __cs_l_clear_bit___cs_dowhile_onetime_4_1;
                            __cs_l_clear_bit___cs_dowhile_onetime_4_1 = 0;
                            __begin_clear_bit_loop_0_clear_bit_1:
;
                            ;;
                        while (__cs_l_clear_bit___cs_dowhile_onetime_4_1 < 1)
            {
                                __cs_l_clear_bit_v = 0;
                                __cs_l_clear_bit___cs_dowhile_onetime_4_1++;
            }
                            __end_clear_bit_loop_0_clear_bit_1:
;
                            ;;
                            __begin_clear_bit_loop_1_clear_bit_1:
;
                            ;;
                        while (0)
            {
                                __cs_l_clear_bit_v = 0;
            }
                            __end_clear_bit_loop_1_clear_bit_1:
;
                            ;;
                            __exit__clear_bit_1:
;
                            ;;
        }
                        tco_expect_close = 0;
                        __exit__i8xx_tco_release_1:
;
                        ;;
    }
                    cnt1++;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 37))
    {
        __cs_pc_1 = 37;
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
        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_6_1;
        if (__cs_simulate == 1)
        {
                __cs_l_i8xx_tco_write___cs_dowhile_onetime_6_1 = 0;
        }
        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_3:;
        if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_3 <= 14) || ((__cs_simulate == 1) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6_1 < 1)))
        {
                    if (__cs_simulate == 0 && __cs_pc_3 == 2) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 2; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_3 <= 6) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_3 == 3) __cs_simulate = 1;
                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 3; __cs_simulate = 2;}
                                if ((__cs_simulate == 0 && __cs_pc_3 <= 6) || (__cs_simulate == 1 && (!nowayout)))
                                {
                                            if (__cs_simulate == 0 && __cs_pc_3 == 4) __cs_simulate = 1;
                                            if (__cs_simulate == 1){
                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 4; __cs_simulate = 2;} else                                            {
                                                    tco_expect_close = 0;
                                            }}
                                            if (__cs_simulate == 0 && __cs_pc_3 == 5) __cs_simulate = 1;
                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 5; __cs_simulate = 2;}
                                            if ((__cs_simulate == 0 && __cs_pc_3 <= 6) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                            {
                                                        if (__cs_simulate == 0 && __cs_pc_3 == 6) __cs_simulate = 1;
                                                        if (__cs_simulate == 1){
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 6; __cs_simulate = 2;} else                                                        {
                                                                tco_expect_close = 42;
                                                        }}
                                            }
                                }
                    }
                    {
                        static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1;
                        if (__cs_simulate == 1)
                        {
                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1 = 0;
                        }
                        __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_5:;
                        if (__cs_simulate == 0 && __cs_pc_3 == 7) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 7; __cs_simulate = 2;}
                        while ((__cs_simulate == 0 && __cs_pc_3 <= 10) || ((__cs_simulate == 1) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1 < 1)))
                        {
                                    {
                                        static int __cs_l_outb_v;
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_outb_v = 0x01;
                                        }
                                        static int __cs_l_outb_l;
                                        if (__cs_simulate == 0 && __cs_pc_3 == 8) __cs_simulate = 1;
                                        if (__cs_simulate == 1){
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 8; __cs_simulate = 2;} else                                        {
                                                __cs_l_outb_l = tco1_rld;
                                        }}
                                        static int __cs_l_outb___cs_dowhile_onetime_3_1;
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_outb___cs_dowhile_onetime_3_1 = 0;
                                        }
                                        __begin_outb_loop_0_outb_9:;
                                        if (__cs_simulate == 0 && __cs_pc_3 == 9) __cs_simulate = 1;
                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 9; __cs_simulate = 2;}
                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 9) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3_1 < 1)))
                                        {
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                    }
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __cs_l_outb___cs_dowhile_onetime_3_1++;
                                                    }
                                        }
                                        __end_outb_loop_0_outb_9:;
                                        __begin_outb_loop_1_outb_9:;
                                        if (__cs_simulate == 0 && __cs_pc_3 == 10) __cs_simulate = 1;
                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 10; __cs_simulate = 2;}
                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 10) || ((__cs_simulate == 1) && (0)))
                                        {
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                    }
                                        }
                                        __end_outb_loop_1_outb_9:;
                                        __exit__outb_9:;
                                    }
                                    if (__cs_simulate == 1)
                                    {
                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1++;
                                    }
                        }
                        __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_5:;
                        __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_5:;
                        if (__cs_simulate == 0 && __cs_pc_3 == 11) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 11; __cs_simulate = 2;}
                        while ((__cs_simulate == 0 && __cs_pc_3 <= 14) || ((__cs_simulate == 1) && (0)))
                        {
                                    {
                                        static int __cs_l_outb_v;
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_outb_v = 0x01;
                                        }
                                        static int __cs_l_outb_l;
                                        if (__cs_simulate == 0 && __cs_pc_3 == 12) __cs_simulate = 1;
                                        if (__cs_simulate == 1){
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 12; __cs_simulate = 2;} else                                        {
                                                __cs_l_outb_l = tco1_rld;
                                        }}
                                        static int __cs_l_outb___cs_dowhile_onetime_3_1;
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_outb___cs_dowhile_onetime_3_1 = 0;
                                        }
                                        __begin_outb_loop_0_outb_10:;
                                        if (__cs_simulate == 0 && __cs_pc_3 == 13) __cs_simulate = 1;
                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 13; __cs_simulate = 2;}
                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 13) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3_1 < 1)))
                                        {
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                    }
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __cs_l_outb___cs_dowhile_onetime_3_1++;
                                                    }
                                        }
                                        __end_outb_loop_0_outb_10:;
                                        __begin_outb_loop_1_outb_10:;
                                        if (__cs_simulate == 0 && __cs_pc_3 == 14) __cs_simulate = 1;
                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 14; __cs_simulate = 2;}
                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 14) || ((__cs_simulate == 1) && (0)))
                                        {
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                    }
                                        }
                                        __end_outb_loop_1_outb_10:;
                                        __exit__outb_10:;
                                    }
                        }
                        __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_5:;
                        __exit__tco_timer_keepalive_5:;
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6_1++;
                    }
        }
        __end_i8xx_tco_write_loop_0_i8xx_tco_write_3:;
        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_3:;
        if (__cs_simulate == 0 && __cs_pc_3 == 15) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 15; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_3 <= 28) || ((__cs_simulate == 1) && (0)))
        {
                    if (__cs_simulate == 0 && __cs_pc_3 == 16) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 16; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_3 <= 20) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_3 == 17) __cs_simulate = 1;
                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 17; __cs_simulate = 2;}
                                if ((__cs_simulate == 0 && __cs_pc_3 <= 20) || (__cs_simulate == 1 && (!nowayout)))
                                {
                                            if (__cs_simulate == 0 && __cs_pc_3 == 18) __cs_simulate = 1;
                                            if (__cs_simulate == 1){
                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 18; __cs_simulate = 2;} else                                            {
                                                    tco_expect_close = 0;
                                            }}
                                            if (__cs_simulate == 0 && __cs_pc_3 == 19) __cs_simulate = 1;
                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 19; __cs_simulate = 2;}
                                            if ((__cs_simulate == 0 && __cs_pc_3 <= 20) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                            {
                                                        if (__cs_simulate == 0 && __cs_pc_3 == 20) __cs_simulate = 1;
                                                        if (__cs_simulate == 1){
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 20; __cs_simulate = 2;} else                                                        {
                                                                tco_expect_close = 42;
                                                        }}
                                            }
                                }
                    }
                    {
                        static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1;
                        if (__cs_simulate == 1)
                        {
                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1 = 0;
                        }
                        __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_6:;
                        if (__cs_simulate == 0 && __cs_pc_3 == 21) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 21; __cs_simulate = 2;}
                        while ((__cs_simulate == 0 && __cs_pc_3 <= 24) || ((__cs_simulate == 1) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1 < 1)))
                        {
                                    {
                                        static int __cs_l_outb_v;
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_outb_v = 0x01;
                                        }
                                        static int __cs_l_outb_l;
                                        if (__cs_simulate == 0 && __cs_pc_3 == 22) __cs_simulate = 1;
                                        if (__cs_simulate == 1){
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 22; __cs_simulate = 2;} else                                        {
                                                __cs_l_outb_l = tco1_rld;
                                        }}
                                        static int __cs_l_outb___cs_dowhile_onetime_3_1;
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_outb___cs_dowhile_onetime_3_1 = 0;
                                        }
                                        __begin_outb_loop_0_outb_11:;
                                        if (__cs_simulate == 0 && __cs_pc_3 == 23) __cs_simulate = 1;
                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 23; __cs_simulate = 2;}
                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 23) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3_1 < 1)))
                                        {
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                    }
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __cs_l_outb___cs_dowhile_onetime_3_1++;
                                                    }
                                        }
                                        __end_outb_loop_0_outb_11:;
                                        __begin_outb_loop_1_outb_11:;
                                        if (__cs_simulate == 0 && __cs_pc_3 == 24) __cs_simulate = 1;
                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 24; __cs_simulate = 2;}
                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 24) || ((__cs_simulate == 1) && (0)))
                                        {
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                    }
                                        }
                                        __end_outb_loop_1_outb_11:;
                                        __exit__outb_11:;
                                    }
                                    if (__cs_simulate == 1)
                                    {
                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1++;
                                    }
                        }
                        __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_6:;
                        __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_6:;
                        if (__cs_simulate == 0 && __cs_pc_3 == 25) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 25; __cs_simulate = 2;}
                        while ((__cs_simulate == 0 && __cs_pc_3 <= 28) || ((__cs_simulate == 1) && (0)))
                        {
                                    {
                                        static int __cs_l_outb_v;
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_outb_v = 0x01;
                                        }
                                        static int __cs_l_outb_l;
                                        if (__cs_simulate == 0 && __cs_pc_3 == 26) __cs_simulate = 1;
                                        if (__cs_simulate == 1){
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 26; __cs_simulate = 2;} else                                        {
                                                __cs_l_outb_l = tco1_rld;
                                        }}
                                        static int __cs_l_outb___cs_dowhile_onetime_3_1;
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_outb___cs_dowhile_onetime_3_1 = 0;
                                        }
                                        __begin_outb_loop_0_outb_12:;
                                        if (__cs_simulate == 0 && __cs_pc_3 == 27) __cs_simulate = 1;
                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 27; __cs_simulate = 2;}
                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 27) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3_1 < 1)))
                                        {
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                    }
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __cs_l_outb___cs_dowhile_onetime_3_1++;
                                                    }
                                        }
                                        __end_outb_loop_0_outb_12:;
                                        __begin_outb_loop_1_outb_12:;
                                        if (__cs_simulate == 0 && __cs_pc_3 == 28) __cs_simulate = 1;
                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 28; __cs_simulate = 2;}
                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 28) || ((__cs_simulate == 1) && (0)))
                                        {
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                    }
                                        }
                                        __end_outb_loop_1_outb_12:;
                                        __exit__outb_12:;
                                    }
                        }
                        __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_6:;
                        __exit__tco_timer_keepalive_6:;
                    }
        }
        __end_i8xx_tco_write_loop_1_i8xx_tco_write_3:;
        __exit__i8xx_tco_write_3:;
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 29) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 29; __cs_simulate = 2;} else    {
            cnt3++;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 30))
    {
        __cs_pc_3 = 30;
        __cs_simulate = 2;
    }
}
/* Simulate closer1_isr_2 */
void closer1_isr_2()
{
        if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else 
{
                    tco_write_buf = 'V';
    {
                        static int __cs_l_i8xx_tco_write_len;
                        __cs_l_i8xx_tco_write_len = 1;
                        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_6_1;
                        __cs_l_i8xx_tco_write___cs_dowhile_onetime_6_1 = 0;
                        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_2:
;
                        ;;
                    while (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6_1 < 1)
        {
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
                                static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1;
                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1 = 0;
                                __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_3:
;
                                ;;
                            while (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1 < 1)
                        {
                                    {
                                        static int __cs_l_outb_v;
                                        __cs_l_outb_v = 0x01;
                                        static int __cs_l_outb_l;
                                        __cs_l_outb_l = tco1_rld;
                                        static int __cs_l_outb___cs_dowhile_onetime_3_1;
                                        __cs_l_outb___cs_dowhile_onetime_3_1 = 0;
                                        __begin_outb_loop_0_outb_5:
;
                                        ;;
                                    while (__cs_l_outb___cs_dowhile_onetime_3_1 < 1)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                            __cs_l_outb___cs_dowhile_onetime_3_1++;
                                        }
                                        __end_outb_loop_0_outb_5:
;
                                        ;;
                                        __begin_outb_loop_1_outb_5:
;
                                        ;;
                                    while (0)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                        }
                                        __end_outb_loop_1_outb_5:
;
                                        ;;
                                        __exit__outb_5:
;
                                        ;;
                                    }
                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1++;
                        }
                                __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_3:
;
                                ;;
                                __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_3:
;
                                ;;
                            while (0)
                        {
                                    {
                                        static int __cs_l_outb_v;
                                        __cs_l_outb_v = 0x01;
                                        static int __cs_l_outb_l;
                                        __cs_l_outb_l = tco1_rld;
                                        static int __cs_l_outb___cs_dowhile_onetime_3_1;
                                        __cs_l_outb___cs_dowhile_onetime_3_1 = 0;
                                        __begin_outb_loop_0_outb_6:
;
                                        ;;
                                    while (__cs_l_outb___cs_dowhile_onetime_3_1 < 1)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                            __cs_l_outb___cs_dowhile_onetime_3_1++;
                                        }
                                        __end_outb_loop_0_outb_6:
;
                                        ;;
                                        __begin_outb_loop_1_outb_6:
;
                                        ;;
                                    while (0)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                        }
                                        __end_outb_loop_1_outb_6:
;
                                        ;;
                                        __exit__outb_6:
;
                                        ;;
                                    }
                        }
                                __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_3:
;
                                ;;
                                __exit__tco_timer_keepalive_3:
;
                                ;;
                    }
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6_1++;
        }
                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_2:
;
                        ;;
                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_2:
;
                        ;;
                    while (0)
        {
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
                                static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1;
                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1 = 0;
                                __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_4:
;
                                ;;
                            while (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1 < 1)
                        {
                                    {
                                        static int __cs_l_outb_v;
                                        __cs_l_outb_v = 0x01;
                                        static int __cs_l_outb_l;
                                        __cs_l_outb_l = tco1_rld;
                                        static int __cs_l_outb___cs_dowhile_onetime_3_1;
                                        __cs_l_outb___cs_dowhile_onetime_3_1 = 0;
                                        __begin_outb_loop_0_outb_7:
;
                                        ;;
                                    while (__cs_l_outb___cs_dowhile_onetime_3_1 < 1)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                            __cs_l_outb___cs_dowhile_onetime_3_1++;
                                        }
                                        __end_outb_loop_0_outb_7:
;
                                        ;;
                                        __begin_outb_loop_1_outb_7:
;
                                        ;;
                                    while (0)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                        }
                                        __end_outb_loop_1_outb_7:
;
                                        ;;
                                        __exit__outb_7:
;
                                        ;;
                                    }
                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5_1++;
                        }
                                __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_4:
;
                                ;;
                                __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_4:
;
                                ;;
                            while (0)
                        {
                                    {
                                        static int __cs_l_outb_v;
                                        __cs_l_outb_v = 0x01;
                                        static int __cs_l_outb_l;
                                        __cs_l_outb_l = tco1_rld;
                                        static int __cs_l_outb___cs_dowhile_onetime_3_1;
                                        __cs_l_outb___cs_dowhile_onetime_3_1 = 0;
                                        __begin_outb_loop_0_outb_8:
;
                                        ;;
                                    while (__cs_l_outb___cs_dowhile_onetime_3_1 < 1)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                            __cs_l_outb___cs_dowhile_onetime_3_1++;
                                        }
                                        __end_outb_loop_0_outb_8:
;
                                        ;;
                                        __begin_outb_loop_1_outb_8:
;
                                        ;;
                                    while (0)
                                        {
                                            __cs_l_outb_l = __cs_l_outb_v;
                                        }
                                        __end_outb_loop_1_outb_8:
;
                                        ;;
                                        __exit__outb_8:
;
                                        ;;
                                    }
                        }
                                __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_4:
;
                                ;;
                                __exit__tco_timer_keepalive_4:
;
                                ;;
                    }
        }
                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_2:
;
                        ;;
                        __exit__i8xx_tco_write_2:
;
                        ;;
    }
                    tco_expect_close = 42;
    {
                                if (tco_expect_close != 42)
        {
                            assert(0);
        }
        {
                            static int __cs_l_clear_bit_unused;
                            __cs_l_clear_bit_unused = 0;
                            static int __cs_l_clear_bit_v;
                            __cs_l_clear_bit_v = timer_alive;
                            static int __cs_l_clear_bit___cs_dowhile_onetime_4_1;
                            __cs_l_clear_bit___cs_dowhile_onetime_4_1 = 0;
                            __begin_clear_bit_loop_0_clear_bit_2:
;
                            ;;
                        while (__cs_l_clear_bit___cs_dowhile_onetime_4_1 < 1)
            {
                                __cs_l_clear_bit_v = 0;
                                __cs_l_clear_bit___cs_dowhile_onetime_4_1++;
            }
                            __end_clear_bit_loop_0_clear_bit_2:
;
                            ;;
                            __begin_clear_bit_loop_1_clear_bit_2:
;
                            ;;
                        while (0)
            {
                                __cs_l_clear_bit_v = 0;
            }
                            __end_clear_bit_loop_1_clear_bit_2:
;
                            ;;
                            __exit__clear_bit_2:
;
                            ;;
        }
                        tco_expect_close = 0;
                        __exit__i8xx_tco_release_2:
;
                        ;;
    }
                    cnt2++;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 37))
    {
        __cs_pc_2 = 37;
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
  __cs_disable_isr_0 = 0;
  __cs_disable_isr_1 = 0;
  __cs_disable_isr_2 = 0;
  __cs_disable_isr_3 = 0;
  while (1)
  {
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 30)) main_task();
    __cs_simulate = 0;
    if (__cs_disable_isr_1 != 1) {
        closer2_isr_1();
        if (__cs_pc_1 == 37) __cs_pc_1 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_2 != 1) {
        closer1_isr_2();
        if (__cs_pc_2 == 37) __cs_pc_2 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_3 != 1) {
        writer1_isr_3();
        if (__cs_pc_3 == 30) __cs_pc_3 = 0;
    }
  }
}
