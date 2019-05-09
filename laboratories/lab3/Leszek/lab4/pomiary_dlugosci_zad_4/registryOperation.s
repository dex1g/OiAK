.globl	registryOperation
.type	registryOperation, @function
registryOperation:
    pushl %ebx
    pushl %esi
    pushl %edi
	xor %eax,%eax
	cpuid                   # modifies %eax, %ebx, %ecx, %edx
	rdtsc					# result in %edx:%eax
    movl %eax, %esi
    movl %edx, %edi
    movl $123, %eax         # not necessary but shows diffrent from two instructions which are always exectued
    rdtsc
    subl %esi,%eax
    sbbl %edi,%edx

    popl %edi
    popl %esi
	popl %ebx
	ret
    