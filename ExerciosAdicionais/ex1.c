#include <detpic32.h>

void send2displays(unsigned char value) {
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
                                          0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C,
                                          0x39, 0x5E, 0x79, 0x71};
    unsigned char dh = value >> 4;
    unsigned char dl = value & 0x0F;
    char segment;
    static char displayFlag = 0;

    if(displayFlag == 0){
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        segment = display7Scodes[dh];
        LATB = (LATB & 0x80FF) | segment << 8;
    }else{
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        segment = display7Scodes[dl];
        LATB = (LATB & 0x80FF) | segment << 8;
    }
    displayFlag = displayFlag ^ 1;
}

void delay(unsigned int ms){
    int k = 20000;
    resetCoreTimer();
    while(readCoreTimer() < k * ms);
}

int main (void){
    //configurar TIMER 2
    T2CONbits.TCKPS = 2; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR2 = 49999; // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR2 = 0; // Reset timer T2 count register
    T2CONbits.TON = 1; // Enable timer T2 (must be the last command of the

    IPC2bits.T2IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T2IE = 1; // Enable timer T2 interrupts
    IFS0bits.T2IF = 0; // Reset timer T2 interrupt flag 

    //CONFIGURE I/O
    TRISE = (TRISE & 0xFFF0);
    TRISD = (TRISD & 0xFF9F);
    TRISB = (TRISB & 0x80FF);

    EnableInterrupts();
    while(1){

    }
    return 0;
}