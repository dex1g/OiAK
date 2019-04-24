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
    clc
    call prod # obliczenie iloczynu
    pop %ebp
    ret

prod:
    movl $0, (%ebx) # zerowanie najniższych cyfr iloczynu
    movl $0, 4(%ebx) # zerowanie najniższych cyfr iloczynu
accum:
    pushl %eax # licznik cyfr mnożnika (iloczynów częściowych) 
    pushl %ebx # bieżący indeks najniższej cyfry iloczynu
    movl 8(,%ebp,4), %ecx # odtworzenie licznika cyfr mnożnej
partp:
    movb (,%esi,1), %al # kolejna cyfra mnożnej
    movb (,%edi,1), %dl # kolejna cyfra mnożnika
    mulb %dl # iloczyn częściowy w %ah:al
    add %al, (,%ebx,1) # aktualizacja niższej cyfry iloczynu częściowego
    adc %al, 1(,%ebx,1) # aktualizacja wyższej cyfry iloczynu częściowego
    incl %esi # wskaźnik kolejnej cyfry mnożnej
    loop partp # zliczanie cyfr mnożnej
    pop %ebx # przygotowanie obliczenia następnego
    inc %ebx # iloczynu częściowego
    inc %edi # wskaźnik kolejnej cyfry mnożnika
    pop %eax
    dec %eax # zliczanie cyfr mnożnika
    jnz accum
    ret
