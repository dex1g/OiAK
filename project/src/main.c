// Contains the main funcion which tests the behaviour of library
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter a number with any precision in system with one of the following bases\n");
    printf("1.Signed binary(insert - at the beginning if the value is negative)\n2.Decimal\n3.Hexadecimal\n4.Octal\n");
    char *number = getNumberFromConsole();
    printf("Number got: %s\n", number);
    unsigned char *thing = hexToBin(number);
    printNumber(thing);
    onesComplement(thing);
    printNumber(thing);
    increment(thing);
    printNumber(thing);
    free(number);
    free(thing);
}