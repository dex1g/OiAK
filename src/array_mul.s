.globl array_mul
.type array_mul @function  # definicja funkcji
array_mul:
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
    movl %edi, %esi         # indeks najmniej znaczącego bitu iloczynu
    add %ebp, %esi
    dec %edi                # ostatni index mnożnej w edi
    movb (%ecx), %cl        # mnożnik w CL

ptmul:
    movb (%ebx, %edi), %al	# wczytanie kolejnego bajta mnożnej do AL
    mulb %cl                # AX = AL*CL
    clc
    adcb %al, (%edx, %esi)	# zapisanie niższej części wyniku
    dec %esi
    adcb %ah, (%edx, %esi)	# zapisanie wyższej częsci wyniku
    jnc mulcarryout

mulcarry:
    dec %esi
    js mulcarryout
    incb (%edx, %esi)
    jz mulcarry

mulcarryout:
    movl %edi, %esi         # aktualny indeks najmniej znaczącego bitu iloczynu
    add %ebp, %esi
    dec %edi                # aktualny indeks mnożnej
    jns ptmul

ret
