	.globl	processorCounter
	.type	processorCounter, @function
processorCounter:
	pushl %ebx
	xor %eax,%eax
	cpuid
	rdtsc					# result in %edx:%eax
	popl %ebx
	ret
	
