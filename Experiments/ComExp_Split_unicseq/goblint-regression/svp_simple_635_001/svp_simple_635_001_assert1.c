
// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }



int g;


// priority 1
void svp_simple_635_001_isr1()
{

    g = 1000;
    assert(g != 0);
    if (g > 0) {
      g--;
    }
  

}

int main()
{
  g = 0;
  return 0;
}
