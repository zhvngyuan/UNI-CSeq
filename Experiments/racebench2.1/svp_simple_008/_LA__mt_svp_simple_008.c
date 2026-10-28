

typedef int pthread_t;


void svp_simple_008_001_func_1();


int svp_simple_008_001_global_var;


int svp_simple_008_001_global_array[100];


void *svp_simple_008_001_isr_1(void *arg)


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


                                                            {
                                        

                                        int k;
                                        

                                        k = 0;
                                        

                                        int loop_2_IOVar1;
                                        

                                        int loop_2_block_1;
                                        

                                        for (int t_2 = 0; (t_2 < 2) && (k < 10); t_2++)                                        {
                                                  

                                                  loop_2_IOVar1 = k;
                                                  

                                                  loop_2_block_1 = nondet_int();
                                                  

                                                  k = loop_2_IOVar1 + (1 * loop_2_block_1);
                                                  

                                                  __CPROVER_assume(loop_2_block_1 >= 0);
                                                  

                                                  __CPROVER_assume(k < 10);


                                                                                                    {
                                                            

                                                            svp_simple_008_001_global_array[k] = 0x05;
                                                  }
                                                  

                                                  k++;
                                        }

                                        

                                        __CPROVER_assume(! (k < 10));
                              }
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_008_001_isr_1:
          

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



void *main_task(void *arg)


{


                    {
                    

                    enable_isr(- 1);
          }
          

          int p = 10;
          

          int q = 30;
          

          disable_isr(1);
          

          svp_simple_008_001_global_array[p + q] = 0x09;
          

          assert(svp_simple_008_001_global_array[40] == 0x09);
          

          enable_isr(1);
          

          svp_simple_008_001_global_array[40] = 0x01;


                    {
                    

                    int reader1;
                    

                    int reader2;
                    

                    int i = 1;
                    

                    int j = 2;
                    

                    int p = 10;
                    

                    int q = 30;
                    

                    reader1 = svp_simple_008_001_global_array[(i * 20) + (j * 10)];
                    

                    reader2 = svp_simple_008_001_global_array[p + q];
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
          

          pthread_create(& t1, 0, svp_simple_008_001_isr_1, 0);
          

          __exit_main:
          

          ;

          

          pthread_exit(0);
}


