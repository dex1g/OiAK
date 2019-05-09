.data
    integer: .int 1
.globl	memoryOperation
.type	memoryOperation, @function
memoryOperation:
    pushl %ebx
    pushl %esi
    pushl %edi
	xor %eax,%eax
	cpuid                   # modifies %eax, %ebx, %ecx, %edx
	rdtsc					# result in %edx:%eax
    movl %eax, %esi
    movl %edx, %edi
    movl $2115,integer
    rdtsc
    subl %esi,%eax
    sbbl %edi,%edx

    popl %edi
    popl %esi
	popl %ebx
	ret
    