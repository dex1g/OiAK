SYSEXIT = 1
EXIT_SUCCESS = 0
SYSWRITE = 4
STDOUT = 1

.align 32

.data
nums: .ascii "53715371"
numsLen = . - nums
output: .ascii "   "

.global _start
_start:
mov $0, %edi
mov $0, %eax

loop:
shl $3, %eax
mov nums(, %edi, 1), %bl
sub $0x30, %bl
add %bl,%al
inc %edi
cmp $8, %edi
jne loop

mov $0, %ebx
mov $1, %edi
mov %ax, output(, %edi, 1)
shr $8, %eax
mov %ah, output

mov $SYSEXIT,%eax
mov $EXIT_SUCCESS,%ebx
int $0x80

