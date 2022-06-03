#include <detpic32.h>

int main(void){
    static const char display7Scode[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };

    TRISB = (TRISB | 0x000F);
    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);
    LATDbits.LATD6 = 1;
    LATDbits.LATD5 = 0;
    int index;
    int value;

    while(1){
        index = PORTB & 0x000F;
        value = display7Scode[index];
        LATB = (LATB & 0x80FF) | (unsigned int)(value) << 8;
    }
    return 0;
}