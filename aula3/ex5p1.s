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

main:
    addiu   $sp, $sp, -12
    sw      $ra, 0($sp)
    sw      $s0, 4($sp)
    sw      $s1, 8($sp)


    li      $s0, 0      #v=0

    lui     $s1, SFR_BASE_HI

    lw      $t1, TRISE($s1)
    andi    $t1, $t1, 0xFFFE
    sw      $t1, TRISE($s1)

loop2:
    lw      $t1, LATE($s1)
    andi    $t1, $t1, 0xFFFE
    or      $t2, $t1, $s0
    sw      $t2, LATE($s1)

    li      $a0, 500
    jal     delay
    xori    $s0, $s0, 1
    
    j       loop2

    lw      $ra, 0($sp)
    lw      $s0, 4($sp)
    lw      $s1, 8($sp)
    addiu   $sp, $sp, 12
    
    jr      $ra


delay:
	li $t1, 20000
	move $t0, $a0
    li $v0, 12
	syscall
while2:
	li $v0, 11
	syscall
	mul $t2, $t1, $t0
	bge $v0, $t2, endw2
	j while2
endw2:
	jr $ra
