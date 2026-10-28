// Main task
unsigned int __cs_pc_0;
// svp_simple_303_001_isr_1
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
extern void abort(void);
int pdev;
/* Simulate original main */
int main_task()
{
    static _Bool __cs_l_main___if_cond_0_1;
    static int __retval__module_init_1;
    {
        if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else        {
                pdev = 1;
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else        {
                if (!(pdev == 1)) __cseq_error();
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;}
        if ((__cs_simulate == 0 && __cs_pc_0 <= 2) || (__cs_simulate == 1 && (__VERIFIER_nondet_int())))
        {
                    if (__cs_simulate == 1)
                    {
                            __retval__module_init_1 = 0;
                    }
                    if (__cs_simulate == 1)
                    {
                        goto __exit__module_init_1;
                    }
        }
        if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else        {
                pdev = 3;
        }}
        if (__cs_simulate == 1)
        {
                __retval__module_init_1 = -1;
        }
        if (__cs_simulate == 1)
        {
            goto __exit__module_init_1;
        }
        __exit__module_init_1:;
    }
    if (__cs_simulate == 1)
    {
            __cs_l_main___if_cond_0_1 = __retval__module_init_1 != 0;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 7) || (__cs_simulate == 1 && (__cs_l_main___if_cond_0_1)))
    {
                {
                    static void *__cs_l_module_exit_status_1;
                    if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
                    if (__cs_simulate == 1){
                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else                    {
                            __cs_init_scalar(&__cs_l_module_exit_status_1, sizeof(void *));
                    }}
                    if (__cs_simulate == 0 && __cs_pc_0 == 6) __cs_simulate = 1;
                    if (__cs_simulate == 1){
                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 6; __cs_simulate = 2;} else                    {
                            pdev = 4;
                    }}
                    if (__cs_simulate == 0 && __cs_pc_0 == 7) __cs_simulate = 1;
                    if (__cs_simulate == 1){
                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 7; __cs_simulate = 2;} else                    {
                            pdev = 5;
                    }}
                    __exit__module_exit_1:;
                }
    }
    {
        static void *__cs_l_module_exit_status_1;
        if (__cs_simulate == 0 && __cs_pc_0 == 8) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 8; __cs_simulate = 2;} else        {
                __cs_init_scalar(&__cs_l_module_exit_status_1, sizeof(void *));
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 9) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 9; __cs_simulate = 2;} else        {
                pdev = 4;
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 10) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 10; __cs_simulate = 2;} else        {
                pdev = 5;
        }}
        __exit__module_exit_2:;
    }
    {
        static void *__cs_l_module_exit_status_1;
        if (__cs_simulate == 0 && __cs_pc_0 == 11) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 11; __cs_simulate = 2;} else        {
                __cs_init_scalar(&__cs_l_module_exit_status_1, sizeof(void *));
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 12) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 12; __cs_simulate = 2;} else        {
                pdev = 4;
        }}
        if (__cs_simulate == 0 && __cs_pc_0 == 13) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 13; __cs_simulate = 2;} else        {
                pdev = 5;
        }}
        __exit__module_exit_3:;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 14))
    {
        __cs_pc_0 = 14;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_303_001_isr_1 */
void svp_simple_303_001_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    pdev = 6;
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
        svp_simple_303_001_isr_1();
        if (__cs_pc_1 == 1) __cs_pc_1 = 0;
    }
  }
}
