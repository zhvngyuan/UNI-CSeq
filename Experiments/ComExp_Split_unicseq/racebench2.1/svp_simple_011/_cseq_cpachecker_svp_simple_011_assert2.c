// Main task
unsigned int __cs_pc_0;
// svp_simple_011_001_isr_1
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
int svp_simple_011_001_global_var1;
int svp_simple_011_001_global_var2;
int svp_simple_011_001_global_var3;
int *svp_simple_011_001_u;
/* Simulate original main */
void main_task()
{
    {
        if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else        {
                /*enable_isr(-1);*/
                __cs_disable_isr_0 = 0;
                __cs_disable_isr_1 = 0;
        }}
        __exit__init_1:;
    }
    static int *__cs_l_main_p_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else    {
            __cs_l_main_p_1 = &svp_simple_011_001_global_var1;
    }}
    static int *__cs_l_main_q_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else    {
            __cs_l_main_q_1 = &svp_simple_011_001_global_var1;
    }}
    if (__cs_simulate == 1)
    {
            *__cs_l_main_p_1 = 0x01;
    }
    if (__cs_simulate == 1)
    {
            *__cs_l_main_q_1 = 0x02;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else    {
            svp_simple_011_001_u = &svp_simple_011_001_global_var2;
    }}
    if (__cs_simulate == 1)
    {
            *svp_simple_011_001_u = 0x01;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;} else    {
            svp_simple_011_001_u = &svp_simple_011_001_global_var3;
    }}
    if (__cs_simulate == 1)
    {
            *svp_simple_011_001_u = 0x02;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else    {
            if (!((*svp_simple_011_001_u) == 0x02)) __cseq_error();
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 6))
    {
        __cs_pc_0 = 6;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_011_001_isr_1 */
void svp_simple_011_001_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    static int __cs_l_svp_simple_011_001_isr_1_reader1_1;
            __cs_init_scalar(&__cs_l_svp_simple_011_001_isr_1_reader1_1, sizeof(int));
                    static int __cs_l_svp_simple_011_001_isr_1_reader2_1;
            __cs_init_scalar(&__cs_l_svp_simple_011_001_isr_1_reader2_1, sizeof(int));
                    static int *__cs_l_svp_simple_011_001_isr_1_m_1;
                    __cs_l_svp_simple_011_001_isr_1_m_1 = &svp_simple_011_001_global_var1;
                    __cs_l_svp_simple_011_001_isr_1_reader1_1 = *__cs_l_svp_simple_011_001_isr_1_m_1;
                    __cs_l_svp_simple_011_001_isr_1_reader2_1 = *svp_simple_011_001_u;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 3))
    {
        __cs_pc_1 = 3;
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
        svp_simple_011_001_isr_1();
        if (__cs_pc_1 == 3) __cs_pc_1 = 0;
    }
  }
}
