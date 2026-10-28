// Main task
unsigned int __cs_pc_0;
// svp_simple_031_001_isr_1
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
void svp_simple_031_001_init();
int svp_simple_031_001_func_1(int __cs_l__a, int __cs_l__b);
int svp_simple_031_001_func_2(int __cs_l__x);
void svp_simple_031_001_func_3();
unsigned16 svp_simple_031_001_tc_block_rcvd_bytes_ch1;
unsigned16 svp_simple_031_001_tc_block_rcvd_bytes_ch2;
unsigned16 svp_simple_031_001_tc_block_rcvd_bytes;
unsigned8 svp_simple_031_001_tc_chan1_buff[256];
unsigned8 svp_simple_031_001_tc_chan2_buff[256];
unsigned8 *svp_simple_031_001_tc_buff_p;
unsigned32 svp_simple_031_001_gloable_var1;
struct svp_simple_031_001_tc_block_data
{
  unsigned8 type;
  unsigned8 id;
  unsigned8 valid_len;
};
/* Simulate svp_simple_031_001_isr_1 */
void svp_simple_031_001_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    svp_simple_031_001_tc_block_rcvd_bytes_ch1 = ((*((volatile unsigned int *) 0x10000000)) >> 3) & 0x1FFF;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 1))
    {
        __cs_pc_1 = 1;
        __cs_simulate = 2;
    }
}
/* Simulate original main */
void main_task()
{
    {
        if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else        {
                svp_simple_031_001_tc_block_rcvd_bytes_ch1 = __VERIFIER_nondet_int();
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else        {
                svp_simple_031_001_tc_block_rcvd_bytes_ch2 = __VERIFIER_nondet_int();
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else        {
                svp_simple_031_001_gloable_var1 = __VERIFIER_nondet_int();
        }}
        {
            if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
            if (__cs_simulate == 1){
            if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else            {
                    /*enable_isr(-1);*/
                    __cs_disable_isr_1 = 0;
                    __cs_disable_isr_0 = 0;
            }}
            __exit__init_1:;
        }
        __exit__svp_simple_031_001_init_1:;
    }
    static struct svp_simple_031_001_tc_block_data __cs_l_main_tc_block_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_tc_block_1, sizeof(struct svp_simple_031_001_tc_block_data));
    }}
    static int __cs_l_main_ichan_1;
    if (__cs_simulate == 1)
    {
            __cs_l_main_ichan_1 = 0;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 7) || (__cs_simulate == 1 && (__cs_l_main_ichan_1 == 0)))
    {
                if (__cs_simulate == 0 && __cs_pc_0 == 6) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 6; __cs_simulate = 2;} else                {
                        svp_simple_031_001_tc_buff_p = svp_simple_031_001_tc_chan1_buff;
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 7) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 7; __cs_simulate = 2;} else                {
                        svp_simple_031_001_tc_block_rcvd_bytes = svp_simple_031_001_tc_block_rcvd_bytes_ch1;
                }}
    }
    if (__cs_simulate == 1)
    {
            __cs_l_main_tc_block_1.type = *(svp_simple_031_001_tc_buff_p + 2);
    }
    if (__cs_simulate == 1)
    {
            __cs_l_main_tc_block_1.id = *(svp_simple_031_001_tc_buff_p + 4);
    }
    if (__cs_simulate == 1)
    {
            __cs_l_main_tc_block_1.valid_len = *(svp_simple_031_001_tc_buff_p + 5);
    }
    {
        static unsigned __cs_l_svp_simple_031_001_func_3_svp_simple_031_001_flag_chan1_1;
        if (__cs_simulate == 0 && __cs_pc_0 == 8) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 8; __cs_simulate = 2;} else        {
                __cs_init_scalar(&__cs_l_svp_simple_031_001_func_3_svp_simple_031_001_flag_chan1_1, sizeof(unsigned));
        }}
        if (__cs_simulate == 1)
        {
                __cs_l_svp_simple_031_001_func_3_svp_simple_031_001_flag_chan1_1 = 0;
        }
        if (__cs_simulate == 0 && __cs_pc_0 == 9) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 9; __cs_simulate = 2;}
        if ((__cs_simulate == 0 && __cs_pc_0 <= 15) || (__cs_simulate == 1 && (svp_simple_031_001_tc_block_rcvd_bytes_ch1 >= 16)))
        {
                    static int __retval__svp_simple_031_001_func_1_1;
                    {
                        static int __cs_l_svp_simple_031_001_func_1_a;
                        if (__cs_simulate == 0 && __cs_pc_0 == 10) __cs_simulate = 1;
                        if (__cs_simulate == 1){
                        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 10; __cs_simulate = 2;} else                        {
                                __cs_l_svp_simple_031_001_func_1_a = svp_simple_031_001_gloable_var1;
                        }}
                        static int __cs_l_svp_simple_031_001_func_1_b;
                        if (__cs_simulate == 0 && __cs_pc_0 == 11) __cs_simulate = 1;
                        if (__cs_simulate == 1){
                        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 11; __cs_simulate = 2;} else                        {
                                __cs_l_svp_simple_031_001_func_1_b = svp_simple_031_001_tc_block_rcvd_bytes_ch1;
                        }}
                        static int __cs_l_svp_simple_031_001_func_1_c_1;
                        if (__cs_simulate == 0 && __cs_pc_0 == 12) __cs_simulate = 1;
                        if (__cs_simulate == 1){
                        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 12; __cs_simulate = 2;} else                        {
                                __cs_init_scalar(&__cs_l_svp_simple_031_001_func_1_c_1, sizeof(int));
                        }}
                        if (__cs_simulate == 0 && __cs_pc_0 == 13) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 13; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_0 <= 13) || (__cs_simulate == 1 && (__cs_l_svp_simple_031_001_func_1_a < __cs_l_svp_simple_031_001_func_1_b)))
                        {
                                    if (__cs_simulate == 1)
                                    {
                                            __cs_l_svp_simple_031_001_func_1_c_1 = __cs_l_svp_simple_031_001_func_1_a * __cs_l_svp_simple_031_001_func_1_b;
                                    }
                        }
                        else
