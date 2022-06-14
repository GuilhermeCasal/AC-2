#include <detpic32.h>

int main(void){

    T2CONbits.TCKPS = 5;
    PR2 = 62499;
    TMR2 = 0;

    IPC2bits.T2IP = 2;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;
    T2CONbits.TON = 1;

    OC1CONbits.OCM = 6; //
    OC1CONbits.OCTSEL =0;//
    OC1RS = 12500;
    OC1CONbits.ON = 1;

}