// Main task
unsigned int __cs_pc_5;
// task_measure1_isr_1
unsigned int __cs_pc_1;
// task_measure2_isr_2
unsigned int __cs_pc_2;
// task_measure3_isr_3
unsigned int __cs_pc_3;
// task_communicate_isr_4
unsigned int __cs_pc_4;
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
int __cs_disable_isr_2;
int __cs_disable_isr_3;
int __cs_disable_isr_4;
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
int cnt1;
int cnt2;
int cnt3;
int cnt4;
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_5 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_5 = 0; __cs_simulate = 2;} else    {
            systemState = 0;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_5 == 1))
    {
        __cs_pc_5 = 1;
        __cs_simulate = 2;
    }
}
/* Simulate task_communicate_isr_4 */
void task_communicate_isr_4()
{
    if (__cs_simulate == 0 && __cs_pc_4 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 0; __cs_simulate = 2;} else    {
            cnt4++;
    }
    static int __cs_l_task_communicate_isr_4__startTime = 1;
    static int __cs_l_task_communicate_isr_4__interval = 1;
    if (__cs_simulate == 0 && __cs_pc_4 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 1; __cs_simulate = 2;} else    {
            cmd = (nondet_rand() % 4) + 1;
    }
    if (__cs_simulate == 0 && __cs_pc_4 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 2; __cs_simulate = 2;} else    {
            rspStatus = (nondet_rand() % 2) + 1;
    }
    if (__cs_simulate == 0 && __cs_pc_4 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 3; __cs_simulate = 2;} else    {
            decodingStatus = 0;
    }
    if (__cs_simulate == 0 && __cs_pc_4 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 4; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_4 <= 5) || (__cs_simulate == 1 && ((((cmd == 2) || (cmd == 3)) || (cmd == 4)) || (cmd == 1))))
    {
                if (__cs_simulate == 0 && __cs_pc_4 == 5) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 5; __cs_simulate = 2;} else                {
                        decodingStatus = 1;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_4 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 6; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_4 <= 30) || (__cs_simulate == 1 && (rspStatus == 1)))
    {
                if (__cs_simulate == 0 && __cs_pc_4 == 7) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 7; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_4 <= 11) || (__cs_simulate == 1 && (cmd == 2)))
                {
                            if (__cs_simulate == 0 && __cs_pc_4 == 8) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 8; __cs_simulate = 2;}
                            if ((__cs_simulate == 0 && __cs_pc_4 <= 9) || (__cs_simulate == 1 && (systemState != 1)))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_4 == 9) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 9; __cs_simulate = 2;} else                                        {
                                                rspStatus = 0;
                                        }
                            }
                            else
if ((__cs_simulate == 0 && __cs_pc_4 <= 10) || (__cs_simulate == 1))                            {
                                        if (__cs_simulate == 0 && __cs_pc_4 == 10) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 10; __cs_simulate = 2;} else                                        {
                                                systemState = 0;
                                        }
                            }
                            if (__cs_simulate == 0 && __cs_pc_4 == 11) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 11; __cs_simulate = 2;} else                            {
                                    sendit = 1;
                            }
                }
                if (__cs_simulate == 0 && __cs_pc_4 == 12) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 12; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_4 <= 13) || (__cs_simulate == 1 && (cmd == 3)))
                {
                            if (__cs_simulate == 0 && __cs_pc_4 == 13) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 13; __cs_simulate = 2;} else                            {
                                    sendit = 1;
                            }
                }
                if (__cs_simulate == 0 && __cs_pc_4 == 14) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 14; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_4 <= 15) || (__cs_simulate == 1 && (cmd == 4)))
                {
                            if (__cs_simulate == 0 && __cs_pc_4 == 15) __cs_simulate = 1;
                            if (__cs_simulate == 1)
                            if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 15; __cs_simulate = 2;} else                            {
                                    sendit = 1;
                            }
                }
                if (__cs_simulate == 0 && __cs_pc_4 == 16) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 16; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_4 <= 30) || (__cs_simulate == 1 && (cmd == 0)))
                {
                            if (__cs_simulate == 0 && __cs_pc_4 == 17) __cs_simulate = 1;
                            if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 17; __cs_simulate = 2;}
                            if ((__cs_simulate == 0 && __cs_pc_4 <= 18) || (__cs_simulate == 1 && (systemState != 0)))
                            {
                                        if (__cs_simulate == 0 && __cs_pc_4 == 18) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 18; __cs_simulate = 2;} else                                        {
                                                rspStatus = 0;
                                        }
                            }
                            else
