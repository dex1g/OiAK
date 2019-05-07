.globl sign_asm
.globl number_asm
.data
	sign_asm: .byte 'A
	number_asm: .int 32

.globl	change
.type	change, @function
change:
	movl $10,number
	movl $'B,sign
	ret
	