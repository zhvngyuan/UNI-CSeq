// Main task
unsigned __CPROVER_bitvector[1] __cs_pc_4;
// task_measure1_isr_1
unsigned __CPROVER_bitvector[4] __cs_pc_1;
// task_measure2_isr_2
unsigned __CPROVER_bitvector[3] __cs_pc_2;
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
int records[64];
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
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_4 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 0; __cs_simulate = 2;} else    {
            systemState = 0;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 1))
    {
        __cs_pc_4 = 1;
        __cs_simulate = 2;
    }
}
/* Simulate task_measure1_isr_1 */
void task_measure1_isr_1(void)
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else {
                    tickCounter++;
                    static int __cs_l_task_measure1_isr_1_tmp_tickCounter;
                    __cs_l_task_measure1_isr_1_tmp_tickCounter = tickCounter;
                    static int __cs_l_task_measure1_isr_1_tmp_interval;
                    __cs_l_task_measure1_isr_1_tmp_interval = interval;
                    static int __cs_l_task_measure1_isr_1_value = 1;
                    tickCounter = 0;
                    if (tickCounter != 0)
                        assert(0);
                    intervalCounter++;
                    records[numberOfRecords] = __cs_l_task_measure1_isr_1_value;
                    numberOfRecords++;
        }
            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 9))
            {
                __cs_pc_1 = 9;
                __cs_simulate = 2;
            }
}
/* Simulate task_communicate_isr_3 */
void task_communicate_isr_3(void)
        {
            static int __cs_l_task_communicate_isr_3__startTime = 1;
            static int __cs_l_task_communicate_isr_3__interval = 1;
            if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
            if (__cs_simulate == 1)
            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else            {
                    cmd = nondet_rand();
            }
            if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
            if (__cs_simulate == 1)
            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;} else            {
                    rspStatus = nondet_rand();
            }
            if (__cs_simulate == 0 && __cs_pc_3 == 2) __cs_simulate = 1;
            if (__cs_simulate == 1)
            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 2; __cs_simulate = 2;} else            {
                    decodingStatus = 0;
            }
            if (__cs_simulate == 0 && __cs_pc_3 == 3) __cs_simulate = 1;
            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 3; __cs_simulate = 2;}
            if ((__cs_simulate == 0 && __cs_pc_3 <= 4) || (__cs_simulate == 1 && ((((cmd == 2) || (cmd == 3)) || (cmd == 4)) || (cmd == 1))))
            {
                        if (__cs_simulate == 0 && __cs_pc_3 == 4) __cs_simulate = 1;
                        if (__cs_simulate == 1)
                        if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 4; __cs_simulate = 2;} else                        {
                                decodingStatus = 1;
                        }
            }
            if (__cs_simulate == 0 && __cs_pc_3 == 5) __cs_simulate = 1;
            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 5; __cs_simulate = 2;}
            if ((__cs_simulate == 0 && __cs_pc_3 <= 27) || (__cs_simulate == 1 && (rspStatus == 1)))
            {
                        if (__cs_simulate == 0 && __cs_pc_3 == 6) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 6; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_3 <= 10) || (__cs_simulate == 1 && (cmd == 2)))
                        {
                                    if (__cs_simulate == 0 && __cs_pc_3 == 7) __cs_simulate = 1;
                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 7; __cs_simulate = 2;}
                                    if ((__cs_simulate == 0 && __cs_pc_3 <= 8) || (__cs_simulate == 1 && (systemState != 1)))
                                    {
                                                if (__cs_simulate == 0 && __cs_pc_3 == 8) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 8; __cs_simulate = 2;} else                                                {
                                                        rspStatus = 0;
                                                }
                                    }
                                    else
if ((__cs_simulate == 0 && __cs_pc_3 <= 9) || (__cs_simulate == 1))                                    {
                                                if (__cs_simulate == 0 && __cs_pc_3 == 9) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 9; __cs_simulate = 2;} else                                                {
                                                        systemState = 0;
                                                }
                                    }
                                    if (__cs_simulate == 0 && __cs_pc_3 == 10) __cs_simulate = 1;
                                    if (__cs_simulate == 1)
                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 10; __cs_simulate = 2;} else                                    {
                                            sendit = 1;
                                    }
                        }
                        if (__cs_simulate == 0 && __cs_pc_3 == 11) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 11; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_3 <= 12) || (__cs_simulate == 1 && (cmd == 3)))
                        {
                                    if (__cs_simulate == 0 && __cs_pc_3 == 12) __cs_simulate = 1;
                                    if (__cs_simulate == 1)
                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 12; __cs_simulate = 2;} else                                    {
                                            sendit = 1;
                                    }
                        }
                        if (__cs_simulate == 0 && __cs_pc_3 == 13) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 13; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_3 <= 14) || (__cs_simulate == 1 && (cmd == 4)))
                        {
                                    if (__cs_simulate == 0 && __cs_pc_3 == 14) __cs_simulate = 1;
                                    if (__cs_simulate == 1)
                                    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 14; __cs_simulate = 2;} else                                    {
                                            sendit = 1;
                                    }
                        }
                        if (__cs_simulate == 0 && __cs_pc_3 == 15) __cs_simulate = 1;
                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 15; __cs_simulate = 2;}
                        if ((__cs_simulate == 0 && __cs_pc_3 <= 27) || (__cs_simulate == 1 && (cmd == 0)))
                        {
                                    if (__cs_simulate == 0 && __cs_pc_3 == 16) __cs_simulate = 1;
                                    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 16; __cs_simulate = 2;}
                                    if ((__cs_simulate == 0 && __cs_pc_3 <= 17) || (__cs_simulate == 1 && (systemState != 0)))
                                    {
                                                if (__cs_simulate == 0 && __cs_pc_3 == 17) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 17; __cs_simulate = 2;} else                                                {
                                                        rspStatus = 0;
                                                }
                                    }
                                    else
