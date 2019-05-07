	.globl	processorTimeCounter
	.type	processorTimeCounter, @function
processorTimeCounter:
	pushl	%ebp			# save %ebp register to not move on the stack pointer
	movl	%esp, %ebp
	pushl	%ecx			# sace %ecx register to make function work with ABI

	movl	8(%ebp), %ecx	# get the argument (it's long)
	rdtsc					# result in %edx:%eax
	movl	%edx, 4(%ecx)	# save the lower part of rdtsc result in the passed argument
	movl	%eax, (%ecx)	# save the upper part of rdtsc result in the passed argument

	popl	%ecx			# pop back the pushed registers
	popl	%ebp
	ret
	