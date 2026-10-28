CONTROL AUTOMATON ErrorPath1

INITIAL STATE ARG0;

STATE USEFIRST ARG0 :
    MATCH "" -> GOTO ARG240;
    TRUE -> STOP;

STATE USEFIRST ARG240 :
    MATCH "unsigned int __cs_pc_3;" -> GOTO ARG241_1_1;
STATE USEFIRST ARG241_0_1 :
    MATCH "unsigned int __cs_pc_3;" -> GOTO ARG241_1_1;
STATE USEFIRST ARG241_1_1 :
    MATCH "unsigned int __cs_pc_1;" -> GOTO ARG241_2_1;
STATE USEFIRST ARG241_2_1 :
    MATCH "unsigned int __cs_pc_2;" -> GOTO ARG241_3_1;
STATE USEFIRST ARG241_3_1 :
    MATCH "int __cs_simulate;" -> GOTO ARG241_4_1;
STATE USEFIRST ARG241_4_1 :
    MATCH "void __cseq_error()" -> GOTO ARG241_5_1;
STATE USEFIRST ARG241_5_1 :
    MATCH "void __VERIFIER_assume(int i)" -> GOTO ARG241_6_1;
STATE USEFIRST ARG241_6_1 :
    MATCH "_Bool __VERIFIER_nondet_bool()" -> GOTO ARG241_7_1;
STATE USEFIRST ARG241_7_1 :
    MATCH "char __VERIFIER_nondet_char()" -> GOTO ARG241_8_1;
STATE USEFIRST ARG241_8_1 :
    MATCH "int __VERIFIER_nondet_int()" -> GOTO ARG241_9_1;
STATE USEFIRST ARG241_9_1 :
    MATCH "unsigned int __VERIFIER_nondet_uint()" -> GOTO ARG241_10_1;
STATE USEFIRST ARG241_10_1 :
    MATCH "void __cs_init_scalar(void *var, unsigned int size)" -> GOTO ARG241_11_1;
STATE USEFIRST ARG241_11_1 :
    MATCH "int __cs_disable_isr_0;" -> GOTO ARG241_12_1;
STATE USEFIRST ARG241_12_1 :
    MATCH "int __cs_disable_isr_1;" -> GOTO ARG241_13_1;
STATE USEFIRST ARG241_13_1 :
    MATCH "int __cs_disable_isr_2;" -> GOTO ARG241_14_1;
STATE USEFIRST ARG241_14_1 :
    MATCH "int g_var;" -> GOTO ARG241_15_1;
STATE USEFIRST ARG241_15_1 :
    MATCH "int g_array[10];" -> GOTO ARG241_16_1;
STATE USEFIRST ARG241_16_1 :
    MATCH "int g_flag;" -> GOTO ARG241_17_1;
STATE USEFIRST ARG241_17_1 :
    MATCH "int x;" -> GOTO ARG241_18_1;
STATE USEFIRST ARG241_18_1 :
    MATCH "int y;" -> GOTO ARG241_19_1;
STATE USEFIRST ARG241_19_1 :
    MATCH "int z;" -> GOTO ARG241_20_1;
STATE USEFIRST ARG241_20_1 :
    MATCH "int reader1;" -> GOTO ARG241_21_1;
STATE USEFIRST ARG241_21_1 :
    MATCH "int reader2;" -> GOTO ARG241_22_1;
STATE USEFIRST ARG241_22_1 :
    MATCH "int reader3;" -> GOTO ARG241_23_1;
STATE USEFIRST ARG241_23_1 :
    MATCH "void main_task()" -> GOTO ARG241_24_1;
STATE USEFIRST ARG241_24_1 :
    MATCH "void isr_2()" -> GOTO ARG241_25_1;
STATE USEFIRST ARG241_25_1 :
    MATCH "void isr_1()" -> GOTO ARG241_26_1;
STATE USEFIRST ARG241_26_1 :
    MATCH "int main()" -> GOTO ARG241_27_1;
STATE USEFIRST ARG241_27_1 :
    MATCH "static int __cs_l_isr_1_i = 0;" -> GOTO ARG241_28_1;
STATE USEFIRST ARG241_28_1 :
    MATCH "" -> GOTO ARG241_29_1;
STATE USEFIRST ARG241_29_1 :
    MATCH "__cs_simulate = 0;" -> GOTO ARG241_30_1;
