#include <stdio.h>

short number;
char sign;
void change();
extern char* array_asm;
extern short number_asm;
char* array_c = "s";
int main()
{
    char *format = "%hi-%c\n";
    sign = 'L';
    printf(format, number, sign);
    change();
    printf(format, number, sign);
    printf("%hi\n", number_asm);
    printf("%s\n", array_c);
    return 0;
}

// Compile with
// gcc -m32 -o test main.c asm.s
