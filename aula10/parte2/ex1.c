#include <detpic32.h>

void putc1(char byte){
    while(U1STAbits.UTXBF == 1);
    U2TXREG = byte;
}

void delay(unsigned int ms){
    int k = 20000;
    resetCoreTimer();
    while(readCoreTimer() < k * ms);
}
                      
int main(void){

    TRISDbits.TRISD3 = 0;
    
            // Configure UART2 
    U1BRG = 10;                 // U2BRG = (20Mhz / (16*115200))-1 ~ 10
    U1MODEbits.PDSEL = 0b00;      // 00 = 8-bit data, no parity
    U1MODEbits.STSEL = 0;       // only 1 stop bit
    U1MODEbits.BRGH = 0;        // divide by 16
    U1STAbits.URXEN = 1;        // Enable Receiver
    U1STAbits.UTXEN = 1;        // Enable Transmitter
    U1MODEbits.ON = 1;          // Enable UART2

    while(1){
        putc1(0x5A);
        delay(10);
    }



    return 0;
}

// TENHO QUE VERIFICAR ESTE