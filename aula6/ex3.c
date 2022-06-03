#include <detpic32.h>

void delay(int ms){
    int k= 20000;
    resetCoreTimer();
    while(readCoreTimer() < ms * k);
}

int main(void){

    TRISBbits.TRISB4 = 1;       // RB4 digital output disconnected
    AD1PCFGbits.PCFG4 = 0;      // RB4 configured as analog input (AN4)
    AD1CON1bits.SSRC = 7;       // Conversion trigger constant
    AD1CON1bits.CLRASAM = 1;    // Stop conversion when the 1st A/D converter intetupr is generated.
                                // At the same time, hardware clears ASAM bit
    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100ns)
    AD1CON2bits.SMPI = 3;       // Interrupt is generated after 1 sample
    AD1CHSbits.CH0SA = 4;       // analog channel input 4
    AD1CON1bits.ON = 1;         // Enable the A/d configuration sequence

    while(1){
        AD1CON1bits.ASAM = 1;               // Start conversion
        while ( IFS1bits.AD1IF == 0 );      // Wait while conversion not done

        int i;
        int *p = (int *)(&ADC1BUF0);

        for(i=0; i<16; i++){
            printInt(p[i*4], 10 | 4<<16);
            putChar(' ');
        }
        putChar('\n');
        
        delay(200);

        IFS1bits.AD1IF = 0;                 // Reset AD1IF
    }

    return 0;
}
