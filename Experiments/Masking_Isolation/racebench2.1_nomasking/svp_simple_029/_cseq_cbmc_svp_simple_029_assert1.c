// Main task
unsigned __CPROVER_bitvector[4] __cs_pc_0;
// svp_simple_029_001_isr_1
unsigned __CPROVER_bitvector[3] __cs_pc_1;
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
unsigned8 svp_simple_029_001_tm_blocks[4096];
unsigned8 svp_simple_029_001_average_adjust_flag;
unsigned8 svp_simple_029_001_average_adjust_count;
unsigned8 (*svp_simple_029_001_ptr_GetTmData)(unsigned32);
void (*svp_simple_029_001_ptr_SetTmData)(unsigned32, unsigned8);
void (*svp_simple_029_001_ptr_SetSelfCtrlFlag)(unsigned32, unsigned8, unsigned8);
void svp_simple_029_001_TmOrgFuncMap();
void svp_simple_029_001_SetSelfCtrlFlag(unsigned32 __cs_l__tm_para, unsigned8 __cs_l__ctrl_flag, unsigned8 __cs_l__flag_pos);
unsigned8 svp_simple_029_001_GetTmData(unsigned32 __cs_l__tm_name);
void svp_simple_029_001_SetTmData(unsigned32 __cs_l__tm_name, unsigned8 __cs_l__tm_data);
void svp_simple_029_001_init();
/* Simulate original main */
void main_task()
{
    static unsigned8 __cs_l_main_svp_simple_029_001_local_status_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            __cs_l_main_svp_simple_029_001_local_status_1 = 1;
    }}
    {
        static int __cs_l_svp_simple_029_001_init_i_1;
        if (__cs_simulate == 1)
        {
                __cs_l_svp_simple_029_001_init_i_1 = 0;
        }
        __begin_svp_simple_029_001_init_loop_0_svp_simple_029_001_init_1:;
        int loop_1_IOVar1;
        int loop_1_block_1;
        int t_1 = 0;
        if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;}
        while ((__cs_simulate == 0 && __cs_pc_0 <= 4) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_svp_simple_029_001_init_i_1 < 4096))))
        {
                    if (__cs_simulate == 1)
                    {
                            loop_1_IOVar1 = __cs_l_svp_simple_029_001_init_i_1;
                    }
                    if (__cs_simulate == 1)
                    {
                            loop_1_block_1 = __VERIFIER_nondet_int();
                    }
                    if (__cs_simulate == 1)
                    {
                            __cs_l_svp_simple_029_001_init_i_1 = loop_1_IOVar1 + (1 * loop_1_block_1);
                    }
                    if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
                    if (__cs_simulate == 1){
                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(loop_1_block_1 >= 0);
                    }}
                    if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
                    if (__cs_simulate == 1){
                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else                    {
                            __CPROVER_assume(__cs_l_svp_simple_029_001_init_i_1 < 4096);
                    }}
                    {
                        if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
                        if (__cs_simulate == 1){
                        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;} else                        {
                                svp_simple_029_001_tm_blocks[__cs_l_svp_simple_029_001_init_i_1] = __VERIFIER_nondet_int();
                        }}
                        if (__cs_simulate == 1)
                        {
                                __cs_l_svp_simple_029_001_init_i_1++;
                        }
                    }
                    if (__cs_simulate == 1)
                    {
                            t_1++;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else        {
                __CPROVER_assume(!(__cs_l_svp_simple_029_001_init_i_1 < 4096));
        }}
        __end_svp_simple_029_001_init_loop_0_svp_simple_029_001_init_1:;
        if (__cs_simulate == 0 && __cs_pc_0 == 6) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 6; __cs_simulate = 2;} else        {
                svp_simple_029_001_average_adjust_flag = 0xFF;
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 7) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 7; __cs_simulate = 2;} else        {
                assert(svp_simple_029_001_average_adjust_flag == 0xFF);
        }}
        {
            if (__cs_simulate == 0 && __cs_pc_0 == 8) __cs_simulate = 1;
            if (__cs_simulate == 1){
            if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 8; __cs_simulate = 2;} else            {
                    /*enable_isr(-1);*/
            }}
            __exit__init_1:;
        }
        __exit__svp_simple_029_001_init_1:;
    }
    {
        if (__cs_simulate == 0 && __cs_pc_0 == 9) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 9; __cs_simulate = 2;} else        {
                svp_simple_029_001_ptr_SetTmData = svp_simple_029_001_SetTmData;
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 10) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 10; __cs_simulate = 2;} else        {
                svp_simple_029_001_ptr_GetTmData = svp_simple_029_001_GetTmData;
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 11) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 11; __cs_simulate = 2;} else        {
                svp_simple_029_001_ptr_SetSelfCtrlFlag = svp_simple_029_001_SetSelfCtrlFlag;
        }}
        __exit__svp_simple_029_001_TmOrgFuncMap_1:;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 12) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 12; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 13) || (__cs_simulate == 1 && (__cs_l_main_svp_simple_029_001_local_status_1 == 1)))
    {
                if (__cs_simulate == 0 && __cs_pc_0 == 13) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 13; __cs_simulate = 2;} else                {
                        svp_simple_029_001_ptr_SetSelfCtrlFlag(36, 0xFF, 0);
                }}
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 14))
    {
        __cs_pc_0 = 14;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_029_001_isr_1 */
void svp_simple_029_001_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    if (svp_simple_029_001_average_adjust_flag == 0xFF)
    {
                        svp_simple_029_001_average_adjust_count++;
                        svp_simple_029_001_ptr_SetTmData(36, svp_simple_029_001_average_adjust_count);
    }
    else
    {
                        svp_simple_029_001_average_adjust_count = 0;
                        svp_simple_029_001_ptr_SetTmData(36, svp_simple_029_001_average_adjust_count);
    }
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 5))
    {
        __cs_pc_1 = 5;
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
        svp_simple_029_001_isr_1();
        if (__cs_pc_1 == 5) __cs_pc_1 = 0;
    }
  }
}
