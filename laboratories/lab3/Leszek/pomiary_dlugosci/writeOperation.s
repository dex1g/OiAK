SYSWRITE = 4
STDOUT = 1

.data
msg_hello: .ascii "Hello world from assembly !\n"
msg_hello_len = . - msg_hello

.globl	writeOperation
.type	writeOperation, @function
writeOperation:
    pushl %ebx                  # this is necessary to support ABI 
    mov $SYSWRITE, %eax
    mov $STDOUT,%ebx
    mov $msg_hello,%ecx
    mov $msg_hello_len,%edx

    int $0x80
    popl %ebx
    ret
    