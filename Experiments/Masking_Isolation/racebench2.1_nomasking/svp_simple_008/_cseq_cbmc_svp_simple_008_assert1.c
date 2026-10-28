// Main task
unsigned __CPROVER_bitvector[4] __cs_pc_0;
// svp_simple_008_001_isr_1
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
void svp_simple_008_001_func_1();
int svp_simple_008_001_global_var;
int svp_simple_008_001_global_array[100];
/* Simulate original main */
void main_task()
{
    {
        if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else        {
                /*enable_isr(-1);*/
        }}
        __exit__init_1:;
    }
    static int __cs_l_main_p_1;
    if (__cs_simulate == 1)
    {
            __cs_l_main_p_1 = 10;
    }
    static int __cs_l_main_q_1;
    if (__cs_simulate == 1)
    {
            __cs_l_main_q_1 = 30;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else    {
            /*disable_isr(1);*/
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else    {
            svp_simple_008_001_global_array[__cs_l_main_p_1 + __cs_l_main_q_1] = 0x09;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else    {
            assert(svp_simple_008_001_global_array[40] == 0x09);
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;} else    {
            /*enable_isr(1);*/
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else    {
            svp_simple_008_001_global_array[40] = 0x01;
    }}
    {
        static int __cs_l_svp_simple_008_001_func_1_reader1_1;
        if (__cs_simulate == 0 && __cs_pc_0 == 6) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 6; __cs_simulate = 2;} else        {
                __cs_init_scalar(&__cs_l_svp_simple_008_001_func_1_reader1_1, sizeof(int));
        }}
        static int __cs_l_svp_simple_008_001_func_1_reader2_1;
        if (__cs_simulate == 0 && __cs_pc_0 == 7) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 7; __cs_simulate = 2;} else        {
                __cs_init_scalar(&__cs_l_svp_simple_008_001_func_1_reader2_1, sizeof(int));
        }}
        static int __cs_l_svp_simple_008_001_func_1_i_1;
        if (__cs_simulate == 1)
        {
                __cs_l_svp_simple_008_001_func_1_i_1 = 1;
        }
        static int __cs_l_svp_simple_008_001_func_1_j_1;
        if (__cs_simulate == 1)
        {
                __cs_l_svp_simple_008_001_func_1_j_1 = 2;
        }
        static int __cs_l_svp_simple_008_001_func_1_p_1;
        if (__cs_simulate == 1)
        {
                __cs_l_svp_simple_008_001_func_1_p_1 = 10;
        }
        static int __cs_l_svp_simple_008_001_func_1_q_1;
        if (__cs_simulate == 1)
        {
                __cs_l_svp_simple_008_001_func_1_q_1 = 30;
        }
        if (__cs_simulate == 0 && __cs_pc_0 == 8) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 8; __cs_simulate = 2;} else        {
                __cs_l_svp_simple_008_001_func_1_reader1_1 = svp_simple_008_001_global_array[(__cs_l_svp_simple_008_001_func_1_i_1 * 20) + (__cs_l_svp_simple_008_001_func_1_j_1 * 10)];
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 9) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 9; __cs_simulate = 2;} else        {
                __cs_l_svp_simple_008_001_func_1_reader2_1 = svp_simple_008_001_global_array[__cs_l_svp_simple_008_001_func_1_p_1 + __cs_l_svp_simple_008_001_func_1_q_1];
        }}
        __exit__svp_simple_008_001_func_1_1:;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 10))
    {
        __cs_pc_0 = 10;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_008_001_isr_1 */
void svp_simple_008_001_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    static int __cs_l_svp_simple_008_001_isr_1_k_1;
                    __cs_l_svp_simple_008_001_isr_1_k_1 = 0;
                    __begin_svp_simple_008_001_isr_1_loop_0:
;
                    ;;
                    int loop_1_IOVar1;
                    int loop_1_block_1;
                    int t_1 = 0;
                while ((t_1 < 2) && (__cs_l_svp_simple_008_001_isr_1_k_1 < 100))
    {
                        loop_1_IOVar1 = __cs_l_svp_simple_008_001_isr_1_k_1;
                        loop_1_block_1 = __VERIFIER_nondet_int();
                        __cs_l_svp_simple_008_001_isr_1_k_1 = loop_1_IOVar1 + (1 * loop_1_block_1);
                        __CPROVER_assume(loop_1_block_1 >= 0);
                        __CPROVER_assume(__cs_l_svp_simple_008_001_isr_1_k_1 < 100);
                {
                            svp_simple_008_001_global_array[__cs_l_svp_simple_008_001_isr_1_k_1] = 0x05;
                            __cs_l_svp_simple_008_001_isr_1_k_1++;
                }
                        t_1++;
    }
            __CPROVER_assume(!(__cs_l_svp_simple_008_001_isr_1_k_1 < 100));
                    __end_svp_simple_008_001_isr_1_loop_0:
;
                    ;;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 6))
    {
        __cs_pc_1 = 6;
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
        svp_simple_008_001_isr_1();
        if (__cs_pc_1 == 6) __cs_pc_1 = 0;
    }
  }
}
