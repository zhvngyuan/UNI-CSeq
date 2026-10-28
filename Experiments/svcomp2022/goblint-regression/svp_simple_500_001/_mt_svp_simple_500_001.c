typedef int pthread_t;


int glob;
// priority 1
void *svp_simple_500_001_isr_1(void *arg) {
  int tmp = glob + 1;
  glob = tmp; 
  // glob++;

}

void *main_task(void *arg) {
  glob = 0;
  int tmp = glob + 1;
  glob = tmp; 
  assert(glob == 1);
  // glob++;
  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_500_001_isr_1, 0);
}
