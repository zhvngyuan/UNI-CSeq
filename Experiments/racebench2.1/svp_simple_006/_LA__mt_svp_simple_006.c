

typedef int pthread_t;


int svp_simple_006_001_global_var1;


int svp_simple_006_001_global_var2;


unsigned char flag = 0x55;


void *svp_simple_006_001_isr_1(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_1_IOVar1;
          

          int loop_1_block_1;
          

          for (int t_1 = 0; (t_1 < 3) && (funcunwind_t < 1); t_1++)          {
                    

                    int reader2;
                    

                    loop_1_IOVar1 = funcunwind_t;
                    

                    loop_1_block_1 = nondet_int();
                    

                    funcunwind_t = loop_1_IOVar1 + (1 * loop_1_block_1);
                    

                    __CPROVER_assume(loop_1_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              int reader2;
                              

                              svp_simple_006_001_global_var1 = 1;
                              

                              reader2 = svp_simple_006_001_global_var2;
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_006_001_isr_1:
          

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
          

          int reader1;
          

          int reader2;


                    {
                    

                    int i;
                    

                    i = 0;
                    

                    int loop_3_IOVar1;
                    

                    int loop_3_block_2;
                    

                    for (int t_3 = 0; (t_3 < 2) && (i < 5); t_3++)                    {
                              

                              loop_3_IOVar1 = i;
                              

                              loop_3_block_2 = nondet_int();
                              

                              i = loop_3_IOVar1 + (1 * loop_3_block_2);
                              

                              __CPROVER_assume(loop_3_block_2 >= 0);
                              

                              __CPROVER_assume(i < 5);


                                                            {


                                                                                {
                                                  

                                                  int j;
                                                  

                                                  _Bool __cs_tmp_if_cond_0; __cs_tmp_if_cond_0 = (j < 5); 
                                                  if (__cs_tmp_if_cond_0)
                                                  {


                                                                                                                        {
                                                                      

                                                                      _Bool __cs_tmp_if_cond_1; __cs_tmp_if_cond_1 = (i == j); 
                                                                      if (__cs_tmp_if_cond_1)


                                                                                                                                            {
                                                                                

                                                                                _Bool __cs_tmp_if_cond_2; __cs_tmp_if_cond_2 = (i == 0); 
                                                                                if (__cs_tmp_if_cond_2)


                                                                                                                                                                {
                                                                                          

                                                                                          reader1 = svp_simple_006_001_global_var1;
                                                                                          

                                                                                          assert(svp_simple_006_001_global_var1 == 0);
                                                                                }
                                                                                else


                                                                                                                                                                {
                                                                                          

                                                                                          _Bool __cs_tmp_if_cond_3; __cs_tmp_if_cond_3 = (i == 4); 
                                                                                          if (__cs_tmp_if_cond_3)


                                                                                                                                                                                    {
                                                                                                    

                                                                                                    reader2 = svp_simple_006_001_global_var1;
                                                                                                    

                                                                                                    assert(svp_simple_006_001_global_var1 == 0);
                                                                                          }
                                                                                          else


                                                                                                                                                                                    {
                                                                                                    

                                                                                                    _Bool __cs_tmp_if_cond_4; __cs_tmp_if_cond_4 = (i == 6); 
                                                                                                    if (__cs_tmp_if_cond_4)


                                                                                                                                                                                                        {
                                                                                                              

                                                                                                              reader2 = svp_simple_006_001_global_var1;
                                                                                                              

                                                                                                              assert(svp_simple_006_001_global_var1 == 0);
                                                                                                    }

                                                                                          }

                                                                                }

                                                                      }

                                                            }
                                                  }

                                                  

                                                  j = 0;
                                                  

                                                  int loop_4_IOVar1;
                                                  

                                                  int loop_4_block_4;
                                                  

                                                  for (int t_4 = 0; (t_4 < 3) && (j < 5); t_4++)                                                  {
                                                            

                                                            loop_4_IOVar1 = j;
                                                            

                                                            loop_4_block_4 = nondet_int();
                                                            

                                                            j = loop_4_IOVar1 + (1 * loop_4_block_4);
                                                            

                                                            __CPROVER_assume(loop_4_block_4 >= 0);
                                                            

                                                            __CPROVER_assume(j < 5);


                                                                                                                        {
                                                                      

                                                                      _Bool __cs_tmp_if_cond_5; __cs_tmp_if_cond_5 = (i == j); 
                                                                      if (__cs_tmp_if_cond_5)


                                                                                                                                            {
                                                                                

                                                                                _Bool __cs_tmp_if_cond_6; __cs_tmp_if_cond_6 = (i == 0); 
                                                                                if (__cs_tmp_if_cond_6)


                                                                                                                                                                {
                                                                                          

                                                                                          reader1 = svp_simple_006_001_global_var1;
                                                                                          

                                                                                          __CPROVER_assume(svp_simple_006_001_global_var1 == 0);
                                                                                }
                                                                                else


                                                                                                                                                                {
                                                                                          

                                                                                          _Bool __cs_tmp_if_cond_7; __cs_tmp_if_cond_7 = (i == 4); 
                                                                                          if (__cs_tmp_if_cond_7)


                                                                                                                                                                                    {
                                                                                                    

                                                                                                    reader2 = svp_simple_006_001_global_var1;
                                                                                                    

                                                                                                    __CPROVER_assume(svp_simple_006_001_global_var1 == 0);
                                                                                          }
                                                                                          else


                                                                                                                                                                                    {
                                                                                                    

                                                                                                    _Bool __cs_tmp_if_cond_8; __cs_tmp_if_cond_8 = (i == 6); 
                                                                                                    if (__cs_tmp_if_cond_8)


                                                                                                                                                                                                        {
                                                                                                              

                                                                                                              reader2 = svp_simple_006_001_global_var1;
                                                                                                              

                                                                                                              __CPROVER_assume(svp_simple_006_001_global_var1 == 0);
                                                                                                    }

                                                                                          }

                                                                                }

                                                                      }

                                                            }
                                                            

                                                            j++;
                                                  }

                                                  

                                                  _Bool __cs_tmp_if_cond_9; __cs_tmp_if_cond_9 = (j < 5); 
                                                  if (__cs_tmp_if_cond_9)
                                                  {


                                                                                                                        {
                                                                      

                                                                      _Bool __cs_tmp_if_cond_10; __cs_tmp_if_cond_10 = (i == j); 
                                                                      if (__cs_tmp_if_cond_10)


                                                                                                                                            {
                                                                                

                                                                                _Bool __cs_tmp_if_cond_11; __cs_tmp_if_cond_11 = (i == 0); 
                                                                                if (__cs_tmp_if_cond_11)


                                                                                                                                                                {
                                                                                          

                                                                                          reader1 = svp_simple_006_001_global_var1;
                                                                                          

                                                                                          assert(svp_simple_006_001_global_var1 == 0);
                                                                                }
                                                                                else


                                                                                                                                                                {
                                                                                          

                                                                                          _Bool __cs_tmp_if_cond_12; __cs_tmp_if_cond_12 = (i == 4); 
                                                                                          if (__cs_tmp_if_cond_12)


                                                                                                                                                                                    {
                                                                                                    

                                                                                                    reader2 = svp_simple_006_001_global_var1;
                                                                                                    

                                                                                                    assert(svp_simple_006_001_global_var1 == 0);
                                                                                          }
                                                                                          else


                                                                                                                                                                                    {
                                                                                                    

                                                                                                    _Bool __cs_tmp_if_cond_13; __cs_tmp_if_cond_13 = (i == 6); 
                                                                                                    if (__cs_tmp_if_cond_13)


                                                                                                                                                                                                        {
                                                                                                              

                                                                                                              reader2 = svp_simple_006_001_global_var1;
                                                                                                              

                                                                                                              assert(svp_simple_006_001_global_var1 == 0);
                                                                                                    }

                                                                                          }

                                                                                }

                                                                      }

                                                            }
                                                  }

                                                  

                                                  __CPROVER_assume(! (j < 5));
                                        }
                              }
                              

                              i++;
                    }

                    

                    __CPROVER_assume(! (i < 5));
          }


                    {
                    

                    int i;
                    

                    i = 0;
                    

                    int loop_5_IOVar1;
                    

                    int loop_5_block_2;
                    

                    for (int t_5 = 0; (t_5 < 2) && (i < 5); t_5++)                    {
                              

                              loop_5_IOVar1 = i;
                              

                              loop_5_block_2 = nondet_int();
                              

                              i = loop_5_IOVar1 + (1 * loop_5_block_2);
                              

                              __CPROVER_assume(loop_5_block_2 >= 0);
                              

                              __CPROVER_assume(i < 5);


                                                            {


                                                                                {
                                                  

                                                  int j;
                                                  

                                                  _Bool __cs_tmp_if_cond_14; __cs_tmp_if_cond_14 = (j < 5); 
                                                  if (__cs_tmp_if_cond_14)
                                                  {


                                                                                                                        {
                                                                      

                                                                      _Bool __cs_tmp_if_cond_15; __cs_tmp_if_cond_15 = (((i + j) == 6) && (i < j)); 
                                                                      if (__cs_tmp_if_cond_15)


                                                                                                                                            {
                                                                                

                                                                                svp_simple_006_001_global_var2 = 0x02;
                                                                                

                                                                                assert(svp_simple_006_001_global_var2 == 0x02);
                                                                      }

                                                            }
                                                  }

                                                  

                                                  j = 0;
                                                  

                                                  int loop_6_IOVar1;
                                                  

                                                  int loop_6_block_2;
                                                  

                                                  for (int t_6 = 0; (t_6 < 2) && (j < 5); t_6++)                                                  {
                                                            

                                                            loop_6_IOVar1 = j;
                                                            

                                                            loop_6_block_2 = nondet_int();
                                                            

                                                            j = loop_6_IOVar1 + (1 * loop_6_block_2);
                                                            

                                                            __CPROVER_assume(loop_6_block_2 >= 0);
                                                            

                                                            __CPROVER_assume(j < 5);


                                                                                                                        {
                                                                      

                                                                      _Bool __cs_tmp_if_cond_16; __cs_tmp_if_cond_16 = (((i + j) == 6) && (i < j)); 
                                                                      if (__cs_tmp_if_cond_16)


                                                                                                                                            {
                                                                                

                                                                                svp_simple_006_001_global_var2 = 0x02;
                                                                                

                                                                                __CPROVER_assume(svp_simple_006_001_global_var2 == 0x02);
                                                                      }

                                                            }
                                                            

                                                            j++;
                                                  }

                                                  

                                                  _Bool __cs_tmp_if_cond_17; __cs_tmp_if_cond_17 = (j < 5); 
                                                  if (__cs_tmp_if_cond_17)
                                                  {


                                                                                                                        {
                                                                      

                                                                      _Bool __cs_tmp_if_cond_18; __cs_tmp_if_cond_18 = (((i + j) == 6) && (i < j)); 
                                                                      if (__cs_tmp_if_cond_18)


                                                                                                                                            {
                                                                                

                                                                                svp_simple_006_001_global_var2 = 0x02;
                                                                                

                                                                                assert(svp_simple_006_001_global_var2 == 0x02);
                                                                      }

                                                            }
                                                  }

                                                  

                                                  __CPROVER_assume(! (j < 5));
                                        }
                              }
                              

                              i++;
                    }

                    

                    __CPROVER_assume(! (i < 5));
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
          

          pthread_create(& t1, 0, svp_simple_006_001_isr_1, 0);
          

          __exit_main:
          

          ;

          

          pthread_exit(0);
}


