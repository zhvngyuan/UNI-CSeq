int data;
// priority 1
void svp_simple_547_001_isr_1()
{
  int tmp = data + 1;
  data = tmp;
  // data++; // RACE!
}

int main()
{
  data = 0;
  assert(data == 0);
  int tmp = data + 1;
  data = tmp;
  // data++; // RACE!

  return 0;
}
