unsigned int __cs_pc_3 = 0U;
unsigned int __cs_pc_1 = 0U;
unsigned int __cs_pc_2 = 0U;
int __cs_simulate = 0;
void __cseq_error();
void __VERIFIER_assume(int i);
_Bool __VERIFIER_nondet_bool();
char __VERIFIER_nondet_char();
int __VERIFIER_nondet_int();
unsigned int __VERIFIER_nondet_uint();
void __cs_init_scalar(void *var, unsigned int size);
int __cs_disable_isr_0 = 0;
int __cs_disable_isr_1 = 0;
int __cs_disable_isr_2 = 0;
int g_var = 0;
int g_array[10] = {  };
int g_flag = 0;
int x = 0;
int y = 0;
int z = 0;
int reader1 = 0;
int reader2 = 0;
int reader3 = 0;
void main_task();
void isr_2();
void isr_1();
int main();
int static__isr_1____cs_l_isr_1_i = 0;
extern void __VERIFIER_error(void);
int main_0();
void main_task_1();
_Bool __VERIFIER_nondet_bool_2();
void isr_1_3();
_Bool __VERIFIER_nondet_bool_4();
_Bool __VERIFIER_nondet_bool_5();
_Bool __VERIFIER_nondet_bool_6();
_Bool __VERIFIER_nondet_bool_7();
_Bool __VERIFIER_nondet_bool_8();
_Bool __VERIFIER_nondet_bool_9();
_Bool __VERIFIER_nondet_bool_10();
_Bool __VERIFIER_nondet_bool_11();
_Bool __VERIFIER_nondet_bool_12();
void __cseq_error_13();
int main_0() {
  __cs_simulate = 0;
  __cs_pc_3 = 0;
  __cs_pc_1 = 0;
  __cs_pc_2 = 0;
  __cs_disable_isr_0 = 0;
  __cs_disable_isr_1 = 0;
  __cs_disable_isr_2 = 0;
  __cs_simulate = 0;
  __CPROVER_assume(__cs_pc_1 == 0);
  __CPROVER_assume(__cs_disable_isr_0 != 1);
  main_task_1();
  __cs_simulate = 0;
  __CPROVER_assume(__cs_disable_isr_1 != 1);
  isr_1_3();
}

void main_task_1() {
  __CPROVER_assume(__cs_simulate == 0);
  __CPROVER_assume(__cs_pc_3 == 0);
  __cs_simulate = 1;
  __CPROVER_assume(__cs_simulate == 1);
  _Bool __CPAchecker_TMP_0;
  __CPAchecker_TMP_0 = __VERIFIER_nondet_bool_2();
  __CPROVER_assume(!(__CPAchecker_TMP_0 == 0));
  __cs_pc_3 = 0;
  __cs_simulate = 2;
  __CPROVER_assume(!(__cs_simulate == 0));
  __CPROVER_assume(!(__cs_simulate == 1));
  __CPROVER_assume(!(__cs_simulate == 1));
  __CPROVER_assume(!(__cs_simulate == 0));
}

_Bool __VERIFIER_nondet_bool_2() {
  _Bool i;
  return i;
}

