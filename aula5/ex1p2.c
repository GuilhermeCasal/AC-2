#include <detpic32.h>


void delay(unsigned int ms){
    int k = 20000;
    resetCoreTimer();
    while(readCoreTimer() < k * ms)
}

void send2displays(unsigned char value){
    static const char display7Scodes[] ={0x3F,0x06,0x5B,0x4F,0x66,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x57,0x79,0x71};
    static char displayFlag = 0;
    char segment;

    char digit_high = value >> 4;
    char digit_low = value & 0x0F;

    if(displayFlag = 0){
        
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        segment = display7Scodes[digit_low];

        LATB = (LATB & 0x80FF) | segment << 8;

    }else{

        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        segment = display7Scodes[digit_high];

        LATB = (LATB & 0x80FF) | segment << 8;
    
    }

    displayFlag = displayFLag ^ 1;
}

unsigned char toBcd(unsigned char value){
    return ((value / 10) << 4) + (value % 4);
}




