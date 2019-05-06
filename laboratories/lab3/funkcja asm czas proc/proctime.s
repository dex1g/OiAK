	.globl	proctime
	.type	proctime, @function
proctime:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx

	movl	8(%ebp), %ecx
	rdtsc
	movl	%edx, 4(%ecx)
	movl	%eax, (%ecx)

	popl	%ecx
	popl	%ebp
	ret
	