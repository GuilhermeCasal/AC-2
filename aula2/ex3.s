    .equ READ_CORE_TIMER,11
	.equ RESET_CORE_TIMER,12
	.equ PUT_CHAR,3
	.equ PRINT_INT,6
	.data
	.text
	.globl main

main: 
    addiu $sp, $sp, -16
    sw  $ra, 0($sp)
    sw  $s0, 4($sp)
    sw  $s1, 8($sp)
    sw  $s2, 12($sp)

    li  $s0, 0  #cnt10 = 0
    li  $s1, 0  #cnt5 = 0
    li  $s2, 0  #cnt1 = 0

while:
    li  $a0, 100
    jal delay

    li  $a0, '\r'
    li  $v0, 3
    syscall

    addi    $s0, $s0, 1
    move    $a0, $s0
    li      $a1, 0x0005000A
    li      $v0, 6
    syscall

if:
    rem     $t0, $s0, 2
    bne     $t0, 0, if2
    addi    $s1, $s1, 1
if2:
    rem     $t0, $s0, 10
    bne     $t0, 0, endif
    addi    $s2, $s2, 1
endif:
    li  $a0, ' '
    li  $v0, 3
    syscall

    move    $a0, $s1
    li      $a1, 0x0005000A
    li      $v0, 6
    syscall

    li  $a0, ' '
    li  $v0, 3
    syscall

    move    $a0, $s2
    li      $a1, 0x0005000A
    li      $v0, 6
    syscall

    j while

    lw  $ra, 0($sp)
    lw  $s0, 4($sp)
    lw  $s1, 8($sp)
    addiu $sp, $sp, 16

    jr $ra

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
