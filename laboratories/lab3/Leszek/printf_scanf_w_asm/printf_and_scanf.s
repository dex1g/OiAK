.section .data
    msg: .asciz "Please type your name:\n"
    mask: .asciz "%s"
    output: .asciz "Your name is %s\n"

.section .bss
    .lcomm input, 32

.section .text
.globl main
    main:
        pushl $msg
        call printf
        addl $4, %esp

        pushl $input
        pushl $mask
        call scanf
        addl $8, %esp
        
        pushl $input
        pushl $output
        call printf
        addl $8, %esp

        mov $0x01, %eax
        mov $0, %ebx
    int $0x80

# Compile this with 
# gcc -m32 -o test printf_and_scanf.s
