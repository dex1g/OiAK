	.text
	.comm	nmb, 4
	
	.globl	doit
	.type	doit, @function
doit:
	pushl	%ebp
	movl	%esp, %ebp

	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax

	movl	nmb@GOT(%eax), %edx
	movl    $12, (%edx)
	addl	$4, (%edx)

	movl	mun@GOT(%eax), %edx
	movb	$'A, (%edx)

	movl    mun@GOT(%eax), %edx
	pushl   (%edx)
	movl    nmb@GOT(%eax), %edx
	pushl   (%edx)
	movl    nyg@GOT(%eax), %edx
	pushl   (%edx)

	call    printf@PLT
	addl    $12, %esp

	popl	%ebp
	ret
	