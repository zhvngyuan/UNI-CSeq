// Main task
unsigned __CPROVER_bitvector[1] __cs_pc_7;
// closer1_isr_1
unsigned __CPROVER_bitvector[7] __cs_pc_1;
// closer2_isr_2
unsigned __CPROVER_bitvector[7] __cs_pc_2;
// closer3_isr_3
unsigned __CPROVER_bitvector[7] __cs_pc_3;
// writer1_isr_4
unsigned __CPROVER_bitvector[7] __cs_pc_4;
// writer2_isr_5
unsigned __CPROVER_bitvector[7] __cs_pc_5;
// writer3_isr_6
unsigned __CPROVER_bitvector[7] __cs_pc_6;
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
                        int loop_77_IOVar1;
                        int loop_77_block_3;
                        int t_77 = 0;
                    while ((t_77 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1)){
                            loop_77_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_6;
                            loop_77_block_3 = nondet_int();
                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = loop_77_IOVar1 + (1 * loop_77_block_3);
                    __CPROVER_assume(loop_77_block_3 >= 0);
                    __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1);
                                                        if (__cs_l_i8xx_tco_write_len)
                                                                                    if (!nowayout)
                                        tco_expect_close = 0;
                                                                                                                if (tco_write_buf == 'V')
                                            tco_expect_close = 42;
                                    static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                    __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_11:
