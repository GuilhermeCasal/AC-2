#include <detpic32.h>

void configUART(unsigned int baud, char parity, unsigned int stopbits){
    
    if(baud>600 && baud<115200){
        U2BRG = (20 / ((16 * baud)-1));
    }else{
        U2BRG = 10;
    }

    if(parity == 'N'){
        U2MODEbits.PDSEL = 0b00;
    }else if(parity == 'E'){
        U2MODEbits.PDSEL = 0b01;
    }else if(parity == 'O'){
        U2MODEbits.PDSEL = 0b10;
    }else{
         U2MODEbits.PDSEL = 0b00;
    }

    if(stopbits == 1 || stopbits == 2){
        U2MODEbits.STSEL = stopbits - 1;
    }else{
        U2MODEbits.STSEL = 0;
    }

    U2MODEbits.BRGH = 0;                
    U2STAbits.URXEN = 1;              
    U2STAbits.UTXEN = 1;              
    U2MODEbits.ON = 1;     
}