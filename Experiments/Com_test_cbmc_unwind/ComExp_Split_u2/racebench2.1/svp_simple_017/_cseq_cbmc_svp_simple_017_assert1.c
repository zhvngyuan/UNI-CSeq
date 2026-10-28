// Main task
unsigned __CPROVER_bitvector[4] __cs_pc_0;
// svp_simple_017_001_isr_1
unsigned __CPROVER_bitvector[2] __cs_pc_1;
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
int svp_simple_017_001_global_var;
int svp_simple_017_001_local_array[10000];
/* Simulate svp_simple_017_001_isr_1 */
void svp_simple_017_001_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    svp_simple_017_001_global_var = 5000;
            assert(svp_simple_017_001_global_var == 50);
                    svp_simple_017_001_local_array[5000] = 0;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 3))
    {
        __cs_pc_1 = 3;
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
                /*enable_isr(-1);*/
                __cs_disable_isr_1 = 0;
                __cs_disable_isr_0 = 0;
        }}
        __exit__init_1:;
    }
    static int __cs_l_main_i_1;
    if (__cs_simulate == 1)
    {
            __cs_l_main_i_1 = 0;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else    {
            svp_simple_017_001_global_var = 0;
    }}
    __begin_main_loop_0:;
    int loop_1_IOVar1;
    int loop_1_block_1;
    int t_1 = 0;
    if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_0 <= 8) || ((__cs_simulate == 1) && ((t_1 < 2) && (svp_simple_017_001_global_var < 10000))))
    {
                if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else                {
                        loop_1_IOVar1 = svp_simple_017_001_global_var;
                }}
                if (__cs_simulate == 1)
                {
                        loop_1_block_1 = __VERIFIER_nondet_int();
                }
                if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;} else                {
                        svp_simple_017_001_global_var = loop_1_IOVar1 + (1 * loop_1_block_1);
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else                {
                        __CPROVER_assume(loop_1_block_1 >= 0);
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 6) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 6; __cs_simulate = 2;} else                {
                        __CPROVER_assume(svp_simple_017_001_global_var < 10000);
                }}
                {
                    if (__cs_simulate == 0 && __cs_pc_0 == 7) __cs_simulate = 1;
                    if (__cs_simulate == 1){
                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 7; __cs_simulate = 2;} else                    {
                            svp_simple_017_001_local_array[svp_simple_017_001_global_var] = __cs_l_main_i_1++;
                    }}
                    if (__cs_simulate == 0 && __cs_pc_0 == 8) __cs_simulate = 1;
                    if (__cs_simulate == 1){
                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 8; __cs_simulate = 2;} else                    {
                            svp_simple_017_001_global_var++;
                    }}
                }
                if (__cs_simulate == 1)
                {
                        t_1++;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 9) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 9; __cs_simulate = 2;} else    {
            __CPROVER_assume(!(svp_simple_017_001_global_var < 10000));
    }}
    __end_main_loop_0:;
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 10))
    {
        __cs_pc_0 = 10;
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
        svp_simple_017_001_isr_1();
        if (__cs_pc_1 == 3) __cs_pc_1 = 0;
    }
  }
}
