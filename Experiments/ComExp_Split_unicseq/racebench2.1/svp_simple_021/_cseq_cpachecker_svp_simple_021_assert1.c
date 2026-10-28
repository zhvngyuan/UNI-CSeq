// Main task
unsigned int __cs_pc_0;
// svp_simple_021_001_isr_1
unsigned int __cs_pc_1;
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
/* Global variables */
typedef unsigned char unsigned8;
typedef unsigned short unsigned16;
typedef unsigned int unsigned32;
typedef unsigned long long unsigned64;
typedef signed char signed8;
typedef signed short signed16;
typedef signed int signed32;
typedef signed long long signed64;
void init();
unsigned16 svp_simple_021_001_tc_block_rcvd_bytes_ch1;
unsigned16 svp_simple_021_001_tc_block_rcvd_bytes_ch2;
unsigned16 svp_simple_021_001_tc_block_rcvd_bytes;
unsigned8 svp_simple_021_001_tc_chan1_buff[256];
unsigned8 svp_simple_021_001_tc_chan2_buff[256];
unsigned8 *svp_simple_021_001_tc_buff_p;
struct svp_simple_021_001_tc_block_data
{
  unsigned8 type;
  unsigned8 id;
  unsigned8 valid_len;
};
/* Simulate original main */
void main_task()
{
    static struct svp_simple_021_001_tc_block_data __cs_l_main_tc_block_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_tc_block_1, sizeof(struct svp_simple_021_001_tc_block_data));
    }}
    {
        if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else        {
                svp_simple_021_001_tc_block_rcvd_bytes_ch1 = __VERIFIER_nondet_int();
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else        {
                svp_simple_021_001_tc_block_rcvd_bytes_ch2 = __VERIFIER_nondet_int();
        }}
        {
            if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
            if (__cs_simulate == 1){
            if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else            {
                    /*enable_isr(-1);*/
                    __cs_disable_isr_0 = 0;
                    __cs_disable_isr_1 = 0;
            }}
            __exit__init_1:;
        }
        __exit__svp_simple_021_001_init_1:;
    }
    {
        static unsigned __cs_l_svp_simple_021_001_RecvTcBlock_svp_simple_021_001_flag_chan1_1;
        if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;} else        {
                __cs_init_scalar(&__cs_l_svp_simple_021_001_RecvTcBlock_svp_simple_021_001_flag_chan1_1, sizeof(unsigned));
        }}
        if (__cs_simulate == 1)
        {
                __cs_l_svp_simple_021_001_RecvTcBlock_svp_simple_021_001_flag_chan1_1 = 0;
        }
        if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;}
        if ((__cs_simulate == 0 && __cs_pc_0 <= 13) || (__cs_simulate == 1 && (svp_simple_021_001_tc_block_rcvd_bytes_ch1 >= 16)))
        {
                    if (__cs_simulate == 0 && __cs_pc_0 == 6) __cs_simulate = 1;
                    if (__cs_simulate == 1){
                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 6; __cs_simulate = 2;} else                    {
                            if (!(svp_simple_021_001_tc_block_rcvd_bytes_ch1 >= 16)) __cseq_error();
                    }}
                    if (__cs_simulate == 0 && __cs_pc_0 == 7) __cs_simulate = 1;
                    if (__cs_simulate == 1){
                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 7; __cs_simulate = 2;} else                    {
                            svp_simple_021_001_tc_block_rcvd_bytes_ch1 = 0;
                    }}
                    static int __cs_l_svp_simple_021_001_RecvTcBlock_i_1;
                    if (__cs_simulate == 0 && __cs_pc_0 == 8) __cs_simulate = 1;
                    if (__cs_simulate == 1){
                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 8; __cs_simulate = 2;} else                    {
                            __cs_init_scalar(&__cs_l_svp_simple_021_001_RecvTcBlock_i_1, sizeof(int));
                    }}
                    if (__cs_simulate == 1)
                    {
                            __cs_l_svp_simple_021_001_RecvTcBlock_i_1 = 0;
                    }
                    __begin_svp_simple_021_001_RecvTcBlock_loop_0_svp_simple_021_001_RecvTcBlock_1:;
                    int loop_1_IOVar1;
                    int loop_1_block_1;
                    int t_1 = 0;
                    if (__cs_simulate == 0 && __cs_pc_0 == 9) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 9; __cs_simulate = 2;}
                    while ((__cs_simulate == 0 && __cs_pc_0 <= 12) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_svp_simple_021_001_RecvTcBlock_i_1 < 256))))
                    {
                                if (__cs_simulate == 1)
                                {
                                        loop_1_IOVar1 = __cs_l_svp_simple_021_001_RecvTcBlock_i_1;
                                }
                                if (__cs_simulate == 1)
                                {
                                        loop_1_block_1 = __VERIFIER_nondet_int();
                                }
                                if (__cs_simulate == 1)
                                {
                                        __cs_l_svp_simple_021_001_RecvTcBlock_i_1 = loop_1_IOVar1 + (1 * loop_1_block_1);
                                }
                                if (__cs_simulate == 0 && __cs_pc_0 == 10) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 10; __cs_simulate = 2;} else                                {
                                        __CPROVER_assume(loop_1_block_1 >= 0);
                                }}
                                if (__cs_simulate == 0 && __cs_pc_0 == 11) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 11; __cs_simulate = 2;} else                                {
                                        __CPROVER_assume(__cs_l_svp_simple_021_001_RecvTcBlock_i_1 < 256);
                                }}
                                {
                                    if (__cs_simulate == 0 && __cs_pc_0 == 12) __cs_simulate = 1;
                                    if (__cs_simulate == 1){
                                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 12; __cs_simulate = 2;} else                                    {
                                            svp_simple_021_001_tc_chan1_buff[__cs_l_svp_simple_021_001_RecvTcBlock_i_1] = 0;
                                    }}
                                    if (__cs_simulate == 1)
                                    {
                                            __cs_l_svp_simple_021_001_RecvTcBlock_i_1++;
                                    }
                                }
                                if (__cs_simulate == 1)
                                {
                                        t_1++;
                                }
                    }
                    if (__cs_simulate == 0 && __cs_pc_0 == 13) __cs_simulate = 1;
                    if (__cs_simulate == 1){
                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 13; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(!(__cs_l_svp_simple_021_001_RecvTcBlock_i_1 < 256));
                    }}
                    __end_svp_simple_021_001_RecvTcBlock_loop_0_svp_simple_021_001_RecvTcBlock_1:;
                    if (__cs_simulate == 1)
                    {
                            __cs_l_svp_simple_021_001_RecvTcBlock_svp_simple_021_001_flag_chan1_1 = 0xFF;
                    }
        }
        __exit__svp_simple_021_001_RecvTcBlock_1:;
    }
    static int __cs_l_main_ichan_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 14) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 14; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_ichan_1, sizeof(int));
    }}
    if (__cs_simulate == 1)
    {
            __cs_l_main_ichan_1 = 0;
    }
    __begin_main_loop_0:;
    unsigned8 *loop_2_IOVar1;
    int loop_2_IOVar2;
    int loop_2_k1_1;
    int loop_2_block_3;
    int t_2 = 0;
    if (__cs_simulate == 0 && __cs_pc_0 == 15) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 15; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_0 <= 29) || ((__cs_simulate == 1) && ((t_2 < 4) && (__cs_l_main_ichan_1 < 2))))
    {
                if (__cs_simulate == 0 && __cs_pc_0 == 16) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 16; __cs_simulate = 2;} else                {
                        loop_2_IOVar1 = svp_simple_021_001_tc_buff_p;
                }}
                if (__cs_simulate == 1)
                {
                        loop_2_IOVar2 = __cs_l_main_ichan_1;
                }
                if (__cs_simulate == 1)
                {
                        loop_2_block_3 = __VERIFIER_nondet_int();
                }
                unsigned8 *resetIOVar_1_list[3];
                if (__cs_simulate == 0 && __cs_pc_0 == 17) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 17; __cs_simulate = 2;} else                {
                        resetIOVar_1_list[0] = loop_2_IOVar1;
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 18) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 18; __cs_simulate = 2;} else                {
                        resetIOVar_1_list[1] = svp_simple_021_001_tc_chan1_buff;
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 19) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 19; __cs_simulate = 2;} else                {
                        resetIOVar_1_list[2] = svp_simple_021_001_tc_chan2_buff;
                }}
                if (__cs_simulate == 1)
                {
                        loop_2_k1_1 = __VERIFIER_nondet_int();
                }
                if (__cs_simulate == 0 && __cs_pc_0 == 20) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 20; __cs_simulate = 2;} else                {
                        __CPROVER_assume(loop_2_k1_1 >= 0);
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 21) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 21; __cs_simulate = 2;} else                {
                        __CPROVER_assume(loop_2_k1_1 <= 2);
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 22) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 22; __cs_simulate = 2;} else                {
                        svp_simple_021_001_tc_buff_p = resetIOVar_1_list[loop_2_k1_1];
                }}
                if (__cs_simulate == 1)
                {
                        __cs_l_main_ichan_1 = loop_2_IOVar2 + (1 * loop_2_block_3);
                }
                if (__cs_simulate == 0 && __cs_pc_0 == 23) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 23; __cs_simulate = 2;} else                {
                        __CPROVER_assume(loop_2_block_3 >= 0);
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 24) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 24; __cs_simulate = 2;} else                {
                        __CPROVER_assume(__cs_l_main_ichan_1 < 2);
                }}
                {
                    if (__cs_simulate == 0 && __cs_pc_0 == 25) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 25; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_0 <= 27) || (__cs_simulate == 1 && (__cs_l_main_ichan_1 == 0)))
                    {
                                if (__cs_simulate == 0 && __cs_pc_0 == 26) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 26; __cs_simulate = 2;} else                                {
                                        svp_simple_021_001_tc_buff_p = svp_simple_021_001_tc_chan1_buff;
                                }}
                                if (__cs_simulate == 0 && __cs_pc_0 == 27) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 27; __cs_simulate = 2;} else                                {
                                        svp_simple_021_001_tc_block_rcvd_bytes = svp_simple_021_001_tc_block_rcvd_bytes_ch1;
                                }}
                    }
                    else
