#include <detpic32.h>

void delay(int ms){
    int k= 20000;
    resetCoreTimer();
    while(readCoreTimer() < ms * k);
}


int main(void){

    TRISBbits.TRISB4 = 1; // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
    AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
                            // mode an internal counter ends sampling and
                            // starts conversion
    AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
                            // interrupt is generated. At the same time,
                            // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 2-1; // Interrupt is generated after XX samples
                            // (replace XX by the desired number of
                            // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
                            // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
                            // This must the last command of the A/D
                            // configuration sequence 


    static const char display7Scodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
    char var = 1;

    TRISEbits.TRISE1 = var;

    TRISB = (TRISB & 0x80FF);
    TRISD = (TRISD & 0xFF9F);
    TRISEbits.TRISE1 = 0;

    LATEbits.LATE1 = 1;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    
    int *p = (int *)(&ADC1BUF0);
    int V=0;
    int uni=16;
    int dig =3;
    int i=0;

    while(1){
        AD1CON1bits.ASAM = 1; // Start conversion
        while( IFS1bits.AD1IF == 0 ); // Wait while conversion not done
        LATEbits.LATE1 = var;
        int media =0;
                
        for (i = 0; i < 16; i++){
            media = media + p[i*4];
        }
        putChar('\n');
        printInt((p[0]), uni | dig << 16);
        putChar(' ');
        V=((media/2)*10-511)/1023;
        LATB = (LATB & 0x80FF) | (display7Scodes[V] << 8);
        IFS1bits.AD1IF = 0;
        delay(1000/5);

        var = var ^ 1;     
        
    }
    return 0;
}