STATE USEFIRST ARG241_30_1 :
    MATCH "__cs_pc_3 = 0;" -> GOTO ARG241_31_1;
STATE USEFIRST ARG241_31_1 :
    MATCH "__cs_pc_1 = 0;" -> GOTO ARG241_32_1;
STATE USEFIRST ARG241_32_1 :
    MATCH "__cs_pc_2 = 0;" -> GOTO ARG241_33_1;
STATE USEFIRST ARG241_33_1 :
    MATCH "__cs_disable_isr_0 = 0;" -> GOTO ARG241_34_1;
STATE USEFIRST ARG241_34_1 :
    MATCH "__cs_disable_isr_1 = 0;" -> GOTO ARG241_35_1;
STATE USEFIRST ARG241_35_1 :
    MATCH "__cs_disable_isr_2 = 0;" -> ASSUME {__cs_pc_3 == (0U);__cs_pc_1 == (0U);__cs_pc_2 == (0U);__cs_simulate == (0);__cs_disable_isr_0 == (0);__cs_disable_isr_1 == (0);__cs_disable_isr_2 == (0);(&g_array) == (4LL);__cs_l_isr_1_i == (0);} GOTO ARG241;
    TRUE -> STOP;

STATE USEFIRST ARG241 :
    MATCH "" -> GOTO ARG480;
    TRUE -> STOP;

STATE USEFIRST ARG480 :
    MATCH "1" -> GOTO ARG481_1_2;
STATE USEFIRST ARG481_0_2 :
    MATCH "1" -> GOTO ARG481_1_2;
STATE USEFIRST ARG481_1_2 :
    MATCH "__cs_simulate = 0;" -> ASSUME {__cs_simulate == (0);} GOTO ARG481;
    TRUE -> STOP;

STATE USEFIRST ARG481 :
    MATCH "[(__cs_pc_1 == 0 || __cs_pc_1 == 12)&&__cs_disable_isr_0 != 1]" -> ASSUME {__cs_pc_1 == (0U);} GOTO ARG486;
    TRUE -> STOP;

STATE USEFIRST ARG486 :
    MATCH "[(__cs_pc_1 == 0 || __cs_pc_1 == 12)&&__cs_disable_isr_0 != 1]" -> ASSUME {__cs_disable_isr_0 == (0);} GOTO ARG487;
    MATCH "[!((__cs_pc_1 == 0 || __cs_pc_1 == 12)&&__cs_disable_isr_0 != 1)]" -> GOTO ARG552;
    TRUE -> STOP;

STATE USEFIRST ARG487 :
    MATCH "main_task();" -> GOTO ARG490;
    TRUE -> STOP;

STATE USEFIRST ARG490 :
    MATCH "" -> GOTO ARG491;
    TRUE -> STOP;

STATE USEFIRST ARG491 :
    MATCH "[__cs_simulate == 0 && __cs_pc_3 == 0]" -> ASSUME {__cs_simulate == (0);} GOTO ARG492;
    MATCH "[!(__cs_simulate == 0 && __cs_pc_3 == 0)]" -> GOTO ARG499;
    TRUE -> STOP;

STATE USEFIRST ARG492 :
    MATCH "[__cs_simulate == 0 && __cs_pc_3 == 0]" -> ASSUME {__cs_pc_3 == (0U);} GOTO ARG494;
    MATCH "[!(__cs_simulate == 0 && __cs_pc_3 == 0)]" -> GOTO ARG499;
    TRUE -> STOP;

STATE USEFIRST ARG494 :
    MATCH "__cs_simulate = 1;" -> ASSUME {__cs_simulate == (1);} GOTO ARG497;
    TRUE -> STOP;

STATE USEFIRST ARG497 :
    MATCH "" -> GOTO ARG499;
    TRUE -> STOP;

STATE USEFIRST ARG499 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG500;
    MATCH "[!(__cs_simulate == 1)]" -> GOTO ARG514;
    TRUE -> STOP;

STATE USEFIRST ARG500 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG502;
    TRUE -> STOP;

STATE USEFIRST ARG502 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG503;
    TRUE -> STOP;

STATE USEFIRST ARG503 :
    MATCH "" -> GOTO ARG504_1_3;
STATE USEFIRST ARG504_0_3 :
    MATCH "" -> GOTO ARG504_1_3;
STATE USEFIRST ARG504_1_3 :
    MATCH "_Bool i;" -> GOTO ARG504;
    TRUE -> STOP;

