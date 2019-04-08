#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

unsigned int numberSize;

/*
    Structure stores a pointer to number in two's complement system with its length and power of the lowest position.
 */
typedef struct
{
    unsigned char *number;
    unsigned int numberSize;
    int numberPosition;
} TCNumber;

TCNumber *createTCNumber(unsigned char *number, unsigned int numberSize, int numberPosition);

/*
    Gets user input from console and performs basic conversionts between systems with different base.
*/
char *getNumberFromConsole(void);

/*
    Converts hexadecimal string representation to positive two's complement.
*/
TCNumber *hexToBin(char *hexNum);

/*
    Converts up to hexadecimal digit to its binary value.
*/
unsigned char asciiToByte(char digit);

/*
    Negates all bits in the provided table.
*/
void onesComplement(TCNumber *number);

/*
    Increments the binary number in the provided table.
*/
void increment(TCNumber *number);

/*
    Prints out the binary number in hex symbols from the provided table,
    uses the numberSize variable to determine its length.
*/
void printNumber(TCNumber *number);

/*
    Converts octal string representation to positive two's complement.
*/
unsigned char *octToBin(char *octNum);

/*
    Converts a string containing 8 digit octal number to 3 bytes containing its value
*/
unsigned char *octToBinTest(unsigned char *octNum);

void delete(TCNumber *n);

void scaleUp(TCNumber *n);

TCNumber *convertFromHex(char *number);

void trimExtension(TCNumber *n);

#endif
