

typedef int pthread_t;


int svp_simple_001_001_global_var;


int svp_simple_001_001_global_array[10];


int svp_simple_001_001_global_flag = 0;


void *svp_simple_001_001_isr_1(void *arg)


{
          

          int funcunwind_t = 0;
          

          _Bool __cs_tmp_if_cond_0; __cs_tmp_if_cond_0 = (funcunwind_t < 1); 
          if (__cs_tmp_if_cond_0)
          {


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_001_001_global_flag = 1;
                              

                              assert(svp_simple_001_001_global_flag == 1);
                              

                              svp_simple_001_001_global_var = 0;
                              

                              svp_simple_001_001_global_var = 1;
                              

                              enable_isr(2);
                    }
          }

          

          int loop_1_IOVar1;
          

          int loop_1_block_1;
          

          for (int t_1 = 0; (t_1 < 3) && (funcunwind_t < 1); t_1++)          {
                    

                    loop_1_IOVar1 = funcunwind_t;
                    

                    loop_1_block_1 = nondet_int();
                    

                    funcunwind_t = loop_1_IOVar1 + (1 * loop_1_block_1);
                    

                    __CPROVER_assume(loop_1_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_001_001_global_flag = 1;
                              

                              __CPROVER_assume(svp_simple_001_001_global_flag == 1);
                              

                              svp_simple_001_001_global_var = 0;
                              

                              svp_simple_001_001_global_var = 1;
                              

                              enable_isr(2);
                    }
          }

          

          _Bool __cs_tmp_if_cond_1; __cs_tmp_if_cond_1 = (funcunwind_t < 1); 
          if (__cs_tmp_if_cond_1)
          {


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_001_001_global_flag = 1;
                              

                              assert(svp_simple_001_001_global_flag == 1);
                              

                              svp_simple_001_001_global_var = 0;
                              

                              svp_simple_001_001_global_var = 1;
                              

                              enable_isr(2);
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_001_001_isr_1:
          

          ;

          

          pthread_exit(0);
}



void *svp_simple_001_001_isr_2(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_2_IOVar1;
          

          int loop_2_block_1;
          

          for (int t_2 = 0; (t_2 < 5) && (funcunwind_t < 1); t_2++)          {
                    

                    int reader1;
                    

                    int reader3;
                    

                    int reader2;
                    

                    loop_2_IOVar1 = funcunwind_t;
                    

                    loop_2_block_1 = nondet_int();
                    

                    funcunwind_t = loop_2_IOVar1 + (1 * loop_2_block_1);
                    

                    __CPROVER_assume(loop_2_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              int reader1;
                              

                              int reader3;
                              

                              _Bool __cs_tmp_if_cond_2; __cs_tmp_if_cond_2 = (svp_simple_001_001_global_flag == 

                              1); 
                              if (__cs_tmp_if_cond_2)


                                                            {
                                        

                                        reader1 = svp_simple_001_001_global_array[9999];
                                        

                                        svp_simple_001_001_global_array[9999] = 0;
                              }
                              else


                                                            {
                                        

                                        reader1 = 

                                        svp_simple_001_001_global_array[0];
                              }

                              

                              reader3 = svp_simple_001_001_global_array[1];
                              

                              int reader2;
                              

                              reader2 = svp_simple_001_001_global_var;
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_001_001_isr_2:
          

          ;

          

          pthread_exit(0);
}



void idlerun()


{
          

          int i = 0;
          

          i = 0;
          

          int loop_3_IOVar1;
          

          int loop_3_block_1;
          

          for (int t_3 = 0; (t_3 < 1) && (i <= 100); t_3++)          {
                    

                    loop_3_IOVar1 = i;
                    

                    loop_3_block_1 = nondet_int();
                    

                    i = loop_3_IOVar1 + (1 * loop_3_block_1);
                    

                    __CPROVER_assume(loop_3_block_1 >= 0);
                    

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
          

          disable_isr(2);


                    {
                    

                    int i;
                    

                    i = 0;
                    

                    int loop_4_IOVar1;
                    

                    int loop_4_block_1;
                    

                    for (int t_4 = 0; (t_4 < 2) && (i < 10000); t_4++)                    {
                              

                              loop_4_IOVar1 = i;
                              

                              loop_4_block_1 = nondet_int();
                              

                              i = loop_4_IOVar1 + (1 * loop_4_block_1);
                              

                              __CPROVER_assume(loop_4_block_1 >= 0);
                              

                              __CPROVER_assume(i < 10000);


                                                            {
                                        

                                        svp_simple_001_001_global_array[i] = 0;
                              }
                              

                              i++;
                    }

                    

                    __CPROVER_assume(! (i < 10000));
          }


                    {
                    

                    int i;
                    

                    i = 0;
                    

                    int loop_5_IOVar1;
                    

                    int loop_5_block_2;
                    

                    for (int t_5 = 0; (t_5 < 2) && (i < 10000); t_5++)                    {
                              

                              loop_5_IOVar1 = i;
                              

                              loop_5_block_2 = nondet_int();
                              

                              i = loop_5_IOVar1 + (1 * loop_5_block_2);
                              

                              __CPROVER_assume(loop_5_block_2 >= 0);
                              

                              __CPROVER_assume(i < 10000);


                                                            {
                                        

                                        _Bool __cs_tmp_if_cond_3; __cs_tmp_if_cond_3 = (i == 9999); 
                                        if (__cs_tmp_if_cond_3)


                                                                                {
                                                  

                                                  svp_simple_001_001_global_array[i] = 1;
                                        }

                              }
                              

                              i++;
                    }

                    

                    __CPROVER_assume(! (i < 10000));
          }
          

          assert(svp_simple_001_001_global_array[9999] == 1);
          

          __exit_main_task:
          

          ;

          

          pthread_exit(0);
}



int main()


{
          

          pthread_t t0;
          

          pthread_t t1;
          

          pthread_t t2;
          

          pthread_create(& t0, 0, main_task, 0);
          

          pthread_create(& t1, 0, svp_simple_001_001_isr_1, 0);
          

          pthread_create(& t2, 0, svp_simple_001_001_isr_2, 0);
          

          __exit_main:
          

          ;

          

          pthread_exit(0);
}


