#include <detpic32.h>

void puts(char *str){
    while(*str != '0'){
        putc(*str);
        str++;
    }
}

void putc(char byte2send){
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte2send;
}

int main (void){

    U2BRG = ((20 + 8 * 1200) / (16 * 1200)) - 1;
    U2MODEbits.PDSEL = 0b00;
    U2MODEbits.STSEL = 0;
    U2MODEbits.BRGH = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;
    U2STAbits.UTXISEL = 0;
    
    T1CONbits.TCKPS = 3;    //20000000/(65535*2)=128  arredonda para 256;      (20000000/256)/(2)-1 = 39061
    PR1 = 39061;            //
    TMR1 = 0;
   
    IFS0bits.T1IF = 0;
    IPC2bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    T1CONbits.ON = 1;

    TRISB = (TRISB | 0x000F);

    EnableInterrupts();
    while(1){

        puts("RB30=");
        putc(PORTBbits.RB3);
        putc(PORTBbits.RB2);
        putc(PORTBbits.RB1);
        putc(PORTBbits.RB0);

        IFS0bits.T1IF = 0;
    }
    return 0;
}