;
                                    ;;
                                    int loop_78_IOVar1;
                                    int loop_78_block_2;
                                    int t_78 = 0;
                                while ((t_78 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)){
                                        loop_78_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                        loop_78_block_2 = nondet_int();
                                        __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_78_IOVar1 + (1 * loop_78_block_2);
                                                        __CPROVER_assume(loop_78_block_2 >= 0);
                                                        __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_21:
;
                                                ;;
                                                int loop_79_IOVar1;
                                                int loop_79_block_1;
                                                int t_79 = 0;
                                            while ((t_79 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_79_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_79_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_79_IOVar1 + (1 * loop_79_block_1);
                                                                    __CPROVER_assume(loop_79_block_1 >= 0);
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_79++;
                                                                __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_21:
;
                                                ;;
                                                __begin_outb_loop_1_outb_21:
;
                                                ;;
                                                int t_80 = 0;
                                            while ((t_80 < 1) && 0){
                                                                    __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_80++;
                                                                __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_21:
;
                                                ;;
                                                __exit__outb_21:
;
                                                ;;
                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                        t_78++;
                                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                }
                                    __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_11:
;
                                    ;;
                                    __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_11:
;
                                    ;;
                                    int t_81 = 0;
                                while ((t_81 < 2) && 0){
                                                        __CPROVER_assume(0);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_22:
;
                                                ;;
                                                int loop_82_IOVar1;
                                                int loop_82_block_1;
                                                int t_82 = 0;
                                            while ((t_82 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_82_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_82_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_82_IOVar1 + (1 * loop_82_block_1);
                                                                    __CPROVER_assume(loop_82_block_1 >= 0);
                                                                    __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_82++;
                                                                __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_22:
;
                                                ;;
                                                __begin_outb_loop_1_outb_22:
;
                                                ;;
                                                int t_83 = 0;
                                            while ((t_83 < 1) && 0){
                                                                    __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_83++;
                                                                __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_22:
;
                                                ;;
                                                __exit__outb_22:
;
                                                ;;
                                        t_81++;
                                                    __CPROVER_assume(!0);
                                }
                                    __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_11:
;
                                    ;;
                                    __exit__tco_timer_keepalive_11:
;
                                    ;;
                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
                            t_77++;
                                        __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1));
                    }
                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_6:
;
                        ;;
                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_6:
;
                        ;;
                        int t_84 = 0;
                    while ((t_84 < 1) && 0){
                                            __CPROVER_assume(0);
                                                                                                        if (__cs_l_i8xx_tco_write_len)
                                                                                                                                    if (!nowayout)
                                        tco_expect_close = 0;
                                                                                                                                                                if (tco_write_buf == 'V')
                                            tco_expect_close = 42;
                                    static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                    __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_12:
;
                                    ;;
                                    int loop_85_IOVar1;
                                    int loop_85_block_2;
                                    int t_85 = 0;
                                while ((t_85 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1)){
                                        loop_85_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                        loop_85_block_2 = nondet_int();
                                        __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_85_IOVar1 + (1 * loop_85_block_2);
                                                                                __CPROVER_assume(loop_85_block_2 >= 0);
                                                                                __CPROVER_assume(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_23:
;
                                                ;;
                                                int loop_86_IOVar1;
                                                int loop_86_block_1;
                                                int t_86 = 0;
                                            while ((t_86 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_86_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_86_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_86_IOVar1 + (1 * loop_86_block_1);
                                                                                            __CPROVER_assume(loop_86_block_1 >= 0);
                                                                                            __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_86++;
                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_23:
;
                                                ;;
                                                __begin_outb_loop_1_outb_23:
;
                                                ;;
                                                int t_87 = 0;
                                            while ((t_87 < 1) && 0){
                                                                                            __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_87++;
                                                                                        __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_23:
;
                                                ;;
                                                __exit__outb_23:
;
                                                ;;
                                            __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                        t_85++;
                                                                            __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                }
                                    __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_12:
;
                                    ;;
                                    __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_12:
;
                                    ;;
                                    int t_88 = 0;
                                while ((t_88 < 2) && 0){
                                                                                __CPROVER_assume(0);
                                                static int __cs_l_outb_v;
                                                __cs_l_outb_v = 0x01;
                                                static int __cs_l_outb_l;
                                                __cs_l_outb_l = tco1_rld;
                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                __begin_outb_loop_0_outb_24:
;
                                                ;;
                                                int loop_89_IOVar1;
                                                int loop_89_block_1;
                                                int t_89 = 0;
                                            while ((t_89 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1)){
                                                    loop_89_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                    loop_89_block_1 = nondet_int();
                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_89_IOVar1 + (1 * loop_89_block_1);
                                                                                            __CPROVER_assume(loop_89_block_1 >= 0);
                                                                                            __CPROVER_assume(__cs_l_outb___cs_dowhile_onetime_3 < 1);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                        __cs_l_outb___cs_dowhile_onetime_3++;
                                                    t_89++;
                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                            }
                                                __end_outb_loop_0_outb_24:
;
                                                ;;
                                                __begin_outb_loop_1_outb_24:
;
                                                ;;
                                                int t_90 = 0;
                                            while ((t_90 < 1) && 0){
                                                                                            __CPROVER_assume(0);
                                                        __cs_l_outb_l = __cs_l_outb_v;
                                                    t_90++;
                                                                                        __CPROVER_assume(!0);
                                            }
                                                __end_outb_loop_1_outb_24:
;
                                                ;;
                                                __exit__outb_24:
;
                                                ;;
                                        t_88++;
                                                                            __CPROVER_assume(!0);
                                }
                                    __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_12:
;
                                    ;;
                                    __exit__tco_timer_keepalive_12:
;
                                    ;;
                            t_84++;
                                                                __CPROVER_assume(!0);
                    }
                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_6:
;
                        ;;
                        __exit__i8xx_tco_write_6:
;
                        ;;
                    cnt6++;
        }
                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_6 == 65))
                                                    {
                                                        __cs_pc_6 = 65;
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
                                                        int loop_1_IOVar1;
                                                        int loop_1_block_3;
                                                        int t_1 = 0;
                                                        if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_1 <= 31) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1))))
                                                        {
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            loop_1_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_6;
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            loop_1_block_3 = nondet_int();
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = loop_1_IOVar1 + (1 * loop_1_block_3);
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;} else                                                                    {
                                                                            __CPROVER_assume(loop_1_block_3 >= 0);
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;} else                                                                    {
                                                                            __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1);
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 6; __cs_simulate = 2;} else                                                                                                {
                                                                                                        tco_expect_close = 0;
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_1 == 7) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 7; __cs_simulate = 2;}
                                                                                                if ((__cs_simulate == 0 && __cs_pc_1 <= 8) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_1 == 8) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 8; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 10; __cs_simulate = 2;} else                                                                                        {
                                                                                                __CPROVER_assume(loop_2_block_2 >= 0);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 11) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 11; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 12; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 14; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_3_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_1 == 15) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 15; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 16; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 18; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 19; __cs_simulate = 2;} else                                                                                                {
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
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 20; __cs_simulate = 2;} else                                                                            {
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
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 22; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 23; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 25; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_6_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_1 == 26) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 26; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 27; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 29; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 30; __cs_simulate = 2;} else                                                                                                {
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
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 31; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(!0);
                                                                            }
                                                                            __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_1:;
                                                                            __exit__tco_timer_keepalive_1:;
                                                                        }
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
                                                                        }
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            t_1++;
                                                                    }
                                                        }
                                                        if (__cs_simulate == 0 && __cs_pc_1 == 32) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 32; __cs_simulate = 2;} else                                                        {
                                                                __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1));
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
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 34; __cs_simulate = 2;} else                                                                    {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 37; __cs_simulate = 2;} else                                                                                                {
                                                                                                        tco_expect_close = 0;
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_1 == 38) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 38; __cs_simulate = 2;}
                                                                                                if ((__cs_simulate == 0 && __cs_pc_1 <= 39) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_1 == 39) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 39; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 41; __cs_simulate = 2;} else                                                                                        {
                                                                                                __CPROVER_assume(loop_9_block_2 >= 0);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 42) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 42; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 43; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 45; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_10_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_1 == 46) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 46; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 47; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 49; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 50; __cs_simulate = 2;} else                                                                                                {
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
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 51; __cs_simulate = 2;} else                                                                            {
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
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 53; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 54; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 56; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_13_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_1 == 57) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 57; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 58; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 60; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 61; __cs_simulate = 2;} else                                                                                                {
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
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 62; __cs_simulate = 2;} else                                                                            {
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
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 63; __cs_simulate = 2;} else                                                        {
                                                                __CPROVER_assume(!0);
                                                        }
                                                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_1:;
                                                        __exit__i8xx_tco_write_1:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_1 == 64) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 64; __cs_simulate = 2;} else                                                    {
                                                            tco_expect_close = 42;
                                                    }
                                                    {
                                                        if (__cs_simulate == 0 && __cs_pc_1 == 65) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 65; __cs_simulate = 2;}
                                                        if ((__cs_simulate == 0 && __cs_pc_1 <= 66) || (__cs_simulate == 1 && (tco_expect_close != 42)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_1 == 66) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 66; __cs_simulate = 2;} else                                                                    {
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
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 67) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 67; __cs_simulate = 2;} else                                                            {
                                                                    __cs_l_clear_bit_v = timer_alive;
                                                            }
                                                            static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                                                            __begin_clear_bit_loop_0_clear_bit_1:;
                                                            int loop_15_IOVar1;
                                                            int loop_15_block_1;
                                                            int t_15 = 0;
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 68) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 68; __cs_simulate = 2;}
                                                            while ((__cs_simulate == 0 && __cs_pc_1 <= 70) || ((__cs_simulate == 1) && ((t_15 < 2) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1))))
                                                            {
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                loop_15_IOVar1 = __cs_l_clear_bit___cs_dowhile_onetime_4;
                                                                        }
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                loop_15_block_1 = nondet_int();
                                                                        }
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                __cs_l_clear_bit___cs_dowhile_onetime_4 = loop_15_IOVar1 + (1 * loop_15_block_1);
                                                                        }
                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 69) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1)
                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 69; __cs_simulate = 2;} else                                                                        {
                                                                                __CPROVER_assume(loop_15_block_1 >= 0);
                                                                        }
                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 70) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1)
                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 70; __cs_simulate = 2;} else                                                                        {
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
                                                                                t_15++;
                                                                        }
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 71) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 71; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(!(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1));
                                                            }
                                                            __end_clear_bit_loop_0_clear_bit_1:;
                                                            __begin_clear_bit_loop_1_clear_bit_1:;
                                                            int t_16 = 0;
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 72) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 72; __cs_simulate = 2;}
                                                            while ((__cs_simulate == 0 && __cs_pc_1 <= 73) || ((__cs_simulate == 1) && ((t_16 < 1) && 0)))
                                                            {
                                                                        if (__cs_simulate == 0 && __cs_pc_1 == 73) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1)
                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 73; __cs_simulate = 2;} else                                                                        {
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
                                                                                t_16++;
                                                                        }
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_1 == 74) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 74; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(!0);
                                                            }
                                                            __end_clear_bit_loop_1_clear_bit_1:;
                                                            __exit__clear_bit_1:;
                                                        }
                                                        if (__cs_simulate == 0 && __cs_pc_1 == 75) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 75; __cs_simulate = 2;} else                                                        {
                                                                tco_expect_close = 0;
                                                        }
                                                        __exit__i8xx_tco_release_1:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_1 == 76) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 76; __cs_simulate = 2;} else                                                    {
                                                            cnt1++;
                                                    }
                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 77))
                                                    {
                                                        __cs_pc_1 = 77;
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
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 2; __cs_simulate = 2;} else                                                                    {
                                                                            __CPROVER_assume(loop_33_block_3 >= 0);
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 3) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 3; __cs_simulate = 2;} else                                                                    {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 6; __cs_simulate = 2;} else                                                                                                {
                                                                                                        tco_expect_close = 0;
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_3 == 7) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 7; __cs_simulate = 2;}
                                                                                                if ((__cs_simulate == 0 && __cs_pc_3 <= 8) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_3 == 8) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 8; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 10; __cs_simulate = 2;} else                                                                                        {
                                                                                                __CPROVER_assume(loop_34_block_2 >= 0);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 11) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 11; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 12; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 14; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_35_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_3 == 15) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 15; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 16; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 18; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 19; __cs_simulate = 2;} else                                                                                                {
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
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 20; __cs_simulate = 2;} else                                                                            {
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
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 22; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 23; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 25; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_38_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_3 == 26) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 26; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 27; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 29; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 30; __cs_simulate = 2;} else                                                                                                {
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
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 31; __cs_simulate = 2;} else                                                                            {
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
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 32; __cs_simulate = 2;} else                                                        {
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
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 34; __cs_simulate = 2;} else                                                                    {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 37; __cs_simulate = 2;} else                                                                                                {
                                                                                                        tco_expect_close = 0;
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_3 == 38) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 38; __cs_simulate = 2;}
                                                                                                if ((__cs_simulate == 0 && __cs_pc_3 <= 39) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_3 == 39) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 39; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 41; __cs_simulate = 2;} else                                                                                        {
                                                                                                __CPROVER_assume(loop_41_block_2 >= 0);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 42) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 42; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 43; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 45; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_42_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_3 == 46) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 46; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 47; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 49; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 50; __cs_simulate = 2;} else                                                                                                {
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
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 51; __cs_simulate = 2;} else                                                                            {
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
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 53; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 54; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 56; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_45_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_3 == 57) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 57; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 58; __cs_simulate = 2;} else                                                                                                {
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
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 60; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 61; __cs_simulate = 2;} else                                                                                                {
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
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 62; __cs_simulate = 2;} else                                                                            {
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
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 63; __cs_simulate = 2;} else                                                        {
                                                                __CPROVER_assume(!0);
                                                        }
                                                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_3:;
                                                        __exit__i8xx_tco_write_3:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_3 == 64) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 64; __cs_simulate = 2;} else                                                    {
                                                            tco_expect_close = 42;
                                                    }
                                                    {
                                                        if (__cs_simulate == 0 && __cs_pc_3 == 65) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 65; __cs_simulate = 2;}
                                                        if ((__cs_simulate == 0 && __cs_pc_3 <= 66) || (__cs_simulate == 1 && (tco_expect_close != 42)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_3 == 66) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 66; __cs_simulate = 2;} else                                                                    {
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
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 67) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 67; __cs_simulate = 2;} else                                                            {
                                                                    __cs_l_clear_bit_v = timer_alive;
                                                            }
                                                            static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                                                            __begin_clear_bit_loop_0_clear_bit_3:;
                                                            int loop_47_IOVar1;
                                                            int loop_47_block_1;
                                                            int t_47 = 0;
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 68) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 68; __cs_simulate = 2;}
                                                            while ((__cs_simulate == 0 && __cs_pc_3 <= 70) || ((__cs_simulate == 1) && ((t_47 < 2) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1))))
                                                            {
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                loop_47_IOVar1 = __cs_l_clear_bit___cs_dowhile_onetime_4;
                                                                        }
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                loop_47_block_1 = nondet_int();
                                                                        }
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                __cs_l_clear_bit___cs_dowhile_onetime_4 = loop_47_IOVar1 + (1 * loop_47_block_1);
                                                                        }
                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 69) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1)
                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 69; __cs_simulate = 2;} else                                                                        {
                                                                                __CPROVER_assume(loop_47_block_1 >= 0);
                                                                        }
                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 70) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1)
                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 70; __cs_simulate = 2;} else                                                                        {
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
                                                                                t_47++;
                                                                        }
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 71) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 71; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(!(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1));
                                                            }
                                                            __end_clear_bit_loop_0_clear_bit_3:;
                                                            __begin_clear_bit_loop_1_clear_bit_3:;
                                                            int t_48 = 0;
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 72) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 72; __cs_simulate = 2;}
                                                            while ((__cs_simulate == 0 && __cs_pc_3 <= 73) || ((__cs_simulate == 1) && ((t_48 < 1) && 0)))
                                                            {
                                                                        if (__cs_simulate == 0 && __cs_pc_3 == 73) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1)
                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 73; __cs_simulate = 2;} else                                                                        {
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
                                                                                t_48++;
                                                                        }
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 74) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 74; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(!0);
                                                            }
                                                            __end_clear_bit_loop_1_clear_bit_3:;
                                                            __exit__clear_bit_3:;
                                                        }
                                                        if (__cs_simulate == 0 && __cs_pc_3 == 75) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 75; __cs_simulate = 2;} else                                                        {
                                                                tco_expect_close = 0;
                                                        }
                                                        __exit__i8xx_tco_release_3:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_3 == 76) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 76; __cs_simulate = 2;} else                                                    {
                                                            cnt3++;
                                                    }
                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 77))
                                                    {
                                                        __cs_pc_3 = 77;
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
                                                        int loop_49_IOVar1;
                                                        int loop_49_block_3;
                                                        int t_49 = 0;
                                                        if (__cs_simulate == 0 && __cs_pc_4 == 1) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 1; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 31) || ((__cs_simulate == 1) && ((t_49 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1))))
                                                        {
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            loop_49_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_6;
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            loop_49_block_3 = nondet_int();
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = loop_49_IOVar1 + (1 * loop_49_block_3);
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_4 == 2) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 2; __cs_simulate = 2;} else                                                                    {
                                                                            __CPROVER_assume(loop_49_block_3 >= 0);
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_4 == 3) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 3; __cs_simulate = 2;} else                                                                    {
                                                                            __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1);
                                                                    }
                                                                    {
                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 4) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 4; __cs_simulate = 2;}
                                                                        if ((__cs_simulate == 0 && __cs_pc_4 <= 8) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                                                                        {
                                                                                    if (__cs_simulate == 0 && __cs_pc_4 == 5) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 5; __cs_simulate = 2;}
                                                                                    if ((__cs_simulate == 0 && __cs_pc_4 <= 8) || (__cs_simulate == 1 && (!nowayout)))
                                                                                    {
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 6) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 6; __cs_simulate = 2;} else                                                                                                {
                                                                                                        tco_expect_close = 0;
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 7) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 7; __cs_simulate = 2;}
                                                                                                if ((__cs_simulate == 0 && __cs_pc_4 <= 8) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 8) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 8; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    tco_expect_close = 42;
                                                                                                            }
                                                                                                }
                                                                                    }
                                                                        }
                                                                        {
                                                                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_7:;
                                                                            int loop_50_IOVar1;
                                                                            int loop_50_block_2;
                                                                            int t_50 = 0;
                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 9) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 9; __cs_simulate = 2;}
                                                                            while ((__cs_simulate == 0 && __cs_pc_4 <= 19) || ((__cs_simulate == 1) && ((t_50 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1))))
                                                                            {
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                loop_50_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                loop_50_block_2 = nondet_int();
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_50_IOVar1 + (1 * loop_50_block_2);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 10) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 10; __cs_simulate = 2;} else                                                                                        {
                                                                                                __CPROVER_assume(loop_50_block_2 >= 0);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 11) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 11; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 12) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 12; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __cs_l_outb_l = tco1_rld;
                                                                                                }
                                                                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                __begin_outb_loop_0_outb_13:;
                                                                                                int loop_51_IOVar1;
                                                                                                int loop_51_block_1;
                                                                                                int t_51 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 13) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 13; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_4 <= 15) || ((__cs_simulate == 1) && ((t_51 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                {
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_51_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_51_block_1 = nondet_int();
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_51_IOVar1 + (1 * loop_51_block_1);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 14) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 14; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_51_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 15) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 15; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_51++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 16) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 16; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                }
                                                                                                __end_outb_loop_0_outb_13:;
                                                                                                __begin_outb_loop_1_outb_13:;
                                                                                                int t_52 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 17) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 17; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_4 <= 18) || ((__cs_simulate == 1) && ((t_52 < 1) && 0)))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 18) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 18; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_52++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 19) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 19; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!0);
                                                                                                }
                                                                                                __end_outb_loop_1_outb_13:;
                                                                                                __exit__outb_13:;
                                                                                            }
                                                                                            if (__cs_simulate == 1)
                                                                                            {
                                                                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                            }
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                t_50++;
                                                                                        }
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 20) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 20; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                                                            }
                                                                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_7:;
                                                                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_7:;
                                                                            int t_53 = 0;
                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 21) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 21; __cs_simulate = 2;}
                                                                            while ((__cs_simulate == 0 && __cs_pc_4 <= 30) || ((__cs_simulate == 1) && ((t_53 < 2) && 0)))
                                                                            {
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 22) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 22; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 23) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 23; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __cs_l_outb_l = tco1_rld;
                                                                                                }
                                                                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                __begin_outb_loop_0_outb_14:;
                                                                                                int loop_54_IOVar1;
                                                                                                int loop_54_block_1;
                                                                                                int t_54 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 24) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 24; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_4 <= 26) || ((__cs_simulate == 1) && ((t_54 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                {
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_54_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_54_block_1 = nondet_int();
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_54_IOVar1 + (1 * loop_54_block_1);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 25) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 25; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_54_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 26) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 26; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_54++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 27) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 27; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                }
                                                                                                __end_outb_loop_0_outb_14:;
                                                                                                __begin_outb_loop_1_outb_14:;
                                                                                                int t_55 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 28) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 28; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_4 <= 29) || ((__cs_simulate == 1) && ((t_55 < 1) && 0)))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 29) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 29; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_55++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 30) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 30; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!0);
                                                                                                }
                                                                                                __end_outb_loop_1_outb_14:;
                                                                                                __exit__outb_14:;
                                                                                            }
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                t_53++;
                                                                                        }
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 31) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 31; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(!0);
                                                                            }
                                                                            __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_7:;
                                                                            __exit__tco_timer_keepalive_7:;
                                                                        }
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
                                                                        }
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            t_49++;
                                                                    }
                                                        }
                                                        if (__cs_simulate == 0 && __cs_pc_4 == 32) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 32; __cs_simulate = 2;} else                                                        {
                                                                __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1));
                                                        }
                                                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_4:;
                                                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_4:;
                                                        int t_56 = 0;
                                                        if (__cs_simulate == 0 && __cs_pc_4 == 33) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 33; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_4 <= 62) || ((__cs_simulate == 1) && ((t_56 < 1) && 0)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_4 == 34) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 34; __cs_simulate = 2;} else                                                                    {
                                                                            __CPROVER_assume(0);
                                                                    }
                                                                    {
                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 35) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 35; __cs_simulate = 2;}
                                                                        if ((__cs_simulate == 0 && __cs_pc_4 <= 39) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                                                                        {
                                                                                    if (__cs_simulate == 0 && __cs_pc_4 == 36) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 36; __cs_simulate = 2;}
                                                                                    if ((__cs_simulate == 0 && __cs_pc_4 <= 39) || (__cs_simulate == 1 && (!nowayout)))
                                                                                    {
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 37) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 37; __cs_simulate = 2;} else                                                                                                {
                                                                                                        tco_expect_close = 0;
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 38) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 38; __cs_simulate = 2;}
                                                                                                if ((__cs_simulate == 0 && __cs_pc_4 <= 39) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 39) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 39; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    tco_expect_close = 42;
                                                                                                            }
                                                                                                }
                                                                                    }
                                                                        }
                                                                        {
                                                                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_8:;
                                                                            int loop_57_IOVar1;
                                                                            int loop_57_block_2;
                                                                            int t_57 = 0;
                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 40) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 40; __cs_simulate = 2;}
                                                                            while ((__cs_simulate == 0 && __cs_pc_4 <= 50) || ((__cs_simulate == 1) && ((t_57 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1))))
                                                                            {
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                loop_57_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                loop_57_block_2 = nondet_int();
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_57_IOVar1 + (1 * loop_57_block_2);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 41) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 41; __cs_simulate = 2;} else                                                                                        {
                                                                                                __CPROVER_assume(loop_57_block_2 >= 0);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 42) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 42; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 43) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 43; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __cs_l_outb_l = tco1_rld;
                                                                                                }
                                                                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                __begin_outb_loop_0_outb_15:;
                                                                                                int loop_58_IOVar1;
                                                                                                int loop_58_block_1;
                                                                                                int t_58 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 44) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 44; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_4 <= 46) || ((__cs_simulate == 1) && ((t_58 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                {
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_58_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_58_block_1 = nondet_int();
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_58_IOVar1 + (1 * loop_58_block_1);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 45) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 45; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_58_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 46) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 46; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_58++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 47) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 47; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                }
                                                                                                __end_outb_loop_0_outb_15:;
                                                                                                __begin_outb_loop_1_outb_15:;
                                                                                                int t_59 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 48) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 48; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_4 <= 49) || ((__cs_simulate == 1) && ((t_59 < 1) && 0)))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 49) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 49; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_59++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 50) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 50; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!0);
                                                                                                }
                                                                                                __end_outb_loop_1_outb_15:;
                                                                                                __exit__outb_15:;
                                                                                            }
                                                                                            if (__cs_simulate == 1)
                                                                                            {
                                                                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                            }
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                t_57++;
                                                                                        }
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 51) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 51; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                                                            }
                                                                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_8:;
                                                                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_8:;
                                                                            int t_60 = 0;
                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 52) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 52; __cs_simulate = 2;}
                                                                            while ((__cs_simulate == 0 && __cs_pc_4 <= 61) || ((__cs_simulate == 1) && ((t_60 < 2) && 0)))
                                                                            {
                                                                                        if (__cs_simulate == 0 && __cs_pc_4 == 53) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 53; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 54) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 54; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __cs_l_outb_l = tco1_rld;
                                                                                                }
                                                                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                __begin_outb_loop_0_outb_16:;
                                                                                                int loop_61_IOVar1;
                                                                                                int loop_61_block_1;
                                                                                                int t_61 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 55) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 55; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_4 <= 57) || ((__cs_simulate == 1) && ((t_61 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                {
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_61_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_61_block_1 = nondet_int();
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_61_IOVar1 + (1 * loop_61_block_1);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 56) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 56; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_61_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 57) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 57; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_61++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 58) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 58; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                }
                                                                                                __end_outb_loop_0_outb_16:;
                                                                                                __begin_outb_loop_1_outb_16:;
                                                                                                int t_62 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 59) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 59; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_4 <= 60) || ((__cs_simulate == 1) && ((t_62 < 1) && 0)))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 60) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 60; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_62++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_4 == 61) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 61; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!0);
                                                                                                }
                                                                                                __end_outb_loop_1_outb_16:;
                                                                                                __exit__outb_16:;
                                                                                            }
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                t_60++;
                                                                                        }
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_4 == 62) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 62; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(!0);
                                                                            }
                                                                            __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_8:;
                                                                            __exit__tco_timer_keepalive_8:;
                                                                        }
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            t_56++;
                                                                    }
                                                        }
                                                        if (__cs_simulate == 0 && __cs_pc_4 == 63) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 63; __cs_simulate = 2;} else                                                        {
                                                                __CPROVER_assume(!0);
                                                        }
                                                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_4:;
                                                        __exit__i8xx_tco_write_4:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_4 == 64) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 64; __cs_simulate = 2;} else                                                    {
                                                            cnt4++;
                                                    }
                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 65))
                                                    {
                                                        __cs_pc_4 = 65;
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
                                                        int loop_17_IOVar1;
                                                        int loop_17_block_3;
                                                        int t_17 = 0;
                                                        if (__cs_simulate == 0 && __cs_pc_2 == 1) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 1; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 31) || ((__cs_simulate == 1) && ((t_17 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1))))
                                                        {
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            loop_17_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_6;
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            loop_17_block_3 = nondet_int();
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = loop_17_IOVar1 + (1 * loop_17_block_3);
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_2 == 2) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 2; __cs_simulate = 2;} else                                                                    {
                                                                            __CPROVER_assume(loop_17_block_3 >= 0);
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_2 == 3) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 3; __cs_simulate = 2;} else                                                                    {
                                                                            __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1);
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 6; __cs_simulate = 2;} else                                                                                                {
                                                                                                        tco_expect_close = 0;
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 7) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 7; __cs_simulate = 2;}
                                                                                                if ((__cs_simulate == 0 && __cs_pc_2 <= 8) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 8) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 8; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    tco_expect_close = 42;
                                                                                                            }
                                                                                                }
                                                                                    }
                                                                        }
                                                                        {
                                                                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_3:;
                                                                            int loop_18_IOVar1;
                                                                            int loop_18_block_2;
                                                                            int t_18 = 0;
                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 9) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 9; __cs_simulate = 2;}
                                                                            while ((__cs_simulate == 0 && __cs_pc_2 <= 19) || ((__cs_simulate == 1) && ((t_18 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1))))
                                                                            {
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                loop_18_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                loop_18_block_2 = nondet_int();
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_18_IOVar1 + (1 * loop_18_block_2);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 10) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 10; __cs_simulate = 2;} else                                                                                        {
                                                                                                __CPROVER_assume(loop_18_block_2 >= 0);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 11) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 11; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 12) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 12; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __cs_l_outb_l = tco1_rld;
                                                                                                }
                                                                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                __begin_outb_loop_0_outb_5:;
                                                                                                int loop_19_IOVar1;
                                                                                                int loop_19_block_1;
                                                                                                int t_19 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 13) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 13; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 15) || ((__cs_simulate == 1) && ((t_19 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                {
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_19_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_19_block_1 = nondet_int();
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_19_IOVar1 + (1 * loop_19_block_1);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 14) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 14; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_19_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 15) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 15; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_19++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 16) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 16; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                }
                                                                                                __end_outb_loop_0_outb_5:;
                                                                                                __begin_outb_loop_1_outb_5:;
                                                                                                int t_20 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 17) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 17; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 18) || ((__cs_simulate == 1) && ((t_20 < 1) && 0)))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 18) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 18; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_20++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 19) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 19; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!0);
                                                                                                }
                                                                                                __end_outb_loop_1_outb_5:;
                                                                                                __exit__outb_5:;
                                                                                            }
                                                                                            if (__cs_simulate == 1)
                                                                                            {
                                                                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                            }
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                t_18++;
                                                                                        }
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 20) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 20; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                                                            }
                                                                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_3:;
                                                                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_3:;
                                                                            int t_21 = 0;
                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 21) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 21; __cs_simulate = 2;}
                                                                            while ((__cs_simulate == 0 && __cs_pc_2 <= 30) || ((__cs_simulate == 1) && ((t_21 < 2) && 0)))
                                                                            {
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 22) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 22; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 23; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __cs_l_outb_l = tco1_rld;
                                                                                                }
                                                                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                __begin_outb_loop_0_outb_6:;
                                                                                                int loop_22_IOVar1;
                                                                                                int loop_22_block_1;
                                                                                                int t_22 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 24) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 24; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 26) || ((__cs_simulate == 1) && ((t_22 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                {
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_22_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_22_block_1 = nondet_int();
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_22_IOVar1 + (1 * loop_22_block_1);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 25) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 25; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_22_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 26) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 26; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_22++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 27) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 27; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                }
                                                                                                __end_outb_loop_0_outb_6:;
                                                                                                __begin_outb_loop_1_outb_6:;
                                                                                                int t_23 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 28) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 28; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 29) || ((__cs_simulate == 1) && ((t_23 < 1) && 0)))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 29) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 29; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_23++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 30) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 30; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!0);
                                                                                                }
                                                                                                __end_outb_loop_1_outb_6:;
                                                                                                __exit__outb_6:;
                                                                                            }
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                t_21++;
                                                                                        }
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 31) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 31; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(!0);
                                                                            }
                                                                            __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_3:;
                                                                            __exit__tco_timer_keepalive_3:;
                                                                        }
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
                                                                        }
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            t_17++;
                                                                    }
                                                        }
                                                        if (__cs_simulate == 0 && __cs_pc_2 == 32) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 32; __cs_simulate = 2;} else                                                        {
                                                                __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1));
                                                        }
                                                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_2:;
                                                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_2:;
                                                        int t_24 = 0;
                                                        if (__cs_simulate == 0 && __cs_pc_2 == 33) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 33; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_2 <= 62) || ((__cs_simulate == 1) && ((t_24 < 1) && 0)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_2 == 34) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 34; __cs_simulate = 2;} else                                                                    {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 37; __cs_simulate = 2;} else                                                                                                {
                                                                                                        tco_expect_close = 0;
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 38) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 38; __cs_simulate = 2;}
                                                                                                if ((__cs_simulate == 0 && __cs_pc_2 <= 39) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 39) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 39; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    tco_expect_close = 42;
                                                                                                            }
                                                                                                }
                                                                                    }
                                                                        }
                                                                        {
                                                                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_4:;
                                                                            int loop_25_IOVar1;
                                                                            int loop_25_block_2;
                                                                            int t_25 = 0;
                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 40) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 40; __cs_simulate = 2;}
                                                                            while ((__cs_simulate == 0 && __cs_pc_2 <= 50) || ((__cs_simulate == 1) && ((t_25 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1))))
                                                                            {
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                loop_25_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                loop_25_block_2 = nondet_int();
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_25_IOVar1 + (1 * loop_25_block_2);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 41) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 41; __cs_simulate = 2;} else                                                                                        {
                                                                                                __CPROVER_assume(loop_25_block_2 >= 0);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 42) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 42; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 43) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 43; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __cs_l_outb_l = tco1_rld;
                                                                                                }
                                                                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                __begin_outb_loop_0_outb_7:;
                                                                                                int loop_26_IOVar1;
                                                                                                int loop_26_block_1;
                                                                                                int t_26 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 44) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 44; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 46) || ((__cs_simulate == 1) && ((t_26 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                {
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_26_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_26_block_1 = nondet_int();
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_26_IOVar1 + (1 * loop_26_block_1);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 45) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 45; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_26_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 46) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 46; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_26++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 47) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 47; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                }
                                                                                                __end_outb_loop_0_outb_7:;
                                                                                                __begin_outb_loop_1_outb_7:;
                                                                                                int t_27 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 48) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 48; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 49) || ((__cs_simulate == 1) && ((t_27 < 1) && 0)))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 49) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 49; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_27++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 50) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 50; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!0);
                                                                                                }
                                                                                                __end_outb_loop_1_outb_7:;
                                                                                                __exit__outb_7:;
                                                                                            }
                                                                                            if (__cs_simulate == 1)
                                                                                            {
                                                                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                            }
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                t_25++;
                                                                                        }
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 51) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 51; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                                                            }
                                                                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_4:;
                                                                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_4:;
                                                                            int t_28 = 0;
                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 52) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 52; __cs_simulate = 2;}
                                                                            while ((__cs_simulate == 0 && __cs_pc_2 <= 61) || ((__cs_simulate == 1) && ((t_28 < 2) && 0)))
                                                                            {
                                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 53) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 53; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 54; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __cs_l_outb_l = tco1_rld;
                                                                                                }
                                                                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                __begin_outb_loop_0_outb_8:;
                                                                                                int loop_29_IOVar1;
                                                                                                int loop_29_block_1;
                                                                                                int t_29 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 55) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 55; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 57) || ((__cs_simulate == 1) && ((t_29 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                {
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_29_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_29_block_1 = nondet_int();
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_29_IOVar1 + (1 * loop_29_block_1);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 56) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 56; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_29_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 57) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 57; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_29++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 58) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 58; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                }
                                                                                                __end_outb_loop_0_outb_8:;
                                                                                                __begin_outb_loop_1_outb_8:;
                                                                                                int t_30 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 59) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 59; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_2 <= 60) || ((__cs_simulate == 1) && ((t_30 < 1) && 0)))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 60) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 60; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_30++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_2 == 61) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 61; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!0);
                                                                                                }
                                                                                                __end_outb_loop_1_outb_8:;
                                                                                                __exit__outb_8:;
                                                                                            }
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                t_28++;
                                                                                        }
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_2 == 62) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 62; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(!0);
                                                                            }
                                                                            __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_4:;
                                                                            __exit__tco_timer_keepalive_4:;
                                                                        }
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            t_24++;
                                                                    }
                                                        }
                                                        if (__cs_simulate == 0 && __cs_pc_2 == 63) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 63; __cs_simulate = 2;} else                                                        {
                                                                __CPROVER_assume(!0);
                                                        }
                                                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_2:;
                                                        __exit__i8xx_tco_write_2:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_2 == 64) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 64; __cs_simulate = 2;} else                                                    {
                                                            tco_expect_close = 42;
                                                    }
                                                    {
                                                        if (__cs_simulate == 0 && __cs_pc_2 == 65) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 65; __cs_simulate = 2;}
                                                        if ((__cs_simulate == 0 && __cs_pc_2 <= 66) || (__cs_simulate == 1 && (tco_expect_close != 42)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_2 == 66) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 66; __cs_simulate = 2;} else                                                                    {
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
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 67) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 67; __cs_simulate = 2;} else                                                            {
                                                                    __cs_l_clear_bit_v = timer_alive;
                                                            }
                                                            static int __cs_l_clear_bit___cs_dowhile_onetime_4 = 0;
                                                            __begin_clear_bit_loop_0_clear_bit_2:;
                                                            int loop_31_IOVar1;
                                                            int loop_31_block_1;
                                                            int t_31 = 0;
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 68) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 68; __cs_simulate = 2;}
                                                            while ((__cs_simulate == 0 && __cs_pc_2 <= 70) || ((__cs_simulate == 1) && ((t_31 < 2) && (__cs_l_clear_bit___cs_dowhile_onetime_4 < 1))))
                                                            {
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                loop_31_IOVar1 = __cs_l_clear_bit___cs_dowhile_onetime_4;
                                                                        }
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                loop_31_block_1 = nondet_int();
                                                                        }
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                __cs_l_clear_bit___cs_dowhile_onetime_4 = loop_31_IOVar1 + (1 * loop_31_block_1);
                                                                        }
                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 69) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1)
                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 69; __cs_simulate = 2;} else                                                                        {
                                                                                __CPROVER_assume(loop_31_block_1 >= 0);
                                                                        }
                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 70) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1)
                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 70; __cs_simulate = 2;} else                                                                        {
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
                                                                                t_31++;
                                                                        }
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 71) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 71; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(!(__cs_l_clear_bit___cs_dowhile_onetime_4 < 1));
                                                            }
                                                            __end_clear_bit_loop_0_clear_bit_2:;
                                                            __begin_clear_bit_loop_1_clear_bit_2:;
                                                            int t_32 = 0;
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 72) __cs_simulate = 1;
                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 72; __cs_simulate = 2;}
                                                            while ((__cs_simulate == 0 && __cs_pc_2 <= 73) || ((__cs_simulate == 1) && ((t_32 < 1) && 0)))
                                                            {
                                                                        if (__cs_simulate == 0 && __cs_pc_2 == 73) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1)
                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 73; __cs_simulate = 2;} else                                                                        {
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
                                                                                t_32++;
                                                                        }
                                                            }
                                                            if (__cs_simulate == 0 && __cs_pc_2 == 74) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 74; __cs_simulate = 2;} else                                                            {
                                                                    __CPROVER_assume(!0);
                                                            }
                                                            __end_clear_bit_loop_1_clear_bit_2:;
                                                            __exit__clear_bit_2:;
                                                        }
                                                        if (__cs_simulate == 0 && __cs_pc_2 == 75) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 75; __cs_simulate = 2;} else                                                        {
                                                                tco_expect_close = 0;
                                                        }
                                                        __exit__i8xx_tco_release_2:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_2 == 76) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 76; __cs_simulate = 2;} else                                                    {
                                                            cnt2++;
                                                    }
                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 77))
                                                    {
                                                        __cs_pc_2 = 77;
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
                                                        int loop_63_IOVar1;
                                                        int loop_63_block_3;
                                                        int t_63 = 0;
                                                        if (__cs_simulate == 0 && __cs_pc_5 == 1) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 1; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 31) || ((__cs_simulate == 1) && ((t_63 < 2) && (__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1))))
                                                        {
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            loop_63_IOVar1 = __cs_l_i8xx_tco_write___cs_dowhile_onetime_6;
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            loop_63_block_3 = nondet_int();
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            __cs_l_i8xx_tco_write___cs_dowhile_onetime_6 = loop_63_IOVar1 + (1 * loop_63_block_3);
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 2) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 2; __cs_simulate = 2;} else                                                                    {
                                                                            __CPROVER_assume(loop_63_block_3 >= 0);
                                                                    }
                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 3) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 3; __cs_simulate = 2;} else                                                                    {
                                                                            __CPROVER_assume(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1);
                                                                    }
                                                                    {
                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 4) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 4; __cs_simulate = 2;}
                                                                        if ((__cs_simulate == 0 && __cs_pc_5 <= 8) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                                                                        {
                                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 5) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 5; __cs_simulate = 2;}
                                                                                    if ((__cs_simulate == 0 && __cs_pc_5 <= 8) || (__cs_simulate == 1 && (!nowayout)))
                                                                                    {
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 6) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 6; __cs_simulate = 2;} else                                                                                                {
                                                                                                        tco_expect_close = 0;
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 7) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 7; __cs_simulate = 2;}
                                                                                                if ((__cs_simulate == 0 && __cs_pc_5 <= 8) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 8) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 8; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    tco_expect_close = 42;
                                                                                                            }
                                                                                                }
                                                                                    }
                                                                        }
                                                                        {
                                                                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_9:;
                                                                            int loop_64_IOVar1;
                                                                            int loop_64_block_2;
                                                                            int t_64 = 0;
                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 9) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 9; __cs_simulate = 2;}
                                                                            while ((__cs_simulate == 0 && __cs_pc_5 <= 19) || ((__cs_simulate == 1) && ((t_64 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1))))
                                                                            {
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                loop_64_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                loop_64_block_2 = nondet_int();
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_64_IOVar1 + (1 * loop_64_block_2);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 10) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 10; __cs_simulate = 2;} else                                                                                        {
                                                                                                __CPROVER_assume(loop_64_block_2 >= 0);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 11) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 11; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 12) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 12; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __cs_l_outb_l = tco1_rld;
                                                                                                }
                                                                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                __begin_outb_loop_0_outb_17:;
                                                                                                int loop_65_IOVar1;
                                                                                                int loop_65_block_1;
                                                                                                int t_65 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 13) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 13; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_5 <= 15) || ((__cs_simulate == 1) && ((t_65 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                {
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_65_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_65_block_1 = nondet_int();
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_65_IOVar1 + (1 * loop_65_block_1);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 14) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 14; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_65_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 15) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 15; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_65++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 16) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 16; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                }
                                                                                                __end_outb_loop_0_outb_17:;
                                                                                                __begin_outb_loop_1_outb_17:;
                                                                                                int t_66 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 17) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 17; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_5 <= 18) || ((__cs_simulate == 1) && ((t_66 < 1) && 0)))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 18) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 18; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_66++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 19) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 19; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!0);
                                                                                                }
                                                                                                __end_outb_loop_1_outb_17:;
                                                                                                __exit__outb_17:;
                                                                                            }
                                                                                            if (__cs_simulate == 1)
                                                                                            {
                                                                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                            }
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                t_64++;
                                                                                        }
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 20) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 20; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                                                            }
                                                                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_9:;
                                                                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_9:;
                                                                            int t_67 = 0;
                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 21) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 21; __cs_simulate = 2;}
                                                                            while ((__cs_simulate == 0 && __cs_pc_5 <= 30) || ((__cs_simulate == 1) && ((t_67 < 2) && 0)))
                                                                            {
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 22) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 22; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 23) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 23; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __cs_l_outb_l = tco1_rld;
                                                                                                }
                                                                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                __begin_outb_loop_0_outb_18:;
                                                                                                int loop_68_IOVar1;
                                                                                                int loop_68_block_1;
                                                                                                int t_68 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 24) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 24; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_5 <= 26) || ((__cs_simulate == 1) && ((t_68 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                {
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_68_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_68_block_1 = nondet_int();
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_68_IOVar1 + (1 * loop_68_block_1);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 25) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 25; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_68_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 26) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 26; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_68++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 27) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 27; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                }
                                                                                                __end_outb_loop_0_outb_18:;
                                                                                                __begin_outb_loop_1_outb_18:;
                                                                                                int t_69 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 28) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 28; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_5 <= 29) || ((__cs_simulate == 1) && ((t_69 < 1) && 0)))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 29) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 29; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_69++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 30) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 30; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!0);
                                                                                                }
                                                                                                __end_outb_loop_1_outb_18:;
                                                                                                __exit__outb_18:;
                                                                                            }
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                t_67++;
                                                                                        }
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 31) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 31; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(!0);
                                                                            }
                                                                            __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_9:;
                                                                            __exit__tco_timer_keepalive_9:;
                                                                        }
                                                                        if (__cs_simulate == 1)
                                                                        {
                                                                                __cs_l_i8xx_tco_write___cs_dowhile_onetime_6++;
                                                                        }
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            t_63++;
                                                                    }
                                                        }
                                                        if (__cs_simulate == 0 && __cs_pc_5 == 32) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 32; __cs_simulate = 2;} else                                                        {
                                                                __CPROVER_assume(!(__cs_l_i8xx_tco_write___cs_dowhile_onetime_6 < 1));
                                                        }
                                                        __end_i8xx_tco_write_loop_0_i8xx_tco_write_5:;
                                                        __begin_i8xx_tco_write_loop_1_i8xx_tco_write_5:;
                                                        int t_70 = 0;
                                                        if (__cs_simulate == 0 && __cs_pc_5 == 33) __cs_simulate = 1;
                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 33; __cs_simulate = 2;}
                                                        while ((__cs_simulate == 0 && __cs_pc_5 <= 62) || ((__cs_simulate == 1) && ((t_70 < 1) && 0)))
                                                        {
                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 34) __cs_simulate = 1;
                                                                    if (__cs_simulate == 1)
                                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 34; __cs_simulate = 2;} else                                                                    {
                                                                            __CPROVER_assume(0);
                                                                    }
                                                                    {
                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 35) __cs_simulate = 1;
                                                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 35; __cs_simulate = 2;}
                                                                        if ((__cs_simulate == 0 && __cs_pc_5 <= 39) || (__cs_simulate == 1 && (__cs_l_i8xx_tco_write_len)))
                                                                        {
                                                                                    if (__cs_simulate == 0 && __cs_pc_5 == 36) __cs_simulate = 1;
                                                                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 36; __cs_simulate = 2;}
                                                                                    if ((__cs_simulate == 0 && __cs_pc_5 <= 39) || (__cs_simulate == 1 && (!nowayout)))
                                                                                    {
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 37) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 37; __cs_simulate = 2;} else                                                                                                {
                                                                                                        tco_expect_close = 0;
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 38) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 38; __cs_simulate = 2;}
                                                                                                if ((__cs_simulate == 0 && __cs_pc_5 <= 39) || (__cs_simulate == 1 && (tco_write_buf == 'V')))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 39) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 39; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    tco_expect_close = 42;
                                                                                                            }
                                                                                                }
                                                                                    }
                                                                        }
                                                                        {
                                                                            static int __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = 0;
                                                                            __begin_tco_timer_keepalive_loop_0_tco_timer_keepalive_10:;
                                                                            int loop_71_IOVar1;
                                                                            int loop_71_block_2;
                                                                            int t_71 = 0;
                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 40) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 40; __cs_simulate = 2;}
                                                                            while ((__cs_simulate == 0 && __cs_pc_5 <= 50) || ((__cs_simulate == 1) && ((t_71 < 3) && (__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1))))
                                                                            {
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                loop_71_IOVar1 = __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5;
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                loop_71_block_2 = nondet_int();
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 = loop_71_IOVar1 + (1 * loop_71_block_2);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 41) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 41; __cs_simulate = 2;} else                                                                                        {
                                                                                                __CPROVER_assume(loop_71_block_2 >= 0);
                                                                                        }
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 42) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 42; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 43) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 43; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __cs_l_outb_l = tco1_rld;
                                                                                                }
                                                                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                __begin_outb_loop_0_outb_19:;
                                                                                                int loop_72_IOVar1;
                                                                                                int loop_72_block_1;
                                                                                                int t_72 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 44) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 44; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_5 <= 46) || ((__cs_simulate == 1) && ((t_72 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                {
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_72_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_72_block_1 = nondet_int();
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_72_IOVar1 + (1 * loop_72_block_1);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 45) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 45; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_72_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 46) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 46; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_72++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 47) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 47; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                }
                                                                                                __end_outb_loop_0_outb_19:;
                                                                                                __begin_outb_loop_1_outb_19:;
                                                                                                int t_73 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 48) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 48; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_5 <= 49) || ((__cs_simulate == 1) && ((t_73 < 1) && 0)))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 49) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 49; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_73++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 50) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 50; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!0);
                                                                                                }
                                                                                                __end_outb_loop_1_outb_19:;
                                                                                                __exit__outb_19:;
                                                                                            }
                                                                                            if (__cs_simulate == 1)
                                                                                            {
                                                                                                    __cs_l_tco_timer_keepalive___cs_dowhile_onetime_5++;
                                                                                            }
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                t_71++;
                                                                                        }
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 51) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 51; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(!(__cs_l_tco_timer_keepalive___cs_dowhile_onetime_5 < 1));
                                                                            }
                                                                            __end_tco_timer_keepalive_loop_0_tco_timer_keepalive_10:;
                                                                            __begin_tco_timer_keepalive_loop_1_tco_timer_keepalive_10:;
                                                                            int t_74 = 0;
                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 52) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 52; __cs_simulate = 2;}
                                                                            while ((__cs_simulate == 0 && __cs_pc_5 <= 61) || ((__cs_simulate == 1) && ((t_74 < 2) && 0)))
                                                                            {
                                                                                        if (__cs_simulate == 0 && __cs_pc_5 == 53) __cs_simulate = 1;
                                                                                        if (__cs_simulate == 1)
                                                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 53; __cs_simulate = 2;} else                                                                                        {
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
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 54) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 54; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __cs_l_outb_l = tco1_rld;
                                                                                                }
                                                                                                static int __cs_l_outb___cs_dowhile_onetime_3 = 0;
                                                                                                __begin_outb_loop_0_outb_20:;
                                                                                                int loop_75_IOVar1;
                                                                                                int loop_75_block_1;
                                                                                                int t_75 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 55) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 55; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_5 <= 57) || ((__cs_simulate == 1) && ((t_75 < 2) && (__cs_l_outb___cs_dowhile_onetime_3 < 1))))
                                                                                                {
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_75_IOVar1 = __cs_l_outb___cs_dowhile_onetime_3;
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    loop_75_block_1 = nondet_int();
                                                                                                            }
                                                                                                            if (__cs_simulate == 1)
                                                                                                            {
                                                                                                                    __cs_l_outb___cs_dowhile_onetime_3 = loop_75_IOVar1 + (1 * loop_75_block_1);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 56) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 56; __cs_simulate = 2;} else                                                                                                            {
                                                                                                                    __CPROVER_assume(loop_75_block_1 >= 0);
                                                                                                            }
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 57) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 57; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_75++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 58) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 58; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!(__cs_l_outb___cs_dowhile_onetime_3 < 1));
                                                                                                }
                                                                                                __end_outb_loop_0_outb_20:;
                                                                                                __begin_outb_loop_1_outb_20:;
                                                                                                int t_76 = 0;
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 59) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_5 = 59; __cs_simulate = 2;}
                                                                                                while ((__cs_simulate == 0 && __cs_pc_5 <= 60) || ((__cs_simulate == 1) && ((t_76 < 1) && 0)))
                                                                                                {
                                                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 60) __cs_simulate = 1;
                                                                                                            if (__cs_simulate == 1)
                                                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 60; __cs_simulate = 2;} else                                                                                                            {
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
                                                                                                                    t_76++;
                                                                                                            }
                                                                                                }
                                                                                                if (__cs_simulate == 0 && __cs_pc_5 == 61) __cs_simulate = 1;
                                                                                                if (__cs_simulate == 1)
                                                                                                if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 61; __cs_simulate = 2;} else                                                                                                {
                                                                                                        __CPROVER_assume(!0);
                                                                                                }
                                                                                                __end_outb_loop_1_outb_20:;
                                                                                                __exit__outb_20:;
                                                                                            }
                                                                                        }
                                                                                        if (__cs_simulate == 1)
                                                                                        {
                                                                                                t_74++;
                                                                                        }
                                                                            }
                                                                            if (__cs_simulate == 0 && __cs_pc_5 == 62) __cs_simulate = 1;
                                                                            if (__cs_simulate == 1)
                                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 62; __cs_simulate = 2;} else                                                                            {
                                                                                    __CPROVER_assume(!0);
                                                                            }
                                                                            __end_tco_timer_keepalive_loop_1_tco_timer_keepalive_10:;
                                                                            __exit__tco_timer_keepalive_10:;
                                                                        }
                                                                    }
                                                                    if (__cs_simulate == 1)
                                                                    {
                                                                            t_70++;
                                                                    }
                                                        }
                                                        if (__cs_simulate == 0 && __cs_pc_5 == 63) __cs_simulate = 1;
                                                        if (__cs_simulate == 1)
                                                        if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 63; __cs_simulate = 2;} else                                                        {
                                                                __CPROVER_assume(!0);
                                                        }
                                                        __end_i8xx_tco_write_loop_1_i8xx_tco_write_5:;
                                                        __exit__i8xx_tco_write_5:;
                                                    }
                                                    if (__cs_simulate == 0 && __cs_pc_5 == 64) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 64; __cs_simulate = 2;} else                                                    {
                                                            cnt5++;
                                                    }
                                                    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_5 == 65))
                                                    {
                                                        __cs_pc_5 = 65;
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
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 77)&&(__cs_pc_3 == 0 || __cs_pc_3 == 77)&&(__cs_pc_4 == 0 || __cs_pc_4 == 65)&&(__cs_pc_2 == 0 || __cs_pc_2 == 77)&&(__cs_pc_5 == 0 || __cs_pc_5 == 65)&&__cs_disable_isr_0 != 1) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 77)&&(__cs_pc_4 == 0 || __cs_pc_4 == 65)&&(__cs_pc_2 == 0 || __cs_pc_2 == 77)&&(__cs_pc_5 == 0 || __cs_pc_5 == 65)&&__cs_disable_isr_1 != 1) closer1_isr_1();
    __cs_simulate = 0;
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 77)&&(__cs_pc_3 == 0 || __cs_pc_3 == 77)&&(__cs_pc_4 == 0 || __cs_pc_4 == 65)&&(__cs_pc_5 == 0 || __cs_pc_5 == 65)&&__cs_disable_isr_2 != 1) closer2_isr_2();
    __cs_simulate = 0;
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 77)&&(__cs_pc_4 == 0 || __cs_pc_4 == 65)&&(__cs_pc_2 == 0 || __cs_pc_2 == 77)&&(__cs_pc_5 == 0 || __cs_pc_5 == 65)&&__cs_disable_isr_3 != 1) closer3_isr_3();
    __cs_simulate = 0;
    if ((__cs_pc_5 == 0 || __cs_pc_5 == 65)&&__cs_disable_isr_4 != 1) writer1_isr_4();
    __cs_simulate = 0;
    if (__cs_disable_isr_5 != 1) writer2_isr_5();
    __cs_simulate = 0;
    if (__cs_disable_isr_6 != 1) writer3_isr_6();
  }
}
