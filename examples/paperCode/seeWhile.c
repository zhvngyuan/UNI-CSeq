int x, y;
int main(){
     x = 0;
     while (x < 10){
     if (y > 10)
         x = x + 1;
     else
         x = x + 2;
 }
 assert(x >= 10);

}
// priority 1
void isr_1(){
    x = 0; 
}