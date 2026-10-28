// Main task
unsigned int __cs_pc_0;
// svp_simple_304_001_isr_1
unsigned int __cs_pc_1;
// svp_simple_304_001_isr_2
unsigned int __cs_pc_2;
// svp_simple_304_001_isr_3
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
int __cs_disable_isr_2;
int __cs_disable_isr_3;
/* Global variables */
extern void abort(void);
int data;
/* Simulate svp_simple_304_001_isr_2 */
void svp_simple_304_001_isr_2()
{
    static int __cs_l_svp_simple_304_001_isr_2_tmp_1;
    if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else    {
            __cs_l_svp_simple_304_001_isr_2_tmp_1 = data + 2;
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 1; __cs_simulate = 2;} else    {
            data = __cs_l_svp_simple_304_001_isr_2_tmp_1;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 2))
    {
        __cs_pc_2 = 2;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_304_001_isr_3 */
void svp_simple_304_001_isr_3()
{
        if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else 
{
                    static int __cs_l_svp_simple_304_001_isr_3_tmp1_1;
            __cs_init_scalar(&__cs_l_svp_simple_304_001_isr_3_tmp1_1, sizeof(int));
                    __cs_l_svp_simple_304_001_isr_3_tmp1_1++;
            if (!(data < 3)) __cseq_error();
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 2))
    {
        __cs_pc_3 = 2;
        __cs_simulate = 2;
    }
}
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            data = 0;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 1))
    {
        __cs_pc_0 = 1;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_304_001_isr_1 */
void svp_simple_304_001_isr_1()
{
    static int __cs_l_svp_simple_304_001_isr_1_tmp_1;
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            __cs_l_svp_simple_304_001_isr_1_tmp_1 = data + 1;
    }}
    if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;} else    {
            data = __cs_l_svp_simple_304_001_isr_1_tmp_1;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 2))
    {
        __cs_pc_1 = 2;
        __cs_simulate = 2;
    }
}
/* main function (scheduler) */
int main()
{
  __cs_simulate = 0;
  __cs_pc_0 = 0;
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
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 2)&&(__cs_pc_1 == 0 || __cs_pc_1 == 2)) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 2)&&__cs_disable_isr_1 != 1) {
        svp_simple_304_001_isr_1();
        if (__cs_pc_1 == 2) __cs_pc_1 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_2 != 1) {
        svp_simple_304_001_isr_2();
        if (__cs_pc_2 == 2) __cs_pc_2 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_3 != 1) {
        svp_simple_304_001_isr_3();
        if (__cs_pc_3 == 2) __cs_pc_3 = 0;
    }
  }
}
