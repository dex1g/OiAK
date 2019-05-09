.globl signptr_asm
.globl number_asm
.data
	schema: .asciz "ASM z C: %hd - %c\n"
	znak: .byte 'A
	number_asm: .short 1488
	signptr_asm: .4byte znak

.globl	asm_print
.type	asm_print, @function
asm_print:
	movl $signptr, %eax
	movl $znak, (%eax)
	movl $105, number
	movl $0, %eax
	ret
	
