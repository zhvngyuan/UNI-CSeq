
int myglobal;


// priority 1
void svp_simple_511_001_isr_1() {
  // lock();
  myglobal++; // NORACE
  // unlock();

}


int main(void) {
  // pthread_t id;
  // pthread_create(&id, NULL, t_fun, NULL);
  // lock();
  disable_isr(1);
  myglobal = 0;
  myglobal++; // NORACE
  assert(myglobal == 1);
  enable_isr(1);
  // unlock();
  // pthread_join (id, NULL);
  return 0;
}
