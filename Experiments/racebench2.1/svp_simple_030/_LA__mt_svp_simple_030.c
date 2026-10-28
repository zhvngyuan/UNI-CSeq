

typedef int pthread_t;


void svp_simple_030_001_init();


void addData();


int svp_simple_030_001_isr_1_flag;


int svp_simple_030_001_gloable_var;


void *svp_simple_030_001_isr_1(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_1_IOVar1;
          

          int loop_1_IOVar2;
          

          int loop_1_block_1;
          

          int loop_1_block_2;
          

          for (int t_1 = 0; (t_1 < 3) && (funcunwind_t < 1); t_1++)          {
                    

                    loop_1_IOVar1 = funcunwind_t;
                    

                    loop_1_IOVar2 = svp_simple_030_001_gloable_var;
                    

                    loop_1_block_1 = nondet_int();
                    

                    loop_1_block_2 = nondet_int();
                    

                    funcunwind_t = loop_1_IOVar1 + (1 * loop_1_block_1);
                    

                    svp_simple_030_001_gloable_var = loop_1_IOVar2 + (1 * loop_1_block_2);
                    

                    __CPROVER_assume(loop_1_block_1 >= 0);
                    

                    __CPROVER_assume(loop_1_block_2 >= 0);
                    

                    __CPROVER_assume(loop_1_block_2 <= loop_1_block_1);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;


                                                            {
                                        

                                        svp_simple_030_001_gloable_var++;
                              }
                              

                              svp_simple_030_001_isr_1_flag = 0;
                              

                              enable_isr(2);
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_030_001_isr_1:
          

          ;

          

          pthread_exit(0);
}



void *svp_simple_030_001_isr_2(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_2_IOVar1;
          

          int loop_2_IOVar2;
          

          int loop_2_block_1;
          

          int loop_2_block_2;
          

          for (int t_2 = 0; (t_2 < 2) && (funcunwind_t < 1); t_2++)          {
                    

                    loop_2_IOVar1 = funcunwind_t;
                    

                    loop_2_IOVar2 = svp_simple_030_001_gloable_var;
                    

                    loop_2_block_1 = nondet_int();
                    

                    loop_2_block_2 = nondet_int();
                    

                    funcunwind_t = loop_2_IOVar1 + (1 * loop_2_block_1);
                    

                    svp_simple_030_001_gloable_var = loop_2_IOVar2 + (1 * loop_2_block_2);
                    

                    __CPROVER_assume(loop_2_block_1 >= 0);
                    

                    __CPROVER_assume(loop_2_block_2 >= 0);
                    

                    __CPROVER_assume(loop_2_block_2 <= loop_2_block_1);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              _Bool __cs_tmp_if_cond_0; __cs_tmp_if_cond_0 = (svp_simple_030_001_isr_1_flag); 
                              if (__cs_tmp_if_cond_0)


                                                            {
                                        

                                        svp_simple_030_001_gloable_var++;
                              }

                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_030_001_isr_2:
          

          ;

          

          pthread_exit(0);
}



void *svp_simple_030_001_isr_3(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_3_IOVar1;
          

          int loop_3_IOVar2;
          

          int loop_3_block_1;
          

          for (int t_3 = 0; (t_3 < 2) && (funcunwind_t < 1); t_3++)          {
                    

                    loop_3_IOVar1 = funcunwind_t;
                    

                    loop_3_IOVar2 = svp_simple_030_001_gloable_var;
                    

                    loop_3_block_1 = nondet_int();
                    

                    funcunwind_t = loop_3_IOVar1 + (1 * loop_3_block_1);
                    

                    svp_simple_030_001_gloable_var = loop_3_IOVar2 + (1 * loop_3_block_1);
                    

                    __CPROVER_assume(loop_3_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_030_001_gloable_var++;
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_030_001_isr_3:
          

          ;

          

          pthread_exit(0);
}



void idlerun()


{
          

          int i = 0;
          

          i = 0;
          

          int loop_4_IOVar1;
          

          int loop_4_block_1;
          

          for (int t_4 = 0; (t_4 < 1) && (i <= 100); t_4++)          {
                    

                    loop_4_IOVar1 = i;
                    

                    loop_4_block_1 = nondet_int();
                    

                    i = loop_4_IOVar1 + (1 * loop_4_block_1);
                    

                    __CPROVER_assume(loop_4_block_1 >= 0);
                    

                    __CPROVER_assume(i <= 100);


                                        {
                    }
                    

                    i++;
          }

          

          __CPROVER_assume(! (i <= 100));
}



void init()


{
          

          enable_isr(- 1);
}



void *main_task(void *arg)


{
          

          disable_isr(- 1);


                    {
                    

                    svp_simple_030_001_gloable_var = __VERIFIER_nondet_int();
                    

                    svp_simple_030_001_isr_1_flag = __VERIFIER_nondet_int();


                                        {
                              

                              enable_isr(- 1);
                    }
          }
          

          disable_isr(- 1);
          

          enable_isr(1);
          

          _Bool __cs_tmp_if_cond_1; __cs_tmp_if_cond_1 = (svp_simple_030_001_gloable_var > 12); 
          if (__cs_tmp_if_cond_1)


                    {
                    

                    assert(svp_simple_030_001_gloable_var > 12);
                    

                    svp_simple_030_001_gloable_var = 0;
                    

                    assert(svp_simple_030_001_gloable_var == 0);
          }

          

          goto __exit_main_task;
          

          __exit_main_task:
          

          ;

          

          pthread_exit(0);
}



int main()


{
          

          pthread_t t0;
          

          pthread_t t1;
          

          pthread_t t2;
          

          pthread_t t3;
          

          pthread_create(& t0, 0, main_task, 0);
          

          pthread_create(& t1, 0, svp_simple_030_001_isr_1, 0);
          

          pthread_create(& t2, 0, svp_simple_030_001_isr_2, 0);
          

          pthread_create(& t3, 0, svp_simple_030_001_isr_3, 0);
          

          __exit_main:
          

          ;

          

          pthread_exit(0);
}


