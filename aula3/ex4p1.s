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
        andi    $t1, $t1, 0xFFF0        #       RE0 = 0 (output)
        sw      $t1, TRISE($t0)         #       WRITE TRISE register

        lw      $t1, TRISB($t0)         #       $t1 = [TRISB]
        ori     $t2, $t1, 0x000F        #       RB0 = 1 (input)
        sw      $t2, TRISB($t0)         #       WRITE TRISB register

loop:
        lw      $t1, PORTB($t0)         #       $t1 = [PORTB]
        andi    $t1, 0x0000F            #       $t1 = RB0, RB1, RB2, RB3
        xori    $t1, $t1, 0x00009       #       $t2 = RB0\ && RB3\

        lw      $t2, LATE($t0)          #       $t2 = [LATE]
        andi    $t2, $t2, 0xFFF0        #       RE0 ... RB3 = 0
        or      $t2, $t2, $t1   
        sw      $t2, LATE($t0)
        
        j       loop
        li      $v0, 0

        jr      $ra