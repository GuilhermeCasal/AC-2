#include <detpic32.h>

typedef struct ex1
{
    char mem[100];
    int nchar;
    int posrd;
} t_buf;

    volatile t_buf txbuf;

void _int_(32) isr_uart2(void){
    if(IFS1bits.U2TX == 1){
        if(txbuf.nchar > 0){
            U2TXREG = txbuf.mem[txbuf.posrd];
            txbuf.posrd++;
            txbuf.nchar--;     
        }else{
            IEC1bits.U2TX = 0; 
        }
        IFS1bits.U2TX = 0;
    }
}