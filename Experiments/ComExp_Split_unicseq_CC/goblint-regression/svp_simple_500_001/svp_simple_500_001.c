

int glob;
// priority 1
void svp_simple_500_001_isr_1() {
  int tmp = glob + 1;
  glob = tmp; 
  // glob++;

}

int main(void) {
  glob = 0;
  int tmp = glob + 1;
  glob = tmp; 
  assert(glob == 1);
  // glob++;
  return 0;
}