STATE USEFIRST ARG504 :
    MATCH "return i;" -> GOTO ARG505;
    TRUE -> STOP;

STATE USEFIRST ARG505 :
    MATCH "" -> GOTO ARG506;
    TRUE -> STOP;

STATE USEFIRST ARG506 :
    MATCH "[__VERIFIER_nondet_bool()]" -> ASSUME {__CPAchecker_TMP_0 == (1);} GOTO ARG508;
    TRUE -> STOP;

STATE USEFIRST ARG508 :
    MATCH "__cs_pc_3 = 0;" -> GOTO ARG509_1_4;
STATE USEFIRST ARG509_0_4 :
    MATCH "__cs_pc_3 = 0;" -> GOTO ARG509_1_4;
STATE USEFIRST ARG509_1_4 :
    MATCH "__cs_simulate = 2;" -> ASSUME {__cs_pc_3 == (0U);__cs_simulate == (2);} GOTO ARG509;
    TRUE -> STOP;

STATE USEFIRST ARG509 :
    MATCH "" -> GOTO ARG514;
    TRUE -> STOP;

STATE USEFIRST ARG514 :
    MATCH "[!(__cs_simulate == 0 && __cs_pc_3 == 1)]" -> ASSUME {__cs_simulate == (2);} GOTO ARG522;
    TRUE -> STOP;

STATE USEFIRST ARG522 :
    MATCH "[!(__cs_simulate == 1)]" -> ASSUME {__cs_simulate == (2);} GOTO ARG537;
    TRUE -> STOP;

STATE USEFIRST ARG537 :
    MATCH "[!(__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 2))]" -> ASSUME {__cs_simulate == (2);} GOTO ARG539;
    TRUE -> STOP;

STATE USEFIRST ARG539 :
    MATCH "[!(__cs_simulate == 1 || (__cs_simulate == 0 && __cs_pc_3 == 2))]" -> ASSUME {__cs_simulate == (2);} GOTO ARG548;
    TRUE -> STOP;

STATE USEFIRST ARG548 :
    MATCH "" -> GOTO ARG549;
    TRUE -> STOP;

STATE USEFIRST ARG549 :
    MATCH "" -> GOTO ARG550;
    TRUE -> STOP;

STATE USEFIRST ARG550 :
    MATCH "" -> GOTO ARG552;
    TRUE -> STOP;

STATE USEFIRST ARG552 :
    MATCH "__cs_simulate = 0;" -> ASSUME {__cs_simulate == (0);} GOTO ARG553;
    TRUE -> STOP;

STATE USEFIRST ARG553 :
    MATCH "[__cs_disable_isr_1 != 1]" -> ASSUME {__cs_disable_isr_1 == (0);} GOTO ARG554;
    TRUE -> STOP;

STATE USEFIRST ARG554 :
    MATCH "isr_1();" -> GOTO ARG556;
    TRUE -> STOP;

STATE USEFIRST ARG556 :
    MATCH "" -> GOTO ARG557;
    TRUE -> STOP;

STATE USEFIRST ARG557 :
    MATCH "[__cs_simulate == 0 && __cs_pc_1 == 0]" -> ASSUME {__cs_simulate == (0);} GOTO ARG558;
    MATCH "[!(__cs_simulate == 0 && __cs_pc_1 == 0)]" -> GOTO ARG565;
    TRUE -> STOP;

STATE USEFIRST ARG558 :
    MATCH "[__cs_simulate == 0 && __cs_pc_1 == 0]" -> ASSUME {__cs_pc_1 == (0U);} GOTO ARG560;
    MATCH "[!(__cs_simulate == 0 && __cs_pc_1 == 0)]" -> GOTO ARG565;
    TRUE -> STOP;

STATE USEFIRST ARG560 :
    MATCH "__cs_simulate = 1;" -> ASSUME {__cs_simulate == (1);} GOTO ARG563;
    TRUE -> STOP;

STATE USEFIRST ARG563 :
    MATCH "" -> GOTO ARG565;
    TRUE -> STOP;

STATE USEFIRST ARG565 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG566;
    MATCH "[!(__cs_simulate == 1)]" -> GOTO ARG580;
    TRUE -> STOP;

STATE USEFIRST ARG566 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG568;
    TRUE -> STOP;

STATE USEFIRST ARG568 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG569;
    TRUE -> STOP;

STATE USEFIRST ARG569 :
    MATCH "" -> GOTO ARG570_1_5;
