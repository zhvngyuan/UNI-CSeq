// Main task
unsigned __CPROVER_bitvector[5] __cs_pc_0;
// svp_simple_019_001_isr_1
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
int svp_simple_019_001_global_condition1 = 1;
int svp_simple_019_001_global_condiiton2 = 1;
int svp_simple_019_001_global_condition3 = 1;
int svp_simple_019_001_global_para1;
int svp_simple_019_001_global_para2;
int svp_simple_019_001_global_para3;
int svp_simple_019_001_global_var1;
int svp_simple_019_001_global_var2;
/* Simulate original main */
void main_task()
{
    static int __cs_l_main_reader1_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_reader1_1, sizeof(int));
    }}
    static int __cs_l_main_reader2_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_reader2_1, sizeof(int));
    }}
    static int __cs_l_main_reader3_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_reader3_1, sizeof(int));
    }}
    static int __cs_l_main_reader4_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_reader4_1, sizeof(int));
    }}
    static int __cs_l_main_reader5_1;
    if (__cs_simulate == 0 && __cs_pc_0 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 4; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_main_reader5_1, sizeof(int));
    }}
    {
        if (__cs_simulate == 0 && __cs_pc_0 == 5) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 5; __cs_simulate = 2;} else        {
                /*enable_isr(-1);*/
        }}
        __exit__init_1:;
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 6; __cs_simulate = 2;} else    {
            svp_simple_019_001_global_para1 = __VERIFIER_nondet_int() % 10;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 7) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 7; __cs_simulate = 2;} else    {
            svp_simple_019_001_global_para2 = __VERIFIER_nondet_int() % 10;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 8) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 8; __cs_simulate = 2;} else    {
            svp_simple_019_001_global_para3 = __VERIFIER_nondet_int() % 10;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 9) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 9; __cs_simulate = 2;} else    {
            svp_simple_019_001_global_var1 = __VERIFIER_nondet_int();
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 10) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 10; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 11) || (__cs_simulate == 1 && ((svp_simple_019_001_global_para1 + svp_simple_019_001_global_para3) > svp_simple_019_001_global_para2)))
    {
                if (__cs_simulate == 0 && __cs_pc_0 == 11) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 11; __cs_simulate = 2;} else                {
                        __cs_l_main_reader1_1 = svp_simple_019_001_global_var2;
                }}
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 12) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 12; __cs_simulate = 2;} else    {
            __cs_l_main_reader2_1 = svp_simple_019_001_global_var2;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 13) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 13; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 14) || (__cs_simulate == 1 && ((svp_simple_019_001_global_condition1 == 1) && (svp_simple_019_001_global_condiiton2 == 1))))
    {
                if (__cs_simulate == 0 && __cs_pc_0 == 14) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 14; __cs_simulate = 2;} else                {
                        __cs_l_main_reader3_1 = svp_simple_019_001_global_var1;
                }}
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 15) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 15; __cs_simulate = 2;} else    {
            /*disable_isr(1);*/
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 16) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 16; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 18) || (__cs_simulate == 1 && ((svp_simple_019_001_global_condition1 == 1) && (svp_simple_019_001_global_condition3 == 1))))
    {
                if (__cs_simulate == 0 && __cs_pc_0 == 17) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 17; __cs_simulate = 2;} else                {
                        /*enable_isr(1);*/
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 18) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 18; __cs_simulate = 2;} else                {
                        __cs_l_main_reader4_1 = svp_simple_019_001_global_var1;
                }}
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 19) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 19; __cs_simulate = 2;} else    {
            /*disable_isr(1);*/
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 20) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 20; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 21) || (__cs_simulate == 1 && ((svp_simple_019_001_global_condiiton2 == 1) && (svp_simple_019_001_global_condition3 == 0))))
    {
                if (__cs_simulate == 0 && __cs_pc_0 == 21) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 21; __cs_simulate = 2;} else                {
                        __cs_l_main_reader5_1 = svp_simple_019_001_global_var1;
                }}
    }
    if (__cs_simulate == 0 && __cs_pc_0 == 22) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 22; __cs_simulate = 2;} else    {
            /*enable_isr(1);*/
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 23) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 23; __cs_simulate = 2;} else    {
            assert(__cs_l_main_reader4_1 == __cs_l_main_reader5_1);
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 24))
    {
        __cs_pc_0 = 24;
        __cs_simulate = 2;
    }
}
/* Simulate svp_simple_019_001_isr_1 */
void svp_simple_019_001_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    if ((svp_simple_019_001_global_para1 + svp_simple_019_001_global_para3) < svp_simple_019_001_global_para2)
    {
                        svp_simple_019_001_global_var2 = 0x55;
    }
                    svp_simple_019_001_global_condition3 = 1;
                    svp_simple_019_001_global_var1 = 0x01;
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
        svp_simple_019_001_isr_1();
        if (__cs_pc_1 == 4) __cs_pc_1 = 0;
    }
  }
}
