#include <detpic32.h>

void send2displays(unsigned char value){
    static const char display7Scodes[] ={0x3F,0x06,0x5B,0x4F,0x66,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x57,0x79,0x71};
    char segment;

    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;

    segment = display7Scodes[value >> 4];
    LATB = (LATB & 0x80FF) | segment << 8;

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    segment = display7Scodes[value & 0x0F];
    LATB = (LATB & 0x80FF) | segment << 8;
}

