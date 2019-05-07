	.text
	.comm	nmb, 4
	
	.globl	doit
	.type	doit, @function
doit:
	pushl	%ebp
	movl	%esp, %ebp

	movl	$69, nmb
	movb	$'B, mun

	pushl   mun
	pushl   nmb
	pushl   nyg

	call    printf
	addl    $12, %esp

	popl	%ebp
	ret
	