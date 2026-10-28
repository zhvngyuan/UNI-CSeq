typedef int pthread_t;
extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }


int g;

// priority 1
void *svp_simple_639_001_isr1(void *arg) {

    g = 1;

    assert(g == 1);
    // printf("g is %i", g);
    g = 0;
}
// priority 2
void *svp_simple_639_001_isr2(void *arg) {
    g = 0;

}

void *main_task(void *arg)
{
    g = 0;

    // sleep(1);


    return 0;
}

int main(){
  pthread_t t0, t1, t2;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_639_001_isr1, 0);
  pthread_create(&t2, 0, svp_simple_639_001_isr2, 0);
}