if ((__cs_simulate == 0 && __cs_pc_4 <= 30) || (__cs_simulate == 1))                            {
                                        static int __cs_l_task_communicate_isr_4_tmp_num;
                                        if (__cs_simulate == 0 && __cs_pc_4 == 19) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 19; __cs_simulate = 2;} else                                        {
                                                __cs_l_task_communicate_isr_4_tmp_num = numberOfRecords + 1;
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_4 == 20) __cs_simulate = 1;
                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 20; __cs_simulate = 2;}
                                        if ((__cs_simulate == 0 && __cs_pc_4 <= 21) || (__cs_simulate == 1 && (__cs_l_task_communicate_isr_4_tmp_num >= 64)))
                                        {
                                                    if (__cs_simulate == 0 && __cs_pc_4 == 21) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 21; __cs_simulate = 2;} else                                                    {
                                                            systemState = 0;
                                                    }
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_4 == 22) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 22; __cs_simulate = 2;} else                                        {
                                                intervalCounter = 0;
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_4 == 23) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 23; __cs_simulate = 2;} else                                        {
                                                tickCounter = 0;
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_4 == 24) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 24; __cs_simulate = 2;} else                                        {
                                                numberOfRecords = 0;
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_4 == 25) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 25; __cs_simulate = 2;} else                                        {
                                                startTime = __cs_l_task_communicate_isr_4__startTime;
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_4 == 26) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 26; __cs_simulate = 2;} else                                        {
                                                interval = __cs_l_task_communicate_isr_4__interval;
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_4 == 27) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 27; __cs_simulate = 2;} else                                        {
                                                systemState = 1;
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_4 == 28) __cs_simulate = 1;
                                        if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_4 = 28; __cs_simulate = 2;}
                                        if ((__cs_simulate == 0 && __cs_pc_4 <= 29) || (__cs_simulate == 1 && (numberOfRecords != 0)))
                                        {
                                                    if (__cs_simulate == 0 && __cs_pc_4 == 29) __cs_simulate = 1;
                                                    if (__cs_simulate == 1)
                                                    if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 29; __cs_simulate = 2;} else                                                    {
                                                            if (!(0)) __cseq_error();
                                                    }
                                        }
                                        if (__cs_simulate == 0 && __cs_pc_4 == 30) __cs_simulate = 1;
                                        if (__cs_simulate == 1)
                                        if (__VERIFIER_nondet_bool()) {__cs_pc_4 = 30; __cs_simulate = 2;} else                                        {
                                                sendit = 1;
                                        }
                            }
                }
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_4 == 31))
    {
        __cs_pc_4 = 31;
        __cs_simulate = 2;
    }
}
/* Simulate task_measure1_isr_1 */
void task_measure1_isr_1()
{
    if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else    {
            cnt1++;
    }
    static int __cs_l_task_measure1_isr_1_tmp_tickCounter;
    if (__cs_simulate == 0 && __cs_pc_1 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 1; __cs_simulate = 2;} else    {
            __cs_l_task_measure1_isr_1_tmp_tickCounter = tickCounter;
    }
    static int __cs_l_task_measure1_isr_1_tmp_interval;
    if (__cs_simulate == 0 && __cs_pc_1 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 2; __cs_simulate = 2;} else    {
            __cs_l_task_measure1_isr_1_tmp_interval = interval;
    }
    static int __cs_l_task_measure1_isr_1_value = 1;
    if (__cs_simulate == 0 && __cs_pc_1 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_1 = 3; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_1 <= 4) || (__cs_simulate == 1 && (tickCounter != 0)))
    {
                if (__cs_simulate == 0 && __cs_pc_1 == 4) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 4; __cs_simulate = 2;} else                {
                        if (!(0)) __cseq_error();
                }
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 5; __cs_simulate = 2;} else    {
            intervalCounter++;
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 6; __cs_simulate = 2;} else    {
            records = __cs_l_task_measure1_isr_1_value;
    }
    if (__cs_simulate == 0 && __cs_pc_1 == 7) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 7; __cs_simulate = 2;} else    {
            numberOfRecords++;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 8))
    {
        __cs_pc_1 = 8;
        __cs_simulate = 2;
    }
}
/* Simulate task_measure3_isr_3 */
void task_measure3_isr_3()
{
    if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else    {
            tickCounter = 0;
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_3 <= 2) || (__cs_simulate == 1 && (tickCounter != 0)))
    {
                if (__cs_simulate == 0 && __cs_pc_3 == 2) __cs_simulate = 1;
                if (__cs_simulate == 1)
                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 2; __cs_simulate = 2;} else                {
                        if (!(0)) __cseq_error();
                }
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1)
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 3; __cs_simulate = 2;} else    {
            cnt3++;
    }
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 4))
    {
        __cs_pc_3 = 4;
        __cs_simulate = 2;
    }
}
/* Simulate task_measure2_isr_2 */
void task_measure2_isr_2()
{
        if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1)
        if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else {
                    cnt2++;
                    tickCounter = 0;
                    if (tickCounter != 0)
                        if (!(0)) __cseq_error();
        }
            if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 4))
            {
                __cs_pc_2 = 4;
                __cs_simulate = 2;
            }
}
/* main function (scheduler) */
int main()
{
  __cs_simulate = 0;
  __cs_pc_5 = 0;
  __cs_pc_1 = 0;
  __cs_pc_2 = 0;
  __cs_pc_3 = 0;
  __cs_pc_4 = 0;
  __cs_disable_isr_0 = 0;
  __cs_disable_isr_1 = 0;
  __cs_disable_isr_2 = 0;
  __cs_disable_isr_3 = 0;
  __cs_disable_isr_4 = 0;
  while (1)
  {
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 4)&&(__cs_pc_4 == 0 || __cs_pc_4 == 31)&&(__cs_pc_1 == 0 || __cs_pc_1 == 8)&&__cs_disable_isr_0 != 1) main_task();
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 4)&&(__cs_pc_4 == 0 || __cs_pc_4 == 31)&&__cs_disable_isr_1 != 1) task_measure1_isr_1();
    __cs_simulate = 0;
    if (__cs_disable_isr_2 != 1) task_measure2_isr_2();
    __cs_simulate = 0;
    if ((__cs_pc_4 == 0 || __cs_pc_4 == 31)&&__cs_disable_isr_3 != 1) task_measure3_isr_3();
    __cs_simulate = 0;
    if (__cs_disable_isr_4 != 1) task_communicate_isr_4();
  }
}
