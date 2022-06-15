#include <detpic32.h>

    volatile int count = 15;
    volatile char k;

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
    if(k == 'U'){
        if(count == 16){
            count = 0;
        }
    }     
    if(k == 'R'){
        count = 0;
        puts("RESET");
        putc('\n');
    }
    count = (count & 0xFF) << 1;
    LATE = (LATE & 0xFFE1) | count; 
    count++;
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

    TRISE = (TRISE & 0xFFE1);

    EnableInterrupts();
    while(1){
        if(IFS1bits.U2RXIF == 1){

            while(U2STAbits.URXDA == 0);
            k = U2RXREG;
        }
    }
    return 0;
}


