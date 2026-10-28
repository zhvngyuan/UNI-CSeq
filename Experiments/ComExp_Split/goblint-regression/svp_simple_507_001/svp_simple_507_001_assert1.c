

int myglobal;
// priority 1
void svp_simple_507_001_isr_1()
{
  int tmp = myglobal + 1;
  myglobal = tmp;
  // myglobal=myglobal+1; // RACE!
}

int main(void)
{
  myglobal = 0;
  int tmp = myglobal + 1;
  myglobal = tmp;
  assert(myglobal == 1);
  // myglobal=myglobal+1; // RACE!
}