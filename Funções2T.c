void putc(char c){
    while(U2STAbits.UTXBF == 1);
    U2TXREG = c;
}

void puts(char *str){
    while(*str != '\0'){
        putc(*str);
        str++;
    }
}

void setPWM(unsigned int dutyCycle){
    if(dutyCycle > 0 && dutyCycle < 100){
        OC2RS = (dutyCycle * (PR3 +1)) / 100;
    }
}

void send2displays(char value){
    int display7codes[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };
    static int displayFlag = 0;
    unsigned char dh = value >> 4;
    unsigned char dl = value & 0x0F;
    char segment;

    if(displayFlag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        segment = display7codes[dl];
        LATB = (LATB & 0x80FF) | segment << 8;
    }else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        segment = display7codes[dh];
        LATB = (LATB & 0x80FF) | segment << 8;
    }
    displayFlag = displayFlag ^ 1;
}

char toBCD(char value){
    return ((value/10) << 4) + (value % 10);
}

void delay(unsigned int ms){
    int k = 20000;
    resetCoreTimer();
    while(readCoreTimer() < k * ms);
}


int voltageConversion(int voltage){
    int temp = ((voltage * 33 + 511) / 1024);
    int aux = 1.36*temp + 0.5;
    return  aux + 20;
}