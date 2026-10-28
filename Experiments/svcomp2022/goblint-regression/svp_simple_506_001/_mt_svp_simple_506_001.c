typedef int pthread_t;


extern void exit (int status);

int glob;


void f() {
  int tmp;
  tmp = glob+1;
  glob = glob+1;
  // glob++; 

  exit(0);
}
// priority 1
void *svp_simple_506_001_isr_1(void *arg) {
  int tmp = glob+1;
  glob=glob+1;
  // glob++;

}

void *main_task(void *arg) {
  glob = 0;
  // while () {
  //   f();
  // }
  f();
  assert(glob == 0);
  
  glob = 8;
  assert(glob == 8);
  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_506_001_isr_1, 0);
}
