// Main task
unsigned __CPROVER_bitvector[3] __cs_pc_0;
// generate_isr_1
unsigned __CPROVER_bitvector[3] __cs_pc_1;
// process_isr_2
unsigned __CPROVER_bitvector[3] __cs_pc_2;
// dispose_isr_3
unsigned __CPROVER_bitvector[3] __cs_pc_3;
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
int __cs_disable_isr_2;
int __cs_disable_isr_3;
/* Global variables */
int A;
int B;
/* Simulate process_isr_2 */
void process_isr_2()
{
    __begin_process_isr_2_loop_0:;
    if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_2 <= 5) || ((__cs_simulate == 1) && (1)))
    {
                if (__cs_simulate == 0 && __cs_pc_2 == 1) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 1; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_2 <= 5) || (__cs_simulate == 1 && (A > 0)))
                {
                            if (__cs_simulate == 0 && __cs_pc_2 == 2) __cs_simulate = 1;
                            if (__cs_simulate == 1){
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 2; __cs_simulate = 2;} else                            {
                                    A++;
                            }}
                            if (__cs_simulate == 0 && __cs_pc_2 == 3) __cs_simulate = 1;
                            if (__cs_simulate == 1){
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 3; __cs_simulate = 2;} else                            {
                                    B = A;
                            }}
                            if (__cs_simulate == 0 && __cs_pc_2 == 4) __cs_simulate = 1;
                            if (__cs_simulate == 1){
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 4; __cs_simulate = 2;} else                            {
                                    B--;
                            }}
                            if (__cs_simulate == 0 && __cs_pc_2 == 5) __cs_simulate = 1;
                            if (__cs_simulate == 1){
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 5; __cs_simulate = 2;} else                            {
                                    A--;
                            }}
                }
    }
    __end_process_isr_2_loop_0:;
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 6))
    {
        __cs_pc_2 = 6;
        __cs_simulate = 2;
    }
}
/* Simulate original main */
int main_task()
{
    static int __cs_l_main_i_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_i_1, sizeof(int));
    }}
    static int __cs_l_main_j_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_j_1, sizeof(int));
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else    {
            A = 5;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else    {
            B = 5;
    }}
    if (__cs_simulate == 1)
    {
            __cs_l_main_i_1 = 0;
    }
    __begin_main_loop_0:;
    if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_0 <= 5) || ((__cs_simulate == 1) && (__cs_l_main_i_1 < 10)))
    {
                if (__cs_simulate == 1)
                {
                        __cs_l_main_j_1 = __cs_l_main_i_1;
                }
                if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else                {
                        assert(A == B);
                }}
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
/* Simulate generate_isr_1 */
void generate_isr_1()
{
    static int __cs_l_generate_isr_1_i_1;
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_generate_isr_1_i_1, sizeof(int));
    }}
    if (__cs_simulate == 1)
    {
            __cs_l_generate_isr_1_i_1 = 1;
    }
    __begin_generate_isr_1_loop_0:;
    if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;}
    while ((__cs_simulate == 0 && __cs_pc_1 <= 3) || ((__cs_simulate == 1) && (__cs_l_generate_isr_1_i_1 < 100)))
    {
                if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;} else                {
                        A = __cs_l_generate_isr_1_i_1;
                }}
                if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;} else                {
                        A = 5;
                }}
                if (__cs_simulate == 1)
                {
                        __cs_l_generate_isr_1_i_1++;
                }
    }
    __end_generate_isr_1_loop_0:;
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 4))
    {
        __cs_pc_1 = 4;
        __cs_simulate = 2;
    }
}
/* Simulate dispose_isr_3 */
void dispose_isr_3()
{
        if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else 
{
                    static int __cs_l_dispose_isr_3_p_1;
            __cs_init_scalar(&__cs_l_dispose_isr_3_p_1, sizeof(int));
                    __begin_dispose_isr_3_loop_0:
;
                    ;;
                while (1)
    {
                                                if (B > 0)
                {
                            __cs_l_dispose_isr_3_p_1 = B;
                }
    }
                    __end_dispose_isr_3_loop_0:
;
                    ;;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 4))
    {
        __cs_pc_3 = 4;
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
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 6)&&(__cs_pc_1 == 0 || __cs_pc_1 == 4)) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 6)&&__cs_disable_isr_1 != 1) {
        generate_isr_1();
        if (__cs_pc_1 == 4) __cs_pc_1 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_2 != 1) {
        process_isr_2();
        if (__cs_pc_2 == 6) __cs_pc_2 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_3 != 1) {
        dispose_isr_3();
        if (__cs_pc_3 == 4) __cs_pc_3 = 0;
    }
  }
}
