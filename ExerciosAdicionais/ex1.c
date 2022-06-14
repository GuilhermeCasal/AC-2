#include <detpic32.h>

    volatile char value = 0x00;

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

void _int_ (8) isr_T2(void){
    send2displays(value);
    IFS0bits.T2IF = 0;
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
    LATE = (LATE & 0x0000);

    EnableInterrupts();
    while(1){
        char c = inkey();
        if(c == '0'){
            LATE = (LATE & 0xFFF0) | 0x0001;
            value = 0;
        }else if(c == '1'){
            LATE = (LATE & 0xFFF0) | 0x0002;
            value = 1;
        }else if(c == '2'){
            LATE = (LATE & 0xFFF0) | 0x0004;
            value = 2;
        }else if(c == '3'){
            LATE = (LATE & 0xFFF0) | 0x0008;
            value = 3;
        }else{
            LATE = LATE | 0x000F;
            value = 0xFF;
            resetCoreTimer();
            while(readCoreTimer < 20000000);
            value = 0;
            LATE = (LATE & 0xFFF0);
        }
    }
    return 0;
}