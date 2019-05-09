#include <stdio.h>

short number;
char* signptr;
void asm_print();
extern short number_asm;
extern char* signptr_asm;

int main()
{
    char letter = 'M';
    number = 937;
    signptr = &letter;
    char *format = "C z ASM: %hd - %c\n";
    printf(format, number_asm, *signptr_asm);
    char *format2 = "ASM z C: %hd - %c\n";
    printf(format2, number, *signptr);
    asm_print();
    printf(format2, number, *signptr);
    return 0;
}
