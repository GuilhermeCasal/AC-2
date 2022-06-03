#include <detpic32.h>


void delay(unsigned int ms){
    int k=20000;
    resetCoreTimer();
    while(readCoreTimer() < k * ms);
}

int main(void){
    unsigned char segment;
    int i;
    LATDbits.LATD6 = 1;
    LATDbits.LATD5 = 0; 
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);
    
    while(1){
        segment = 1;
        for ( i = 0; i < 7; i++)
        {
            LATB = (LATB & 0x80FF) | (unsigned int)(segment) << 8;
            delay(200);
            segment = segment << 1;
        }
        LATDbits.LATD5 = !LATDbits.LATD5;
        LATDbits.LATD6 = !LATDbits.LATD6;
    }  
    return 0;
}