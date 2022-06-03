.equ READ_CORE_TIMER,11
	.equ RESET_CORE_TIMER,12
	.equ PUT_CHAR,3
	.equ PRINT_INT,6
	.data
	.text
	.globl main

main: 
	addiu $sp, $sp, -8
	sw	$ra, 0($sp)
	sw 	$s0, 4($sp)

	li $a0, 1000
	jal delay

	li $s0,0
while: 					# while (1) {
		li 		$v0,12 #
		syscall 
while1:			
		li 		$v0, 11
		syscall
	
		bge		$v0, 200000, endw
		j	while1
endw:
		move	$a0, $s0
		li 		$a1,  0x0004000A
		li		$v0, 6
		syscall
		
		addi 	$s0, $s0, 1
		
		li		$a0, '\r'
		li		$v0, 3
		syscall
			
	j	while
	
	li		$v0, 0

	lw	$ra, 0($sp)
	lw	$s0, 4($sp)
	addiu $sp, $sp, 8	


	jr $ra #



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


