	.equ READ_CORE_TIMER,11
	.equ RESET_CORE_TIMER,12
	.equ PUT_CHAR,3
	.equ PRINT_INT,6
	.data
	.text
	.globl main
main: 
	li $t0,0
while: 					# while (1) {
		li 		$v0,12 #
		syscall 
while1:			
		li 		$v0, 11
		syscall
	
		bge		$v0, 200000, endw
		j	while1
endw:
		move	$a0, $t0
		li 		$a1,  0x0004000A
		li		$v0, 6
		syscall
		
		addi 	$t0, $t0, 1
		
		li		$a0, '\r'
		li		$v0, 3
		syscall
			
	j	while
	
	li		$v0, 0
	
	jr $ra #
