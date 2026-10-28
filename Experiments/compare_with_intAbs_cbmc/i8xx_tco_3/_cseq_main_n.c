// Main task
unsigned __CPROVER_bitvector[1] __cs_pc_7;
// closer1_isr_1
unsigned __CPROVER_bitvector[6] __cs_pc_1;
// closer2_isr_2
unsigned __CPROVER_bitvector[6] __cs_pc_2;
// closer3_isr_3
unsigned __CPROVER_bitvector[6] __cs_pc_3;
// writer1_isr_4
unsigned __CPROVER_bitvector[5] __cs_pc_4;
// writer2_isr_5
unsigned __CPROVER_bitvector[5] __cs_pc_5;
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
int cnt6;
int cnt7;
int cnt8;
/* Simulate writer3_isr_6 */
void writer3_isr_6()
{
        if (__cs_simulate == 0 && __cs_pc_6 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_6 = 0; __cs_simulate = 2;} else {
                        static int __cs_l_i8xx_tco_write_len;
                        __cs_l_i8xx_tco_write_len = 0;
                        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = 0;
                        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_6:
;
                        ;;
                    while (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1){
                                            if (__cs_l_i8xx_tco_write_len)
                                                                        if (!nowayout)
                                    tco_expect_close = 0;
                                                                                                    if (tco_write_buf == 'V')
                                        tco_expect_close = 42;
                                static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_11:
;
                                ;;
                            while (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1){
                                        static int __cs_l_outb_v;
                                        __cs_l_outb_v = 0x01;
                                        static int __cs_l_outb_l;
                                        __cs_l_outb_l = tco1_rld;
                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                        __begin_outb_loop_0_outb_21:
;
                                        ;;
                                    while (__cs_l_outb___cs_dowhile_onetime_3 < 1){
                                            __cs_l_outb_l = __cs_l_outb_v;
                                            __cs_l_outb___cs_dowhile_onetime_3++;
                                    }
                                        __end_outb_loop_0_outb_21:
;
                                        ;;
                                        __begin_outb_loop_1_outb_21:
;
                                        ;;
                                    while (0){
                                            __cs_l_outb_l = __cs_l_outb_v;
                                    }
                                        __end_outb_loop_1_outb_21:
;
                                        ;;
                                        __exit__outb_21:
;
                                        ;;
                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                            }
                                __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_11:
;
                                ;;
                                __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_11:
;
                                ;;
                            while (0){
                                        static int __cs_l_outb_v;
                                        __cs_l_outb_v = 0x01;
                                        static int __cs_l_outb_l;
                                        __cs_l_outb_l = tco1_rld;
                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                        __begin_outb_loop_0_outb_22:
;
                                        ;;
                                    while (__cs_l_outb___cs_dowhile_onetime_3 < 1){
                                            __cs_l_outb_l = __cs_l_outb_v;
                                            __cs_l_outb___cs_dowhile_onetime_3++;
                                    }
                                        __end_outb_loop_0_outb_22:
;
                                        ;;
                                        __begin_outb_loop_1_outb_22:
;
                                        ;;
                                    while (0){
                                            __cs_l_outb_l = __cs_l_outb_v;
                                    }
                                        __end_outb_loop_1_outb_22:
;
                                        ;;
                                        __exit__outb_22:
;
                                        ;;
                            }
                                __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_11:
;
                                ;;
                                __exit__tco_timer_keepalive_11:
;
                                ;;
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
                    }
                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_6:
;
                        ;;
                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_6:
;
                        ;;
                    while (0){
                                                                                            if (__cs_l_i8xx_tco_write_len)
                                                                                                                        if (!nowayout)
                                    tco_expect_close = 0;
                                                                                                                                                    if (tco_write_buf == 'V')
                                        tco_expect_close = 42;
                                static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_12:
;
                                ;;
                            while (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1){
                                        static int __cs_l_outb_v;
                                        __cs_l_outb_v = 0x01;
                                        static int __cs_l_outb_l;
                                        __cs_l_outb_l = tco1_rld;
                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                        __begin_outb_loop_0_outb_23:
;
                                        ;;
                                    while (__cs_l_outb___cs_dowhile_onetime_3 < 1){
                                            __cs_l_outb_l = __cs_l_outb_v;
                                            __cs_l_outb___cs_dowhile_onetime_3++;
                                    }
                                        __end_outb_loop_0_outb_23:
;
                                        ;;
                                        __begin_outb_loop_1_outb_23:
;
                                        ;;
                                    while (0){
                                            __cs_l_outb_l = __cs_l_outb_v;
                                    }
                                        __end_outb_loop_1_outb_23:
;
                                        ;;
                                        __exit__outb_23:
;
                                        ;;
                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                            }
                                __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_12:
;
                                ;;
                                __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_12:
;
                                ;;
                            while (0){
                                        static int __cs_l_outb_v;
                                        __cs_l_outb_v = 0x01;
                                        static int __cs_l_outb_l;
                                        __cs_l_outb_l = tco1_rld;
                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                        __begin_outb_loop_0_outb_24:
;
                                        ;;
                                    while (__cs_l_outb___cs_dowhile_onetime_3 < 1){
                                            __cs_l_outb_l = __cs_l_outb_v;
                                            __cs_l_outb___cs_dowhile_onetime_3++;
                                    }
                                        __end_outb_loop_0_outb_24:
;
                                        ;;
                                        __begin_outb_loop_1_outb_24:
;
                                        ;;
                                    while (0){
                                            __cs_l_outb_l = __cs_l_outb_v;
                                    }
                                        __end_outb_loop_1_outb_24:
;
                                        ;;
                                        __exit__outb_24:
;
                                        ;;
                            }
                                __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_12:
;
                                ;;
                                __exit__tco_timer_keepalive_12:
;
                                ;;
                    }
                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_6:
;
                        ;;
                        __exit__i8xx_tco_write_6:
;
                        ;;
                    cnt6++;
        }
                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_6 == 30))
                                                    {
                                                        __cs_pc_6 = 30;
                                                        __cs_simulate = 2;
                                                    }
}
/* Simulate original main */
int main_task()
                                                {
                                                    if (__cs_simulate == 0 && __cs_pc_7 == 0) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_7 = 0; __cs_simulate = 2;} else                                                    {
                                                            tco_expect_close = 0;
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
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else                                                    {
                                                            tco_write_buf = 'V';
                                                    }
                                                    {
                                                        static int __cs_l_i8xx_tco_write_len;
                                                        if (__cs_simulate == 1)
                                                        {
                                                                __cs_l_i8xx_tco_write_len = 1;
                                                        }
                                                        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = 0;
                                                        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_1:;
                                                        if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 14) || ((__cs_simulate == 1) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;}
                                                                    if ((__cs_simulate == 0 && __cs_pc_1 <= 6) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                                                                    {
                                                                                if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;}
                                                                                if ((__cs_simulate == 0 && __cs_pc_1 <= 6) || (__cs_simulate == 1 && (!nowayout)))
                                                                                {
                                                                                            if (__cs_simulate == 0 && __cs_pc_1 == 4) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1)
                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 4; __cs_simulate = 2;} else                                                                                            {
                                                                                                    tco_expect_close = 0;
                                                                                            }
                                                                                            if (__cs_simulate == 0 && __cs_pc_1 == 5) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 5; __cs_simulate = 2;}
                                                                                            if ((__cs_simulate == 0 && __cs_pc_1 <= 6) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                            {
                                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 6) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 6; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                tco_expect_close = 42;
                                                                                                        }
                                                                                            }
                                                                                }
                                                                    }
                                                                    {
                                                                        static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                        __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_1:;
                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 7) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 7; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 10) || ((__cs_simulate == 1) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 8) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 8; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_1:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 9) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 9; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 9) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_1:;
                                                                                        __begin_outb_loop_1_outb_1:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 10) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 10; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 10) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_1:;
                                                                                        __exit__outb_1:;
                                                                                    }
                                                                                    if (__cs_simulate == 1)
                                                                                    {
                                                                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_1:;
                                                                        __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_1:;
                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 11) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 11; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 14) || ((__cs_simulate == 1) && (0)))
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
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 12; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_2:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 13) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 13; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 13) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_2:;
                                                                                        __begin_outb_loop_1_outb_2:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 14) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 14; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 14) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_2:;
                                                                                        __exit__outb_2:;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_1:;
                                                                        __exit__tco_timer_keepalive_1:;
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
                                                                    }
                                                        }
                                                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_1:;
                                                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_1:;
                                                        if (__cs_simulate == 0 && __cs_pc_1 == 15) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 15; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 28) || ((__cs_simulate == 1) && (0)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_1 == 16) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 16; __cs_simulate = 2;}
                                                                    if ((__cs_simulate == 0 && __cs_pc_1 <= 20) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                                                                    {
                                                                                if (__cs_simulate == 0 && __cs_pc_1 == 17) __cs_simulate = 1;
                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 17; __cs_simulate = 2;}
                                                                                if ((__cs_simulate == 0 && __cs_pc_1 <= 20) || (__cs_simulate == 1 && (!nowayout)))
                                                                                {
                                                                                            if (__cs_simulate == 0 && __cs_pc_1 == 18) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1)
                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 18; __cs_simulate = 2;} else                                                                                            {
                                                                                                    tco_expect_close = 0;
                                                                                            }
                                                                                            if (__cs_simulate == 0 && __cs_pc_1 == 19) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 19; __cs_simulate = 2;}
                                                                                            if ((__cs_simulate == 0 && __cs_pc_1 <= 20) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                            {
                                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 20) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 20; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                tco_expect_close = 42;
                                                                                                        }
                                                                                            }
                                                                                }
                                                                    }
                                                                    {
                                                                        static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                        __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_2:;
                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 21) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 21; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 24) || ((__cs_simulate == 1) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 22) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 22; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_3:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 23) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 23; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 23) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_3:;
                                                                                        __begin_outb_loop_1_outb_3:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 24) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 24; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 24) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_3:;
                                                                                        __exit__outb_3:;
                                                                                    }
                                                                                    if (__cs_simulate == 1)
                                                                                    {
                                                                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_2:;
                                                                        __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_2:;
                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 25) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 25; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 28) || ((__cs_simulate == 1) && (0)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 26) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 26; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_4:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 27) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 27; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 27) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_4:;
                                                                                        __begin_outb_loop_1_outb_4:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 28) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 28; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 28) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_4:;
                                                                                        __exit__outb_4:;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_2:;
                                                                        __exit__tco_timer_keepalive_2:;
                                                                    }
                                                        }
                                                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_1:;
                                                        __exit__i8xx_tco_write_1:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_1 == 29) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 29; __cs_simulate = 2;} else                                                    {
                                                            tco_expect_close = 42;
                                                    }
                                                    {
                                                        if (__cs_simulate == 0 && __cs_pc_1 == 30) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 30; __cs_simulate = 2;}
                                                        if ((__cs_simulate == 0 && __cs_pc_1 <= 31) || (__cs_simulate == 1 && (tco_expect_close != 42)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_1 == 31) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 31; __cs_simulate = 2;} else                                                                    {
                                                                            assert(0);
                                                                    }
                                                        }
                                                        {
                                                            static int __cs_l_clear_bit_unused;
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_clear_bit_unused = 0;
                                                            }
                                                            static int __cs_l_clear_bit_v;
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 32) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 32; __cs_simulate = 2;} else                                                            {
                                                                    __cs_l_clear_bit_v = timer_alive;
                                                            }
                                                            static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                                                            __begin_clear_bit_loop_0_clear_bit_1:;
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 33) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 33; __cs_simulate = 2;}
                                                            while ((__cs_simulate == 0 && __cs_pc_1 <= 33) || ((__cs_simulate == 1) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1)))
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
                                                            __end_clear_bit_loop_0_clear_bit_1:;
                                                            __begin_clear_bit_loop_1_clear_bit_1:;
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 34) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 34; __cs_simulate = 2;}
                                                            while ((__cs_simulate == 0 && __cs_pc_1 <= 34) || ((__cs_simulate == 1) && (0)))
                                                            {
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                __cs_l_clear_bit_v = 0;
                                                                        }
                                                            }
                                                            __end_clear_bit_loop_1_clear_bit_1:;
                                                            __exit__clear_bit_1:;
                                                        }
                                                        if (__cs_simulate == 0 && __cs_pc_1 == 35) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 35; __cs_simulate = 2;} else                                                        {
                                                                tco_expect_close = 0;
                                                        }
                                                        __exit__i8xx_tco_release_1:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_1 == 36) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 36; __cs_simulate = 2;} else                                                    {
                                                            cnt1++;
                                                    }
                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 37))
                                                    {
                                                        __cs_pc_1 = 37;
                                                        __cs_simulate = 2;
                                                    }
                                                }
