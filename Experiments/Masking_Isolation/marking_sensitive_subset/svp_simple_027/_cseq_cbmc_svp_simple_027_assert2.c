// Main task
unsigned __CPROVER_bitvector[3] __cs_pc_0;
// svp_simple_027_001_isr_1
unsigned __CPROVER_bitvector[1] __cs_pc_1;
// svp_simple_027_001_isr_2
unsigned __CPROVER_bitvector[1] __cs_pc_2;
// svp_simple_027_001_isr_3
unsigned __CPROVER_bitvector[2] __cs_pc_3;
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
void svp_simple_027_001_init();
int svp_simple_027_001_gloable_var;
/* Simulate svp_simple_027_001_isr_1 */
void svp_simple_027_001_isr_1()
{
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            svp_simple_027_001_gloable_var++;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 1))
    {
        __cs_pc_1 = 1;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_027_001_isr_2 */
void svp_simple_027_001_isr_2()
{
    if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else    {
            svp_simple_027_001_gloable_var += 2;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 1))
    {
        __cs_pc_2 = 1;
        __cs_simulate = 2;
    }
}
/* Simulate original main */
int main_task()
{
    {
        if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else        {
                svp_simple_027_001_gloable_var = 15;
        }}
        {
            if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
            if (__cs_simulate == 1){
            if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else            {
                    /*enable_isr(-1);*/
                    __cs_disable_isr_1 = 0;
                    __cs_disable_isr_2 = 0;
                    __cs_disable_isr_0 = 0;
                    __cs_disable_isr_3 = 0;
            }}
            __exit__init_1:;
        }
        __exit__svp_simple_027_001_init_1:;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else    {
            /*disable_isr(-1);*/
            __cs_disable_isr_1 = 1;
            __cs_disable_isr_2 = 1;
            __cs_disable_isr_0 = 1;
            __cs_disable_isr_3 = 1;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else    {
            /*enable_isr(1);*/
            __cs_disable_isr_1 = 0;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 5) || (__cs_simulate == 1 && (svp_simple_027_001_gloable_var > 12)))
    {
                if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else                {
                        svp_simple_027_001_gloable_var = 0;
                }}
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 6))
    {
        __cs_pc_0 = 6;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_027_001_isr_3 */
void svp_simple_027_001_isr_3()
{
        if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else 
{
                    svp_simple_027_001_gloable_var += 3;
                    svp_simple_027_001_gloable_var = 0;
            assert(svp_simple_027_001_gloable_var == 0);
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 3))
    {
        __cs_pc_3 = 3;
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
    if ((__cs_pc_1 == 0 || __cs_pc_1 == 1)&&(__cs_pc_2 == 0 || __cs_pc_2 == 1)) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 1)&&__cs_disable_isr_1 != 1) {
        svp_simple_027_001_isr_1();
        if (__cs_pc_1 == 1) __cs_pc_1 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_2 != 1) {
        svp_simple_027_001_isr_2();
        if (__cs_pc_2 == 1) __cs_pc_2 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_3 != 1) {
        svp_simple_027_001_isr_3();
        if (__cs_pc_3 == 3) __cs_pc_3 = 0;
    }
  }
}
