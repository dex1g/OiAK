#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
    Structure stores a pointer to number in two's complement system with its length and power of the lowest position.
 */
typedef struct
{
    unsigned char *number;
    unsigned int numberSize; // bytewise
    int numberPosition;      // bitwise
} TCNumber;

/*
    Creates new TCNumber based on the given parameters.
 */
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
    Deallocates the used resources (array which contains byte representation and the structure itself).
*/
void delete (TCNumber *n);

/*
    Removes trailing zeroes from given number.
*/
void scaleUp(TCNumber *n);

/*
    Converts given number in char array format into byte representation which is stored with all additional data in TCNumber structure.
*/
TCNumber *convertFromHex(char *number);

/*
    Trims unnecessary extension bytes from given number.
*/
void trimExtension(TCNumber *n);

/*
    Scales given number to length and size given in parameters.
    Used in arithmetic operations such as addition and substraction.
*/
TCNumber *scaleNumber(TCNumber *n, unsigned int targetSize, int targetPosition);

/*
    Reads number stored in file and returns it in TCNumberRepresentation.
    Reading only one number is supported (number must be in the first line)
*/
TCNumber *getNumberFromFile(char *filename);

#endif
