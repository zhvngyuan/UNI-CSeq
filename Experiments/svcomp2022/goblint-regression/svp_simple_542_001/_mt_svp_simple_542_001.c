typedef int pthread_t;

int myglobal;

int f(int x) {
  return 5;
}
// priority 1
void *svp_simple_542_001_isr_1(void *arg) {
    int tmp;
    myglobal=f(myglobal);
    if(myglobal == 5){
          tmp = 1;
    }
}

void *main_task(void *arg) {
//  int tmp=myglobal+1;
//  myglobal = tmp;
  myglobal = 0;
  assert(myglobal == 0);
  myglobal = f(myglobal);
  assert(myglobal == 5);
  myglobal = f(myglobal);
  return 0;
}
int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_542_001_isr_1, 0);
}
