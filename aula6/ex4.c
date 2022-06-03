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
    AD1CON2bits.SMPI = 3;       // Interrupt is generated after 4 samples
    AD1CHSbits.CH0SA = 4;       // analog channel input 4
    AD1CON1bits.ON = 1;         // Enable the A/d configuration sequence

    int i;
    int V;

    while(1){
        AD1CON1bits.ASAM = 1;               	// Start conversion
        while ( IFS1bits.AD1IF == 0 );      	// Wait while conversion not done
        
        int *p = (int *)(&ADC1BUF0);
        V=0;

        for ( i = 0; i < 4; i++)
        {
            V= (p[i*4]*33+511)/1023;
        }
        printInt(V/4 , 10 | 2<<16);
        putChar('\n');
        delay(200);
        IFS1bits.AD1IF = 0; 
    }
    return 0;
}
