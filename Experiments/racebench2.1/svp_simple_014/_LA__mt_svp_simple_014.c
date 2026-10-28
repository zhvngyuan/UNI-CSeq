

typedef int pthread_t;


int svp_simple_014_001_global_var1 = 0x01;


int svp_simple_014_001_global_var2 = 0x02;


int svp_simple_014_001_global_flag1 = 0;


int svp_simple_014_001_global_flag2 = 1;


int reader1;


int reader2;


int reader3;


int reader4;


void *svp_simple_014_001_isr_1(void *arg)


{
          

          int funcunwind_t = 0;
          

          _Bool __cs_tmp_if_cond_0; __cs_tmp_if_cond_0 = (funcunwind_t < 1); 
          if (__cs_tmp_if_cond_0)
          {


                                        {
                              

                              funcunwind_t++;
                              

                              disable_isr(3);


                                                            {
                                        

                                        int i;
                                        

                                        i = 0;
                                        

                                        int loop_2_IOVar1;
                                        

                                        int loop_2_block_2;
                                        

                                        for (int t_2 = 0; (t_2 < 2) && (i < 10000); t_2++)                                        {
                                                  

                                                  loop_2_IOVar1 = i;
                                                  

                                                  loop_2_block_2 = nondet_int();
                                                  

                                                  i = loop_2_IOVar1 + (1 * loop_2_block_2);
                                                  

                                                  __CPROVER_assume(loop_2_block_2 >= 0);
                                                  

                                                  __CPROVER_assume(i < 10000);


                                                                                                    {
                                                            

                                                            _Bool __cs_tmp_if_cond_1; __cs_tmp_if_cond_1 = (i == 9999); 
                                                            if (__cs_tmp_if_cond_1)


                                                                                                                        {
                                                                      

                                                                      reader1 = svp_simple_014_001_global_var1;
                                                            }

                                                  }
                                                  

                                                  i++;
                                        }

                                        

                                        __CPROVER_assume(! (i < 10000));
                              }
                              

                              reader2 = svp_simple_014_001_global_var1;
                              

                              assert(reader1 == reader2);
                              

                              reader3 = svp_simple_014_001_global_var2;
                              

                              reader4 = svp_simple_014_001_global_var2;
                              

                              assert(reader1 == reader2);
                    }
          }

          

          int loop_1_IOVar1;
          

          int loop_1_block_1;
          

          for (int t_1 = 0; (t_1 < 5) && (funcunwind_t < 1); t_1++)          {
                    

                    loop_1_IOVar1 = funcunwind_t;
                    

                    loop_1_block_1 = nondet_int();
                    

                    funcunwind_t = loop_1_IOVar1 + (1 * loop_1_block_1);
                    

                    __CPROVER_assume(loop_1_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              disable_isr(3);


                                                            {
                                        

                                        int i;
                                        

                                        i = 0;
                                        

                                        int loop_2_IOVar1;
                                        

                                        int loop_2_block_2;
                                        

                                        for (int t_2 = 0; (t_2 < 2) && (i < 10000); t_2++)                                        {
                                                  

                                                  loop_2_IOVar1 = i;
                                                  

                                                  loop_2_block_2 = nondet_int();
                                                  

                                                  i = loop_2_IOVar1 + (1 * loop_2_block_2);
                                                  

                                                  __CPROVER_assume(loop_2_block_2 >= 0);
                                                  

                                                  __CPROVER_assume(i < 10000);


                                                                                                    {
                                                            

                                                            _Bool __cs_tmp_if_cond_2; __cs_tmp_if_cond_2 = (i == 9999); 
                                                            if (__cs_tmp_if_cond_2)


                                                                                                                        {
                                                                      

                                                                      reader1 = svp_simple_014_001_global_var1;
                                                            }

                                                  }
                                                  

                                                  i++;
                                        }

                                        

                                        __CPROVER_assume(! (i < 10000));
                              }
                              

                              reader2 = svp_simple_014_001_global_var1;
                              

                              __CPROVER_assume(reader1 == reader2);
                              

                              reader3 = svp_simple_014_001_global_var2;
                              

                              reader4 = svp_simple_014_001_global_var2;
                              

                              __CPROVER_assume(reader1 == reader2);
                    }
          }

          

          _Bool __cs_tmp_if_cond_3; __cs_tmp_if_cond_3 = (funcunwind_t < 1); 
          if (__cs_tmp_if_cond_3)
          {


                                        {
                              

                              funcunwind_t++;
                              

                              disable_isr(3);


                                                            {
                                        

                                        int i;
                                        

                                        i = 0;
                                        

                                        int loop_2_IOVar1;
                                        

                                        int loop_2_block_2;
                                        

                                        for (int t_2 = 0; (t_2 < 2) && (i < 10000); t_2++)                                        {
                                                  

                                                  loop_2_IOVar1 = i;
                                                  

                                                  loop_2_block_2 = nondet_int();
                                                  

                                                  i = loop_2_IOVar1 + (1 * loop_2_block_2);
                                                  

                                                  __CPROVER_assume(loop_2_block_2 >= 0);
                                                  

                                                  __CPROVER_assume(i < 10000);


                                                                                                    {
                                                            

                                                            _Bool __cs_tmp_if_cond_4; __cs_tmp_if_cond_4 = (i == 9999); 
                                                            if (__cs_tmp_if_cond_4)


                                                                                                                        {
                                                                      

                                                                      reader1 = svp_simple_014_001_global_var1;
                                                            }

                                                  }
                                                  

                                                  i++;
                                        }

                                        

                                        __CPROVER_assume(! (i < 10000));
                              }
                              

                              reader2 = svp_simple_014_001_global_var1;
                              

                              assert(reader1 == reader2);
                              

                              reader3 = svp_simple_014_001_global_var2;
                              

                              reader4 = svp_simple_014_001_global_var2;
                              

                              assert(reader1 == reader2);
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_014_001_isr_1:
          

          ;

          

          pthread_exit(0);
}



void *svp_simple_014_001_isr_2(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_3_IOVar1;
          

          int loop_3_block_1;
          

          for (int t_3 = 0; (t_3 < 3) && (funcunwind_t < 1); t_3++)          {
                    

                    loop_3_IOVar1 = funcunwind_t;
                    

                    loop_3_block_1 = nondet_int();
                    

                    funcunwind_t = loop_3_IOVar1 + (1 * loop_3_block_1);
                    

                    __CPROVER_assume(loop_3_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_014_001_global_flag1 = 1;
                              

                              svp_simple_014_001_global_flag2 = 0;
                              

                              enable_isr(3);
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_014_001_isr_2:
          

          ;

          

          pthread_exit(0);
}



void *svp_simple_014_001_isr_3(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_4_IOVar1;
          

          int loop_4_block_1;
          

          for (int t_4 = 0; (t_4 < 3) && (funcunwind_t < 1); t_4++)          {
                    

                    loop_4_IOVar1 = funcunwind_t;
                    

                    loop_4_block_1 = nondet_int();
                    

                    funcunwind_t = loop_4_IOVar1 + (1 * loop_4_block_1);
                    

                    __CPROVER_assume(loop_4_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              _Bool __cs_tmp_if_cond_5; __cs_tmp_if_cond_5 = (svp_simple_014_001_global_flag1 == 1); 
                              if (__cs_tmp_if_cond_5)


                                                            {
                                        

                                        svp_simple_014_001_global_var1 = 0x09;
                              }

                              

                              _Bool __cs_tmp_if_cond_6; __cs_tmp_if_cond_6 = (svp_simple_014_001_global_flag2 == 1); 
                              if (__cs_tmp_if_cond_6)


                                                            {
                                        

                                        svp_simple_014_001_global_var2 = 0x09;
                              }

                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_014_001_isr_3:
          

          ;

          

          pthread_exit(0);
}



void idlerun()


{
          

          int i = 0;
          

          i = 0;
          

          int loop_5_IOVar1;
          

          int loop_5_block_1;
          

          for (int t_5 = 0; (t_5 < 1) && (i <= 100); t_5++)          {
                    

                    loop_5_IOVar1 = i;
                    

                    loop_5_block_1 = nondet_int();
                    

                    i = loop_5_IOVar1 + (1 * loop_5_block_1);
                    

                    __CPROVER_assume(loop_5_block_1 >= 0);
                    

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
          

          pthread_create(& t1, 0, svp_simple_014_001_isr_1, 0);
          

          pthread_create(& t2, 0, svp_simple_014_001_isr_2, 0);
          

          pthread_create(& t3, 0, svp_simple_014_001_isr_3, 0);
          

          __exit_main:
          

          ;

          

          pthread_exit(0);
}


