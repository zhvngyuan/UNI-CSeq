// Main task
unsigned int __cs_pc_0;
// task_compute_isr_1
unsigned int __cs_pc_1;
// task_RR_Wheel_isr_2
unsigned int __cs_pc_2;
// task_FL_Wheel_isr_3
unsigned int __cs_pc_3;
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
int __cs_disable_isr_2;
int __cs_disable_isr_3;
/* Global variables */
int brake_acc_nodiv_ctrl_B_local_RT_h;
int brake_acc_nodiv_ctrl_B_local_RTH;
int brake_acc_nodiv_ctrl_B_local_RT4;
int brake_acc_nodiv_ctrl_B_local_RT1;
int brake_acc_nodiv_ctrl_B_local_RT2;
int brake_acc_nodiv_ctrl_B_local_RT3;
int brake_acc_nodiv_ctrl_B_local_RT14;
int brake_acc_nodiv_ctrl_B_local_ABS_FL_Wheel_Threshold_10kmh = 100;
int brake_acc_nodiv_ctrl_B_local_ABS_RL_Wheel_Threshold_10kmh = 100;
int brake_acc_nodiv_ctrl_B_local_ABS_RR_Wheel_Threshold_10kmh = 100;
int brake_acc_nodiv_ctrl_B_local_ABS_FR_Wheel_Threshold_10kmh = 100;
int brake_acc_nodiv_ctrl_P_RT_X0;
int brake_acc_nodiv_ctrl_P_RT4_X0;
int brake_acc_nodiv_ctrl_P_RT1_X0;
int brake_acc_nodiv_ctrl_P_RT2_X0;
int brake_acc_nodiv_ctrl_P_RT3_X0;
int brake_acc_nodiv_ctrl_P_Gain1_Gain;
int brake_acc_nodiv_ctrl_P_Distribution_Gain0;
int brake_acc_nodiv_ctrl_P_Distribution_Gain1;
int brake_acc_nodiv_ctrl_P_Distribution_Gain2;
int brake_acc_nodiv_ctrl_P_Distribution_Gain3;
int brake_acc_nodiv_ctrl_P_average_rpm_Gain;
int brake_acc_nodiv_ctrl_P_wgrads_Gain;
int brake_acc_nodiv_ctrl_P_vkmh_Gain;
int vkmh;
int test;
int RT9;
int RT10;
int RT11;
int RT12;
int RT14;
int RT_Buffer0;
int RT0_Buffer0;
int RT1_Buffer0;
int RT2_Buffer0;
int RT3_Buffer0;
int RT4_Buffer0;
int Distribution_idx;
int Distribution_idx_0;
int Distribution_idx_1;
int cnt1;
int cnt2;
int cnt3;
/* Simulate task_RR_Wheel_isr_2 */
void task_RR_Wheel_isr_2()
{
    if (__cs_simulate == 0 && __cs_pc_2 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 0; __cs_simulate = 2;} else    {
            cnt2++;
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 1; __cs_simulate = 2;} else    {
            test = 0;
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 2; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT_h = brake_acc_nodiv_ctrl_P_RT_X0;
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 3; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT4 = brake_acc_nodiv_ctrl_P_RT4_X0;
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 4; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT1 = brake_acc_nodiv_ctrl_P_RT1_X0;
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 5; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT2 = brake_acc_nodiv_ctrl_P_RT2_X0;
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 6; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT3 = brake_acc_nodiv_ctrl_P_RT3_X0;
    }}
    static int __cs_l_task_RR_Wheel_isr_2_rtb_to_int_1;
    if (__cs_simulate == 0 && __cs_pc_2 == 7) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 7; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_task_RR_Wheel_isr_2_rtb_to_int_1, sizeof(int));
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 8) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 8; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT_h = RT_Buffer0;
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 9) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 9; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT4 = RT4_Buffer0;
    }}
    if (__cs_simulate == 1)
    {
            __cs_l_task_RR_Wheel_isr_2_rtb_to_int_1 = 10;
    }
    static int __cs_l_task_RR_Wheel_isr_2_rtb_RelationalOperator_1;
    if (__cs_simulate == 0 && __cs_pc_2 == 10) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 10; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_task_RR_Wheel_isr_2_rtb_RelationalOperator_1, sizeof(int));
    }}
    static int __cs_l_task_RR_Wheel_isr_2_rtb_vms_1;
    if (__cs_simulate == 0 && __cs_pc_2 == 11) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 11; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_task_RR_Wheel_isr_2_rtb_vms_1, sizeof(int));
    }}
    static int __cs_l_task_RR_Wheel_isr_2_u_1;
    if (__cs_simulate == 0 && __cs_pc_2 == 12) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 12; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_task_RR_Wheel_isr_2_u_1, sizeof(int));
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 13) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 13; __cs_simulate = 2;} else    {
            __cs_l_task_RR_Wheel_isr_2_rtb_vms_1 = 10 + brake_acc_nodiv_ctrl_B_local_RT4;
    }}
    if (__cs_simulate == 1)
    {
            __cs_l_task_RR_Wheel_isr_2_u_1 = __cs_l_task_RR_Wheel_isr_2_rtb_vms_1 + 10;
    }
    if (__cs_simulate == 1)
    {
            __cs_l_task_RR_Wheel_isr_2_u_1 = __cs_l_task_RR_Wheel_isr_2_u_1 + __cs_l_task_RR_Wheel_isr_2_rtb_to_int_1;
    }
    static int __cs_l_task_RR_Wheel_isr_2_positive_UpperSat_local_1;
    if (__cs_simulate == 1)
    {
            __cs_l_task_RR_Wheel_isr_2_positive_UpperSat_local_1 = 100;
    }
    if (__cs_simulate == 0 && __cs_pc_2 == 14) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 14; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_2 <= 14) || (__cs_simulate == 1 && (__cs_l_task_RR_Wheel_isr_2_u_1 >= __cs_l_task_RR_Wheel_isr_2_positive_UpperSat_local_1)))
    {
                if (__cs_simulate == 1)
                {
                        __cs_l_task_RR_Wheel_isr_2_u_1 = 100;
                }
    }
    else
