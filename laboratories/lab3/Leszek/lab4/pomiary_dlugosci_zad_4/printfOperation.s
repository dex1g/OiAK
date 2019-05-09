.data
msg_hello: .asciz "Hello world from assembly with printf !\n"

.globl	printfOperation
.type	printfOperation, @function
printfOperation:
    pushl %ebx
    pushl %esi
    pushl %edi
    xor %eax,%eax
	cpuid                   # modifies %eax, %ebx, %ecx, %edx
	rdtsc					# result in %edx:%eax
    movl %eax, %esi
    movl %edx, %edi
    pushl $msg_hello
    call printf
    addl $4, %esp
    rdtsc
    subl %esi,%eax
    sbbl %edi,%edx

    popl %edi
    popl %esi
	popl %ebx
    ret
    