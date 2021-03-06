    .equ SFR_BASE_HI, 0xBF88
    .equ TRISE, 0x6100
    .equ PORTE, 0x6110
    .equ LATE, 0x6120
    .equ TRISB, 0x6040
    .equ PORTB, 0x6050
    .equ LATB, 0x6060
    .equ print_int, 6
    .equ print_char, 3
    .equ READ_CORE_TIMER, 11
    .equ RESET_CORE_TIMER, 12


    .data    
    .text
    .globl main

main:
    addiu   $sp, $sp, -16
    sw      $ra, 0($sp)
    sw      $s0, 4($sp)
    sw      $s1, 8($sp)
    sw      $s2, 12($sp)

    lui     $s0, SFR_BASE_HI
    lw      $s1, TRISE($s0)
    andi    $s1, $s1, 0xFFE1
    sw      $s1, TRISE($s0)


     li      $s2, 1 
       

while:
    lw      $s1, LATE($s0)
    andi    $s1, $s1, 0xFFE1

if:
    beqz     $s2, else
    or      $s1, $s1, 0x0012
    j       end_if

else:
    or      $s1, $s1, 0x000C

end_if:
    sw      $s1, LATE($s0)
    xori    $s2, $s2, 1

    move    $a0, $s1
    li      $v0, print_int
    li      $a1, 0x00040002
    syscall

    li     $v0, print_char
    li      $a0, '\n'
    syscall

    li      $t2, 1000
    div     $a0, $t2, 7
    jal     delay

    j       while

    lw      $ra, 0($sp)
    lw      $s0, 4($sp)
    lw      $s1, 8($sp)
    lw      $s2, 12($sp)
    addiu   $sp, $sp, 16

    jr      $ra







delay:
    
    li      $t5, 20000

    li      $v0, RESET_CORE_TIMER
    syscall

while1: 
    mul     $t4, $t5, $a0

    li      $v0, READ_CORE_TIMER
    syscall

    blt     $v0, $t4, while1

    jr      $ra 


    