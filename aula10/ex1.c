#include <detpic32.h>

int main (void){

    //configure UART2
    U2BRG =10                   //(20 MHz / (16*115200)-1)=~10
    U2MODEbits.PDSEL = 0b00;    //8 bit-data , odd parity
    U2MODEbits.STSEL = 0;       //number of stop bits
    U2MODEbits.BRGH = 0;        //divide by 16
    U2STAbits.URXEN = 1;        // Enable Receiver
    U2STAbits.UTXEN = 1;        // Enable Transmitter
    U2MODEbits.ON = 1;          //enable U2

    return 0;
}