if ((__cs_simulate == 0 && __cs_pc_0 <= 29) || (__cs_simulate == 1))                    {
                                if (__cs_simulate == 0 && __cs_pc_0 == 28) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 28; __cs_simulate = 2;} else                                {
                                        svp_simple_021_001_tc_buff_p = svp_simple_021_001_tc_chan2_buff;
                                }}
                                if (__cs_simulate == 0 && __cs_pc_0 == 29) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 29; __cs_simulate = 2;} else                                {
                                        svp_simple_021_001_tc_block_rcvd_bytes = svp_simple_021_001_tc_block_rcvd_bytes_ch2;
                                }}
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_main_tc_block_1.type = *(svp_simple_021_001_tc_buff_p + 2);
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_main_tc_block_1.id = *(svp_simple_021_001_tc_buff_p + 4);
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_main_tc_block_1.valid_len = *(svp_simple_021_001_tc_buff_p + 5);
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_main_ichan_1++;
                    }
                }
                if (__cs_simulate == 1)
                {
                        t_2++;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 30) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 30; __cs_simulate = 2;} else    {
            __CPROVER_assume(!(__cs_l_main_ichan_1 < 2));
    }}
    __end_main_loop_0:;
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 31))
    {
        __cs_pc_0 = 31;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_021_001_isr_1 */
void svp_simple_021_001_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    svp_simple_021_001_tc_block_rcvd_bytes_ch1 = ((*((volatile unsigned int *) 0x10000000)) >> 3) & 0x1FFF;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 1))
    {
        __cs_pc_1 = 1;
        __cs_simulate = 2;
    }
}
/* main function (scheduler) */
int main()
{
  __cs_simulate = 0;
  __cs_pc_0 = 0;
  __cs_pc_1 = 0;
  __cs_disable_isr_0 = 0;
  __cs_disable_isr_1 = 0;
  while (1)
  {
    __cs_simulate = 0;
    if (1) main_task();
    __cs_simulate = 0;
    if (__cs_disable_isr_1 != 1) {
        svp_simple_021_001_isr_1();
        if (__cs_pc_1 == 1) __cs_pc_1 = 0;
    }
  }
}
