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

    lui     $s0, SFR_BASE_HI
    lw      $t1, TRISE($s0)
    andi    $t1, $t1, 0xFFF0
    sw      $t1, TRISE($s0)

    li      $s1, 0      #count = 0

loop:
    lw      $t1, LATE($s0)
    andi    $t1, $t1, 0xFFF0
    or      $t1, $t1, $s1
    sw      $t1, LATE($s0)
    li      $a0, 666
    jal     delay

    andi    $t2, $t1, 0x0008
    srl     $t2, $t2, 3
    sll     $s1, $s1, 1
    xori    $t2, $t2, 0x0001
    or      $s1, $s1, $t2
    andi    $s1, $s1, 0x000F

    j       loop

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