if ((__cs_simulate == 0 && __cs_pc_0 <= 15) || (__cs_simulate == 1))                        {
                                    static int __retval__svp_simple_031_001_func_2_1;
                                    {
                                        static int __cs_l_svp_simple_031_001_func_2_x;
                                        if (__cs_simulate == 1)
                                        {
                                                __cs_l_svp_simple_031_001_func_2_x = 10;
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_0 == 14) __cs_simulate = 1;
                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 14; __cs_simulate = 2;}
                                        if ((__cs_simulate == 0 && __cs_pc_0 <= 15) || (__cs_simulate == 1 && (svp_simple_031_001_tc_block_rcvd_bytes_ch1 > 0)))
                                        {
                                                    if (__cs_simulate == 0 && __cs_pc_0 == 15) __cs_simulate = 1;
                                                    if (__cs_simulate == 1){
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 15; __cs_simulate = 2;} else                                                    {
                                                            if (!(svp_simple_031_001_tc_block_rcvd_bytes_ch1 > 0)) __cseq_error();
                                                    }}
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __retval__svp_simple_031_001_func_2_1 = __cs_l_svp_simple_031_001_func_2_x;
                                                    }
                                                    if (__cs_simulate == 1)
                                                    {
                                                        goto __exit__svp_simple_031_001_func_2_1;
                                                    }
                                        }
                                        else
if ((__cs_simulate == 0 && __cs_pc_0 <= 15) || (__cs_simulate == 1))                                        {
                                                    if (__cs_simulate == 1)
                                                    {
                                                            __retval__svp_simple_031_001_func_2_1 = 0;
                                                    }
                                                    if (__cs_simulate == 1)
                                                    {
                                                        goto __exit__svp_simple_031_001_func_2_1;
                                                    }
                                        }
                                        __exit__svp_simple_031_001_func_2_1:;
                                    }
                                    if (__cs_simulate == 1)
                                    {
                                            __cs_l_svp_simple_031_001_func_1_c_1 = __retval__svp_simple_031_001_func_2_1;
                                    }
                        }
                        if (__cs_simulate == 1)
                        {
                                __retval__svp_simple_031_001_func_1_1 = __cs_l_svp_simple_031_001_func_1_c_1;
                        }
                        if (__cs_simulate == 1)
                        {
                            goto __exit__svp_simple_031_001_func_1_1;
                        }
                        __exit__svp_simple_031_001_func_1_1:;
                    }
        }
        __exit__svp_simple_031_001_func_3_1:;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 16))
    {
        __cs_pc_0 = 16;
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
        svp_simple_031_001_isr_1();
        if (__cs_pc_1 == 1) __cs_pc_1 = 0;
    }
  }
}
