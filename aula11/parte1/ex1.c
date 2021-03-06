#include <detpic32.h>

int main(void){
   // Configure UART2: 115200, N, 8, 1
    U2BRG = 10;                 // U2BRG = (20Mhz / (16*115200))-1 ~ 10
    U2MODEbits.PDSEL = 00;      // 00 = 8-bit data, no parity
    U2MODEbits.STSEL = 0;       // only 1 stop bit
    U2MODEbits.BRGH = 0;        // divide by 16
    U2STAbits.URXEN = 1;        // Enable Receiver
    U2STAbits.UTXEN = 1;        // Enable Transmitter
    U2MODEbits.ON = 1;          // Enable UART2

     // enable U2RXIE, disable U2TXIE (register IEC1)
    IEC1bits.U2RXIE = 1; // ativar a interrupçao de receçao         // Configure UART2 interrupts, with RX interrupts enabled
    IEC1bits.U2TXIE = 0; // desativar transmissao // and TX interrupts disabled:
    
    IPC8bits.U2IP = 1;  // set UART2 priority level (register IPC8)  // prioridades 

    IFS1bits.U2RXIF = 0;  // clear Interrupt Flag bit U2RXIF (register IFS1)                                 
    IFS1bits.U2TXIF = 0;
    IFS1bits.U2EIF = 0;//erro
    
    EnableInterrupts();
    // define RX interrupt mode (URXISEL bits)

    while(1);
    return 0;
 } 
 