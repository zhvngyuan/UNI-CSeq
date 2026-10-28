

typedef int pthread_t;


int svp_simple_017_001_global_var;


int svp_simple_017_001_local_array[10000];


void *svp_simple_017_001_isr_1(void *arg)


{
          

          int funcunwind_t = 0;
          

          _Bool __cs_tmp_if_cond_0; __cs_tmp_if_cond_0 = (funcunwind_t < 1); 
          if (__cs_tmp_if_cond_0)
          {


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_017_001_global_var = 5000;
                              

                              assert(svp_simple_017_001_global_var == 50);
                              

                              svp_simple_017_001_local_array[5000] = 0;
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
                              

                              svp_simple_017_001_global_var = 5000;
                              

                              __CPROVER_assume(svp_simple_017_001_global_var == 50);
                              

                              svp_simple_017_001_local_array[5000] = 0;
                    }
          }

          

          _Bool __cs_tmp_if_cond_1; __cs_tmp_if_cond_1 = (funcunwind_t < 1); 
          if (__cs_tmp_if_cond_1)
          {


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_017_001_global_var = 5000;
                              

                              assert(svp_simple_017_001_global_var == 50);
                              

                              svp_simple_017_001_local_array[5000] = 0;
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_017_001_isr_1:
          

          ;

          

          pthread_exit(0);
}



void idlerun()


{
          

          int i = 0;
          

          i = 0;
          

          int loop_2_IOVar1;
          

          int loop_2_block_1;
          

          for (int t_2 = 0; (t_2 < 1) && (i <= 100); t_2++)          {
                    

                    loop_2_IOVar1 = i;
                    

                    loop_2_block_1 = nondet_int();
                    

                    i = loop_2_IOVar1 + (1 * loop_2_block_1);
                    

                    __CPROVER_assume(loop_2_block_1 >= 0);
                    

                    __CPROVER_assume(i <= 100);


                                        {
                    }
                    

                    i++;
          }

          

          __CPROVER_assume(! (i <= 100));
}



void *main_task(void *arg)


{


                    {
                    

                    enable_isr(- 1);
          }
          

          int i = 0;
          

          svp_simple_017_001_global_var = 0;
          

          int loop_3_IOVar1;
          

          int loop_3_block_2;
          

          for (int t_3 = 0; (t_3 < 2) && (svp_simple_017_001_global_var < 10000); t_3++)          {
                    

                    loop_3_IOVar1 = svp_simple_017_001_global_var;
                    

                    loop_3_block_2 = nondet_int();
                    

                    svp_simple_017_001_global_var = loop_3_IOVar1 + (1 * loop_3_block_2);
                    

                    __CPROVER_assume(loop_3_block_2 >= 0);
                    

                    __CPROVER_assume(svp_simple_017_001_global_var < 10000);


                                        {
                              

                              svp_simple_017_001_local_array[svp_simple_017_001_global_var] = i++;
                    }
                    

                    svp_simple_017_001_global_var++;
          }

          

          __CPROVER_assume(! (svp_simple_017_001_global_var < 10000));
          

          __exit_main_task:
          

          ;

          

          pthread_exit(0);
}



int main()


{
          

          pthread_t t0;
          

          pthread_t t1;
          

          pthread_create(& t0, 0, main_task, 0);
          

          pthread_create(& t1, 0, svp_simple_017_001_isr_1, 0);
          

          __exit_main:
          

          ;

          

          pthread_exit(0);
}


