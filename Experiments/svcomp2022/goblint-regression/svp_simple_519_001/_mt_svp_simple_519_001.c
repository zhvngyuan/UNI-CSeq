typedef int pthread_t;

int myglobal;

// priority 1
void *svp_simple_519_001_isr_1(void *arg) {
  myglobal=myglobal+1; 
  assert(myglobal <=2);
}

int add1 (int x) {
  return x+1;
}

void *main_task(void *arg) {
  myglobal = 0;

  // printf("myglobal equals %dn",myglobal); // NORACE
  assert(myglobal == 0);

  add1(myglobal); 
  assert(myglobal == 1);

  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_519_001_isr_1, 0);
}
