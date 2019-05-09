SYSWRITE = 4
STDOUT = 1

.data
msg_hello: .ascii "Hello world from assembly !\n"
msg_hello_len = . - msg_hello

.globl	writeOperationTime
.type	writeOperationTime, @function
writeOperationTime:
    pushl %ebx
    pushl %esi
    pushl %edi

    xor %eax, %eax
    cpuid
    rdtsc

    mov %edx, %edi
    mov %eax, %esi

    mov $SYSWRITE, %eax
    mov $STDOUT, %ebx
    mov $msg_hello, %ecx
    mov $msg_hello_len, %edx
    int $0x80

    xor %eax, %eax
    cpuid
    rdtsc

    subl %esi, %eax
    sbbl %edi, %edx

    popl %edi
    popl %esi
    popl %ebx
    ret
    