STATE USEFIRST ARG570_0_5 :
    MATCH "" -> GOTO ARG570_1_5;
STATE USEFIRST ARG570_1_5 :
    MATCH "_Bool i;" -> GOTO ARG570;
    TRUE -> STOP;

STATE USEFIRST ARG570 :
    MATCH "return i;" -> GOTO ARG571;
    TRUE -> STOP;

STATE USEFIRST ARG571 :
    MATCH "" -> GOTO ARG572;
    TRUE -> STOP;

STATE USEFIRST ARG572 :
    MATCH "[!(__VERIFIER_nondet_bool())]" -> ASSUME {__CPAchecker_TMP_0 == (0);} GOTO ARG573;
    TRUE -> STOP;

STATE USEFIRST ARG573 :
    MATCH "g_flag = 1;" -> GOTO ARG578;
    TRUE -> STOP;

STATE USEFIRST ARG578 :
    MATCH "" -> GOTO ARG580;
    TRUE -> STOP;

STATE USEFIRST ARG580 :
    MATCH "[!(__cs_simulate == 0 && __cs_pc_1 == 1)]" -> ASSUME {__cs_simulate == (1);} GOTO ARG588;
    TRUE -> STOP;

STATE USEFIRST ARG588 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG589;
    MATCH "[!(__cs_simulate == 1)]" -> GOTO ARG603;
    TRUE -> STOP;

STATE USEFIRST ARG589 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG591;
    TRUE -> STOP;

STATE USEFIRST ARG591 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG592;
    TRUE -> STOP;

STATE USEFIRST ARG592 :
    MATCH "" -> GOTO ARG593_1_6;
STATE USEFIRST ARG593_0_6 :
    MATCH "" -> GOTO ARG593_1_6;
STATE USEFIRST ARG593_1_6 :
    MATCH "_Bool i;" -> GOTO ARG593;
    TRUE -> STOP;

STATE USEFIRST ARG593 :
    MATCH "return i;" -> GOTO ARG594;
    TRUE -> STOP;

STATE USEFIRST ARG594 :
    MATCH "" -> GOTO ARG595;
    TRUE -> STOP;

STATE USEFIRST ARG595 :
    MATCH "[!(__VERIFIER_nondet_bool())]" -> ASSUME {__CPAchecker_TMP_1 == (0);} GOTO ARG596;
    TRUE -> STOP;

STATE USEFIRST ARG596 :
    MATCH "__cs_disable_isr_2 = 1;" -> ASSUME {__cs_disable_isr_2 == (1);} GOTO ARG601;
    TRUE -> STOP;

STATE USEFIRST ARG601 :
    MATCH "" -> GOTO ARG603;
    TRUE -> STOP;

STATE USEFIRST ARG603 :
    MATCH "[!(__cs_simulate == 0 && __cs_pc_1 == 2)]" -> ASSUME {__cs_simulate == (1);} GOTO ARG611;
    TRUE -> STOP;

STATE USEFIRST ARG611 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG612;
    MATCH "[!(__cs_simulate == 1)]" -> GOTO ARG626;
    TRUE -> STOP;

STATE USEFIRST ARG612 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG614;
    TRUE -> STOP;

STATE USEFIRST ARG614 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG615;
    TRUE -> STOP;

STATE USEFIRST ARG615 :
    MATCH "" -> GOTO ARG616_1_7;
STATE USEFIRST ARG616_0_7 :
    MATCH "" -> GOTO ARG616_1_7;
STATE USEFIRST ARG616_1_7 :
    MATCH "_Bool i;" -> GOTO ARG616;
    TRUE -> STOP;

STATE USEFIRST ARG616 :
    MATCH "return i;" -> GOTO ARG617;
    TRUE -> STOP;

STATE USEFIRST ARG617 :
    MATCH "" -> GOTO ARG618;
    TRUE -> STOP;

STATE USEFIRST ARG618 :
    MATCH "[!(__VERIFIER_nondet_bool())]" -> ASSUME {__CPAchecker_TMP_2 == (0);} GOTO ARG619;
    TRUE -> STOP;

STATE USEFIRST ARG619 :
    MATCH "x = 5;" -> GOTO ARG624;
    TRUE -> STOP;

STATE USEFIRST ARG624 :
    MATCH "" -> GOTO ARG626;
    TRUE -> STOP;

STATE USEFIRST ARG626 :
    MATCH "__begin_isr_1_loop_0:;" -> GOTO ARG627;
    TRUE -> STOP;

