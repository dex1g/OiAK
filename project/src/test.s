movl 0, %edi;
movl (binRep), %ecx;
loop: mov $0, %eax;
    mov $7, %esi;
    jmp inner;

inner: sall $3, %eax;
    lea (octnum), %edx;
    lea (%edx, %edi, 8), %ebx;
    addl (%ebx, %esi, 1), %eax;
    decl %esi;
    cmpl $0, %esi;
    jge inner;
    jmp done;

done: movl %edi, %edx;
    sall %edx;
    addl %edi, %edx;
    movl %edx, %esi;
    incl %esi;
    movw %ax, (%ecx, %esi, 1);
    sall $8, %eax;
    movb %ah, (%ecx, %edx, 1);
    incl %edi;
    movl {iterator}, %ebx;
    cmpl %ebx, %edi;
    jb loop;
