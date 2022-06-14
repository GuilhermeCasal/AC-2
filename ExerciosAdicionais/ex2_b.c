#include <detpic32.h>
#include <stdio.h>

    volatile int counter=0;

void _int_(8) isr_T2(void){
    send2displays(counter);
    IEC0bits.T2IE = 1;
}

void _int_(4) isr_T1(void){
    if(counter == 9){
        counter = 0;
    }
    printf(%d, counter);
    counter++;
    IEC0bits.T1IE = 1;
}

void send2displays(unsigned char value){
    static char displays7codes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0;
    unsigned char dh = value >> 4;
    unsigned char dl = value & 0x0F;
    char segment;

    if(displayFlag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        segment = displays7codes[dl];
        LATB = (LATB & 0x80FF) | segment << 8;
    }else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        segment = displays7codes[dh];
        LATB = (LATB & 0x80FF) | segment << 8;
    }
    displayFlag = displayFlag ^ 1;
}

int main(void){
    T2CONbits.TCKPS = 3;    //20000000/(65535*50)= 6 arredonda para 8;      (20000000/8)/(50)-1 = 49999
    PR2 = 49999;            //
    TMR2 = 0;
   
    IFS0bits.T2IF = 0;
    IPC2bits.T2IP = 2;
    IEC0bits.T2IE = 1;
    T2CONbits.ON = 1;

    T1CONbits.TCKPS = 2;     // 20MHz / (65536*10) = 30 arredonada para 64;        (20000000/64)/(10Hz) -1 = 32249 
    PR1 = 31249;             //
    TMR1 = 0;

    IFS0bits.T1IF = 0;
    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    T1CONbits.ON = 1;

    TRISD = (TRISD & 0xFF9F);
    TRISB = (TRISB & 0x80FF); 

    EnableInterrupts();

    while(1){
        char c = inkey();
        if(c >= '0' && c <= '4'){
            PR1 = (20000000/256)/(2*(1+c))-1;
            printf("Nova frequencia: %d", c);
        }
    }
    return 0;
}