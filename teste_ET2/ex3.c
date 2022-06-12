#include <detpic32.h>

    static char DS4, DS1, DS2, DS3;

char getc(void){
    while(U2STAbits.URXDA == 0);
    return U2RXREG;
}

void putc(char c){
    while(U2STAbits.UTXBF == 1);
    U2TXREG = c;
}

void puts(char *str){
    while(*str != '\0'){
        putc(*str);
        str++;
    }
}

void _int_(32) isr_uart(){
    if(IFS1bits.U2RXIF == 1){

        while(U2STAbits.URXDA == 0);
        char k = U2RXREG;

        if(k == 'T'){
            LATEbits.LATE4 = !LATEbits.LATE4;
        }
        
        if(k == 'P'){
            puts("DipSwitch=");
            putc(DS4);
            putc(DS3);
            putc(DS2);
            putc(DS1);
            putc('\n');
        }
    }
    IFS1bits.U2RXIF == 0;
} 

int main(void){
    //config timer 2
    U2BRG = ((20 + 8 * 9600) / (16 * 9600)) - 1;
    U2MODEbits.PDSEL = 0b10;
    U2MODEbits.STSEL = 1;
    U2MODEbits.BRGH = 0;
    U2STAbits.URXEN = 1;
    U2STAbits.UTXEN = 1;
    U2MODEbits.ON = 1;

    IPC8bits.U2IP = 1;
	IEC1bits.U2RXIE = 1;
    IFS1bits.U2RXIF = 0;

    TRISB = (TRISB | 0x000F);
    TRISEbits.TRISE4 = 0;
    LATEbits.LATE4 = 1;

    while(1){
        DS4 = (PORTB & 0x0008) >> 3;
        DS3 = (PORTB & 0x0004) >> 2;
        DS2 = (PORTB & 0x0002) >> 1;
        DS0 = (PORTB & 0x0001);
    }

    return 0;
}