#include <detpic32.h>

void delay(unsigned int ms){
    int k=20000;
    resetCoreTimer();
    while(readCoreTimer() < k * ms);
}

int main(void){
    LATE = LATE & 0xFFF0;
    TRISE = TRISE & 0xFFF0;
    
    
    int count = 0;
    while(1){
        LATE = (LATE & 0xFFF0) | count;
        delay(250);
        count++;

        if(count > 15){
            count = 0;
        }
    }
    return 0;

}