/* Simulate closer3_isr_3 */
void closer3_isr_3()
                                                {
                                                    if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else                                                    {
                                                            tco_write_buf = 'V';
                                                    }
                                                    {
                                                        static int __cs_l_i8xx_tco_write_len;
                                                        if (__cs_simulate == 1)
                                                        {
                                                                __cs_l_i8xx_tco_write_len = 1;
                                                        }
                                                        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = 0;
                                                        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_3:;
                                                        if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 14) || ((__cs_simulate == 1) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1)))
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
                                                                                            if (__cs_simulate == 1)
                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 4; __cs_simulate = 2;} else                                                                                            {
                                                                                                    tco_expect_close = 0;
                                                                                            }
                                                                                            if (__cs_simulate == 0 && __cs_pc_3 == 5) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 5; __cs_simulate = 2;}
                                                                                            if ((__cs_simulate == 0 && __cs_pc_3 <= 6) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                            {
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 6) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 6; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                tco_expect_close = 42;
                                                                                                        }
                                                                                            }
                                                                                }
                                                                    }
                                                                    {
                                                                        static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                        __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_5:;
                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 7) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 7; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 10) || ((__cs_simulate == 1) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 8) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 8; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_9:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 9) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 9; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 9) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
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
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 12; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_10:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 13) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 13; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 13) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
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
                                                                                            if (__cs_simulate == 1)
                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 18; __cs_simulate = 2;} else                                                                                            {
                                                                                                    tco_expect_close = 0;
                                                                                            }
                                                                                            if (__cs_simulate == 0 && __cs_pc_3 == 19) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 19; __cs_simulate = 2;}
                                                                                            if ((__cs_simulate == 0 && __cs_pc_3 <= 20) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                            {
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 20) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 20; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                tco_expect_close = 42;
                                                                                                        }
                                                                                            }
                                                                                }
                                                                    }
                                                                    {
                                                                        static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                        __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_6:;
                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 21) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 21; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 24) || ((__cs_simulate == 1) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 22) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 22; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_11:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 23) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 23; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 23) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
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
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 26; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_12:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 27) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 27; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 27) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 29; __cs_simulate = 2;} else                                                    {
                                                            tco_expect_close = 42;
                                                    }
                                                    {
                                                        if (__cs_simulate == 0 && __cs_pc_3 == 30) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 30; __cs_simulate = 2;}
                                                        if ((__cs_simulate == 0 && __cs_pc_3 <= 31) || (__cs_simulate == 1 && (tco_expect_close != 42)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 31) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 31; __cs_simulate = 2;} else                                                                    {
                                                                            assert(0);
                                                                    }
                                                        }
                                                        {
                                                            static int __cs_l_clear_bit_unused;
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_clear_bit_unused = 0;
                                                            }
                                                            static int __cs_l_clear_bit_v;
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 32) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 32; __cs_simulate = 2;} else                                                            {
                                                                    __cs_l_clear_bit_v = timer_alive;
                                                            }
                                                            static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                                                            __begin_clear_bit_loop_0_clear_bit_3:;
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 33) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 33; __cs_simulate = 2;}
                                                            while ((__cs_simulate == 0 && __cs_pc_3 <= 33) || ((__cs_simulate == 1) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1)))
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
                                                            __end_clear_bit_loop_0_clear_bit_3:;
                                                            __begin_clear_bit_loop_1_clear_bit_3:;
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 34) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 34; __cs_simulate = 2;}
                                                            while ((__cs_simulate == 0 && __cs_pc_3 <= 34) || ((__cs_simulate == 1) && (0)))
                                                            {
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                __cs_l_clear_bit_v = 0;
                                                                        }
                                                            }
                                                            __end_clear_bit_loop_1_clear_bit_3:;
                                                            __exit__clear_bit_3:;
                                                        }
                                                        if (__cs_simulate == 0 && __cs_pc_3 == 35) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 35; __cs_simulate = 2;} else                                                        {
                                                                tco_expect_close = 0;
                                                        }
                                                        __exit__i8xx_tco_release_3:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_3 == 36) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 36; __cs_simulate = 2;} else                                                    {
                                                            cnt3++;
                                                    }
                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 37))
                                                    {
                                                        __cs_pc_3 = 37;
                                                        __cs_simulate = 2;
                                                    }
                                                }
