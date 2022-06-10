#include <detpic32.h>

typedef struct ex1
{
    char mem[100];
    int nchar;
    int posrd;
} t_buf;

    volatile t_buf txbuf;

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