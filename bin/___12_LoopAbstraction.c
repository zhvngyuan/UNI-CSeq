int g;
int x;
void isr_1()
{
          static int __cs_l_isr_1_cnt_1;
          __cs_l_isr_1_cnt_1 = 0;
          __cs_l_isr_1_cnt_1++;
          assert(__cs_l_isr_1_cnt_1 == 1);
          __cs_exit(0);
}

void isr_2()
{
          g = 1;
          __cs_exit(0);
}

int main()
{
          x = 0;
          __cs_exit(0);
}

