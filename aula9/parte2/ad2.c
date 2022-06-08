#include <detpic32.h>

    volatile int voltage;

void configureall(){

    T3CONbits.TCKPS = 2;   
    PR3 = 49999;              
    TMR3 = 0;                   
    T3CONbits.TON = 1;          
    // Setup PWM
    OC1CONbits.OCM = 6;         
    OC1CONbits.OCTSEL =1;    
    OC1RS = 0;                
    OC1CONbits.ON = 1;          

    // Timer1
    T1CONbits.TCKPS = 3;        
    PR1 = 39062;              
    TMR1 = 0;                   
    T1CONbits.TON = 1;          
    
    // Displays
    TRISB = TRISB & 0x80FF;   //RB8-RB14  
    TRISD = TRISD & 0xFF9F;     //Displays
    TRISB = TRISB | 0x0003;     // RB1 and RB0 
    // ADC
    TRISBbits.TRISB4 = 1;      
    AD1PCFGbits.PCFG4 = 0;      
    AD1CON1bits.SSRC = 7;       
    AD1CON1bits.CLRASAM = 1;   
    AD1CON3bits.SAMC = 16;      
    AD1CON2bits.SMPI = 7;       
    AD1CHSbits.CH0SA = 4;       
    AD1CON1bits.ON = 1;        

    // Enable interrupts ADC, T1, T3
    IPC6bits.AD1IP = 2;        
    IEC1bits.AD1IE = 1;        
    IPC1bits.T1IP = 1;          
    IEC0bits.T1IE = 1;          
    IPC3bits.T3IP = 3;          
    IEC0bits.T3IE = 3;         
    
}

void send2displays(unsigned char value) {
	static const char display7Scodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
	static char displayFlag = 0;

	LATDbits.LATD5 = displayFlag ^ 1;
	LATDbits.LATD6 = displayFlag;

	char value_normalized = (value >> displayFlag*4) & 0x0F;
	char segment = display7Scodes[ value_normalized ];
	LATB = (LATB & 0x80FF) | segment << 8;

	displayFlag = displayFlag ^ 1;
}

unsigned char toBcd(unsigned char value){
    return ((value / 10) << 4) + (value % 4);
}

void _int_(4) isr_T1(void){
    AD1CON1bits.ASAM = 1;
    IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void){
    send2displays(voltage);
    IFS0bits.T3IF = 0;
}

void _int_(27) isr_adc(void){
    int i=0, media=0;
    int *p = (int *)(&ADC1BUF0);

    for ( i = 0; i < 8; i++){
        media += p[i*4];
    }
    voltage = ((media/8)* 33 + 511) / 1023;  
    IFS1bits.AD1IF = 0;  
}

void setPWM(unsigned int dutyCycle)
{
    if (dutyCycle >= 0 && dutyCycle <= 100)
        OC1RS = (dutyCycle * (PR3 + 1)) /100;
}

int main (void){

    int dutyCycle;
    int portVal;
    configureall();

    IFS0bits.T3IF = 0;          
    IFS0bits.T1IF = 0;          
    IFS1bits.AD1IF = 0;         
    EnableInterrupts();

    while(1){
    
        portVal = PORTB & 0x03;

        switch(portVal){
            case 0:
                IEC0bits.T1IE = 1;
                setPWM(0);
                break;
            case 1:
                IEC0bits.T1IE = 0;
                setPWM(100);
                break;
            default:
                IEC0bits.T1IE = 1;
                dutyCycle = voltage *3;
                setPWM(dutyCycle);
                break;
        }
    }
    return 0;
}
