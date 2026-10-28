// Main task
unsigned int __cs_pc_4;
// closer2_isr_1
unsigned int __cs_pc_1;
// closer1_isr_2
unsigned int __cs_pc_2;
// writer1_isr_3
unsigned int __cs_pc_3;
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
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else {
                    tco_write_buf = 'V';
                        static int __cs_l_i8xx_tco_write_len;
                        __cs_l_i8xx_tco_write_len = 1;
                        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = 0;
                        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_1:
;
                        ;;
                        int loop_1_IOVar1;
                        int loop_1_block_3;
                        int t_1 = 0;
                    while ((t_1 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1)){
                            loop_1_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_6;
                            loop_1_block_3 = nondet_int();
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = loop_1_IOVar1 + (1 * loop_1_block_3);
                    __CPROVER_assume(loop_1_block_3 >= 0);
                    __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1);
                                                        if (__cs_l_i8xx_tco_write_len)
                                                                                    if (!nowayout)
                                        tco_expect_close = 0;
                                                                                                                if (tco_write_buf == 'V')
                                            tco_expect_close = 42;
                                    static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                    __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_1:
;
                                    ;;
                                    int loop_2_IOVar1;
                                    int loop_2_block_2;
                                    int t_2 = 0;
                                while ((t_2 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)){
                                        loop_2_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                        loop_2_block_2 = nondet_int();
                                        __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_2_IOVar1 + (1 * loop_2_block_2);
                                                        __CPROVER_assume(loop_2_block_2 >= 0);
                                                        __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_1:
;
                                                ;;
                                                int loop_3_IOVar1;
                                                int loop_3_block_1;
                                                int t_3 = 0;
                                            while ((t_3 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_3_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_3_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_3_IOVar1 + (1 * loop_3_block_1);
                                                                    __CPROVER_assume(loop_3_block_1 >= 0);
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_3++;
                                                                __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_1:
;
                                                ;;
                                                __begin_outb_loop_1_outb_1:
;
                                                ;;
                                                int t_4 = 0;
                                            while ((t_4 < 1) && 0){
                                                                    __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_4++;
                                                                __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_1:
;
                                                ;;
                                                __exit__outb_1:
;
                                                ;;
                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                        t_2++;
                                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                }
                                    __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_1:
;
                                    ;;
                                    __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_1:
;
                                    ;;
                                    int t_5 = 0;
                                while ((t_5 < 2) && 0){
                                                        __CPROVER_assume(0);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_2:
;
                                                ;;
                                                int loop_6_IOVar1;
                                                int loop_6_block_1;
                                                int t_6 = 0;
                                            while ((t_6 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_6_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_6_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_6_IOVar1 + (1 * loop_6_block_1);
                                                                    __CPROVER_assume(loop_6_block_1 >= 0);
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_6++;
                                                                __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_2:
;
                                                ;;
                                                __begin_outb_loop_1_outb_2:
;
                                                ;;
                                                int t_7 = 0;
                                            while ((t_7 < 1) && 0){
                                                                    __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_7++;
                                                                __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_2:
;
                                                ;;
                                                __exit__outb_2:
;
                                                ;;
                                        t_5++;
                                                    __CPROVER_assume(!0);
                                }
                                    __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_1:
;
                                    ;;
                                    __exit__tco_timer_keepalive_1:
;
                                    ;;
                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
                            t_1++;
                                        __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1));
                    }
                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_1:
;
                        ;;
                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_1:
;
                        ;;
                        int t_8 = 0;
                    while ((t_8 < 1) && 0){
                                            __CPROVER_assume(0);
                                                                                                        if (__cs_l_i8xx_tco_write_len)
                                                                                                                                    if (!nowayout)
                                        tco_expect_close = 0;
                                                                                                                                                                if (tco_write_buf == 'V')
                                            tco_expect_close = 42;
                                    static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                    __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_2:
;
                                    ;;
                                    int loop_9_IOVar1;
                                    int loop_9_block_2;
                                    int t_9 = 0;
                                while ((t_9 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)){
                                        loop_9_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                        loop_9_block_2 = nondet_int();
                                        __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_9_IOVar1 + (1 * loop_9_block_2);
                                                                                __CPROVER_assume(loop_9_block_2 >= 0);
                                                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_3:
;
                                                ;;
                                                int loop_10_IOVar1;
                                                int loop_10_block_1;
                                                int t_10 = 0;
                                            while ((t_10 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_10_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_10_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_10_IOVar1 + (1 * loop_10_block_1);
                                                                                            __CPROVER_assume(loop_10_block_1 >= 0);
                                                                                            __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_10++;
                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_3:
;
                                                ;;
                                                __begin_outb_loop_1_outb_3:
;
                                                ;;
                                                int t_11 = 0;
                                            while ((t_11 < 1) && 0){
                                                                                            __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_11++;
                                                                                        __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_3:
;
                                                ;;
                                                __exit__outb_3:
;
                                                ;;
                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                        t_9++;
                                                                            __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                }
                                    __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_2:
;
                                    ;;
                                    __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_2:
;
                                    ;;
                                    int t_12 = 0;
                                while ((t_12 < 2) && 0){
                                                                                __CPROVER_assume(0);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_4:
;
                                                ;;
                                                int loop_13_IOVar1;
                                                int loop_13_block_1;
                                                int t_13 = 0;
                                            while ((t_13 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_13_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_13_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_13_IOVar1 + (1 * loop_13_block_1);
                                                                                            __CPROVER_assume(loop_13_block_1 >= 0);
                                                                                            __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_13++;
                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_4:
;
                                                ;;
                                                __begin_outb_loop_1_outb_4:
;
                                                ;;
                                                int t_14 = 0;
                                            while ((t_14 < 1) && 0){
                                                                                            __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_14++;
                                                                                        __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_4:
;
                                                ;;
                                                __exit__outb_4:
;
                                                ;;
                                        t_12++;
                                                                            __CPROVER_assume(!0);
                                }
                                    __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_2:
;
                                    ;;
                                    __exit__tco_timer_keepalive_2:
;
                                    ;;
                            t_8++;
                                                                __CPROVER_assume(!0);
                    }
                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_1:
;
                        ;;
                        __exit__i8xx_tco_write_1:
;
                        ;;
                    tco_expect_close = 42;
                                                                                                                                if (tco_expect_close != 42)
                                                                            if (!(0)) __cseq_error();
                            static int __cs_l_clear_bit_unused;
                            __cs_l_clear_bit_unused = 0;
                            static int __cs_l_clear_bit_v;
                            __cs_l_clear_bit_v = timer_alive;
                            static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                            __begin_clear_bit_loop_0_clear_bit_1:
;
                            ;;
                            int loop_15_IOVar1;
                            int loop_15_block_1;
                            int t_15 = 0;
                        while ((t_15 < 2) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1)){
                                loop_15_IOVar1 = __cs_l_clear_bit___cs_dowhile_onetime_4;
                                loop_15_block_1 = nondet_int();
                                __cs_l_clear_bit___cs_dowhile_onetime_4 = loop_15_IOVar1 + (1 * loop_15_block_1);
                                                                                __CPROVER_assume(loop_15_block_1 >= 0);
                                                                                __CPROVER_assume(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1);
                                    __cs_l_clear_bit_v = 0;
                                    __cs_l_clear_bit___cs_dowhile_onetime_4++;
                                t_15++;
                                                                            __CPROVER_assume(!(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1));
                        }
                            __end_clear_bit_loop_0_clear_bit_1:
;
                            ;;
                            __begin_clear_bit_loop_1_clear_bit_1:
;
                            ;;
                            int t_16 = 0;
                        while ((t_16 < 1) && 0){
                                                                                __CPROVER_assume(0);
                                    __cs_l_clear_bit_v = 0;
                                t_16++;
                                                                            __CPROVER_assume(!0);
                        }
                            __end_clear_bit_loop_1_clear_bit_1:
;
                            ;;
                            __exit__clear_bit_1:
;
                            ;;
                        tco_expect_close = 0;
                        __exit__i8xx_tco_release_1:
;
                        ;;
                    cnt1++;
        }
                                                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 77))
                                                            {
                                                                __cs_pc_1 = 77;
                                                                __cs_simulate = 2;
                                                            }
}
/* Simulate original main */
int main_task()
                                                        {
                                                            if (__cs_simulate == 0 && __cs_pc_4 == 0) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 0; __cs_simulate = 2;} else                                                            {
                                                                    tco_expect_close = 0;
                                                            }
                                                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 1))
                                                            {
                                                                __cs_pc_4 = 1;
                                                                __cs_simulate = 2;
                                                            }
                                                        }
/* Simulate writer1_isr_3 */
void writer1_isr_3()
                                                        {
                                                            {
                                                                static int __cs_l_i8xx_tco_write_len;
                                                                if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
                                                                if (__cs_simulate == 1)
                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else                                                                {
                                                                        __cs_l_i8xx_tco_write_len = 0;
                                                                }
                                                                static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = 0;
                                                                __begin_i8xx_tco_write_loop_0_i8xx_tco_write_3:;
                                                                int loop_33_IOVar1;
                                                                int loop_33_block_3;
                                                                int t_33 = 0;
                                                                if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;}
                                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 31) || ((__cs_simulate == 1) && ((t_33 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1))))
                                                                {
                                                                            if (__cs_simulate == 1)
                                                                            {
                                                                                    loop_33_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_6;
                                                                            }
                                                                            if (__cs_simulate == 1)
                                                                            {
                                                                                    loop_33_block_3 = nondet_int();
                                                                            }
                                                                            if (__cs_simulate == 1)
                                                                            {
                                                                                    __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = loop_33_IOVar1 + (1 * loop_33_block_3);
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_3 == 2) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 2; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(loop_33_block_3 >= 0);
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_3 == 3) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 3; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1);
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
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 6; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                tco_expect_close = 0;
                                                                                                        }
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 7) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 7; __cs_simulate = 2;}
                                                                                                        if ((__cs_simulate == 0 && __cs_pc_3 <= 8) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                                        {
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 8) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 8; __cs_simulate = 2;} else                                                                                                                    {
                                                                                                                            tco_expect_close = 42;
                                                                                                                    }
                                                                                                        }
                                                                                            }
                                                                                }
                                                                                {
                                                                                    static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                                    __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_5:;
                                                                                    int loop_34_IOVar1;
                                                                                    int loop_34_block_2;
                                                                                    int t_34 = 0;
                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 9) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 9; __cs_simulate = 2;}
                                                                                    while ((__cs_simulate == 0 && __cs_pc_3 <= 19) || ((__cs_simulate == 1) && ((t_34 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1))))
                                                                                    {
                                                                                                if (__cs_simulate == 1)
                                                                                                {
                                                                                                        loop_34_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                                                                                }
                                                                                                if (__cs_simulate == 1)
                                                                                                {
                                                                                                        loop_34_block_2 = nondet_int();
                                                                                                }
                                                                                                if (__cs_simulate == 1)
                                                                                                {
                                                                                                        __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_34_IOVar1 + (1 * loop_34_block_2);
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_3 == 10) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 10; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(loop_34_block_2 >= 0);
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_3 == 11) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 11; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 12; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                                        }
                                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                        __begin_outb_loop_0_outb_9:;
                                                                                                        int loop_35_IOVar1;
                                                                                                        int loop_35_block_1;
                                                                                                        int t_35 = 0;
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 13) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 13; __cs_simulate = 2;}
                                                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 15) || ((__cs_simulate == 1) && ((t_35 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                        {
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    {
                                                                                                                            loop_35_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    {
                                                                                                                            loop_35_block_1 = nondet_int();
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    {
                                                                                                                            __cs_l_outb___cs_dowhile_onetime_3 = loop_35_IOVar1 + (1 * loop_35_block_1);
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 14) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 14; __cs_simulate = 2;} else                                                                                                                    {
                                                                                                                            __CPROVER_assume(loop_35_block_1 >= 0);
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 15) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 15; __cs_simulate = 2;} else                                                                                                                    {
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
                                                                                                                            t_35++;
                                                                                                                    }
                                                                                                        }
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 16) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 16; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                        }
                                                                                                        __end_outb_loop_0_outb_9:;
                                                                                                        __begin_outb_loop_1_outb_9:;
                                                                                                        int t_36 = 0;
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 17) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 17; __cs_simulate = 2;}
                                                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 18) || ((__cs_simulate == 1) && ((t_36 < 1) && 0)))
                                                                                                        {
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 18) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 18; __cs_simulate = 2;} else                                                                                                                    {
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
                                                                                                                            t_36++;
                                                                                                                    }
                                                                                                        }
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 19) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 19; __cs_simulate = 2;} else                                                                                                        {
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
                                                                                                        t_34++;
                                                                                                }
                                                                                    }
                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 20) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1)
                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 20; __cs_simulate = 2;} else                                                                                    {
                                                                                            __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                                                                    }
                                                                                    __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_5:;
                                                                                    __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_5:;
                                                                                    int t_37 = 0;
                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 21) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 21; __cs_simulate = 2;}
                                                                                    while ((__cs_simulate == 0 && __cs_pc_3 <= 30) || ((__cs_simulate == 1) && ((t_37 < 2) && 0)))
                                                                                    {
                                                                                                if (__cs_simulate == 0 && __cs_pc_3 == 22) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 22; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 23; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                                        }
                                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                        __begin_outb_loop_0_outb_10:;
                                                                                                        int loop_38_IOVar1;
                                                                                                        int loop_38_block_1;
                                                                                                        int t_38 = 0;
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 24) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 24; __cs_simulate = 2;}
                                                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 26) || ((__cs_simulate == 1) && ((t_38 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                        {
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    {
                                                                                                                            loop_38_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    {
                                                                                                                            loop_38_block_1 = nondet_int();
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    {
                                                                                                                            __cs_l_outb___cs_dowhile_onetime_3 = loop_38_IOVar1 + (1 * loop_38_block_1);
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 25) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 25; __cs_simulate = 2;} else                                                                                                                    {
                                                                                                                            __CPROVER_assume(loop_38_block_1 >= 0);
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 26) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 26; __cs_simulate = 2;} else                                                                                                                    {
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
                                                                                                                            t_38++;
                                                                                                                    }
                                                                                                        }
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 27) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 27; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                        }
                                                                                                        __end_outb_loop_0_outb_10:;
                                                                                                        __begin_outb_loop_1_outb_10:;
                                                                                                        int t_39 = 0;
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 28) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 28; __cs_simulate = 2;}
                                                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 29) || ((__cs_simulate == 1) && ((t_39 < 1) && 0)))
                                                                                                        {
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 29) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 29; __cs_simulate = 2;} else                                                                                                                    {
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
                                                                                                                            t_39++;
                                                                                                                    }
                                                                                                        }
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 30) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 30; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                __CPROVER_assume(!0);
                                                                                                        }
                                                                                                        __end_outb_loop_1_outb_10:;
                                                                                                        __exit__outb_10:;
                                                                                                    }
                                                                                                }
                                                                                                if (__cs_simulate == 1)
                                                                                                {
                                                                                                        t_37++;
                                                                                                }
                                                                                    }
                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 31) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1)
                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 31; __cs_simulate = 2;} else                                                                                    {
                                                                                            __CPROVER_assume(!0);
                                                                                    }
                                                                                    __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_5:;
                                                                                    __exit__tco_timer_keepalive_5:;
                                                                                }
                                                                                if (__cs_simulate == 1)
                                                                                {
                                                                                        __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
                                                                                }
                                                                            }
                                                                            if (__cs_simulate == 1)
                                                                            {
                                                                                    t_33++;
                                                                            }
                                                                }
                                                                if (__cs_simulate == 0 && __cs_pc_3 == 32) __cs_simulate = 1;
                                                                if (__cs_simulate == 1)
                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 32; __cs_simulate = 2;} else                                                                {
                                                                        __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1));
                                                                }
                                                                __end_i8xx_tco_write_loop_0_i8xx_tco_write_3:;
                                                                __begin_i8xx_tco_write_loop_1_i8xx_tco_write_3:;
                                                                int t_40 = 0;
                                                                if (__cs_simulate == 0 && __cs_pc_3 == 33) __cs_simulate = 1;
                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 33; __cs_simulate = 2;}
                                                                while ((__cs_simulate == 0 && __cs_pc_3 <= 62) || ((__cs_simulate == 1) && ((t_40 < 1) && 0)))
                                                                {
                                                                            if (__cs_simulate == 0 && __cs_pc_3 == 34) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 34; __cs_simulate = 2;} else                                                                            {
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
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 37; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                tco_expect_close = 0;
                                                                                                        }
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 38) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 38; __cs_simulate = 2;}
                                                                                                        if ((__cs_simulate == 0 && __cs_pc_3 <= 39) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                                        {
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 39) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 39; __cs_simulate = 2;} else                                                                                                                    {
                                                                                                                            tco_expect_close = 42;
                                                                                                                    }
                                                                                                        }
                                                                                            }
                                                                                }
                                                                                {
                                                                                    static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                                    __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_6:;
                                                                                    int loop_41_IOVar1;
                                                                                    int loop_41_block_2;
                                                                                    int t_41 = 0;
                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 40) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 40; __cs_simulate = 2;}
                                                                                    while ((__cs_simulate == 0 && __cs_pc_3 <= 50) || ((__cs_simulate == 1) && ((t_41 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1))))
                                                                                    {
                                                                                                if (__cs_simulate == 1)
                                                                                                {
                                                                                                        loop_41_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                                                                                }
                                                                                                if (__cs_simulate == 1)
                                                                                                {
                                                                                                        loop_41_block_2 = nondet_int();
                                                                                                }
                                                                                                if (__cs_simulate == 1)
                                                                                                {
                                                                                                        __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_41_IOVar1 + (1 * loop_41_block_2);
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_3 == 41) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 41; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(loop_41_block_2 >= 0);
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_3 == 42) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 42; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 43; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                                        }
                                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                        __begin_outb_loop_0_outb_11:;
                                                                                                        int loop_42_IOVar1;
                                                                                                        int loop_42_block_1;
                                                                                                        int t_42 = 0;
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 44) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 44; __cs_simulate = 2;}
                                                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 46) || ((__cs_simulate == 1) && ((t_42 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                        {
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    {
                                                                                                                            loop_42_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    {
                                                                                                                            loop_42_block_1 = nondet_int();
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    {
                                                                                                                            __cs_l_outb___cs_dowhile_onetime_3 = loop_42_IOVar1 + (1 * loop_42_block_1);
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 45) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 45; __cs_simulate = 2;} else                                                                                                                    {
                                                                                                                            __CPROVER_assume(loop_42_block_1 >= 0);
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 46) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 46; __cs_simulate = 2;} else                                                                                                                    {
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
                                                                                                                            t_42++;
                                                                                                                    }
                                                                                                        }
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 47) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 47; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                        }
                                                                                                        __end_outb_loop_0_outb_11:;
                                                                                                        __begin_outb_loop_1_outb_11:;
                                                                                                        int t_43 = 0;
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 48) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 48; __cs_simulate = 2;}
                                                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 49) || ((__cs_simulate == 1) && ((t_43 < 1) && 0)))
                                                                                                        {
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 49) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 49; __cs_simulate = 2;} else                                                                                                                    {
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
                                                                                                                            t_43++;
                                                                                                                    }
                                                                                                        }
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 50) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 50; __cs_simulate = 2;} else                                                                                                        {
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
                                                                                                        t_41++;
                                                                                                }
                                                                                    }
                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 51) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1)
                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 51; __cs_simulate = 2;} else                                                                                    {
                                                                                            __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                                                                    }
                                                                                    __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_6:;
                                                                                    __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_6:;
                                                                                    int t_44 = 0;
                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 52) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 52; __cs_simulate = 2;}
                                                                                    while ((__cs_simulate == 0 && __cs_pc_3 <= 61) || ((__cs_simulate == 1) && ((t_44 < 2) && 0)))
                                                                                    {
                                                                                                if (__cs_simulate == 0 && __cs_pc_3 == 53) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 53; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 54; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                __cs_l_outb_l = tco1_rld;
                                                                                                        }
                                                                                                        static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                        __begin_outb_loop_0_outb_12:;
                                                                                                        int loop_45_IOVar1;
                                                                                                        int loop_45_block_1;
                                                                                                        int t_45 = 0;
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 55) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 55; __cs_simulate = 2;}
                                                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 57) || ((__cs_simulate == 1) && ((t_45 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                        {
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    {
                                                                                                                            loop_45_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    {
                                                                                                                            loop_45_block_1 = nondet_int();
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    {
                                                                                                                            __cs_l_outb___cs_dowhile_onetime_3 = loop_45_IOVar1 + (1 * loop_45_block_1);
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 56) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 56; __cs_simulate = 2;} else                                                                                                                    {
                                                                                                                            __CPROVER_assume(loop_45_block_1 >= 0);
                                                                                                                    }
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 57) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 57; __cs_simulate = 2;} else                                                                                                                    {
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
                                                                                                                            t_45++;
                                                                                                                    }
                                                                                                        }
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 58) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 58; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                        }
                                                                                                        __end_outb_loop_0_outb_12:;
                                                                                                        __begin_outb_loop_1_outb_12:;
                                                                                                        int t_46 = 0;
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 59) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 59; __cs_simulate = 2;}
                                                                                                        while ((__cs_simulate == 0 && __cs_pc_3 <= 60) || ((__cs_simulate == 1) && ((t_46 < 1) && 0)))
                                                                                                        {
                                                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 60) __cs_simulate = 1;
                                                                                                                    if (__cs_simulate == 1)
                                                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 60; __cs_simulate = 2;} else                                                                                                                    {
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
                                                                                                                            t_46++;
                                                                                                                    }
                                                                                                        }
                                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 61) __cs_simulate = 1;
                                                                                                        if (__cs_simulate == 1)
                                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 61; __cs_simulate = 2;} else                                                                                                        {
                                                                                                                __CPROVER_assume(!0);
                                                                                                        }
                                                                                                        __end_outb_loop_1_outb_12:;
                                                                                                        __exit__outb_12:;
                                                                                                    }
                                                                                                }
                                                                                                if (__cs_simulate == 1)
                                                                                                {
                                                                                                        t_44++;
                                                                                                }
                                                                                    }
                                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 62) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1)
                                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 62; __cs_simulate = 2;} else                                                                                    {
                                                                                            __CPROVER_assume(!0);
                                                                                    }
                                                                                    __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_6:;
                                                                                    __exit__tco_timer_keepalive_6:;
                                                                                }
                                                                            }
                                                                            if (__cs_simulate == 1)
                                                                            {
                                                                                    t_40++;
                                                                            }
                                                                }
                                                                if (__cs_simulate == 0 && __cs_pc_3 == 63) __cs_simulate = 1;
                                                                if (__cs_simulate == 1)
                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 63; __cs_simulate = 2;} else                                                                {
                                                                        __CPROVER_assume(!0);
                                                                }
                                                                __end_i8xx_tco_write_loop_1_i8xx_tco_write_3:;
                                                                __exit__i8xx_tco_write_3:;
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 64) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 64; __cs_simulate = 2;} else                                                            {
                                                                    cnt3++;
                                                            }
                                                            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 65))
                                                            {
                                                                __cs_pc_3 = 65;
                                                                __cs_simulate = 2;
                                                            }
                                                        }
