.section .data
    msg1: .asciz "Write an integer:"
    mask1: .asciz "%d"
    msg2: .asciz "Write 10 chars:"
    mask2: .asciz "%10s"
    output1: .asciz "The number is %d"
    output2: .asciz "The chars are %s"

.section .bss
    .lcomm number, 4
    .lcomm table, 11

.section .text
.globl main
    main:
        pushl $msg1
        call printf
        addl $4, %esp

        pushl $number
        pushl $mask1
        call scanf
        addl $8, %esp

        pushl $msg2
        call printf
        addl $4, %esp

        pushl $table
        pushl $mask2
        call scanf
        addl $8, %esp
        
	mov $number, %eax
        pushl (%eax)
        pushl $output1
        call printf
        addl $8, %esp
        
        pushl $table
        pushl $output2
        call printf
        addl $8, %esp

        mov $0, %eax
    ret

