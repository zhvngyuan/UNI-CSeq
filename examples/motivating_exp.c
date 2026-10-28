int x, y,z;



// priority 1
void isr_1() {
        disable_isr(2);
        z = 1;
        z = 2;
        z = 3;
        z = 4;
        z = 5;
        x = 1;
        assert(x == 1);
        enable_isr(2);
}

// priority 2
void isr_2() {
        x ++;
}

int main() {
        disable_isr(2);
        x = 1;
        assert(x == 1);
        enable_isr(2);
        y = 1;
        
}