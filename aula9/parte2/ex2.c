#include <detpic32.h>

void setPWM(unsigned int dutycycle){
    if (dutycycle>=0 && dutycycle<=100){
        OC1RS = (dutyCycle * (PR3 + 1)) /100;
    }
    
}