STATE USEFIRST ARG627 :
    MATCH "int loop_1_IOVar1;" -> GOTO ARG628_1_8;
STATE USEFIRST ARG628_0_8 :
    MATCH "int loop_1_IOVar1;" -> GOTO ARG628_1_8;
STATE USEFIRST ARG628_1_8 :
    MATCH "int loop_1_block_1;" -> GOTO ARG628_2_8;
STATE USEFIRST ARG628_2_8 :
    MATCH "int t_1 = 0;" -> ASSUME {t_1 == (0);} GOTO ARG628;
    TRUE -> STOP;

STATE USEFIRST ARG628 :
    MATCH "[!(__cs_simulate == 0 && __cs_pc_1 == 3)]" -> ASSUME {__cs_simulate == (1);} GOTO ARG636;
    TRUE -> STOP;

STATE USEFIRST ARG636 :
    MATCH "[__cs_simulate == 1 && __VERIFIER_nondet_bool()]" -> ASSUME {__cs_simulate == (1);} GOTO ARG637;
    MATCH "[!(__cs_simulate == 1 && __VERIFIER_nondet_bool())]" -> GOTO ARG649;
    TRUE -> STOP;

STATE USEFIRST ARG637 :
    MATCH "__cs_simulate == 1 && __VERIFIER_nondet_bool()" -> GOTO ARG639;
    TRUE -> STOP;

STATE USEFIRST ARG639 :
    MATCH "__cs_simulate == 1 && __VERIFIER_nondet_bool()" -> GOTO ARG640;
    TRUE -> STOP;

STATE USEFIRST ARG640 :
    MATCH "" -> GOTO ARG641_1_9;
STATE USEFIRST ARG641_0_9 :
    MATCH "" -> GOTO ARG641_1_9;
STATE USEFIRST ARG641_1_9 :
    MATCH "_Bool i;" -> GOTO ARG641;
    TRUE -> STOP;

STATE USEFIRST ARG641 :
    MATCH "return i;" -> GOTO ARG642;
    TRUE -> STOP;

STATE USEFIRST ARG642 :
    MATCH "" -> GOTO ARG643;
    TRUE -> STOP;

STATE USEFIRST ARG643 :
    MATCH "[!(__cs_simulate == 1 && __VERIFIER_nondet_bool())]" -> ASSUME {__CPAchecker_TMP_3 == (0);} GOTO ARG649;
    TRUE -> STOP;

STATE USEFIRST ARG649 :
    MATCH "" -> GOTO ARG651;
    TRUE -> STOP;

STATE USEFIRST ARG651 :
    MATCH "[!((__cs_simulate == 0 && __cs_pc_1 <= 6) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_isr_1_i < 10))))]" -> ASSUME {__cs_simulate == (1);} GOTO ARG656;
    TRUE -> STOP;

STATE USEFIRST ARG656 :
    MATCH "[(__cs_simulate == 0 && __cs_pc_1 <= 6) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_isr_1_i < 10)))]" -> ASSUME {__cs_simulate == (1);} GOTO ARG657;
    TRUE -> STOP;

STATE USEFIRST ARG657 :
    MATCH "[(__cs_simulate == 0 && __cs_pc_1 <= 6) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_isr_1_i < 10)))]" -> ASSUME {t_1 == (0);} GOTO ARG659;
    TRUE -> STOP;

STATE USEFIRST ARG659 :
    MATCH "[(__cs_simulate == 0 && __cs_pc_1 <= 6) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_isr_1_i < 10)))]" -> ASSUME {__cs_l_isr_1_i == (0);} GOTO ARG664;
    TRUE -> STOP;

STATE USEFIRST ARG664 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG799;
    MATCH "[!(__cs_simulate == 1)]" -> GOTO ARG803;
    TRUE -> STOP;

STATE USEFIRST ARG799 :
    MATCH "loop_1_IOVar1 = __cs_l_isr_1_i;" -> ASSUME {loop_1_IOVar1 == (0);} GOTO ARG801;
    TRUE -> STOP;

STATE USEFIRST ARG801 :
    MATCH "" -> GOTO ARG803;
    TRUE -> STOP;

STATE USEFIRST ARG803 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG804;
    MATCH "[!(__cs_simulate == 1)]" -> GOTO ARG808;
    TRUE -> STOP;

