

typedef int pthread_t;


int svp_simple_004_001_condition1 = 1;


int svp_simple_004_001_condition2 = 1;


int svp_simple_004_001_condition3 = 1;


int svp_simple_004_001_condition4 = 1;


int svp_simple_004_001_condition5 = 1;


int svp_simple_004_001_condition6 = 1;


int svp_simple_004_001_global_var1 = 0x11;


int svp_simple_004_001_global_var2 = 0x22;


int svp_simple_004_001_global_var3 = 0x33;


int reader1;


int reader2;


int reader3;


int reader4;


int reader5;


int reader6;


void *svp_simple_004_001_isr_1(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_1_IOVar1;
          

          int loop_1_block_1;
          

          for (int t_1 = 0; (t_1 < 4) && (funcunwind_t < 1); t_1++)          {
                    

                    loop_1_IOVar1 = funcunwind_t;
                    

                    loop_1_block_1 = nondet_int();
                    

                    funcunwind_t = loop_1_IOVar1 + (1 * loop_1_block_1);
                    

                    __CPROVER_assume(loop_1_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              svp_simple_004_001_condition6 = 0;
                              

                              _Bool __cs_tmp_if_cond_0; __cs_tmp_if_cond_0 = (svp_simple_004_001_condition3 == 1); 
                              if (__cs_tmp_if_cond_0)


                                                            {
                                        

                                        svp_simple_004_001_global_var1 = 0xaa;
                              }
                              else


                                                            {
                                        

                                        svp_simple_004_001_global_var3 = 0xcc;
                              }

                              

                              enable_isr(2);
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_004_001_isr_1:
          

          ;

          

          pthread_exit(0);
}



void *svp_simple_004_001_isr_2(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_2_IOVar1;
          

          int loop_2_block_1;
          

          for (int t_2 = 0; (t_2 < 2) && (funcunwind_t < 1); t_2++)          {
                    

                    loop_2_IOVar1 = funcunwind_t;
                    

                    loop_2_block_1 = nondet_int();
                    

                    funcunwind_t = loop_2_IOVar1 + (1 * loop_2_block_1);
                    

                    __CPROVER_assume(loop_2_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              _Bool __cs_tmp_if_cond_1; __cs_tmp_if_cond_1 = (svp_simple_004_001_condition6 == 1); 
                              if (__cs_tmp_if_cond_1)


                                                            {
                                        

                                        svp_simple_004_001_global_var2 = 0x22;
                              }

                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_004_001_isr_2:
          

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
          

          disable_isr(2);
          

          _Bool __cs_tmp_if_cond_2; __cs_tmp_if_cond_2 = (svp_simple_004_001_condition1 == 1); 
          if (__cs_tmp_if_cond_2)


                    {
                    

                    reader1 = svp_simple_004_001_global_var1;
                    

                    reader5 = svp_simple_004_001_global_var3;
          }

          

          _Bool __cs_tmp_if_cond_3; __cs_tmp_if_cond_3 = (svp_simple_004_001_condition2 == 1); 
          if (__cs_tmp_if_cond_3)


                    {
                    

                    reader2 = svp_simple_004_001_global_var1;
                    

                    reader6 = svp_simple_004_001_global_var3;
          }

          

          assert(reader1 == reader2);
          

          _Bool __cs_tmp_if_cond_4; __cs_tmp_if_cond_4 = (svp_simple_004_001_condition4 == 1); 
          if (__cs_tmp_if_cond_4)


                    {
                    

                    reader3 = svp_simple_004_001_global_var2;
          }

          

          _Bool __cs_tmp_if_cond_5; __cs_tmp_if_cond_5 = (svp_simple_004_001_condition5 == 1); 
          if (__cs_tmp_if_cond_5)


                    {
                    

                    reader4 = svp_simple_004_001_global_var2;
          }

          

          assert(reader3 == reader4);
          

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
          

          pthread_create(& t1, 0, svp_simple_004_001_isr_1, 0);
          

          pthread_create(& t2, 0, svp_simple_004_001_isr_2, 0);
          

          __exit_main:
          

          ;

          

          pthread_exit(0);
}


