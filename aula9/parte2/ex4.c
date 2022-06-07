#include <detpic32.h>

void _int_(12) isr_T3(void){
     IFS0bits.T3IF = 0;          // Reset timer T3 interrupt flag
}

void setPWM(unsigned int dutyCycle){
    if (dutyCycle>=0 && dutyCycle<=100){
        OC1RS = (dutyCycle * (PR3 + 1)) /100;
    }  
}

int main(void){

    T3CONbits.TCKPS = 2;        // 1:4 prescaler Fout_presc = 5Mhz;
    PR3 = 49999;                // Fout = 20Mhz / 4(49999+1) = 100Hz
    TMR3 = 0;                   // Reset timer T3 count register
    T3CONbits.TON = 1;          // Enable timer T3

    IPC3bits.T3IP = 2;          // Interrupt priority 2
    IEC0bits.T3IE = 1;          // Enable timer T3 interrupts
    IFS0bits.T3IF = 0;          // Reset timer T3 interrupt flag

    OC1CONbits.OCM = 6;         // PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL =1;       // Use timer T2 as the time base for PWM generation
    OC1RS = 0;              // Ton constant
    OC1CONbits.ON = 1;          // Enable OC1 module   

    
    TRISC = (TRISC & 0xBFFF);
    TRISDbits.TRISD0 = 1;

    int func[3] = {10, 65, 80};

    EnableInterrupts();
    while(1){
        setPWM(func[PORTDbits.RD0]);
        LATCbits.LATC14 = (PORTD & 0x0001);
    }

    return 0;
}


    