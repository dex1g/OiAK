.globl array_asm
.globl number_asm
.data
	array_asm: .asciz "asm ascii string\n"
	number_asm: .short 32
	sign_asm: .asciz "A"

.globl	change
.type	change, @function
change:
	movl $10,number
	movl $'B,sign
	mov $array_c, %eax
	movl $sign_asm, (%eax)
	ret
	
