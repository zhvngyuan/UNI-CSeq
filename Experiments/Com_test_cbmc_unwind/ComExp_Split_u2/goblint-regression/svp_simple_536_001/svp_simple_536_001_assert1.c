

static int data1;
static int data2;

// priority 1
void svp_simple_536_001_isr_1() {
  int tmp1 = data1+1;
  data1 = tmp1;
  // data1++;            // NORACE

  // printf("%d",data2); // NORACE
}

int main(void) {
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