if ((__cs_simulate == 0 && __cs_pc_2 <= 15) || (__cs_simulate == 1))    {
                static int __cs_l_task_RR_Wheel_isr_2_positive_LowerSat_local_1;
                if (__cs_simulate == 1)
                {
                        __cs_l_task_RR_Wheel_isr_2_positive_LowerSat_local_1 = 5;
                }
                if (__cs_simulate == 0 && __cs_pc_2 == 15) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 15; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_2 <= 15) || (__cs_simulate == 1 && (__cs_l_task_RR_Wheel_isr_2_u_1 <= __cs_l_task_RR_Wheel_isr_2_positive_LowerSat_local_1)))
                {
                            if (__cs_simulate == 1)
                            {
                                    __cs_l_task_RR_Wheel_isr_2_u_1 = 5;
                            }
                }
    }
    static int __cs_l_task_RR_Wheel_isr_2_tmp0_1;
    if (__cs_simulate == 1)
    {
            __cs_l_task_RR_Wheel_isr_2_tmp0_1 = 10;
    }
    static int __cs_l_task_RR_Wheel_isr_2_tmp1_1;
    if (__cs_simulate == 1)
    {
            __cs_l_task_RR_Wheel_isr_2_tmp1_1 = 10 + __cs_l_task_RR_Wheel_isr_2_rtb_vms_1;
    }
    if (__cs_simulate == 0 && __cs_pc_2 == 16) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 16; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_2 <= 16) || (__cs_simulate == 1 && (__cs_l_task_RR_Wheel_isr_2_tmp0_1 > __cs_l_task_RR_Wheel_isr_2_tmp1_1)))
    {
                if (__cs_simulate == 1)
                {
                        __cs_l_task_RR_Wheel_isr_2_rtb_RelationalOperator_1 = 1;
                }
    }
    else
if ((__cs_simulate == 0 && __cs_pc_2 <= 16) || (__cs_simulate == 1))    {
                if (__cs_simulate == 1)
                {
                        __cs_l_task_RR_Wheel_isr_2_rtb_RelationalOperator_1 = 0;
                }
    }
    static int __cs_l_task_RR_Wheel_isr_2_Threshold_10kmh_Threshold_local_1;
    if (__cs_simulate == 1)
    {
            __cs_l_task_RR_Wheel_isr_2_Threshold_10kmh_Threshold_local_1 = 100;
    }
    if (__cs_simulate == 0 && __cs_pc_2 == 17) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 17; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_2 <= 20) || (__cs_simulate == 1 && (brake_acc_nodiv_ctrl_B_local_RT4 >= __cs_l_task_RR_Wheel_isr_2_Threshold_10kmh_Threshold_local_1)))
    {
                if (__cs_simulate == 0 && __cs_pc_2 == 18) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_2 = 18; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_2 <= 19) || (__cs_simulate == 1 && (__cs_l_task_RR_Wheel_isr_2_rtb_RelationalOperator_1)))
                {
                            if (__cs_simulate == 0 && __cs_pc_2 == 19) __cs_simulate = 1;
                            if (__cs_simulate == 1){
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 19; __cs_simulate = 2;} else                            {
                                    brake_acc_nodiv_ctrl_B_local_ABS_RR_Wheel_Threshold_10kmh = 8;
                            }}
                }
                else
