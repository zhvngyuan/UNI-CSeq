

typedef int pthread_t;


int svp_simple_023_001_global_var;


void svp_simple_023_001_func_1(int x);


void svp_simple_023_001_init();


void *svp_simple_023_001_isr_1(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_1_IOVar1;
          

          int loop_1_block_1;
          

          for (int t_1 = 0; (t_1 < 2) && (funcunwind_t < 1); t_1++)          {
                    

                    loop_1_IOVar1 = funcunwind_t;
                    

                    loop_1_block_1 = nondet_int();
                    

                    funcunwind_t = loop_1_IOVar1 + (1 * loop_1_block_1);
                    

                    __CPROVER_assume(loop_1_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_023_001_global_var = __VERIFIER_nondet_int();
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_023_001_isr_1:
          

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



void init()


{
          

          enable_isr(- 1);
}



void *main_task(void *arg)


{


                    {
                    

                    svp_simple_023_001_global_var = __VERIFIER_nondet_int();


                                        {
                              

                              enable_isr(- 1);
                    }
          }


                    {
                    

                    int var = svp_simple_023_001_global_var;
                    

                    _Bool __cs_tmp_if_cond_0; __cs_tmp_if_cond_0 = ((var > 0) && (var < 12)); 
                    if (__cs_tmp_if_cond_0)


                                        {
                              

                              svp_simple_023_001_global_var = svp_simple_023_001_global_var + 1;
                              

                              assert(svp_simple_023_001_global_var < 13);
                    }

          }
          

          __exit_main_task:
          

          ;

          

          pthread_exit(0);
}



int main()


{
          

          pthread_t t0;
          

          pthread_t t1;
          

          pthread_create(& t0, 0, main_task, 0);
          

          pthread_create(& t1, 0, svp_simple_023_001_isr_1, 0);
          

          __exit_main:
          

          ;

          

          pthread_exit(0);
}


