

typedef int pthread_t;


int svp_simple_002_001_global_array[10000];


void *svp_simple_002_001_isr_1(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_1_IOVar1;
          

          int loop_1_block_1;
          

          for (int t_1 = 0; (t_1 < 5) && (funcunwind_t < 1); t_1++)          {
                    

                    int mininum;
                    

                    int maxnum;
                    

                    loop_1_IOVar1 = funcunwind_t;
                    

                    loop_1_block_1 = nondet_int();
                    

                    funcunwind_t = loop_1_IOVar1 + (1 * loop_1_block_1);
                    

                    __CPROVER_assume(loop_1_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              int mininum;
                              

                              int maxnum;


                                                            {
                                        

                                        int i;
                                        

                                        _Bool __cs_tmp_if_cond_0; __cs_tmp_if_cond_0 = (i < 10000); 
                                        if (__cs_tmp_if_cond_0)
                                        {


                                                                                                    {
                                                            

                                                            _Bool __cs_tmp_if_cond_1; __cs_tmp_if_cond_1 = (i == 9999); 
                                                            if (__cs_tmp_if_cond_1)


                                                                                                                        {
                                                                      

                                                                      svp_simple_002_001_global_array[9999] = 10;
                                                                      

                                                                      assert(svp_simple_002_001_global_array[9999] == 10);
                                                            }

                                                            

                                                            _Bool __cs_tmp_if_cond_2; __cs_tmp_if_cond_2 = (i == (10000 + 1)); 
                                                            if (__cs_tmp_if_cond_2)


                                                                                                                        {
                                                                      

                                                                      svp_simple_002_001_global_array[9999] = 1;
                                                            }

                                                  }
                                        }

                                        

                                        i = 0;
                                        

                                        int loop_2_IOVar1;
                                        

                                        int loop_2_block_3;
                                        

                                        for (int t_2 = 0; (t_2 < 2) && (i < 10000); t_2++)                                        {
                                                  

                                                  loop_2_IOVar1 = i;
                                                  

                                                  loop_2_block_3 = nondet_int();
                                                  

                                                  i = loop_2_IOVar1 + (1 * loop_2_block_3);
                                                  

                                                  __CPROVER_assume(loop_2_block_3 >= 0);
                                                  

                                                  __CPROVER_assume(i < 10000);


                                                                                                    {
                                                            

                                                            _Bool __cs_tmp_if_cond_3; __cs_tmp_if_cond_3 = (i == 9999); 
                                                            if (__cs_tmp_if_cond_3)


                                                                                                                        {
                                                                      

                                                                      svp_simple_002_001_global_array[9999] = 10;
                                                                      

                                                                      __CPROVER_assume(svp_simple_002_001_global_array[9999] == 10);
                                                            }

                                                            

                                                            _Bool __cs_tmp_if_cond_4; __cs_tmp_if_cond_4 = (i == (10000 + 1)); 
                                                            if (__cs_tmp_if_cond_4)


                                                                                                                        {
                                                                      

                                                                      svp_simple_002_001_global_array[9999] = 1;
                                                            }

                                                  }
                                                  

                                                  i++;
                                        }

                                        

                                        _Bool __cs_tmp_if_cond_5; __cs_tmp_if_cond_5 = (i < 10000); 
                                        if (__cs_tmp_if_cond_5)
                                        {


                                                                                                    {
                                                            

                                                            _Bool __cs_tmp_if_cond_6; __cs_tmp_if_cond_6 = (i == 9999); 
                                                            if (__cs_tmp_if_cond_6)


                                                                                                                        {
                                                                      

                                                                      svp_simple_002_001_global_array[9999] = 10;
                                                                      

                                                                      assert(svp_simple_002_001_global_array[9999] == 10);
                                                            }

                                                            

                                                            _Bool __cs_tmp_if_cond_7; __cs_tmp_if_cond_7 = (i == (10000 + 1)); 
                                                            if (__cs_tmp_if_cond_7)


                                                                                                                        {
                                                                      

                                                                      svp_simple_002_001_global_array[9999] = 1;
                                                            }

                                                  }
                                        }

                                        

                                        __CPROVER_assume(! (i < 10000));
                              }
                              

                              mininum = svp_simple_002_001_global_array[9999] - 1;
                              

                              svp_simple_002_001_global_array[0] = 0;
                              

                              maxnum = svp_simple_002_001_global_array[0] + 1;
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_002_001_isr_1:
          

          ;

          

          pthread_exit(0);
}



void *svp_simple_002_001_isr_2(void *arg)


{
          

          int funcunwind_t = 0;
          

          _Bool __cs_tmp_if_cond_8; __cs_tmp_if_cond_8 = (funcunwind_t < 1); 
          if (__cs_tmp_if_cond_8)
          {


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_002_001_global_array[9999] = 999;
                              

                              assert(svp_simple_002_001_global_array[9999] == 999);
                    }
          }

          

          int loop_3_IOVar1;
          

          int loop_3_block_1;
          

          for (int t_3 = 0; (t_3 < 2) && (funcunwind_t < 1); t_3++)          {
                    

                    loop_3_IOVar1 = funcunwind_t;
                    

                    loop_3_block_1 = nondet_int();
                    

                    funcunwind_t = loop_3_IOVar1 + (1 * loop_3_block_1);
                    

                    __CPROVER_assume(loop_3_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_002_001_global_array[9999] = 999;
                              

                              __CPROVER_assume(svp_simple_002_001_global_array[9999] == 999);
                    }
          }

          

          _Bool __cs_tmp_if_cond_9; __cs_tmp_if_cond_9 = (funcunwind_t < 1); 
          if (__cs_tmp_if_cond_9)
          {


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_002_001_global_array[9999] = 999;
                              

                              assert(svp_simple_002_001_global_array[9999] == 999);
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_002_001_isr_2:
          

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
          

          pthread_create(& t0, 0, main_task, 0);
          

          pthread_create(& t1, 0, svp_simple_002_001_isr_1, 0);
          

          pthread_create(& t2, 0, svp_simple_002_001_isr_2, 0);
          

          __exit_main:
          

          ;

          

          pthread_exit(0);
}


