

typedef int pthread_t;


void svp_simple_027_001_init();


int svp_simple_027_001_gloable_var;


void *svp_simple_027_001_isr_1(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_1_IOVar1;
          

          int loop_1_IOVar2;
          

          int loop_1_block_1;
          

          for (int t_1 = 0; (t_1 < 2) && (funcunwind_t < 1); t_1++)          {
                    

                    loop_1_IOVar1 = funcunwind_t;
                    

                    loop_1_IOVar2 = svp_simple_027_001_gloable_var;
                    

                    loop_1_block_1 = nondet_int();
                    

                    funcunwind_t = loop_1_IOVar1 + (1 * loop_1_block_1);
                    

                    svp_simple_027_001_gloable_var = loop_1_IOVar2 + (1 * loop_1_block_1);
                    

                    __CPROVER_assume(loop_1_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_027_001_gloable_var++;
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_027_001_isr_1:
          

          ;

          

          pthread_exit(0);
}



void *svp_simple_027_001_isr_2(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_2_IOVar1;
          

          int loop_2_IOVar2;
          

          int loop_2_block_1;
          

          for (int t_2 = 0; (t_2 < 2) && (funcunwind_t < 1); t_2++)          {
                    

                    loop_2_IOVar1 = funcunwind_t;
                    

                    loop_2_IOVar2 = svp_simple_027_001_gloable_var;
                    

                    loop_2_block_1 = nondet_int();
                    

                    funcunwind_t = loop_2_IOVar1 + (1 * loop_2_block_1);
                    

                    svp_simple_027_001_gloable_var = loop_2_IOVar2 + (2 * loop_2_block_1);
                    

                    __CPROVER_assume(loop_2_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_027_001_gloable_var += 2;
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_027_001_isr_2:
          

          ;

          

          pthread_exit(0);
}



void *svp_simple_027_001_isr_3(void *arg)


{
          

          int funcunwind_t = 0;
          

          _Bool __cs_tmp_if_cond_0; __cs_tmp_if_cond_0 = (funcunwind_t < 1); 
          if (__cs_tmp_if_cond_0)
          {


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_027_001_gloable_var += 3;
                              

                              svp_simple_027_001_gloable_var = 0;
                              

                              assert(svp_simple_027_001_gloable_var == 0);
                    }
          }

          

          int loop_3_IOVar1;
          

          int loop_3_IOVar2;
          

          int loop_3_k2_1;
          

          int loop_3_block_1;
          

          for (int t_3 = 0; (t_3 < 2) && (funcunwind_t < 1); t_3++)          {
                    

                    loop_3_IOVar1 = funcunwind_t;
                    

                    loop_3_IOVar2 = svp_simple_027_001_gloable_var;
                    

                    loop_3_block_1 = nondet_int();
                    

                    funcunwind_t = loop_3_IOVar1 + (1 * loop_3_block_1);
                    

                    int IOVar_2_list[2];
                    

                    IOVar_2_list[0] = loop_3_IOVar2;
                    

                    IOVar_2_list[1] = 0;
                    

                    loop_3_k2_1 = nondet_int();
                    

                    __CPROVER_assume(loop_3_k2_1 >= 0);
                    

                    __CPROVER_assume(loop_3_k2_1 <= 1);
                    

                    svp_simple_027_001_gloable_var = IOVar_2_list[loop_3_k2_1] + (3 * loop_3_block_1);
                    

                    __CPROVER_assume(loop_3_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_027_001_gloable_var += 3;
                              

                              svp_simple_027_001_gloable_var = 0;
                              

                              __CPROVER_assume(svp_simple_027_001_gloable_var == 0);
                    }
          }

          

          _Bool __cs_tmp_if_cond_1; __cs_tmp_if_cond_1 = (funcunwind_t < 1); 
          if (__cs_tmp_if_cond_1)
          {


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_027_001_gloable_var += 3;
                              

                              svp_simple_027_001_gloable_var = 0;
                              

                              assert(svp_simple_027_001_gloable_var == 0);
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_027_001_isr_3:
          

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


                    {
                    

                    svp_simple_027_001_gloable_var = 15;
                    

                    assert(svp_simple_027_001_gloable_var == 15);


                                        {
                              

                              enable_isr(- 1);
                    }
          }
          

          disable_isr(- 1);
          

          enable_isr(1);
          

          _Bool __cs_tmp_if_cond_2; __cs_tmp_if_cond_2 = (svp_simple_027_001_gloable_var > 12); 
          if (__cs_tmp_if_cond_2)


                    {
                    

                    svp_simple_027_001_gloable_var = 0;
                    

                    assert(svp_simple_027_001_gloable_var == 0);
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
          

          pthread_create(& t1, 0, svp_simple_027_001_isr_1, 0);
          

          pthread_create(& t2, 0, svp_simple_027_001_isr_2, 0);
          

          pthread_create(& t3, 0, svp_simple_027_001_isr_3, 0);
          

          __exit_main:
          

          ;

          

          pthread_exit(0);
}