if ((__cs_simulate == 0 && __cs_pc_2 <= 20) || (__cs_simulate == 1))                {
                            if (__cs_simulate == 0 && __cs_pc_2 == 20) __cs_simulate = 1;
                            if (__cs_simulate == 1){
                            if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 20; __cs_simulate = 2;} else                            {
                                    brake_acc_nodiv_ctrl_B_local_ABS_RR_Wheel_Threshold_10kmh = brake_acc_nodiv_ctrl_B_local_RT_h;
                            }}
                }
    }
    else
if ((__cs_simulate == 0 && __cs_pc_2 <= 21) || (__cs_simulate == 1))    {
                if (__cs_simulate == 0 && __cs_pc_2 == 21) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 21; __cs_simulate = 2;} else                {
                        brake_acc_nodiv_ctrl_B_local_ABS_RR_Wheel_Threshold_10kmh = brake_acc_nodiv_ctrl_B_local_RT_h;
                }}
    }
    if (__cs_simulate == 0 && __cs_pc_2 == 22) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 22; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT1 = RT1_Buffer0;
    }}
    if (__cs_simulate == 0 && __cs_pc_2 == 23) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_2 = 23; __cs_simulate = 2;} else    {
            RT9 = __cs_l_task_RR_Wheel_isr_2_rtb_to_int_1;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_2 == 24))
    {
        __cs_pc_2 = 24;
        __cs_simulate = 2;
    }
}
/* Simulate original main */
int main_task()
{
    if (__cs_simulate == 0 && __cs_pc_0 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_0 = 0; __cs_simulate = 2;} else    {
            test = 0;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_0 == 1))
    {
        __cs_pc_0 = 1;
        __cs_simulate = 2;
    }
}
/* Simulate task_compute_isr_1 */
void task_compute_isr_1()
{
        if (__cs_simulate == 0 && __cs_pc_1 == 0) __cs_simulate = 1;
        if (__cs_simulate == 1){
        if (__VERIFIER_nondet_bool()) {__cs_pc_1 = 0; __cs_simulate = 2;} else 
{
                    cnt1++;
                    brake_acc_nodiv_ctrl_B_local_RT_h = brake_acc_nodiv_ctrl_P_RT_X0;
                    brake_acc_nodiv_ctrl_B_local_RT4 = brake_acc_nodiv_ctrl_P_RT4_X0;
                    brake_acc_nodiv_ctrl_B_local_RT1 = brake_acc_nodiv_ctrl_P_RT1_X0;
                    brake_acc_nodiv_ctrl_B_local_RT2 = brake_acc_nodiv_ctrl_P_RT2_X0;
                    brake_acc_nodiv_ctrl_B_local_RT3 = brake_acc_nodiv_ctrl_P_RT3_X0;
                    test = 0;
                    Distribution_idx = brake_acc_nodiv_ctrl_P_Distribution_Gain1 + brake_acc_nodiv_ctrl_B_local_RT14;
                    Distribution_idx_0 = brake_acc_nodiv_ctrl_P_Distribution_Gain2 + brake_acc_nodiv_ctrl_B_local_RT14;
                    Distribution_idx_1 = brake_acc_nodiv_ctrl_P_Distribution_Gain3 + brake_acc_nodiv_ctrl_B_local_RT14;
                    vkmh = RT9 + RT10;
                    vkmh = vkmh + RT11;
                    vkmh = vkmh + RT12;
                    vkmh = vkmh + brake_acc_nodiv_ctrl_P_average_rpm_Gain;
                    vkmh = vkmh + brake_acc_nodiv_ctrl_P_wgrads_Gain;
                    vkmh = vkmh + brake_acc_nodiv_ctrl_P_vkmh_Gain;
                    test++;
            if (!(test == 1)) __cseq_error();
                    RT_Buffer0 = brake_acc_nodiv_ctrl_P_Distribution_Gain0 + brake_acc_nodiv_ctrl_B_local_RT14;
                    RT4_Buffer0 = vkmh;
                    RT1_Buffer0 = Distribution_idx;
                    RT2_Buffer0 = Distribution_idx_0;
                    RT3_Buffer0 = Distribution_idx_1;
        }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_1 == 23))
    {
        __cs_pc_1 = 23;
        __cs_simulate = 2;
    }
}
/* Simulate task_FL_Wheel_isr_3 */
void task_FL_Wheel_isr_3()
{
    if (__cs_simulate == 0 && __cs_pc_3 == 0) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 0; __cs_simulate = 2;} else    {
            cnt3++;
    }}
    if (__cs_simulate == 0 && __cs_pc_3 == 1) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 1; __cs_simulate = 2;} else    {
            test = 0;
    }}
    if (__cs_simulate == 0 && __cs_pc_3 == 2) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 2; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT_h = brake_acc_nodiv_ctrl_P_RT_X0;
    }}
    if (__cs_simulate == 0 && __cs_pc_3 == 3) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 3; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT4 = brake_acc_nodiv_ctrl_P_RT4_X0;
    }}
    if (__cs_simulate == 0 && __cs_pc_3 == 4) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 4; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT1 = brake_acc_nodiv_ctrl_P_RT1_X0;
    }}
    if (__cs_simulate == 0 && __cs_pc_3 == 5) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 5; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT2 = brake_acc_nodiv_ctrl_P_RT2_X0;
    }}
    if (__cs_simulate == 0 && __cs_pc_3 == 6) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 6; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT3 = brake_acc_nodiv_ctrl_P_RT3_X0;
    }}
    static int __cs_l_task_FL_Wheel_isr_3_rtb_to_int1_1;
    if (__cs_simulate == 0 && __cs_pc_3 == 7) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 7; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_task_FL_Wheel_isr_3_rtb_to_int1_1, sizeof(int));
    }}
    if (__cs_simulate == 1)
    {
            __cs_l_task_FL_Wheel_isr_3_rtb_to_int1_1 = 10;
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 8) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 8; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT_h = RT_Buffer0;
    }}
    if (__cs_simulate == 0 && __cs_pc_3 == 9) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 9; __cs_simulate = 2;} else    {
            brake_acc_nodiv_ctrl_B_local_RT4 = RT4_Buffer0;
    }}
    static int __cs_l_task_FL_Wheel_isr_3_rtb_RelationalOperator_1;
    if (__cs_simulate == 0 && __cs_pc_3 == 10) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 10; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_task_FL_Wheel_isr_3_rtb_RelationalOperator_1, sizeof(int));
    }}
    static int __cs_l_task_FL_Wheel_isr_3_rtb_vms_1;
    if (__cs_simulate == 0 && __cs_pc_3 == 11) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 11; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_task_FL_Wheel_isr_3_rtb_vms_1, sizeof(int));
    }}
    static int __cs_l_task_FL_Wheel_isr_3_u_1;
    if (__cs_simulate == 0 && __cs_pc_3 == 12) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 12; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_task_FL_Wheel_isr_3_u_1, sizeof(int));
    }}
    if (__cs_simulate == 0 && __cs_pc_3 == 13) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 13; __cs_simulate = 2;} else    {
            __cs_l_task_FL_Wheel_isr_3_rtb_vms_1 = 10 + brake_acc_nodiv_ctrl_B_local_RT4;
    }}
    if (__cs_simulate == 1)
    {
            __cs_l_task_FL_Wheel_isr_3_u_1 = __cs_l_task_FL_Wheel_isr_3_rtb_vms_1 + 10;
    }
    if (__cs_simulate == 1)
    {
            __cs_l_task_FL_Wheel_isr_3_u_1 = __cs_l_task_FL_Wheel_isr_3_u_1 + __cs_l_task_FL_Wheel_isr_3_rtb_to_int1_1;
    }
    static int __cs_l_task_FL_Wheel_isr_3_positive_UpperSat_local_1;
    if (__cs_simulate == 1)
    {
            __cs_l_task_FL_Wheel_isr_3_positive_UpperSat_local_1 = 100;
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 14) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 14; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_3 <= 14) || (__cs_simulate == 1 && (__cs_l_task_FL_Wheel_isr_3_u_1 >= __cs_l_task_FL_Wheel_isr_3_positive_UpperSat_local_1)))
    {
                if (__cs_simulate == 1)
                {
                        __cs_l_task_FL_Wheel_isr_3_u_1 = 100;
                }
    }
    else
