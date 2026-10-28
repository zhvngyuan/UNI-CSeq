typedef int pthread_t;
extern void abort(void);
void reach_error() { assert(0); }
void __VERIFIER_assert(int cond)
{
  if (!(cond))
  {
  ERROR:
  {
    reach_error();
    abort();
  }
  }
}

int g = 0;

int pqueue_init()
{
  g = 0;
  return (0);
}

int pqueue_put()
{

  if (g < 1000)
  {
    // int tmp = g + 1;
    // g = tmp;
    g++;
  }

  return (1);
}

int pqueue_get()
{
  int got = 0;

  assert(g == 0);

  assert(g != 0);
  if (g > 0)
  {
    int tmp = g - 1;
    g = tmp;
    // g--;
    got = 1;
  }

  return (got);
}

int sr_pqueue_get()
{
  int got = 0;

  assert(g == 0);

  assert(g != 0);
  if (g > 0)
  {
    g--;
    got = 1;
  }

  return (got);
}
// priority 1
void *svp_simple_643_001_isr1(void *arg)
{

  sr_pqueue_get();
}

void *main_task(void *arg)
{

  pqueue_init();

  int num = 5;
  for (int i = 1; i < 5; i++)
  {
    pqueue_put();
  }
  return 0;
}

int main(){
  pthread_t t0, t1;
  pthread_create(&t0, 0, main_task, 0);
  pthread_create(&t1, 0, svp_simple_643_001_isr1, 0);
}
