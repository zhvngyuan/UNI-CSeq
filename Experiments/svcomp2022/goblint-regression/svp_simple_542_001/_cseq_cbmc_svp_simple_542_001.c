// Main task
unsigned __CPROVER_bitvector[3] __cs_pc_0;
// svp_simple_542_001_isr_1
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
int myglobal;
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            myglobal = 0;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else    {
            assert(myglobal == 0);
    }}
    static int __retval__f_2;
    {
        static int __cs_l_f_x;
        if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else        {
                __cs_l_f_x = myglobal;
        }}
        if (__cs_simulate == 1)
        {
                __retval__f_2 = 5;
        }
        if (__cs_simulate == 1)
        {
            goto __exit__f_2;
        }
        __exit__f_2:;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else    {
            myglobal = __retval__f_2;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;} else    {
            assert(myglobal == 5);
    }}
    static int __retval__f_3;
    {
        static int __cs_l_f_x;
        if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else        {
                __cs_l_f_x = myglobal;
        }}
        if (__cs_simulate == 1)
        {
                __retval__f_3 = 5;
        }
        if (__cs_simulate == 1)
        {
            goto __exit__f_3;
        }
        __exit__f_3:;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 6; __cs_simulate = 2;} else    {
            myglobal = __retval__f_3;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 7))
    {
        __cs_pc_0 = 7;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_542_001_isr_1 */
void svp_simple_542_001_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    static int __cs_l_svp_simple_542_001_isr_1_tmp_1;
            __cs_init_scalar(&__cs_l_svp_simple_542_001_isr_1_tmp_1, sizeof(int));
                    static int __retval__f_1;
    {
                        static int __cs_l_f_x;
                        __cs_l_f_x = myglobal;
                        __retval__f_1 = 5;
                        goto __exit__f_1;;
                        __exit__f_1:
;
                        ;;
    }
                    myglobal = __retval__f_1;
                    if (myglobal == 5)
    {
                        __cs_l_svp_simple_542_001_isr_1_tmp_1 = 1;
    }
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 4))
    {
        __cs_pc_1 = 4;
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
        svp_simple_542_001_isr_1();
        if (__cs_pc_1 == 4) __cs_pc_1 = 0;
    }
  }
}
