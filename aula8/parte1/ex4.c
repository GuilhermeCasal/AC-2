#include <detpic32.h>

void _int_(4) isr_T1(void){
    printStr("1\n");
    IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
    printStr("3\n");
    IFS0bits.T3IF = 0;
}

int main(void){
    T3CONbits.TCKPS = 5;    // 1:256 prescaler Fout_presc = 78125;
    PR3 = 62499;            // Fout = 20Mhz / (256 * (39063 + 1)) = 1,999Hz
    TMR3 = 0;               // Reset timer T3 count register
    T3CONbits.TON = 1;      // Enable timer T3  

    T1CONbits.TCKPS = 3;    // 1:256 prescaler Fout_presc = 78125;
    PR1 = 39062;            // Fout = 20Mhz / (256 * (39063 + 1)) = 1,999Hz
    TMR1 = 0;               // Reset timer T3 count register
    T1CONbits.TON = 1;      // Enable timer T3  

    IPC3bits.T3IP = 2;      // Interrupt priority 2
    IEC0bits.T3IE = 1;      // Enable timer T3 interrupts
    IFS0bits.T3IF = 0;      // Reset timer T3 interrupt flag 

    IPC1bits.T1IP = 2;      // Interrupt priority 2
    IEC0bits.T1IE = 1;      // Enable timer T3 interrupts
    IFS0bits.T1IF = 0;      // Reset timer T3 interrupt flag 

    EnableInterrupts();
    while(1);
    return 0;
}



