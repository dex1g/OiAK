.section .data
    msg: .asciz "Enter integer:"
    msg1: .asciz "Enter char[10]:"
    char: .asciz "%s"
    int: .asciz "%d"
    output: .asciz "Inserted integer %d"
    output1: .asciz "Inserted string %s"

.section .bss
    .lcomm input, 11
    .lcomm integer, 4

.section .text
.globl main
    main:
        pushl $msg
        call printf
        addl $4, %esp


	pushl $integer
	pushl $int
	call scanf
	addl $8, %esp

	mov $integer, %eax
	pushl (%eax)
        pushl $output
        call printf
        addl $8, %esp

	pushl $msg1
        call printf
        addl $4, %esp

	pushl $input
	pushl $char
	call scanf
	addl $8, %esp

	pushl $input
	pushl $output1
	call printf
	addl $8, %esp

        mov $0x00, %eax
	ret

# Compile this with 
# gcc -m32 -o test printf_and_scanf.s
