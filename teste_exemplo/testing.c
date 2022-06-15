#include <detpic32.h>


void putc(char byte2send)
{
    while(U2STAbits.UTXBF == 1);    // wait while UTXBF == 1
    return U2TXREG;                 // Copy byte2send to the UxTXREG register
}

void _int_(32) isr_uart(){
    if(  IFS1bits.U2RXIF == 1){
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
      IFS1bits.U2RXIF = 0;
}
void puts(char *str){
    while(*str != '\0'){
        putc(*str);
        str++;
    }
}

int main(void){
    
    U2BRG= ((20 + 8 * 9600) / (16 * 9600)) - 1;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0b10;
    U2MODEbits.STSEL = 1;
    U2STAbits.URXEN = 1;
    U2STAbits.UTXEN = 1;
    U2MODEbits.ON = 1;

    IPC8bits.U2IP = 1;
	IEC1bits.U2RXIE = 1;
    IFS1bits.U2RXIF = 0;

    TRISB = (TRISB | 0x000F);
    TRISEbits.TRISE4 = 0;
    LATEbits.LATE4 = 1;

    EnableInterrupts();
    while(1){
        DS4 = (PORTB & 0x0008) >> 3;
        DS3 = (PORTB & 0x0004) >> 2;
        DS2 = (PORTB & 0x0002) >> 1;
        DS1 = (PORTB & 0x0001);
    }

    return 0;
}

