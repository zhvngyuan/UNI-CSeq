typedef int pthread_t;


static int data1;
static int data2;

// priority 1
void *svp_simple_536_001_isr_1(void *arg) {
  int tmp1 = data1+1;
  data1 = tmp1;
  // data1++;            // NORACE

  // printf("%d",data2); // NORACE
}

void *main_task(void *arg) {
  data1 = 0;
  data2 = 0;
  // printf("%d",data1); // NORACE
  int tmp;
  tmp = data2+1;
  data2 = tmp;
  assert(data2 == 1);
  // data2++;            // NORACE
 
  return 0;
}


int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_536_001_isr_1, 0);
}
