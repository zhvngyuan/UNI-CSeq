// Main task
unsigned int __cs_pc_0;
// svp_simple_702_001_isr_1
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
int plus(int __cs_l__a, int __cs_l__b);
int sr_plus(int __cs_l__a, int __cs_l__b);
int g;
int h;
int i;
/* Simulate svp_simple_702_001_isr_1 */
void svp_simple_702_001_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    static int __cs_l_svp_simple_702_001_isr_1_x_1;
                    __cs_l_svp_simple_702_001_isr_1_x_1 = __VERIFIER_nondet_int();
                    static int __cs_l_svp_simple_702_001_isr_1_y_1;
                    __cs_l_svp_simple_702_001_isr_1_y_1 = __VERIFIER_nondet_int();
                    static int __cs_l_svp_simple_702_001_isr_1_z_1;
                    __cs_l_svp_simple_702_001_isr_1_z_1 = __VERIFIER_nondet_int();
                    if (__cs_l_svp_simple_702_001_isr_1_x_1 < 1000)
    {
                        __cs_l_svp_simple_702_001_isr_1_x_1 = g;
                        __cs_l_svp_simple_702_001_isr_1_y_1 = h;
                        static int __retval__plus_1;
                {
                            static int __cs_l_plus_a;
                            __cs_l_plus_a = __cs_l_svp_simple_702_001_isr_1_x_1;
                            static int __cs_l_plus_b;
                            __cs_l_plus_b = 31;
                    {
                                static int __cs_l_assume_abort_if_not_cond;
                                __cs_l_assume_abort_if_not_cond = (__cs_l_plus_b >= 0) || (__cs_l_plus_a >= ((-2147483648) - __cs_l_plus_b));
                                                                        if (!__cs_l_assume_abort_if_not_cond)
                        {
                                            abort();
                        }
                                __exit__assume_abort_if_not_1:
;
                                ;;
                    }
                    {
                                static int __cs_l_assume_abort_if_not_cond;
                                __cs_l_assume_abort_if_not_cond = (__cs_l_plus_b <= 0) || (__cs_l_plus_a <= (2147483647 - __cs_l_plus_b));
                                                                        if (!__cs_l_assume_abort_if_not_cond)
                        {
                                            abort();
                        }
                                __exit__assume_abort_if_not_2:
;
                                ;;
                    }
                            __retval__plus_1 = __cs_l_plus_a + __cs_l_plus_b;
                            goto __exit__plus_1;;
                            __exit__plus_1:
;
                            ;;
                }
                        i = __retval__plus_1;
                        __cs_l_svp_simple_702_001_isr_1_z_1 = i;
                        if (!(__cs_l_svp_simple_702_001_isr_1_z_1 >= __cs_l_svp_simple_702_001_isr_1_x_1)) __cseq_error();
    }
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 11))
    {
        __cs_pc_1 = 11;
        __cs_simulate = 2;
    }
}
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            g = 0;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else    {
            h = 0;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else    {
            i = 0;
    }}
    static int __cs_l_main_x_1;
    if (__cs_simulate == 1)
    {
            __cs_l_main_x_1 = __VERIFIER_nondet_int();
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 12) || (__cs_simulate == 1 && (__cs_l_main_x_1 > (-1000))))
    {
                if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;} else                {
                        i = 11;
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else                {
                        g = __cs_l_main_x_1;
                }}
                static int __retval__plus_2;
                {
                    static int __cs_l_plus_a;
                    if (__cs_simulate == 1)
                    {
                            __cs_l_plus_a = __cs_l_main_x_1;
                    }
                    static int __cs_l_plus_b;
                    if (__cs_simulate == 1)
                    {
                            __cs_l_plus_b = -17;
                    }
                    {
                        static int __cs_l_assume_abort_if_not_cond;
                        if (__cs_simulate == 1)
                        {
                                __cs_l_assume_abort_if_not_cond = (__cs_l_plus_b >= 0) || (__cs_l_plus_a >= ((-2147483648) - __cs_l_plus_b));
                        }
                        if (__cs_simulate == 0 && __cs_pc_0 == 6) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 6; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_0 <= 7) || (__cs_simulate == 1 && (!__cs_l_assume_abort_if_not_cond)))
                        {
                                    if (__cs_simulate == 0 && __cs_pc_0 == 7) __cs_simulate = 1;
                                    if (__cs_simulate == 1){
                                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 7; __cs_simulate = 2;} else                                    {
                                            abort();
                                    }}
                        }
                        __exit__assume_abort_if_not_3:;
                    }
                    {
                        static int __cs_l_assume_abort_if_not_cond;
                        if (__cs_simulate == 1)
                        {
                                __cs_l_assume_abort_if_not_cond = (__cs_l_plus_b <= 0) || (__cs_l_plus_a <= (2147483647 - __cs_l_plus_b));
                        }
                        if (__cs_simulate == 0 && __cs_pc_0 == 8) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 8; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_0 <= 9) || (__cs_simulate == 1 && (!__cs_l_assume_abort_if_not_cond)))
                        {
                                    if (__cs_simulate == 0 && __cs_pc_0 == 9) __cs_simulate = 1;
                                    if (__cs_simulate == 1){
                                    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 9; __cs_simulate = 2;} else                                    {
                                            abort();
                                    }}
                        }
                        __exit__assume_abort_if_not_4:;
                    }
                    if (__cs_simulate == 1)
                    {
                            __retval__plus_2 = __cs_l_plus_a + __cs_l_plus_b;
                    }
                    if (__cs_simulate == 1)
                    {
                        goto __exit__plus_2;
                    }
                    __exit__plus_2:;
                }
                if (__cs_simulate == 0 && __cs_pc_0 == 10) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 10; __cs_simulate = 2;} else                {
                        h = __retval__plus_2;
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 11) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 11; __cs_simulate = 2;} else                {
                        h = __cs_l_main_x_1;
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 12) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 12; __cs_simulate = 2;} else                {
                        i = 3;
                }}
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 13))
    {
        __cs_pc_0 = 13;
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
        svp_simple_702_001_isr_1();
        if (__cs_pc_1 == 11) __cs_pc_1 = 0;
    }
  }
}
