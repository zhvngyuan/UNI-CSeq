// Main task
unsigned int __cs_pc_0;
// svp_simple_024_001_isr_1
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
union bytetoword
{
  unsigned char bytedata[2];
  unsigned int worddata;
};
int svp_simple_024_001_global_var;
int *svp_simple_024_001_global_array[100];
unsigned8 svp_simple_024_001_reset_RT;
unsigned int svp_simple_024_001_RTData(int *__cs_l__array, int __cs_l__size);
void svp_simple_024_001_init();
/* Simulate svp_simple_024_001_isr_1 */
void svp_simple_024_001_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    static int __cs_l_svp_simple_024_001_isr_1_i_1;
                    __cs_l_svp_simple_024_001_isr_1_i_1 = 0;
                    __begin_svp_simple_024_001_isr_1_loop_0:
;
                    ;;
                    int loop_1_IOVar1;
                    int loop_1_block_1;
                    int t_1 = 0;
                while ((t_1 < 2) && (__cs_l_svp_simple_024_001_isr_1_i_1 < 100))
    {
                        loop_1_IOVar1 = __cs_l_svp_simple_024_001_isr_1_i_1;
                        loop_1_block_1 = __VERIFIER_nondet_int();
                        __cs_l_svp_simple_024_001_isr_1_i_1 = loop_1_IOVar1 + (1 * loop_1_block_1);
                        __CPROVER_assume(loop_1_block_1 >= 0);
                        __CPROVER_assume(__cs_l_svp_simple_024_001_isr_1_i_1 < 100);
                {
                            svp_simple_024_001_global_array[__cs_l_svp_simple_024_001_isr_1_i_1] = 10;
                            __cs_l_svp_simple_024_001_isr_1_i_1++;
                }
                        t_1++;
    }
            __CPROVER_assume(!(__cs_l_svp_simple_024_001_isr_1_i_1 < 100));
                    __end_svp_simple_024_001_isr_1_loop_0:
