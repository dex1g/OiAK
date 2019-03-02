#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char binaryToHexSymbols[19][5] = {
    "0000",
    "0001",
    "0010",
    "0011",
    "0100",
    "0101",
    "0110",
    "0111",
    "1000",
    "1001",
    "1010",
    "1011",
    "1100",
    "1101",
    "1110",
    "1111",
    "-",
    ",",
    "."};
const char hexSymbols[] = "0123456789abcdef-,.";

char *getNumberFromConsole()
{
    char *str = NULL;
    scanf("%m[^\n]%*c", &str);
    return str;
}

char *convertBinaryToTwosComplement(char *binaryNumber)
{
    int numberLength = strlen(binaryNumber);
    char *complementRepresentation = malloc(numberLength * sizeof(char)); // allocate new pointer to not modify the parameter value
    strcpy(complementRepresentation, binaryNumber);                       // copy the contents of given number to newly allocated number
    if (*binaryNumber == '-')                                             //check whether value is negative
    {
        // Traverse the string to get first '1' from
        // the end of the string
        int j;
        for (j = numberLength - 1; j >= 0; j--)
        {
            if (complementRepresentation[j] == '1')
                break;
        }

        // Case when someone inserted -0000000 etc.
        if (j == -1)
        {
            memmove(complementRepresentation, complementRepresentation + 1, strlen(complementRepresentation)); // there is not such sign as - in complement system so get rid of it
            return complementRepresentation;
        }

        // Continue the traversal after the position of first '1' bit
        for (int i = j - 1; i >= 0; i--)
        {
            if (complementRepresentation[i] == '1')
                complementRepresentation[i] = '0';
            else if (complementRepresentation[i] == '0')
                complementRepresentation[i] = '1';
            else if (complementRepresentation[i] == '-')
                complementRepresentation[i] = '1';
        }
    }
    else
    {
        // we got a non negative value
        // append 0 at the beginning and it's done
        char *tmp = strdup(complementRepresentation); // save the contents
        char zero[2] = "0";                           // zero as string to append
        strcpy(complementRepresentation, zero);       // copy zero character to array
        strcat(complementRepresentation, tmp);        // concatenation of "0" + given number
        free(tmp);                                    // free allocated resources
    }

    return complementRepresentation;
}

char *convertHexadecimalToBinary(char *hexadecimalNumber)
{
    int numberLength = strlen(hexadecimalNumber) * 4;                 //each symbol is written on 4 chars so allocate proper memory
    char *binaryRepresentation = malloc(numberLength * sizeof(char)); // allocate new array to not modify parameter
    binaryRepresentation[0] = '\0';                                   // insert terminating sign
    int p = 0;

    while (hexadecimalNumber[p])
    {
        char *v = strchr(hexSymbols, tolower(hexadecimalNumber[p++])); // find first occurance of the given hexSymbol
        if (v)
            strcat(binaryRepresentation, binaryToHexSymbols[v - hexSymbols]); //append to string the binary representation of hex symbol
    }
    return binaryRepresentation;
}