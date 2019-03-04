SYSEXIT = 1
EXITSUCCESS = 0
SYSWRITE = 4
STDOUT = 1
SYSREAD = 3
STDIN = 0

.text 
message: .ascii "Write 10 letters\n"
message_len = . - message

message2: .ascii "\nWynik: "
message2_len = . - message

.data
buffer: .ascii "           " 
buffer_len = . - buffer

.global _start

_start:

# Write message to screen

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $message, %ecx
mov $message_len, %edx
int $0x80

# GET 10 signs from user
 
mov $SYSREAD, %eax
mov $STDIN, %ebx
mov $buffer, %ecx
mov $buffer_len, %edx
int $0x80

mov $0, %edi

while:
    mov buffer( , %edi, 1), %al
    cmp $96, %al
    ja small_letter
    jmp big_letter
return:

    mov %al, buffer( , %edi, 1)

    inc %edi 

cmp $11, %edi
    jne while

    jmp exit

small_letter:
sub $32, %al
jmp return

big_letter:
add $32, %al
jmp return

exit:   

# Write message2 to screen

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $message2, %ecx
mov $message2_len, %edx
int $0x80

# Write result to screen

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $buffer, %ecx
mov $buffer_len, %edx
int $0x80

# Exit program

mov $SYSEXIT, %eax
mov $EXITSUCCESS, %ebx
int $0x80

/* vim: ft=gas : 
*/ 
