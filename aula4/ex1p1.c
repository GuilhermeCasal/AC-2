#include <detpic32.h>

void delay(unsigned int ms){
    int k=20000;
    resetCoreTimer();
    while(readCoreTimer() < k * ms);
}
int main(void){

    TRISCbits.TRISC14 = 0;
    
    while(1){
        delay(1000);
        LATCbits.LATC14 = !LATCbits.LATC14;
    }
    return 0;
}