/* Simulate writer1_isr_4 */
void writer1_isr_4()
                                                {
                                                    {
                                                        static int __cs_l_i8xx_tco_write_len;
                                                        if (__cs_simulate == 0 && __cs_pc_4 == 0) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 0; __cs_simulate = 2;} else                                                        {
                                                                __cs_l_i8xx_tco_write_len = 0;
                                                        }
                                                        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = 0;
                                                        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_4:;
                                                        if (__cs_simulate == 0 && __cs_pc_4 == 1) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 1; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 14) || ((__cs_simulate == 1) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_4 == 2) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 2; __cs_simulate = 2;}
                                                                    if ((__cs_simulate == 0 && __cs_pc_4 <= 6) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                                                                    {
                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 3) __cs_simulate = 1;
                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 3; __cs_simulate = 2;}
                                                                                if ((__cs_simulate == 0 && __cs_pc_4 <= 6) || (__cs_simulate == 1 && (!nowayout)))
                                                                                {
                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 4) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1)
                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 4; __cs_simulate = 2;} else                                                                                            {
                                                                                                    tco_expect_close = 0;
                                                                                            }
                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 5) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 5; __cs_simulate = 2;}
                                                                                            if ((__cs_simulate == 0 && __cs_pc_4 <= 6) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                            {
                                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 6) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 6; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                tco_expect_close = 42;
                                                                                                        }
                                                                                            }
                                                                                }
                                                                    }
                                                                    {
                                                                        static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                        __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_7:;
                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 7) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 7; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 10) || ((__cs_simulate == 1) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 8) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 8; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_13:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 9) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 9; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 9) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_13:;
                                                                                        __begin_outb_loop_1_outb_13:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 10) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 10; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 10) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_13:;
                                                                                        __exit__outb_13:;
                                                                                    }
                                                                                    if (__cs_simulate == 1)
                                                                                    {
                                                                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_7:;
                                                                        __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_7:;
                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 11) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 11; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 14) || ((__cs_simulate == 1) && (0)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 12) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 12; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_14:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 13) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 13; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 13) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_14:;
                                                                                        __begin_outb_loop_1_outb_14:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 14) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 14; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 14) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_14:;
                                                                                        __exit__outb_14:;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_7:;
                                                                        __exit__tco_timer_keepalive_7:;
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
                                                                    }
                                                        }
                                                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_4:;
                                                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_4:;
                                                        if (__cs_simulate == 0 && __cs_pc_4 == 15) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 15; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 28) || ((__cs_simulate == 1) && (0)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_4 == 16) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 16; __cs_simulate = 2;}
                                                                    if ((__cs_simulate == 0 && __cs_pc_4 <= 20) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                                                                    {
                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 17) __cs_simulate = 1;
                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 17; __cs_simulate = 2;}
                                                                                if ((__cs_simulate == 0 && __cs_pc_4 <= 20) || (__cs_simulate == 1 && (!nowayout)))
                                                                                {
                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 18) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1)
                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 18; __cs_simulate = 2;} else                                                                                            {
                                                                                                    tco_expect_close = 0;
                                                                                            }
                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 19) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 19; __cs_simulate = 2;}
                                                                                            if ((__cs_simulate == 0 && __cs_pc_4 <= 20) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                            {
                                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 20) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 20; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                tco_expect_close = 42;
                                                                                                        }
                                                                                            }
                                                                                }
                                                                    }
                                                                    {
                                                                        static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                        __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_8:;
                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 21) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 21; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 24) || ((__cs_simulate == 1) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 22) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 22; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_15:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 23) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 23; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 23) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_15:;
                                                                                        __begin_outb_loop_1_outb_15:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 24) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 24; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 24) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_15:;
                                                                                        __exit__outb_15:;
                                                                                    }
                                                                                    if (__cs_simulate == 1)
                                                                                    {
                                                                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_8:;
                                                                        __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_8:;
                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 25) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 25; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 28) || ((__cs_simulate == 1) && (0)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 26) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 26; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_16:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 27) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 27; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 27) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_16:;
                                                                                        __begin_outb_loop_1_outb_16:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 28) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 28; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 28) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_16:;
                                                                                        __exit__outb_16:;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_8:;
                                                                        __exit__tco_timer_keepalive_8:;
                                                                    }
                                                        }
                                                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_4:;
                                                        __exit__i8xx_tco_write_4:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_4 == 29) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 29; __cs_simulate = 2;} else                                                    {
                                                            cnt4++;
                                                    }
                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 30))
                                                    {
                                                        __cs_pc_4 = 30;
                                                        __cs_simulate = 2;
                                                    }
                                                }
