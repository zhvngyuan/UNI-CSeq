

typedef int pthread_t;


typedef struct pack1
{
          

          unsigned char header;
          

          unsigned int data;
} svp_simple_010_001_union;


typedef struct pack2
{
          

          unsigned char header;
          

          unsigned int data;
} svp_simple_010_001_struct;


svp_simple_010_001_union svp_simple_010_001_global_union;


svp_simple_010_001_struct svp_simple_010_001_global_struct;


void *svp_simple_010_001_isr_1(void *arg)


{
          

          int funcunwind_t = 0;
          

          int loop_1_IOVar1;
          

          int loop_1_block_1;
          

          for (int t_1 = 0; (t_1 < 3) && (funcunwind_t < 1); t_1++)          {
                    

                    int reader1;
                    

                    int reader2;
                    

                    loop_1_IOVar1 = funcunwind_t;
                    

                    loop_1_block_1 = nondet_int();
                    

                    funcunwind_t = loop_1_IOVar1 + (1 * loop_1_block_1);
                    

                    __CPROVER_assume(loop_1_block_1 >= 0);
                    

                    __CPROVER_assume(funcunwind_t < 1);


                                        {
                              

                              funcunwind_t++;
                              

                              int reader1;
                              

                              int reader2;
                              

                              reader1 = svp_simple_010_001_global_union.header;
                              

                              reader2 = svp_simple_010_001_global_struct.header;
                    }
          }

          

          __CPROVER_assume(! (funcunwind_t < 1));
          

          __exit_svp_simple_010_001_isr_1:
          

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
          

          int svp_simple_010_001_local_var1 = 0x01;
          

          int svp_simple_010_001_local_var2 = 0x02;
          

          int svp_simple_010_001_local_var3 = 0x03;
          

          int svp_simple_010_001_local_var4 = 0x04;
          

          svp_simple_010_001_global_union.header = svp_simple_010_001_local_var1;
          

          assert(svp_simple_010_001_global_union.header == 0x01);
          

          svp_simple_010_001_global_union.data = svp_simple_010_001_local_var2;
          

          assert(svp_simple_010_001_global_union.data == 0x02);
          

          svp_simple_010_001_global_struct.header = svp_simple_010_001_local_var3;
          

          svp_simple_010_001_global_struct.data = svp_simple_010_001_local_var4;
          

          __exit_main_task:
          

          ;

          

          pthread_exit(0);
}



int main()


{
          

          pthread_t t0;
          

          pthread_t t1;
          

          pthread_create(& t0, 0, main_task, 0);
          

          pthread_create(& t1, 0, svp_simple_010_001_isr_1, 0);
          

          __exit_main:
          

          ;

          

          pthread_exit(0);
}