if ((__cs_simulate == 0 && __cs_pc_3 <= 15) || (__cs_simulate == 1))    {
                static int __cs_l_task_FL_Wheel_isr_3_positive_LowerSat_local_1;
                if (__cs_simulate == 1)
                {
                        __cs_l_task_FL_Wheel_isr_3_positive_LowerSat_local_1 = 5;
                }
                if (__cs_simulate == 0 && __cs_pc_3 == 15) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 15; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_3 <= 15) || (__cs_simulate == 1 && (__cs_l_task_FL_Wheel_isr_3_u_1 <= __cs_l_task_FL_Wheel_isr_3_positive_LowerSat_local_1)))
                {
                            if (__cs_simulate == 1)
                            {
                                    __cs_l_task_FL_Wheel_isr_3_u_1 = 5;
                            }
                }
    }
    static int __cs_l_task_FL_Wheel_isr_3_tmp0_1;
    if (__cs_simulate == 1)
    {
            __cs_l_task_FL_Wheel_isr_3_tmp0_1 = 10;
    }
    static int __cs_l_task_FL_Wheel_isr_3_tmp1_1;
    if (__cs_simulate == 1)
    {
            __cs_l_task_FL_Wheel_isr_3_tmp1_1 = 10 + __cs_l_task_FL_Wheel_isr_3_rtb_vms_1;
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 16) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 16; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_3 <= 16) || (__cs_simulate == 1 && (__cs_l_task_FL_Wheel_isr_3_tmp0_1 > __cs_l_task_FL_Wheel_isr_3_tmp1_1)))
    {
                if (__cs_simulate == 1)
                {
                        __cs_l_task_FL_Wheel_isr_3_rtb_RelationalOperator_1 = 1;
                }
    }
    else