/* Simulate closer2_isr_2 */
void closer2_isr_2()
                                                {
                                                    if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else                                                    {
                                                            tco_write_buf = 'V';
                                                    }
                                                    {
                                                        static int __cs_l_i8xx_tco_write_len;
                                                        if (__cs_simulate == 1)
                                                        {
                                                                __cs_l_i8xx_tco_write_len = 1;
                                                        }
                                                        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = 0;
                                                        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_2:;
                                                        if (__cs_simulate == 0 && __cs_pc_2 == 1) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 1; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 14) || ((__cs_simulate == 1) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_2 == 2) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 2; __cs_simulate = 2;}
                                                                    if ((__cs_simulate == 0 && __cs_pc_2 <= 6) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                                                                    {
                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 3) __cs_simulate = 1;
                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 3; __cs_simulate = 2;}
                                                                                if ((__cs_simulate == 0 && __cs_pc_2 <= 6) || (__cs_simulate == 1 && (!nowayout)))
                                                                                {
                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 4) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1)
                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 4; __cs_simulate = 2;} else                                                                                            {
                                                                                                    tco_expect_close = 0;
                                                                                            }
                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 5) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 5; __cs_simulate = 2;}
                                                                                            if ((__cs_simulate == 0 && __cs_pc_2 <= 6) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                            {
                                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 6) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 6; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                tco_expect_close = 42;
                                                                                                        }
                                                                                            }
                                                                                }
                                                                    }
                                                                    {
                                                                        static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                        __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_3:;
                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 7) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 7; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 10) || ((__cs_simulate == 1) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 8) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 8; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_5:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 9) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 9; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 9) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_5:;
                                                                                        __begin_outb_loop_1_outb_5:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 10) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 10; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 10) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_5:;
                                                                                        __exit__outb_5:;
                                                                                    }
                                                                                    if (__cs_simulate == 1)
                                                                                    {
                                                                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_3:;
                                                                        __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_3:;
                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 11) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 11; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 14) || ((__cs_simulate == 1) && (0)))
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
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 12; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_6:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 13) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 13; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 13) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_6:;
                                                                                        __begin_outb_loop_1_outb_6:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 14) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 14; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 14) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_6:;
                                                                                        __exit__outb_6:;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_3:;
                                                                        __exit__tco_timer_keepalive_3:;
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
                                                                    }
                                                        }
                                                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_2:;
                                                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_2:;
                                                        if (__cs_simulate == 0 && __cs_pc_2 == 15) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 15; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 28) || ((__cs_simulate == 1) && (0)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_2 == 16) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 16; __cs_simulate = 2;}
                                                                    if ((__cs_simulate == 0 && __cs_pc_2 <= 20) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                                                                    {
                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 17) __cs_simulate = 1;
                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 17; __cs_simulate = 2;}
                                                                                if ((__cs_simulate == 0 && __cs_pc_2 <= 20) || (__cs_simulate == 1 && (!nowayout)))
                                                                                {
                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 18) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1)
                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 18; __cs_simulate = 2;} else                                                                                            {
                                                                                                    tco_expect_close = 0;
                                                                                            }
                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 19) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 19; __cs_simulate = 2;}
                                                                                            if ((__cs_simulate == 0 && __cs_pc_2 <= 20) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                            {
                                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 20) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 20; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                tco_expect_close = 42;
                                                                                                        }
                                                                                            }
                                                                                }
                                                                    }
                                                                    {
                                                                        static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                        __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_4:;
                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 21) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 21; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 24) || ((__cs_simulate == 1) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 22) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 22; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_7:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 23) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 23; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 23) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_7:;
                                                                                        __begin_outb_loop_1_outb_7:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 24) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 24; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 24) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_7:;
                                                                                        __exit__outb_7:;
                                                                                    }
                                                                                    if (__cs_simulate == 1)
                                                                                    {
                                                                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_4:;
                                                                        __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_4:;
                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 25) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 25; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 28) || ((__cs_simulate == 1) && (0)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 26) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 26; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_8:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 27) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 27; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 27) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_8:;
                                                                                        __begin_outb_loop_1_outb_8:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 28) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 28; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 28) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_8:;
                                                                                        __exit__outb_8:;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_4:;
                                                                        __exit__tco_timer_keepalive_4:;
                                                                    }
                                                        }
                                                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_2:;
                                                        __exit__i8xx_tco_write_2:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_2 == 29) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 29; __cs_simulate = 2;} else                                                    {
                                                            tco_expect_close = 42;
                                                    }
                                                    {
                                                        if (__cs_simulate == 0 && __cs_pc_2 == 30) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 30; __cs_simulate = 2;}
                                                        if ((__cs_simulate == 0 && __cs_pc_2 <= 31) || (__cs_simulate == 1 && (tco_expect_close != 42)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_2 == 31) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 31; __cs_simulate = 2;} else                                                                    {
                                                                            assert(0);
                                                                    }
                                                        }
                                                        {
                                                            static int __cs_l_clear_bit_unused;
                                                            if (__cs_simulate == 1)
                                                            {
                                                                    __cs_l_clear_bit_unused = 0;
                                                            }
                                                            static int __cs_l_clear_bit_v;
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 32) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 32; __cs_simulate = 2;} else                                                            {
                                                                    __cs_l_clear_bit_v = timer_alive;
                                                            }
                                                            static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                                                            __begin_clear_bit_loop_0_clear_bit_2:;
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 33) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 33; __cs_simulate = 2;}
                                                            while ((__cs_simulate == 0 && __cs_pc_2 <= 33) || ((__cs_simulate == 1) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1)))
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
                                                            __end_clear_bit_loop_0_clear_bit_2:;
                                                            __begin_clear_bit_loop_1_clear_bit_2:;
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 34) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 34; __cs_simulate = 2;}
                                                            while ((__cs_simulate == 0 && __cs_pc_2 <= 34) || ((__cs_simulate == 1) && (0)))
                                                            {
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                __cs_l_clear_bit_v = 0;
                                                                        }
                                                            }
                                                            __end_clear_bit_loop_1_clear_bit_2:;
                                                            __exit__clear_bit_2:;
                                                        }
                                                        if (__cs_simulate == 0 && __cs_pc_2 == 35) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 35; __cs_simulate = 2;} else                                                        {
                                                                tco_expect_close = 0;
                                                        }
                                                        __exit__i8xx_tco_release_2:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_2 == 36) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 36; __cs_simulate = 2;} else                                                    {
                                                            cnt2++;
                                                    }
                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 37))
                                                    {
                                                        __cs_pc_2 = 37;
                                                        __cs_simulate = 2;
                                                    }
                                                }
