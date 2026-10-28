// Main task
unsigned int __cs_pc_0;
// isr_1
unsigned int __cs_pc_1;
// isr_2
unsigned int __cs_pc_2;
// isr_3
unsigned int __cs_pc_3;
int __cs_simulate;
/* Predefined functions type 1 */
#define assume(X) __VERIFIER_assume(X)
//Already defined
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
int g_var;
int g_array[10];
int g_flag;
int x;
int y;
int z;
/* Simulate original main */
void main_task()
{
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            x = 1;
    }}
    if (__cs_simulate == 0 && __cs_pc_0 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_0 = 1; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_0 <= 3) || (__cs_simulate == 1 && (y >= 10)))
    {
                if (__cs_simulate == 0 && __cs_pc_0 == 2) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 2; __cs_simulate = 2;} else                {
                        z = 1;
                }}
                if (__cs_simulate == 0 && __cs_pc_0 == 3) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 3; __cs_simulate = 2;} else                {
                        if (!(z == 1)) __VERIFIER_error();
                }}
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 4))
    {
        __cs_pc_0 = 4;
        __cs_simulate = 2;
    }
}
/* Simulate isr_2 */
void isr_2()
{
    if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else    {
            y = 5;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 1))
    {
        __cs_pc_2 = 1;
        __cs_simulate = 2;
    }
}
/* Simulate isr_3 */
void isr_3()
{
        if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else 
{
                    y = 1;
                    x = 2;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 2))
    {
        __cs_pc_3 = 2;
        __cs_simulate = 2;
    }
}
/* Simulate isr_1 */
void isr_1()
{
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            g_flag = 1;
    }}
    if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;} else    {
            y++;
    }}
    if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;} else    {
            z = 4;
    }}
    if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;} else    {
            g_var = 1;
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
  __cs_pc_2 = 0;
  __cs_pc_3 = 0;
  __cs_disable_isr_0 = 0;
  __cs_disable_isr_1 = 0;
  __cs_disable_isr_2 = 0;
  __cs_disable_isr_3 = 0;
  while (1)
  {
    __cs_simulate = 0;
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 1)&&(__cs_pc_1 == 0 || __cs_pc_1 == 4)&&__cs_disable_isr_0 != 1) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 1)&&__cs_disable_isr_1 != 1) {
        isr_1();
        if (__cs_pc_1 == 4) __cs_pc_1 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_2 != 1) {
        isr_2();
        if (__cs_pc_2 == 1) __cs_pc_2 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_3 != 1) {
        isr_3();
        if (__cs_pc_3 == 2) __cs_pc_3 = 0;
    }
  }
}
