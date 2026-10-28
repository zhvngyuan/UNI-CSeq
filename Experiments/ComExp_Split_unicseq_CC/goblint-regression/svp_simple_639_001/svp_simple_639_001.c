// extern void abort(void);
// void reach_error() { assert(0); }
// void __VERIFIER_assert(int cond) { if(!(cond)) { ERROR: {reach_error();abort();} } }


int g;

// priority 1
void svp_simple_639_001_isr1() {

    g = 1;

    assert(g == 1);
    // printf("g is %i", g);
    g = 0;
}
// priority 2
void svp_simple_639_001_isr2() {
    g = 0;

}

int main()
{
    g = 0;

    // sleep(1);


    return 0;
}