STATE USEFIRST ARG804 :
    MATCH "loop_1_block_1 = nondet_int();" -> ASSUME {loop_1_block_1 == (15);} GOTO ARG806;
    TRUE -> STOP;

STATE USEFIRST ARG806 :
    MATCH "" -> GOTO ARG808;
    TRUE -> STOP;

STATE USEFIRST ARG808 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG809;
    MATCH "[!(__cs_simulate == 1)]" -> GOTO ARG813;
    TRUE -> STOP;

STATE USEFIRST ARG809 :
    MATCH "__cs_l_isr_1_i = loop_1_IOVar1 + (1 * loop_1_block_1);" -> ASSUME {__cs_l_isr_1_i == (15);} GOTO ARG811;
    TRUE -> STOP;

STATE USEFIRST ARG811 :
    MATCH "" -> GOTO ARG813;
    TRUE -> STOP;

STATE USEFIRST ARG813 :
    MATCH "[!(__cs_simulate == 0 && __cs_pc_1 == 4)]" -> ASSUME {__cs_simulate == (1);} GOTO ARG821;
    TRUE -> STOP;

STATE USEFIRST ARG821 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG822;
    MATCH "[!(__cs_simulate == 1)]" -> GOTO ARG836;
    TRUE -> STOP;

STATE USEFIRST ARG822 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG824;
    TRUE -> STOP;

STATE USEFIRST ARG824 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG825;
    TRUE -> STOP;

STATE USEFIRST ARG825 :
    MATCH "" -> GOTO ARG826_1_10;
STATE USEFIRST ARG826_0_10 :
    MATCH "" -> GOTO ARG826_1_10;
STATE USEFIRST ARG826_1_10 :
    MATCH "_Bool i;" -> GOTO ARG826;
    TRUE -> STOP;

STATE USEFIRST ARG826 :
    MATCH "return i;" -> GOTO ARG827;
    TRUE -> STOP;

STATE USEFIRST ARG827 :
    MATCH "" -> GOTO ARG828;
    TRUE -> STOP;

STATE USEFIRST ARG828 :
    MATCH "[!(__VERIFIER_nondet_bool())]" -> ASSUME {__CPAchecker_TMP_4 == (0);} GOTO ARG829;
    TRUE -> STOP;

STATE USEFIRST ARG829 :
    MATCH "__CPROVER_assume(loop_1_block_1 >= 0);" -> GOTO ARG834;
    TRUE -> STOP;

STATE USEFIRST ARG834 :
    MATCH "" -> GOTO ARG836;
    TRUE -> STOP;

STATE USEFIRST ARG836 :
    MATCH "[!(__cs_simulate == 0 && __cs_pc_1 == 5)]" -> ASSUME {__cs_simulate == (1);} GOTO ARG844;
    TRUE -> STOP;

STATE USEFIRST ARG844 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG845;
    MATCH "[!(__cs_simulate == 1)]" -> GOTO ARG859;
    TRUE -> STOP;

STATE USEFIRST ARG845 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG847;
    TRUE -> STOP;

STATE USEFIRST ARG847 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG848;
    TRUE -> STOP;

STATE USEFIRST ARG848 :
    MATCH "" -> GOTO ARG849_1_11;
STATE USEFIRST ARG849_0_11 :
    MATCH "" -> GOTO ARG849_1_11;
STATE USEFIRST ARG849_1_11 :
    MATCH "_Bool i;" -> GOTO ARG849;
    TRUE -> STOP;

STATE USEFIRST ARG849 :
    MATCH "return i;" -> GOTO ARG850;
    TRUE -> STOP;

STATE USEFIRST ARG850 :
    MATCH "" -> GOTO ARG851;
    TRUE -> STOP;

STATE USEFIRST ARG851 :
    MATCH "[!(__VERIFIER_nondet_bool())]" -> ASSUME {__CPAchecker_TMP_5 == (0);} GOTO ARG852;
    TRUE -> STOP;

STATE USEFIRST ARG852 :
    MATCH "__CPROVER_assume(__cs_l_isr_1_i < 10);" -> GOTO ARG857;
    TRUE -> STOP;

STATE USEFIRST ARG857 :
    MATCH "" -> GOTO ARG859;
    TRUE -> STOP;

STATE USEFIRST ARG859 :
    MATCH "[!(__cs_simulate == 0 && __cs_pc_1 == 6)]" -> ASSUME {__cs_simulate == (1);} GOTO ARG867;
    TRUE -> STOP;