/* Simulate closer1_isr_2 */
void closer1_isr_2()
{
        if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else {
                    tco_write_buf = 'V';
                        static int __cs_l_i8xx_tco_write_len;
                        __cs_l_i8xx_tco_write_len = 1;
                        static int __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = 0;
                        __begin_i8xx_tco_write_loop_0_i8xx_tco_write_2:
;
                        ;;
                        int loop_17_IOVar1;
                        int loop_17_block_3;
                        int t_17 = 0;
                    while ((t_17 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1)){
                            loop_17_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_6;
                            loop_17_block_3 = nondet_int();
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = loop_17_IOVar1 + (1 * loop_17_block_3);
                                                                            __CPROVER_assume(loop_17_block_3 >= 0);
                                                                            __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1);
                                                                                                                                                                        if (__cs_l_i8xx_tco_write_len)
                                                                                                                                                                                                    if (!nowayout)
                                        tco_expect_close = 0;
                                                                                                                                                                                                                                if (tco_write_buf == 'V')
                                            tco_expect_close = 42;
                                    static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                    __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_3:
;
                                    ;;
                                    int loop_18_IOVar1;
                                    int loop_18_block_2;
                                    int t_18 = 0;
                                while ((t_18 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)){
                                        loop_18_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                        loop_18_block_2 = nondet_int();
                                        __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_18_IOVar1 + (1 * loop_18_block_2);
                                                                                                                __CPROVER_assume(loop_18_block_2 >= 0);
                                                                                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_5:
;
                                                ;;
                                                int loop_19_IOVar1;
                                                int loop_19_block_1;
                                                int t_19 = 0;
                                            while ((t_19 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_19_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_19_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_19_IOVar1 + (1 * loop_19_block_1);
                                                                                                                            __CPROVER_assume(loop_19_block_1 >= 0);
                                                                                                                            __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_19++;
                                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_5:
;
                                                ;;
                                                __begin_outb_loop_1_outb_5:
;
                                                ;;
                                                int t_20 = 0;
                                            while ((t_20 < 1) && 0){
                                                                                                                            __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_20++;
                                                                                                                        __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_5:
;
                                                ;;
                                                __exit__outb_5:
;
                                                ;;
                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                        t_18++;
                                                                                                            __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                }
                                    __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_3:
;
                                    ;;
                                    __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_3:
;
                                    ;;
                                    int t_21 = 0;
                                while ((t_21 < 2) && 0){
                                                                                                                __CPROVER_assume(0);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_6:
;
                                                ;;
                                                int loop_22_IOVar1;
                                                int loop_22_block_1;
                                                int t_22 = 0;
                                            while ((t_22 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_22_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_22_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_22_IOVar1 + (1 * loop_22_block_1);
                                                                                                                            __CPROVER_assume(loop_22_block_1 >= 0);
                                                                                                                            __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_22++;
                                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_6:
;
                                                ;;
                                                __begin_outb_loop_1_outb_6:
;
                                                ;;
                                                int t_23 = 0;
                                            while ((t_23 < 1) && 0){
                                                                                                                            __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_23++;
                                                                                                                        __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_6:
;
                                                ;;
                                                __exit__outb_6:
;
                                                ;;
                                        t_21++;
                                                                                                            __CPROVER_assume(!0);
                                }
                                    __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_3:
;
                                    ;;
                                    __exit__tco_timer_keepalive_3:
;
                                    ;;
                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
                            t_17++;
                                                                                                __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1));
                    }
                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_2:
;
                        ;;
                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_2:
;
                        ;;
                        int t_24 = 0;
                    while ((t_24 < 1) && 0){
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
                                    int loop_25_IOVar1;
                                    int loop_25_block_2;
                                    int t_25 = 0;
                                while ((t_25 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)){
                                        loop_25_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                        loop_25_block_2 = nondet_int();
                                        __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_25_IOVar1 + (1 * loop_25_block_2);
                                                                                                                                        __CPROVER_assume(loop_25_block_2 >= 0);
                                                                                                                                        __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_7:
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
                                                __end_outb_loop_0_outb_7:
;
                                                ;;
                                                __begin_outb_loop_1_outb_7:
;
                                                ;;
                                                int t_27 = 0;
                                            while ((t_27 < 1) && 0){
                                                                                                                                                    __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_27++;
                                                                                                                                                __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_7:
;
                                                ;;
                                                __exit__outb_7:
;
                                                ;;
                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                        t_25++;
                                                                                                                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                }
                                    __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_4:
;
                                    ;;
                                    __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_4:
;
                                    ;;
                                    int t_28 = 0;
                                while ((t_28 < 2) && 0){
                                                                                                                                        __CPROVER_assume(0);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_8:
;
                                                ;;
                                                int loop_29_IOVar1;
                                                int loop_29_block_1;
                                                int t_29 = 0;
                                            while ((t_29 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_29_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_29_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_29_IOVar1 + (1 * loop_29_block_1);
                                                                                                                                                    __CPROVER_assume(loop_29_block_1 >= 0);
                                                                                                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_29++;
                                                                                                                                                __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_8:
;
                                                ;;
                                                __begin_outb_loop_1_outb_8:
;
                                                ;;
                                                int t_30 = 0;
                                            while ((t_30 < 1) && 0){
                                                                                                                                                    __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_30++;
                                                                                                                                                __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_8:
;
                                                ;;
                                                __exit__outb_8:
;
                                                ;;
                                        t_28++;
                                                                                                                                    __CPROVER_assume(!0);
                                }
                                    __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_4:
;
                                    ;;
                                    __exit__tco_timer_keepalive_4:
;
                                    ;;
                            t_24++;
                                                                                                                        __CPROVER_assume(!0);
                    }
                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_2:
;
                        ;;
                        __exit__i8xx_tco_write_2:
;
                        ;;
                    tco_expect_close = 42;
                                                                                                                                                                                                                                                if (tco_expect_close != 42)
                                                                                                                                    if (!(0)) __cseq_error();
                            static int __cs_l_clear_bit_unused;
                            __cs_l_clear_bit_unused = 0;
                            static int __cs_l_clear_bit_v;
                            __cs_l_clear_bit_v = timer_alive;
                            static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                            __begin_clear_bit_loop_0_clear_bit_2:
;
                            ;;
                            int loop_31_IOVar1;
                            int loop_31_block_1;
                            int t_31 = 0;
                        while ((t_31 < 2) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1)){
                                loop_31_IOVar1 = __cs_l_clear_bit___cs_dowhile_onetime_4;
                                loop_31_block_1 = nondet_int();
                                __cs_l_clear_bit___cs_dowhile_onetime_4 = loop_31_IOVar1 + (1 * loop_31_block_1);
                                                                                                                                        __CPROVER_assume(loop_31_block_1 >= 0);
                                                                                                                                        __CPROVER_assume(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1);
                                    __cs_l_clear_bit_v = 0;
                                    __cs_l_clear_bit___cs_dowhile_onetime_4++;
                                t_31++;
                                                                                                                                    __CPROVER_assume(!(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1));
                        }
                            __end_clear_bit_loop_0_clear_bit_2:
;
                            ;;
                            __begin_clear_bit_loop_1_clear_bit_2:
;
                            ;;
                            int t_32 = 0;
                        while ((t_32 < 1) && 0){
                                                                                                                                        __CPROVER_assume(0);
                                    __cs_l_clear_bit_v = 0;
                                t_32++;
                                                                                                                                    __CPROVER_assume(!0);
                        }
                            __end_clear_bit_loop_1_clear_bit_2:
;
                            ;;
                            __exit__clear_bit_2:
;
                            ;;
                        tco_expect_close = 0;
                        __exit__i8xx_tco_release_2:
;
                        ;;
                    cnt2++;
        }
                                                                                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 77))
                                                                                                                    {
                                                                                                                        __cs_pc_2 = 77;
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
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 65)&&__cs_disable_isr_0 != 1) main_task();
    __cs_simulate = 0;
    if (__cs_disable_isr_1 != 1) closer2_isr_1();
    __cs_simulate = 0;
    if (__cs_disable_isr_2 != 1) closer1_isr_2();
    __cs_simulate = 0;
    if (__cs_disable_isr_3 != 1) writer1_isr_3();
  }
}
