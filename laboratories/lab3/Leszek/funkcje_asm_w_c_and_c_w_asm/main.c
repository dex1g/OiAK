#include <stdio.h>

int number;
char sign;
void change();
extern int sign_asm;
extern char number_asm;

int main()
{
    char *format = "%d-%c\n";
    sign = 'L';
    printf(format, number, sign);
    change();
    printf(format, number, sign);
    printf(format, number_asm, sign_asm);
    return 0;
}

// Compile with
// gcc -m32 -o test main.c asm.s