STATE USEFIRST ARG867 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG868;
    MATCH "[!(__cs_simulate == 1)]" -> GOTO ARG882;
    TRUE -> STOP;

STATE USEFIRST ARG868 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG870;
    TRUE -> STOP;

STATE USEFIRST ARG870 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG871;
    TRUE -> STOP;

STATE USEFIRST ARG871 :
    MATCH "" -> GOTO ARG872_1_12;
STATE USEFIRST ARG872_0_12 :
    MATCH "" -> GOTO ARG872_1_12;
STATE USEFIRST ARG872_1_12 :
    MATCH "_Bool i;" -> GOTO ARG872;
    TRUE -> STOP;

STATE USEFIRST ARG872 :
    MATCH "return i;" -> GOTO ARG873;
    TRUE -> STOP;

STATE USEFIRST ARG873 :
    MATCH "" -> GOTO ARG874;
    TRUE -> STOP;

STATE USEFIRST ARG874 :
    MATCH "[!(__VERIFIER_nondet_bool())]" -> ASSUME {__CPAchecker_TMP_6 == (0);} GOTO ARG875;
    TRUE -> STOP;

STATE USEFIRST ARG875 :
    MATCH "g_array[__cs_l_isr_1_i] = 1;" -> ASSUME {(g_array[__cs_l_isr_1_i]) == (1);} GOTO ARG880;
    TRUE -> STOP;

STATE USEFIRST ARG880 :
    MATCH "" -> GOTO ARG882;
    TRUE -> STOP;

STATE USEFIRST ARG882 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG883;
    MATCH "[!(__cs_simulate == 1)]" -> GOTO ARG887;
    TRUE -> STOP;

STATE USEFIRST ARG883 :
    MATCH "__cs_l_isr_1_i++;" -> GOTO ARG885_1_13;
STATE USEFIRST ARG885_0_13 :
    MATCH "__cs_l_isr_1_i++;" -> GOTO ARG885_1_13;
STATE USEFIRST ARG885_1_13 :
    MATCH "__cs_l_isr_1_i++;" -> GOTO ARG885_2_13;
STATE USEFIRST ARG885_2_13 :
    MATCH "__cs_l_isr_1_i++;" -> ASSUME {__cs_l_isr_1_i == (16);} GOTO ARG885;
    TRUE -> STOP;

STATE USEFIRST ARG885 :
    MATCH "" -> GOTO ARG887;
    TRUE -> STOP;

STATE USEFIRST ARG887 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG888;
    MATCH "[!(__cs_simulate == 1)]" -> GOTO ARG892;
    TRUE -> STOP;

STATE USEFIRST ARG888 :
    MATCH "t_1++;" -> GOTO ARG890_1_14;
STATE USEFIRST ARG890_0_14 :
    MATCH "t_1++;" -> GOTO ARG890_1_14;
STATE USEFIRST ARG890_1_14 :
    MATCH "t_1++;" -> GOTO ARG890_2_14;
STATE USEFIRST ARG890_2_14 :
    MATCH "t_1++;" -> ASSUME {t_1 == (1);} GOTO ARG890;
    TRUE -> STOP;

STATE USEFIRST ARG890 :
    MATCH "" -> GOTO ARG892;
    TRUE -> STOP;

STATE USEFIRST ARG892 :
    MATCH "" -> GOTO ARG894;
    TRUE -> STOP;

STATE USEFIRST ARG894 :
    MATCH "[!((__cs_simulate == 0 && __cs_pc_1 <= 6) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_isr_1_i < 10))))]" -> ASSUME {__cs_simulate == (1);} GOTO ARG899;
    TRUE -> STOP;

STATE USEFIRST ARG899 :
    MATCH "[(__cs_simulate == 0 && __cs_pc_1 <= 6) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_isr_1_i < 10)))]" -> ASSUME {__cs_simulate == (1);} GOTO ARG900;
    MATCH "[!((__cs_simulate == 0 && __cs_pc_1 <= 6) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_isr_1_i < 10))))]" -> GOTO ARG908;
    TRUE -> STOP;

STATE USEFIRST ARG900 :
    MATCH "[(__cs_simulate == 0 && __cs_pc_1 <= 6) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_isr_1_i < 10)))]" -> ASSUME {t_1 == (1);} GOTO ARG902;
    MATCH "[!((__cs_simulate == 0 && __cs_pc_1 <= 6) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_isr_1_i < 10))))]" -> GOTO ARG908;
    TRUE -> STOP;