void isr_1_3() {
  __CPROVER_assume(__cs_simulate == 0);
  __CPROVER_assume(__cs_pc_1 == 0);
  __cs_simulate = 1;
  __CPROVER_assume(__cs_simulate == 1);
  _Bool __CPAchecker_TMP_0;
  __CPAchecker_TMP_0 = __VERIFIER_nondet_bool_4();
  __CPROVER_assume(__CPAchecker_TMP_0 == 0);
  g_flag = 1;
  __CPROVER_assume(!(__cs_simulate == 0));
  __CPROVER_assume(__cs_simulate == 1);
  _Bool __CPAchecker_TMP_1;
  __CPAchecker_TMP_1 = __VERIFIER_nondet_bool_5();
  __CPROVER_assume(__CPAchecker_TMP_1 == 0);
  __cs_disable_isr_2 = 1;
  __CPROVER_assume(!(__cs_simulate == 0));
  __CPROVER_assume(__cs_simulate == 1);
  _Bool __CPAchecker_TMP_2;
  __CPAchecker_TMP_2 = __VERIFIER_nondet_bool_6();
  __CPROVER_assume(__CPAchecker_TMP_2 == 0);
  x = 5;
  int loop_1_IOVar1;
  int loop_1_block_1;
  int t_1 = 0;
  __CPROVER_assume(!(__cs_simulate == 0));
  __CPROVER_assume(__cs_simulate == 1);
  _Bool __CPAchecker_TMP_3;
  __CPAchecker_TMP_3 = __VERIFIER_nondet_bool_7();
  __CPROVER_assume(__CPAchecker_TMP_3 == 0);
  __CPROVER_assume(!(__cs_simulate == 0));
  __CPROVER_assume(__cs_simulate == 1);
  __CPROVER_assume(t_1 < 2);
  __CPROVER_assume(static__isr_1____cs_l_isr_1_i < 10);
  __CPROVER_assume(__cs_simulate == 1);
  loop_1_IOVar1 = static__isr_1____cs_l_isr_1_i;
  __CPROVER_assume(__cs_simulate == 1);
  loop_1_block_1 = nondet_int();
  __CPROVER_assume(__cs_simulate == 1);
  static__isr_1____cs_l_isr_1_i = loop_1_IOVar1 + (1 * loop_1_block_1);
  __CPROVER_assume(!(__cs_simulate == 0));
  __CPROVER_assume(__cs_simulate == 1);
  _Bool __CPAchecker_TMP_4;
  __CPAchecker_TMP_4 = __VERIFIER_nondet_bool_8();
  __CPROVER_assume(__CPAchecker_TMP_4 == 0);
  __CPROVER_assume(loop_1_block_1 >= 0);
  __CPROVER_assume(!(__cs_simulate == 0));
  __CPROVER_assume(__cs_simulate == 1);
  _Bool __CPAchecker_TMP_5;
  __CPAchecker_TMP_5 = __VERIFIER_nondet_bool_9();
  __CPROVER_assume(__CPAchecker_TMP_5 == 0);
  __CPROVER_assume(static__isr_1____cs_l_isr_1_i < 10);
  __CPROVER_assume(!(__cs_simulate == 0));
  __CPROVER_assume(__cs_simulate == 1);
  _Bool __CPAchecker_TMP_6;
  __CPAchecker_TMP_6 = __VERIFIER_nondet_bool_10();
  __CPROVER_assume(__CPAchecker_TMP_6 == 0);
  g_array[static__isr_1____cs_l_isr_1_i] = 1;
  __CPROVER_assume(__cs_simulate == 1);
  const int __CPAchecker_TMP_7 = static__isr_1____cs_l_isr_1_i;
  static__isr_1____cs_l_isr_1_i = static__isr_1____cs_l_isr_1_i + 1;
  __CPAchecker_TMP_7;
  __CPROVER_assume(__cs_simulate == 1);
  const int __CPAchecker_TMP_8 = t_1;
  t_1 = t_1 + 1;
  __CPAchecker_TMP_8;
  __CPROVER_assume(!(__cs_simulate == 0));
  __CPROVER_assume(__cs_simulate == 1);
  __CPROVER_assume(t_1 < 2);
  __CPROVER_assume(!(static__isr_1____cs_l_isr_1_i < 10));
  __CPROVER_assume(!(__cs_simulate == 0));
  __CPROVER_assume(__cs_simulate == 1);
  _Bool __CPAchecker_TMP_9;
  __CPAchecker_TMP_9 = __VERIFIER_nondet_bool_11();
  __CPROVER_assume(__CPAchecker_TMP_9 == 0);
  __CPROVER_assume(static__isr_1____cs_l_isr_1_i >= 10);
  __CPROVER_assume(!(__cs_simulate == 0));
  __CPROVER_assume(__cs_simulate == 1);
  _Bool __CPAchecker_TMP_10;
  __CPAchecker_TMP_10 = __VERIFIER_nondet_bool_12();
  __CPROVER_assume(__CPAchecker_TMP_10 == 0);
  __CPROVER_assume(!((g_array[5]) == 1));
  __cseq_error_13();
}

_Bool __VERIFIER_nondet_bool_4() {
  _Bool i;
  return i;
}

_Bool __VERIFIER_nondet_bool_5() {
  _Bool i;
  return i;
}

_Bool __VERIFIER_nondet_bool_6() {
  _Bool i;
  return i;
}

_Bool __VERIFIER_nondet_bool_7() {
  _Bool i;
  return i;
}

_Bool __VERIFIER_nondet_bool_8() {
  _Bool i;
  return i;
}

_Bool __VERIFIER_nondet_bool_9() {
  _Bool i;
  return i;
}

_Bool __VERIFIER_nondet_bool_10() {
  _Bool i;
  return i;
}

_Bool __VERIFIER_nondet_bool_11() {
  _Bool i;
  return i;
}

_Bool __VERIFIER_nondet_bool_12() {
  _Bool i;
  return i;
}

void __cseq_error_13() {
  __VERIFIER_error(); // target state
}
