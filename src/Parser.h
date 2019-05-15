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

TCNumber *createTCNumber_no_realloc(unsigned char *number, unsigned int numberSize, int numberPosition);

/*
    Gets user input from console and performs basic conversionts between systems with different base.
*/
char *getNumberFromSTDIN(void);

/*
    Converts hexadecimal string representation to positive two's complement.
*/
TCNumber *hexToBin(char *hexNum);

/*
    Converts up to hexadecimal digit to its binary value.
*/
unsigned char asciiToByte(char digit);

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
TCNumber *scaleUp(TCNumber *n);

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
TCNumber *getHexNumberFromTxtFile(char *filename);

/*
    Reads number from binary field and returns it as an array of bytes.
*/
TCNumber *getNumberFromBinaryFile(char *filename, int numberPosition);

/*
    Converts given number stored in TCNUmber structure into human readable form in base 16 system.
*/
char *convertToString(TCNumber *num);

/*
    Function converts byte to 2 ascii characters (hex representation)
    Used only in convertToString()
*/
char *byteToAscii(unsigned char *number, unsigned size, char *result);

/*
    Negates all bits in the provided table.
*/
void onesComplement(TCNumber *number);

/*
    Increments the binary number in the provided table.
*/
void increment(TCNumber *number);

#endif
