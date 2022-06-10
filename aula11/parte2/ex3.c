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

void putstrInt(char *s){
    while(txbuf.nchar > 0); //esperar ate que o buffer noa esteja vazio

    int i=0;
    for (int i = 0; s[i] != '\0' ; i++) //copiar todos os carateres da string s para o buffer
    {
        txbuf.mem[i] = s[i];
        txbuf.nchar++;
    }

    txbuf.posrd = 0;            //inicializar posrd =0
    IEC1bits.U2TXIE = 1;        //U2TX Int Enable
}

int main (void){

    U2BRG = 10;
    U2MODEbits.PDSEL = 0b00;
    U2MODEbits.STSEL = 0;
    U2MODEbits.BRGH = 0;
    U2MODEbits.UTXISEL = 0b00;
    U2STAbits.URXEN = 1;        
    U2STAbits.UTXEN = 1;        
    IEC1bits.U2RXIE = 0;
    IEC1bits.U2TXIE = 0;
    IPC8bits.U2IP = 1;
    IFS1bits.U2RXIF = 0;      
    IFS1bits.U2TXIF = 0;      
    
    EnableInterrupts();
    txbuf.nchar = 0;

    while (1)
    {
        putstrInt("Teste string wich can be as long as you like as long as it is no longer than 100 characteres\n ");
    }
    return 0;
}