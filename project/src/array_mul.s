.globl array_mul
.type array_mul @function # definicja funkcji
array_mul:
    pushl %ebp
    movl %esp, %ebp # wskaźnik parametrów wywołania
    movl 8(%ebp), %ecx # rozmiar mnożnej ze stosu
    movl 12(%ebp), %esi # adres mnożnej ze stosu
    movl 16(%ebp), %eax # rozmiar mnożnika ze stosu
    movl 20(%ebp), %edi # adres mnożnika ze stosu
    movl 24(%ebp), %ebx # adres iloczynu ze stosu
    movl 28(%ebp), %ebx # rozmiar iloczynu ze stosu
    pushl %ebx
    pushl %edi
    pushl %esi
    clc
    call prod # obliczenie iloczynu
    popl %esi
    popl %edi
    popl %ebx
    popl %ebp
ret

prod:
    # Tu ma byc wywolywanie bajtowego mula dla kolejnych bajtow mnoznika
ret
