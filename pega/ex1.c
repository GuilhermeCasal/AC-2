#include <detpic32.h>

void delay(unsigned int ms){
    int k= 20000;
    resetCoreTimer();
    while(readCoreTimer() < k * ms);
}

int main(void){

    TRISE = TRISE & 0xFFC0;
    TRISBbits.TRISB2 = 1;
    int segment = 0x0003;
    int flag = 0;
    int count = 0;

while(1){    
    if(count==6){
        segment = 0x0003;
        count = 0;
    }
    LATE = (LATE & 0xFFC0) | segment;

    flag = PORTBbits.RB2;

    if(flag == 0){
        delay(1000/3);
    }else{
        delay(1000/7);
    }
    
    segment = segment << 1;
    count++;
}

    return 0;
}
