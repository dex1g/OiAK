EXIT=1
READ=3
WRITE=4
STDOUT=1

.data
msg: .ascii "Hello world!\n"
len = . - msg

.text
.global _start

_start:
mov $len, %edx
mov $msg, %ecx
mov $STDOUT, %ebx
mov $WRITE, %eax
int $0x80

mov $EXIT, %eax
int $0x80