STATE USEFIRST ARG902 :
    MATCH "[!((__cs_simulate == 0 && __cs_pc_1 <= 6) || ((__cs_simulate == 1) && ((t_1 < 2) && (__cs_l_isr_1_i < 10))))]" -> ASSUME {__cs_l_isr_1_i == (16);} GOTO ARG908;
    TRUE -> STOP;

STATE USEFIRST ARG908 :
    MATCH "[!(__cs_simulate == 0 && __cs_pc_1 == 7)]" -> ASSUME {__cs_simulate == (1);} GOTO ARG916;
    TRUE -> STOP;

STATE USEFIRST ARG916 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG917;
    MATCH "[!(__cs_simulate == 1)]" -> GOTO ARG931;
    TRUE -> STOP;

STATE USEFIRST ARG917 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG919;
    TRUE -> STOP;

STATE USEFIRST ARG919 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG920;
    TRUE -> STOP;

STATE USEFIRST ARG920 :
    MATCH "" -> GOTO ARG921_1_15;
STATE USEFIRST ARG921_0_15 :
    MATCH "" -> GOTO ARG921_1_15;
STATE USEFIRST ARG921_1_15 :
    MATCH "_Bool i;" -> GOTO ARG921;
    TRUE -> STOP;

STATE USEFIRST ARG921 :
    MATCH "return i;" -> GOTO ARG922;
    TRUE -> STOP;

STATE USEFIRST ARG922 :
    MATCH "" -> GOTO ARG923;
    TRUE -> STOP;

STATE USEFIRST ARG923 :
    MATCH "[!(__VERIFIER_nondet_bool())]" -> ASSUME {__CPAchecker_TMP_9 == (0);} GOTO ARG924;
    TRUE -> STOP;

STATE USEFIRST ARG924 :
    MATCH "__CPROVER_assume(!(__cs_l_isr_1_i < 10));" -> GOTO ARG929;
    TRUE -> STOP;

STATE USEFIRST ARG929 :
    MATCH "" -> GOTO ARG931;
    TRUE -> STOP;

STATE USEFIRST ARG931 :
    MATCH "__end_isr_1_loop_0:;" -> GOTO ARG932;
    TRUE -> STOP;

STATE USEFIRST ARG932 :
    MATCH "[!(__cs_simulate == 0 && __cs_pc_1 == 8)]" -> ASSUME {__cs_simulate == (1);} GOTO ARG940;
    TRUE -> STOP;

STATE USEFIRST ARG940 :
    MATCH "[__cs_simulate == 1]" -> ASSUME {__cs_simulate == (1);} GOTO ARG941;
    TRUE -> STOP;

STATE USEFIRST ARG941 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG943;
    TRUE -> STOP;

STATE USEFIRST ARG943 :
    MATCH "__VERIFIER_nondet_bool()" -> GOTO ARG944;
    TRUE -> STOP;

STATE USEFIRST ARG944 :
    MATCH "" -> GOTO ARG945_1_16;
STATE USEFIRST ARG945_0_16 :
    MATCH "" -> GOTO ARG945_1_16;
STATE USEFIRST ARG945_1_16 :
    MATCH "_Bool i;" -> GOTO ARG945;
    TRUE -> STOP;

STATE USEFIRST ARG945 :
    MATCH "return i;" -> GOTO ARG946;
    TRUE -> STOP;

STATE USEFIRST ARG946 :
    MATCH "" -> GOTO ARG947;
    TRUE -> STOP;

STATE USEFIRST ARG947 :
    MATCH "[!(__VERIFIER_nondet_bool())]" -> ASSUME {__CPAchecker_TMP_10 == (0);} GOTO ARG948;
    TRUE -> STOP;

STATE USEFIRST ARG948 :
    MATCH "[!(g_array[5] == 1)]" -> GOTO ARG954;
    TRUE -> STOP;

STATE USEFIRST ARG954 :
    MATCH "__cseq_error();" -> GOTO ARG955;
    TRUE -> STOP;

STATE USEFIRST ARG955 :
    MATCH "" -> GOTO ARG956;
    TRUE -> STOP;

STATE USEFIRST ARG956 :
    MATCH "ERROR: goto ERROR;" -> ERROR;
    TRUE -> STOP;

STATE USEFIRST ARG958 :
    TRUE -> STOP;

END AUTOMATON
