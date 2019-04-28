.globl array_mul_byte
.type array_mul_byte @function  # definicja funkcji
array_mul_byte:
    pushl %ebp
    movl %esp, %ebp         # wskaźnik parametrów wywołania
    pushl %ebx
    pushl %edi
    pushl %esi
    movl 8(%ebp), %edi      # rozmiar mnożnej ze stosu
    movl 12(%ebp), %ebx     # adres mnożnej ze stosu
    movl 16(%ebp), %ecx     # adres bajtowego mnożnika ze stosu
    movl 20(%ebp), %edx     # adres iloczynu ze stosu
    movl 24(%ebp), %ebp     # ilosc bardziej znaczacych bitow pozostalych w iloczynie ze stosu
    call ptprod             # obliczenie iloczynu
    popl %esi
    popl %edi
    popl %ebx
    popl %ebp
ret

ptprod:
    movl %edi, %esi         # indeks LSB iloczynu
    add %ebp, %esi              # TESTTTT
    dec %edi                # last index of mnożna w EDI
    movb (%ecx), %cl        # mnożnik w CL

ptmul:
    movb (%ebx, %edi), %al	# wczytanie kolejnego bajta mnożnej do AL
    mulb %cl                # AX = AL*CL
    clc
    adcb %al, (%edx, %esi)	# save lower result
    dec %esi
    adcb %ah, (%edx, %esi)	# save higher result
    jnc mulcarryout

mulcarry:
    dec %esi
    js mulcarryout
    incb (%edx, %esi)
    jz mulcarry

mulcarryout:
    movl %edi, %esi         # aktualny indeks LSB iloczynu
    add %ebp, %esi
    dec %edi                # aktualny indeks mnożnej
    jns ptmul

ret
