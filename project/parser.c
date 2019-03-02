#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getNumberFromConsole()
{
    char *str = NULL;
    scanf("%m[^\n]%*c", &str);
    return str;
}

char *convertBinaryToTwosComplement(char *binaryNumber)
{
    int numberLength = strlen(binaryNumber);
    char *complementRepresentation = NULL;

    if (*binaryNumber == '-') //check whether value is negative
    {
        complementRepresentation = malloc(numberLength * sizeof(char)); //create new pointer to not modify the parameter value
        strcpy(complementRepresentation, binaryNumber);                 // copy the contents of given number to newly allocated number
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
            return complementRepresentation;

        // Continue the traversal after the position of first '1' bit
        for (int i = j - 1; i >= 0; i--)
        {
            if (complementRepresentation[i] == '1')
                complementRepresentation[i] = '0';
            else
                complementRepresentation[i] = '1';
        }
    }
    else
    {
        // we got a non negative value
        // append 0 at the beginning and it's done
        complementRepresentation = malloc(numberLength * sizeof(char)); //create new pointer to not modify the parameter value
        strcpy(complementRepresentation, binaryNumber);                 // copy the contents of given number to newly allocated number
        char *tmp = strdup(complementRepresentation);                   // save the contents
        char zero[2] = "0";                                             // zero as string to append
        strcpy(complementRepresentation, zero);                         // copy zero character to array
        strcat(complementRepresentation, tmp);                          // concatenation of "0" + given number
        free(tmp);                                                      // free allocated resources
    }

    return complementRepresentation;
}