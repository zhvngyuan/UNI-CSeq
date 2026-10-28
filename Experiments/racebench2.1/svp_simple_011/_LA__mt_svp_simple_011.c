

typedef int pthread_t;


int svp_simple_011_001_global_var1;


int svp_simple_011_001_global_var2;


int svp_simple_011_001_global_var3;


int *svp_simple_011_001_u;


void *svp_simple_011_001_isr_1(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_1_IOVar1;
          

          int loop_1_block_1;
          

          for (int t_1 = 0; (t_1 < 3) && (funcunwind_t < 1); t_1++)          {
                    

                    int reader1;
                    

                    int reader2;
                    

                    int *m = & svp_simple_011_001_global_var1;
                    

                    loop_1_IOVar1 = funcunwind_t;
                    

                    loop_1_block_1 = nondet_int();
                    

                    funcunwind_t = loop_1_IOVar1 + (1 * loop_1_block_1);
                    

                    __CPROVER_assume(loop_1_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              int reader1;
                              

                              int reader2;
                              

                              int *m = & svp_simple_011_001_global_var1;
                              

                              reader1 = * m;
                              

                              reader2 = * svp_simple_011_001_u;
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_011_001_isr_1:
          

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
          

          int *p = & svp_simple_011_001_global_var1;
          

          int *q = & svp_simple_011_001_global_var1;
          

          * p = 0x01;
          

          * q = 0x02;
          

          svp_simple_011_001_u = & svp_simple_011_001_global_var2;
          

          * svp_simple_011_001_u = 0x01;
          

          assert((* svp_simple_011_001_u) == 0x01);
          

          svp_simple_011_001_u = & svp_simple_011_001_global_var3;
          

          * svp_simple_011_001_u = 0x02;
          

          assert((* svp_simple_011_001_u) == 0x02);
          

          __exit_main_task:
          

          ;

          

          pthread_exit(0);
}



int main()


{
          

          pthread_t t0;
          

          pthread_t t1;
          

          pthread_create(& t0, 0, main_task, 0);
          

          pthread_create(& t1, 0, svp_simple_011_001_isr_1, 0);
          

          __exit_main:
          

          ;

          

          pthread_exit(0);
}