if ((__cs_simulate == 0 && __cs_pc_3 <= 16) || (__cs_simulate == 1))    {
                if (__cs_simulate == 1)
                {
                        __cs_l_task_FL_Wheel_isr_3_rtb_RelationalOperator_1 = 0;
                }
    }
    static int __cs_l_task_FL_Wheel_isr_3_Threshold_10kmh_Threshold_local_1;
    if (__cs_simulate == 1)
    {
            __cs_l_task_FL_Wheel_isr_3_Threshold_10kmh_Threshold_local_1 = 100;
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 17) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 17; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_3 <= 20) || (__cs_simulate == 1 && (brake_acc_nodiv_ctrl_B_local_RT4 >= __cs_l_task_FL_Wheel_isr_3_Threshold_10kmh_Threshold_local_1)))
    {
                if (__cs_simulate == 0 && __cs_pc_3 == 18) __cs_simulate = 1;
                if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 18; __cs_simulate = 2;}
                if ((__cs_simulate == 0 && __cs_pc_3 <= 19) || (__cs_simulate == 1 && (__cs_l_task_FL_Wheel_isr_3_rtb_RelationalOperator_1)))
                {
                            if (__cs_simulate == 0 && __cs_pc_3 == 19) __cs_simulate = 1;
                            if (__cs_simulate == 1){
                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 19; __cs_simulate = 2;} else                            {
                                    brake_acc_nodiv_ctrl_B_local_ABS_FL_Wheel_Threshold_10kmh = 8;
                            }}
                }
                else
if ((__cs_simulate == 0 && __cs_pc_3 <= 20) || (__cs_simulate == 1))                {
                            if (__cs_simulate == 0 && __cs_pc_3 == 20) __cs_simulate = 1;
                            if (__cs_simulate == 1){
                            if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 20; __cs_simulate = 2;} else                            {
                                    brake_acc_nodiv_ctrl_B_local_ABS_FL_Wheel_Threshold_10kmh = brake_acc_nodiv_ctrl_B_local_RT3;
                            }}
                }
    }
    else
if ((__cs_simulate == 0 && __cs_pc_3 <= 21) || (__cs_simulate == 1))    {
                if (__cs_simulate == 0 && __cs_pc_3 == 21) __cs_simulate = 1;
                if (__cs_simulate == 1){
                if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 21; __cs_simulate = 2;} else                {
                        brake_acc_nodiv_ctrl_B_local_ABS_FL_Wheel_Threshold_10kmh = brake_acc_nodiv_ctrl_B_local_RT3;
                }}
    }
    static int __cs_l_task_FL_Wheel_isr_3_In_BrakePedal_1;
    if (__cs_simulate == 0 && __cs_pc_3 == 22) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 22; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_task_FL_Wheel_isr_3_In_BrakePedal_1, sizeof(int));
    }}
    if (__cs_simulate == 0 && __cs_pc_3 == 23) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 23; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_3 <= 23) || (__cs_simulate == 1 && (__cs_l_task_FL_Wheel_isr_3_rtb_RelationalOperator_1)))
    {
                if (__cs_simulate == 1)
                {
                        __cs_l_task_FL_Wheel_isr_3_In_BrakePedal_1 = 15;
                }
    }
    else
