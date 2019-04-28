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
    call ptprod             # obliczenie iloczynu
    popl %esi
    popl %edi
    popl %ebx
    popl %ebp
ret

ptprod:
    movl %edi, %esi         # indeks LSB iloczynu
    dec %edi                # last index of mnożna w EDI
    movb (%ecx), %cl        # mnożnik w CL

ptmul:
    movb (%ebx, %edi), %al	# wczytanie kolejnego bajta mnożnej do AL
    mulb %cl                # AX = AL*CL
    clc
    adcb %al, (%edx, %esi)	# save lower result
    dec %esi
    adcb %ah, (%edx, %esi)	# save higher result
mulcarry:
    dec %esi
    js ptmul
    incb (%edx, %esi)
    jz mulcarry
    
    movl %edi, %esi         # aktualny indeks LSB iloczynu
    dec %edi                # aktualny indeks mnożnej
    jns ptmul

ret