;
                    ;;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 6))
    {
        __cs_pc_1 = 6;
        __cs_simulate = 2;
    }
}
/* Simulate original main */
void main_task()
{
    static union bytetoword __cs_l_main_svp_simple_024_001_local_a_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_svp_simple_024_001_local_a_1, sizeof(union bytetoword));
    }}
    static union bytetoword __cs_l_main_svp_simple_024_001_local_b_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_svp_simple_024_001_local_b_1, sizeof(union bytetoword));
    }}
    {
        if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else        {
                svp_simple_024_001_global_var = __VERIFIER_nondet_int();
        }}
        {
            if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
            if (__cs_simulate == 1){
            if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else            {
                    /*enable_isr(-1);*/
            }}
            __exit__init_1:;
        }
        __exit__svp_simple_024_001_init_1:;
    }
    static unsigned int __retval__svp_simple_024_001_RTData_1;
    {
        static int *__cs_l_svp_simple_024_001_RTData_array;
        if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;} else        {
                __cs_l_svp_simple_024_001_RTData_array = svp_simple_024_001_global_array;
        }}
        static int __cs_l_svp_simple_024_001_RTData_index;
        if (__cs_simulate == 1)
        {
                __cs_l_svp_simple_024_001_RTData_index = 0;
        }
        static union bytetoword __cs_l_svp_simple_024_001_RTData_svp_simple_024_001_local_r_1;
        if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else        {
                __cs_init_scalar(&__cs_l_svp_simple_024_001_RTData_svp_simple_024_001_local_r_1, sizeof(union bytetoword));
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 6) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 6; __cs_simulate = 2;} else        {
                __cs_l_svp_simple_024_001_RTData_svp_simple_024_001_local_r_1.bytedata[0] = __cs_l_svp_simple_024_001_RTData_array[__cs_l_svp_simple_024_001_RTData_index + 1];
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 7) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 7; __cs_simulate = 2;} else        {
                __cs_l_svp_simple_024_001_RTData_svp_simple_024_001_local_r_1.bytedata[1] = __cs_l_svp_simple_024_001_RTData_array[__cs_l_svp_simple_024_001_RTData_index];
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 8) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 8; __cs_simulate = 2;} else        {
                __retval__svp_simple_024_001_RTData_1 = __cs_l_svp_simple_024_001_RTData_svp_simple_024_001_local_r_1.worddata;
        }}
        if (__cs_simulate == 1)
        {
            goto __exit__svp_simple_024_001_RTData_1;
        }
        __exit__svp_simple_024_001_RTData_1:;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 9) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 9; __cs_simulate = 2;} else    {
            __cs_l_main_svp_simple_024_001_local_a_1.worddata = __retval__svp_simple_024_001_RTData_1;
    }}
    static unsigned int __retval__svp_simple_024_001_RTData_2;
    {
        static int *__cs_l_svp_simple_024_001_RTData_array;
        if (__cs_simulate == 0 && __cs_pc_0 == 10) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 10; __cs_simulate = 2;} else        {
                __cs_l_svp_simple_024_001_RTData_array = svp_simple_024_001_global_array;
        }}
        static int __cs_l_svp_simple_024_001_RTData_index;
        if (__cs_simulate == 1)
        {
                __cs_l_svp_simple_024_001_RTData_index = 1;
        }
        static union bytetoword __cs_l_svp_simple_024_001_RTData_svp_simple_024_001_local_r_1;
        if (__cs_simulate == 0 && __cs_pc_0 == 11) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 11; __cs_simulate = 2;} else        {
                __cs_init_scalar(&__cs_l_svp_simple_024_001_RTData_svp_simple_024_001_local_r_1, sizeof(union bytetoword));
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 12) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 12; __cs_simulate = 2;} else        {
                __cs_l_svp_simple_024_001_RTData_svp_simple_024_001_local_r_1.bytedata[0] = __cs_l_svp_simple_024_001_RTData_array[__cs_l_svp_simple_024_001_RTData_index + 1];
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 13) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 13; __cs_simulate = 2;} else        {
                __cs_l_svp_simple_024_001_RTData_svp_simple_024_001_local_r_1.bytedata[1] = __cs_l_svp_simple_024_001_RTData_array[__cs_l_svp_simple_024_001_RTData_index];
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 14) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 14; __cs_simulate = 2;} else        {
                __retval__svp_simple_024_001_RTData_2 = __cs_l_svp_simple_024_001_RTData_svp_simple_024_001_local_r_1.worddata;
        }}
        if (__cs_simulate == 1)
        {
            goto __exit__svp_simple_024_001_RTData_2;
        }
        __exit__svp_simple_024_001_RTData_2:;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 15) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 15; __cs_simulate = 2;} else    {
            __cs_l_main_svp_simple_024_001_local_b_1.worddata = __retval__svp_simple_024_001_RTData_2;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 16) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 16; __cs_simulate = 2;} else    {
            if (!(svp_simple_024_001_global_array[1] == 0)) __cseq_error();
    }}
    static int __cs_l_main_svp_simple_024_001_local_casereg_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 17) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 17; __cs_simulate = 2;} else    {
            __cs_l_main_svp_simple_024_001_local_casereg_1 = __cs_l_main_svp_simple_024_001_local_a_1.worddata | (__cs_l_main_svp_simple_024_001_local_b_1.worddata & 0x02f0);
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 18) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 18; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 19) || (__cs_simulate == 1 && (__cs_l_main_svp_simple_024_001_local_casereg_1 == 0x02f0)))
    {
                if (__cs_simulate == 0 && __cs_pc_0 == 19) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 19; __cs_simulate = 2;} else                {
                        svp_simple_024_001_reset_RT = 1;
                }}
                if (__cs_simulate == 1)
                {
                    goto __switch_1_exit;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 20) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 20; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 21) || (__cs_simulate == 1 && (__cs_l_main_svp_simple_024_001_local_casereg_1 == 0x0390)))
    {
                __switch_1_case_2:;
                if (__cs_simulate == 0 && __cs_pc_0 == 21) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 21; __cs_simulate = 2;} else                {
                        svp_simple_024_001_reset_RT = 0;
                }}
                if (__cs_simulate == 1)
                {
                    goto __switch_1_exit;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 22) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 22; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 22) || (__cs_simulate == 1 && (!((__cs_l_main_svp_simple_024_001_local_casereg_1 == 0x02f0) || (__cs_l_main_svp_simple_024_001_local_casereg_1 == 0x0390)))))
    {
                __switch_1_case_3:;
                if (__cs_simulate == 1)
                {
                    goto __switch_1_exit;
                }
    }
    __switch_1_exit:;
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 23))
    {
        __cs_pc_0 = 23;
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
        svp_simple_024_001_isr_1();
        if (__cs_pc_1 == 6) __cs_pc_1 = 0;
    }
  }
}
