	.globl	proctime
	.type	proctime, @function
proctime:
	pushl %ebx
	xor %eax, %eax
	cpuid
	rdtsc
	popl %ebx
	ret
	
