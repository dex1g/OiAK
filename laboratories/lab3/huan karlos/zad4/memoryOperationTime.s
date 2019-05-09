.data
number: .int 15

.globl	memoryOperationTime
.type	memoryOperationTime, @function
memoryOperationTime:
    pushl %esi
    pushl %edi
    pushl %ebx

    xor %eax, %eax
    cpuid
    rdtsc

    mov %edx, %edi
    mov %eax, %esi

    movl $200, number

    rdtsc

    subl %esi, %eax
    sbbl %edi, %edx

    popl %ebx
    popl %edi
    popl %esi
    ret
    