if ((__cs_simulate == 0 && __cs_pc_3 <= 27) || (__cs_simulate == 1))                                    {
                                                static int __cs_l_task_communicate_isr_3_tmp_num;
                                                if (__cs_simulate == 0 && __cs_pc_3 == 18) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 18; __cs_simulate = 2;} else                                                {
                                                        __cs_l_task_communicate_isr_3_tmp_num = numberOfRecords + 1;
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 19) __cs_simulate = 1;
                                                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 19; __cs_simulate = 2;}
                                                if ((__cs_simulate == 0 && __cs_pc_3 <= 20) || (__cs_simulate == 1 && (__cs_l_task_communicate_isr_3_tmp_num >= 64)))
                                                {
                                                            if (__cs_simulate == 0 && __cs_pc_3 == 20) __cs_simulate = 1;
                                                            if (__cs_simulate == 1)
                                                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 20; __cs_simulate = 2;} else                                                            {
                                                                    systemState = 0;
                                                            }
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 21) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 21; __cs_simulate = 2;} else                                                {
                                                        intervalCounter = 0;
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 22) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 22; __cs_simulate = 2;} else                                                {
                                                        tickCounter = 0;
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 23) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 23; __cs_simulate = 2;} else                                                {
                                                        numberOfRecords = 0;
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 24) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 24; __cs_simulate = 2;} else                                                {
                                                        startTime = __cs_l_task_communicate_isr_3__startTime;
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 25) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 25; __cs_simulate = 2;} else                                                {
                                                        interval = __cs_l_task_communicate_isr_3__interval;
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 26) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 26; __cs_simulate = 2;} else                                                {
                                                        systemState = 1;
                                                }
                                                if (__cs_simulate == 0 && __cs_pc_3 == 27) __cs_simulate = 1;
                                                if (__cs_simulate == 1)
                                                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 27; __cs_simulate = 2;} else                                                {
                                                        sendit = 1;
                                                }
                                    }
                        }
            }
            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 28))
            {
                __cs_pc_3 = 28;
                __cs_simulate = 2;
            }
        }
/* Simulate task_measure2_isr_2 */
void task_measure2_isr_2(void)
        {
            if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
            if (__cs_simulate == 1)
            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else            {
                    /*disable_isr(1);*/
                    __cs_disable_isr_1 = 1;
            }
            if (__cs_simulate == 0 && __cs_pc_2 == 1) __cs_simulate = 1;
            if (__cs_simulate == 1)
            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 1; __cs_simulate = 2;} else            {
                    /*disable_isr(3);*/
                    __cs_disable_isr_3 = 1;
            }
            if (__cs_simulate == 0 && __cs_pc_2 == 2) __cs_simulate = 1;
            if (__cs_simulate == 1)
            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 2; __cs_simulate = 2;} else            {
                    tickCounter = 0;
            }
            if (__cs_simulate == 0 && __cs_pc_2 == 3) __cs_simulate = 1;
            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 3; __cs_simulate = 2;}
            if ((__cs_simulate == 0 && __cs_pc_2 <= 4) || (__cs_simulate == 1 && (tickCounter != 0)))
            {
                        if (__cs_simulate == 0 && __cs_pc_2 == 4) __cs_simulate = 1;
                        if (__cs_simulate == 1)
                        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 4; __cs_simulate = 2;} else                        {
                                assert(0);
                        }
            }
            if (__cs_simulate == 0 && __cs_pc_2 == 5) __cs_simulate = 1;
            if (__cs_simulate == 1)
            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 5; __cs_simulate = 2;} else            {
                    /*enable_isr(1);*/
                    __cs_disable_isr_1 = 0;
            }
            if (__cs_simulate == 0 && __cs_pc_2 == 6) __cs_simulate = 1;
            if (__cs_simulate == 1)
            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 6; __cs_simulate = 2;} else            {
                    /*enable_isr(3);*/
                    __cs_disable_isr_3 = 0;
            }
            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 7))
            {
                __cs_pc_2 = 7;
                __cs_simulate = 2;
            }
        }
/* main function (scheduler) */
int main()
{
  __cs_simulate = 0;
  __cs_pc_4 = 0;
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
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 7)&&(__cs_pc_3 == 0 || __cs_pc_3 == 28)&&__cs_disable_isr_0 != 1) main_task();
    __cs_simulate = 0;
    if (__cs_disable_isr_1 != 1) task_measure1_isr_1();
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 28)&&__cs_disable_isr_2 != 1) task_measure2_isr_2();
    __cs_simulate = 0;
    if (__cs_disable_isr_3 != 1) task_communicate_isr_3();
  }
}
