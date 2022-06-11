#include <detpi32.h>

void setPWM(unsigned int dutyCycle){
    if(dutyCycle > 0 && dutyCycle < 100){
        OC2RS = (dutyCycle * (PR3 +1)) / 100;
    }
}

int main (void){

    T3CONbits.TCKPS = 1;
    PR3 = 35713;
    TMR3 = 0;
    T3CONbits.TON = 1;

    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    OC2CONbits.OCM = 6; 
    OC2CONbits.OCTSEL =0;
    OC2CONbits.ON = 1;

    TRISB = (TRISB | 0x0009);
    char portVal;

    while(1){
        resetCoreTimer();       
        //250 microsec = 250000ns
        //ciclos = 250000 / 50 = 5000 ciclos;
        while(readCoreTimer() < 5000);

        portVal = PORTB & 0x0009;

        if(portVal == 0x1){
            setPWM(25);
        }else{
            setPWM(70);
        }
        IFS0bits.T3IF = 0;
    }
    return 0;
}

