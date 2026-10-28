// Main task
unsigned __CPROVER_bitvector[1] __cs_pc_0;
// task_measure1_isr_1
unsigned __CPROVER_bitvector[4] __cs_pc_1;
// task_measure2_isr_2
unsigned __CPROVER_bitvector[2] __cs_pc_2;
// task_communicate_isr_3
unsigned __CPROVER_bitvector[5] __cs_pc_3;
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
int numberOfRecords;
int records;
int msgBuffer[64];
int intervalCounter;
int tickCounter;
int interval;
int startTime;
int decodingStatus;
int cmd;
int sendit;
int systemState;
int rspStatus;
const int __CPROVER_thread_priorities[] = {5, 2, 3};
const char *__CPROVER_threads[] = {"c::task_communicate", "c::task_measure1", "c::task_measure2"};
int cnt1;
int cnt2;
int cnt3;
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            systemState = 0;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 1))
    {
        __cs_pc_0 = 1;
        __cs_simulate = 2;
    }
}
/* Simulate task_communicate_isr_3 */
void task_communicate_isr_3()
{
        if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else 
{
                    cnt3++;
                    static int __cs_l_task_communicate_isr_3__startTime_1;
                    __cs_l_task_communicate_isr_3__startTime_1 = 1;
                    static int __cs_l_task_communicate_isr_3__interval_1;
                    __cs_l_task_communicate_isr_3__interval_1 = 1;
                    cmd = (rand() % 4) + 1;
                    rspStatus = (rand() % 2) + 1;
                    decodingStatus = 0;
                    if ((((cmd == 2) || (cmd == 3)) || (cmd == 4)) || (cmd == 1))
    {
                        decodingStatus = 1;
    }
                    if (rspStatus == 1)
    {
                                                if (cmd == 2)
                {
                                                                            if (systemState != 1)
                            {
                                rspStatus = 0;
                            }
                            else
                            {
                                systemState = 0;
                            }
                            sendit = 1;
                }
                                                if (cmd == 3)
                {
                            sendit = 1;
                }
                                                if (cmd == 4)
                {
                            sendit = 1;
                }
                                                if (cmd == 0)
                {
                                                                            if (systemState != 0)
                            {
                                rspStatus = 0;
                            }
                            else
                            {
                                static int __cs_l_task_communicate_isr_3_tmp_num_1;
                                __cs_l_task_communicate_isr_3_tmp_num_1 = numberOfRecords + 1;
                                                                                                        if (__cs_l_task_communicate_isr_3_tmp_num_1 >= 64)
                                        {
                                    systemState = 0;
                                        }
                                intervalCounter = 0;
                                tickCounter = 0;
                                numberOfRecords = 0;
                                startTime = __cs_l_task_communicate_isr_3__startTime_1;
                                interval = __cs_l_task_communicate_isr_3__interval_1;
                                systemState = 1;
                                                assert(numberOfRecords == 0);
                                sendit = 1;
                            }
                }
    }
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 30))
    {
        __cs_pc_3 = 30;
        __cs_simulate = 2;
    }
}
/* Simulate task_measure1_isr_1 */
void task_measure1_isr_1()
{
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            cnt1++;
    }}
    if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;} else    {
            tickCounter++;
    }}
    static int __cs_l_task_measure1_isr_1_tmp_tickCounter_1;
    if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;} else    {
            __cs_l_task_measure1_isr_1_tmp_tickCounter_1 = tickCounter;
    }}
    static int __cs_l_task_measure1_isr_1_tmp_interval_1;
    if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;} else    {
            __cs_l_task_measure1_isr_1_tmp_interval_1 = interval;
    }}
    static int __cs_l_task_measure1_isr_1_value_1;
    if (__cs_simulate == 1)
    {
            __cs_l_task_measure1_isr_1_value_1 = 1;
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 4; __cs_simulate = 2;} else    {
            tickCounter = 0;
    }}
    if (__cs_simulate == 0 && __cs_pc_1 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 5; __cs_simulate = 2;} else    {
            intervalCounter++;
    }}
    if (__cs_simulate == 0 && __cs_pc_1 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 6; __cs_simulate = 2;} else    {
            records = __cs_l_task_measure1_isr_1_value_1;
    }}
    if (__cs_simulate == 0 && __cs_pc_1 == 7) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 7; __cs_simulate = 2;} else    {
            numberOfRecords++;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 8))
    {
        __cs_pc_1 = 8;
        __cs_simulate = 2;
    }
}
/* Simulate task_measure2_isr_2 */
void task_measure2_isr_2()
{
    if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else    {
            cnt2++;
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 1; __cs_simulate = 2;} else    {
            tickCounter = 0;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 2))
    {
        __cs_pc_2 = 2;
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
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 2)&&(__cs_pc_1 == 0 || __cs_pc_1 == 8)) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 2)&&__cs_disable_isr_1 != 1) {
        task_measure1_isr_1();
        if (__cs_pc_1 == 8) __cs_pc_1 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_2 != 1) {
        task_measure2_isr_2();
        if (__cs_pc_2 == 2) __cs_pc_2 = 0;
    }
    __cs_simulate = 0;
    if (__cs_disable_isr_3 != 1) {
        task_communicate_isr_3();
        if (__cs_pc_3 == 30) __cs_pc_3 = 0;
    }
  }
}
