    .eqv SFR_BASE_HI, 0xBF88
    .eqv TRISE, 0x6100
    .eqv PORTE, 0x6110
    .eqv LATE, 0x6120
    .eqv TRISB, 0x6040
    .eqv PORTB, 0x6050
    .eqv LATB, 0x6060
    .data
    .text
    .globl main:

main:                                   #int void main{
        lui     $t0, SFR_BASE_HI        #             
        lw      $t1, TRISE($t0)         #       $t1 = [TRISE]
        andi    $t1, $t1, 0xFFFE        #       RE0 = 0 (output)
        sw      $t1, TRISE($t0)         #       WRITE TRISE register

        lw      $t1, TRISB($t0)         #       $t1 = [TRISB]
        ori     $t2, $t1, 0x1           #       RB0 = 1 (input)
        sw      $t2, TRISB($t0)         #       WRITE TRISB register

loop:
        lw      $t1, PORTB($t0)         #       $t1 = [PORTB] 
        andi    $t1, $t1, 1             #       $t1 = RB0
        lw      $t2, LATE($t0)          #       $t2 = [LATE]
        andi    $t2, $t2, 0xFFFE        #       RE0 = 0 (output)
        or      $t2, $t2, $t1           #       RE0 = RB0
        sw      $t2, LATE($t0)          #       

        j       loop
        
        lui     $v0, 0                  #

        jr $ra                          #    
