// Main task
unsigned int __cs_pc_0;
// svp_simple_643_001_isr1
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
int g;
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            g = 0;
    }}
    static int __retval__pqueue_init_1;
    {
        if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else        {
                g = 0;
        }}
        if (__cs_simulate == 1)
        {
                __retval__pqueue_init_1 = 0;
        }
        if (__cs_simulate == 1)
        {
            goto __exit__pqueue_init_1;
        }
        __exit__pqueue_init_1:;
    }
    static int __cs_l_main_num_1;
    if (__cs_simulate == 1)
    {
            __cs_l_main_num_1 = 5;
    }
    static int __cs_l_main_i_1;
    if (__cs_simulate == 1)
    {
            __cs_l_main_i_1 = 1;
    }
    __begin_main_loop_0:;
    if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_0 <= 5) || ((__cs_simulate == 1) && (__cs_l_main_i_1 < 5)))
    {
                static int __retval__pqueue_put_1;
                {
                    if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;}
                    if ((__cs_simulate == 0 && __cs_pc_0 <= 5) || (__cs_simulate == 1 && (g < 1000)))
                    {
                                static int __cs_l_pqueue_put_tmp_1;
                                if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;} else                                {
                                        __cs_l_pqueue_put_tmp_1 = g + 1;
                                }}
                                if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
                                if (__cs_simulate == 1){
                                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else                                {
                                        g = __cs_l_pqueue_put_tmp_1;
                                }}
                    }
                    if (__cs_simulate == 1)
                    {
                            __retval__pqueue_put_1 = 1;
                    }
                    if (__cs_simulate == 1)
                    {
                        goto __exit__pqueue_put_1;
                    }
                    __exit__pqueue_put_1:;
                }
                if (__cs_simulate == 1)
                {
                        __cs_l_main_i_1++;
                }
    }
    __end_main_loop_0:;
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 6))
    {
        __cs_pc_0 = 6;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_643_001_isr1 */
void svp_simple_643_001_isr1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    static int __retval__sr_pqueue_get_1;
    {
                        static int __cs_l_sr_pqueue_get_got_1;
                        __cs_l_sr_pqueue_get_got_1 = 0;
                                if (g > 0)
        {
                            g--;
                            __cs_l_sr_pqueue_get_got_1 = 1;
        }
                        __retval__sr_pqueue_get_1 = __cs_l_sr_pqueue_get_got_1;
                        goto __exit__sr_pqueue_get_1;;
                        __exit__sr_pqueue_get_1:
;
                        ;;
    }
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
        svp_simple_643_001_isr1();
        if (__cs_pc_1 == 3) __cs_pc_1 = 0;
    }
  }
}
