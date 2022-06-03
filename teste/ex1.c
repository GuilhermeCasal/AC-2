#include <detpic32.h>

void delay(unsigned int ms){
    int k=20000;
    resetCoreTimer();
    while(readCoreTimer() < k * ms);
}

int main(void){
    
    TRISBbits.TRISB2 = 1;
    TRISE = (TRISE & 0xFFC0);
    int value = 1;
    int flag=0;
    int count = 0;

    while(1){
       
        if(count==6){
            count = 0;
            value = 1;
        }

        LATE = (LATE & 0xFFC0) | value;

        value = value << 1;

        flag = PORTBbits.RB2;
        if(flag==0){
            delay(1000/3);
        }else{
            delay(1000/7);
        }
        count++;
    }  
    return 0;
}

