SYSWRITE = 4
STDOUT = 1

.data
msg_hello: .ascii "Hello world from assembly with syswrite !\n"
msg_hello_len = . - msg_hello

.globl	writeOperation
.type	writeOperation, @function
writeOperation:
    pushl %ebx
    pushl %esi
    pushl %edi
    xor %eax,%eax
	cpuid                   # modifies %eax, %ebx, %ecx, %edx
	rdtsc					# result in %edx:%eax
    movl %eax, %esi
    movl %edx, %edi
    mov $SYSWRITE, %eax
    mov $STDOUT,%ebx
    mov $msg_hello,%ecx
    mov $msg_hello_len,%edx
    int $0x80
    rdtsc
    subl %esi,%eax
    sbbl %edi,%edx

    popl %edi
    popl %esi
	popl %ebx
    ret
    