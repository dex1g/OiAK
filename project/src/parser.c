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
    int numberLength = (strlen(hexNum) + 1) / 2;
    numberSize = numberLength + 1;
    unsigned char *binRep = malloc(numberLength * sizeof(char) + 1);
    binRep[0] = 0;

    for (int i = 0; i < numberLength; i++)
    {
        binRep[i + 1] = asciiToByte(hexNum[2 * i]);

        binRep[i + 1] = binRep[i + 1] << 4;
        binRep[i + 1] += asciiToByte(hexNum[2 * i + 1]);
    }
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