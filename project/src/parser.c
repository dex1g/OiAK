#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *getNumberFromConsole()
{
    char *str = NULL;
    scanf("%m[^\n]%*c", &str);
    return str;
}

unsigned char asciiToByte(char digit)
{
    unsigned char ret;
    if (digit >= 'A' && digit <= 'F')
        ret = digit - 'A' + 10;
    else if (digit >= 'a' && digit <= 'f')
        ret = digit - 'a' + 10;
    else if (digit >= '0' && digit <= '9')
        ret = digit - '0';
    else
        return 0;
    return ret;
}

int lengthOfHexToBin(char *hexNum)
{
    int numberLength = (strlen(hexNum) + 1) / 2;
    return numberLength + 1;
}

unsigned char *hexToBin(char *hexNum)
{
    int hexNumIndex = strlen(hexNum) - 1;
    int numberLength = (strlen(hexNum) + 1) / 2;
    numberSize = numberLength + 1;
    unsigned char *binRep = malloc(numberSize * sizeof(char));
    binRep[0] = 0;

    for (int i = numberLength; i > 0; i--)
    {
        if (hexNumIndex - 1 >= 0)
            binRep[i] = asciiToByte(hexNum[hexNumIndex - 1]);
        binRep[i] = binRep[i] << 4;
        binRep[i] += asciiToByte(hexNum[hexNumIndex]);
        hexNumIndex = hexNumIndex - 2;
    }
    return binRep;
}

unsigned char *octToBin(char *octNum)
{
    int newTableLength = strlen(octNum) + 1;
    if (!(newTableLength % 8))
        newTableLength += (8 - (newTableLength % 8));
    unsigned char *bcoNum = calloc(newTableLength, sizeof(char));
    int octNumIndex = newTableLength - 1;
    //int numberLength = ((strlen(octNum)*3)+7)/8;
    int iterator = newTableLength / 8;
    int numberLength = iterator * 3;
    numberSize = numberLength;
    unsigned char *binRep = calloc(numberLength, sizeof(char));

    asm volatile(
        "movl $0, %%edi;"
        "movl (%0), %%ecx;"
        "loop: mov $0, %%eax;"
        "mov $7, %%esi;"
        "jmp inner;"
        "inner: sall $3, %%eax;"
        "lea (%2), %%edx;"
        "lea (%%edx, %%edi, 8), %%ebx;"
        "addl (%%ebx, %%esi, 1), %%eax;"
        "decl %%esi;"
        "cmpl $0, %%esi;"
        "jge inner;"
        "jmp done;"
        "done: movl %%edi, %%edx;"
        "sall %%edx;"
        "addl %%edi, %%edx;"
        "movl %%edx, %%esi;"
        "incl %%esi;"
        "movw %%ax, (%%ecx, %%esi, 1);"
        "sall $8, %%eax;"
        "movb %%ah, (%%ecx, %%edx, 1);"
        "incl %%edi;"
        "movl %1, %%ebx;"
        "cmpl %%ebx, %%edi;"
        "jb loop;"
        : "=r"(binRep)                                   /* output */
        : "r"(iterator), "r"(octNum)                     /* input */
        : "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi" /* clobbered register */
    );
    printf("%s\n", binRep);

    return binRep;
}

void onesComplement(unsigned char *number)
{
    int numberLength = numberSize;
    for (int i = 0; i < numberLength; i++)
    {
        number[i] = ~number[i];
    }
}

void increment(unsigned char *number)
{
    int numberLength = numberSize;
    int carry = 1;
    for (int i = numberLength - 1; i >= 0; i--)
    {
        if (!carry)
            break;
        if (++number[i])
            carry = 0;
    }
}

void printNumber(char *number)
{
    int numberLength = numberSize;
    for (int i = 0; i < numberLength; i++)
    {
        printf("%hhx ", number[i]);
    }
    printf("\n");
}