if ((__cs_simulate == 0 && __cs_pc_3 <= 23) || (__cs_simulate == 1))    {
                if (__cs_simulate == 1)
                {
                        __cs_l_task_FL_Wheel_isr_3_In_BrakePedal_1 = 65;
                }
    }
    static int __cs_l_task_FL_Wheel_isr_3_Pedal_map_UpperSat_1;
    if (__cs_simulate == 1)
    {
            __cs_l_task_FL_Wheel_isr_3_Pedal_map_UpperSat_1 = 50;
    }
    static int __cs_l_task_FL_Wheel_isr_3_Pedal_map_LowerSat_1;
    if (__cs_simulate == 1)
    {
            __cs_l_task_FL_Wheel_isr_3_Pedal_map_LowerSat_1 = 20;
    }
    static int __cs_l_task_FL_Wheel_isr_3_tmp_1;
    if (__cs_simulate == 0 && __cs_pc_3 == 24) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 24; __cs_simulate = 2;} else    {
            __cs_init_scalar(&__cs_l_task_FL_Wheel_isr_3_tmp_1, sizeof(int));
    }}
    if (__cs_simulate == 0 && __cs_pc_3 == 25) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 25; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_3 <= 25) || (__cs_simulate == 1 && (__cs_l_task_FL_Wheel_isr_3_In_BrakePedal_1 >= __cs_l_task_FL_Wheel_isr_3_Pedal_map_UpperSat_1)))
    {
                if (__cs_simulate == 1)
                {
                        __cs_l_task_FL_Wheel_isr_3_tmp_1 = 50;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 26) __cs_simulate = 1;
    if (__cs_simulate == 1 && __VERIFIER_nondet_bool()) {__cs_pc_3 = 26; __cs_simulate = 2;}
    if ((__cs_simulate == 0 && __cs_pc_3 <= 26) || (__cs_simulate == 1 && (__cs_l_task_FL_Wheel_isr_3_In_BrakePedal_1 <= __cs_l_task_FL_Wheel_isr_3_Pedal_map_LowerSat_1)))
    {
                if (__cs_simulate == 1)
                {
                        __cs_l_task_FL_Wheel_isr_3_tmp_1 = 20;
                }
    }
    else
if ((__cs_simulate == 0 && __cs_pc_3 <= 26) || (__cs_simulate == 1))    {
                if (__cs_simulate == 1)
                {
                        __cs_l_task_FL_Wheel_isr_3_tmp_1 = 15;
                }
    }
    if (__cs_simulate == 0 && __cs_pc_3 == 27) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 27; __cs_simulate = 2;} else    {
            RT14 = brake_acc_nodiv_ctrl_P_Gain1_Gain + __cs_l_task_FL_Wheel_isr_3_tmp_1;
    }}
    if (__cs_simulate == 0 && __cs_pc_3 == 28) __cs_simulate = 1;
    if (__cs_simulate == 1){
    if (__VERIFIER_nondet_bool()) {__cs_pc_3 = 28; __cs_simulate = 2;} else    {
            RT12 = __cs_l_task_FL_Wheel_isr_3_rtb_to_int1_1;
    }}
    if (__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 29))
    {
        __cs_pc_3 = 29;
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
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 24)&&(__cs_pc_3 == 0 || __cs_pc_3 == 29)) main_task();
    __cs_simulate = 0;
    if (__cs_disable_isr_1 != 1) {
        task_compute_isr_1();
        if (__cs_pc_1 == 23) __cs_pc_1 = 0;
    }
    __cs_simulate = 0;
    if ((__cs_pc_3 == 0 || __cs_pc_3 == 29)&&__cs_disable_isr_2 != 1) {
        task_RR_Wheel_isr_2();
        if (__cs_pc_2 == 24) __cs_pc_2 = 0;
    }
    __cs_simulate = 0;
    if ((__cs_pc_2 == 0 || __cs_pc_2 == 24)&&__cs_disable_isr_3 != 1) {
        task_FL_Wheel_isr_3();
        if (__cs_pc_3 == 29) __cs_pc_3 = 0;
    }
  }
}
