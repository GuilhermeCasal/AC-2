#include <detpic32.h>

void delay(unsigned int ms){
    int k=20000;
    resetCoreTimer();
    while(readCoreTimer() < k * ms);
}

int main(void){
    unsigned char segment;
    int i;
    LATD = (LATD & 0xFF9F) | 0x0040; 
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);
    
    while(1){
        segment = 1;
        for ( i = 0; i < 7; i++)
        {
            LATB = (LATB & 0x80FF) | (unsigned int)(segment) << 8;
            delay(500);
            segment = segment << 1;
        }
        LATD = LATD ^ 0x0060;
    }  
    return 0;
}