/* Simulate writer2_isr_5 */
void writer2_isr_5()
                                                {
                                                    {
                                                        static int __cs_l_i8xx_tco_write_len;
                                                        if (__cs_simulate == 0 && __cs_pc_5 == 0) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 0; __cs_simulate = 2;} else                                                        {
                                                                __cs_l_i8xx_tco_write_len = 0;
                                                        }
                                                        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = 0;
                                                        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_5:;
                                                        if (__cs_simulate == 0 && __cs_pc_5 == 1) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 1; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 14) || ((__cs_simulate == 1) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 2) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 2; __cs_simulate = 2;}
                                                                    if ((__cs_simulate == 0 && __cs_pc_5 <= 6) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                                                                    {
                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 3) __cs_simulate = 1;
                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 3; __cs_simulate = 2;}
                                                                                if ((__cs_simulate == 0 && __cs_pc_5 <= 6) || (__cs_simulate == 1 && (!nowayout)))
                                                                                {
                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 4) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1)
                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 4; __cs_simulate = 2;} else                                                                                            {
                                                                                                    tco_expect_close = 0;
                                                                                            }
                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 5) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 5; __cs_simulate = 2;}
                                                                                            if ((__cs_simulate == 0 && __cs_pc_5 <= 6) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                            {
                                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 6) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 6; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                tco_expect_close = 42;
                                                                                                        }
                                                                                            }
                                                                                }
                                                                    }
                                                                    {
                                                                        static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                        __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_9:;
                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 7) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 7; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 10) || ((__cs_simulate == 1) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 8) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 8; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_17:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 9) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 9; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 9) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_17:;
                                                                                        __begin_outb_loop_1_outb_17:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 10) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 10; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 10) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_17:;
                                                                                        __exit__outb_17:;
                                                                                    }
                                                                                    if (__cs_simulate == 1)
                                                                                    {
                                                                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_9:;
                                                                        __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_9:;
                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 11) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 11; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 14) || ((__cs_simulate == 1) && (0)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 12) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 12; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_18:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 13) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 13; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 13) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_18:;
                                                                                        __begin_outb_loop_1_outb_18:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 14) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 14; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 14) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_18:;
                                                                                        __exit__outb_18:;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_9:;
                                                                        __exit__tco_timer_keepalive_9:;
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
                                                                    }
                                                        }
                                                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_5:;
                                                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_5:;
                                                        if (__cs_simulate == 0 && __cs_pc_5 == 15) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 15; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 28) || ((__cs_simulate == 1) && (0)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 16) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 16; __cs_simulate = 2;}
                                                                    if ((__cs_simulate == 0 && __cs_pc_5 <= 20) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                                                                    {
                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 17) __cs_simulate = 1;
                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 17; __cs_simulate = 2;}
                                                                                if ((__cs_simulate == 0 && __cs_pc_5 <= 20) || (__cs_simulate == 1 && (!nowayout)))
                                                                                {
                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 18) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1)
                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 18; __cs_simulate = 2;} else                                                                                            {
                                                                                                    tco_expect_close = 0;
                                                                                            }
                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 19) __cs_simulate = 1;
                                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 19; __cs_simulate = 2;}
                                                                                            if ((__cs_simulate == 0 && __cs_pc_5 <= 20) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                            {
                                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 20) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 20; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                tco_expect_close = 42;
                                                                                                        }
                                                                                            }
                                                                                }
                                                                    }
                                                                    {
                                                                        static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                        __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_10:;
                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 21) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 21; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 24) || ((__cs_simulate == 1) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 22) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 22; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_19:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 23) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 23; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 23) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_19:;
                                                                                        __begin_outb_loop_1_outb_19:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 24) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 24; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 24) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_19:;
                                                                                        __exit__outb_19:;
                                                                                    }
                                                                                    if (__cs_simulate == 1)
                                                                                    {
                                                                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_10:;
                                                                        __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_10:;
                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 25) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 25; __cs_simulate = 2;}
                                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 28) || ((__cs_simulate == 1) && (0)))
                                                                        {
                                                                                    {
                                                                                        static int __cs_l_outb_v;
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_outb_v = 0x01;
                                                                                        }
                                                                                        static int __cs_l_outb_l;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 26) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 26; __cs_simulate = 2;} else                                                                                        {
                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                        }
                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                        __begin_outb_loop_0_outb_20:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 27) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 27; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 27) || ((__cs_simulate == 1) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)))
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
                                                                                        __end_outb_loop_0_outb_20:;
                                                                                        __begin_outb_loop_1_outb_20:;
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 28) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 28; __cs_simulate = 2;}
                                                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 28) || ((__cs_simulate == 1) && (0)))
                                                                                        {
                                                                                                    if (__cs_simulate == 1)
                                                                                                    {
                                                                                                            __cs_l_outb_l = __cs_l_outb_v;
                                                                                                    }
                                                                                        }
                                                                                        __end_outb_loop_1_outb_20:;
                                                                                        __exit__outb_20:;
                                                                                    }
                                                                        }
                                                                        __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_10:;
                                                                        __exit__tco_timer_keepalive_10:;
                                                                    }
                                                        }
                                                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_5:;
                                                        __exit__i8xx_tco_write_5:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_5 == 29) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 29; __cs_simulate = 2;} else                                                    {
                                                            cnt5++;
                                                    }
                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_5 == 30))
                                                    {
                                                        __cs_pc_5 = 30;
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
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 37)&&(__cs_pc_3 == 0 || __cs_pc_3 == 37)&&(__cs_pc_4 == 0 || __cs_pc_4 == 30)&&(__cs_pc_2 == 0 || __cs_pc_2 == 37)&&(__cs_pc_5 == 0 || __cs_pc_5 == 30)&&__cs_disable_isr_0 != 1) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 37)&&(__cs_pc_4 == 0 || __cs_pc_4 == 30)&&(__cs_pc_2 == 0 || __cs_pc_2 == 37)&&(__cs_pc_5 == 0 || __cs_pc_5 == 30)&&__cs_disable_isr_1 != 1) closer1_isr_1();
    __cs_simulate = 0;
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 37)&&(__cs_pc_3 == 0 || __cs_pc_3 == 37)&&(__cs_pc_4 == 0 || __cs_pc_4 == 30)&&(__cs_pc_5 == 0 || __cs_pc_5 == 30)&&__cs_disable_isr_2 != 1) closer2_isr_2();
    __cs_simulate = 0;
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 37)&&(__cs_pc_4 == 0 || __cs_pc_4 == 30)&&(__cs_pc_2 == 0 || __cs_pc_2 == 37)&&(__cs_pc_5 == 0 || __cs_pc_5 == 30)&&__cs_disable_isr_3 != 1) closer3_isr_3();
    __cs_simulate = 0;
    if ((__cs_pc_5 == 0 || __cs_pc_5 == 30)&&__cs_disable_isr_4 != 1) writer1_isr_4();
    __cs_simulate = 0;
    if (__cs_disable_isr_5 != 1) writer2_isr_5();
    __cs_simulate = 0;
    if (__cs_disable_isr_6 != 1) writer3_isr_6();
  }
}
