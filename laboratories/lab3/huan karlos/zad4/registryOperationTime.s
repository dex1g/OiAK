	.globl	registryOperationTime
	.type	registryOperationTime, @function
registryOperationTime:
    pushl %esi
    pushl %edi
    pushl %ebx

    xor %eax, %eax
    cpuid
    rdtsc

    mov %edx, %edi
    mov %eax, %esi

    rdtsc

    subl %esi, %eax
    sbbl %edi, %edx

    popl %ebx
    popl %edi
    popl %esi
    ret
    
