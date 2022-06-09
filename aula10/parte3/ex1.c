#include <detpic32.h>

void putc(char byte){
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

void puts(char *str){
    if(*str != '\0'){
        putc(*str);
    }
}

int main (void){
    
    U2BRG = 10;                 // U2BRG = (20Mhz / (16*115200))-1 ~ 10
    U2MODEbits.PDSEL = 0b00;      // 00 = 8-bit data, no parity
    U2MODEbits.STSEL = 0;       // only 1 stop bit
    U2MODEbits.BRGH = 0;        // divide by 16
    U2STAbits.URXEN = 1;        // Enable Receiver
    U2STAbits.UTXEN = 1;        // Enable Transmitter
    U2MODEbits.ON = 1;          // Enable UART2

    TRISDbits.TRISD11 = 0;

    while(1){
        while(U2STAbits.TRMT == 0);
        LATDbits.LATD11 = 1;
        puts("12345");
        LATDbits.LATD11 = 1;
    }    
    return 0;
}