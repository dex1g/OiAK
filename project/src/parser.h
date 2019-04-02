#ifndef PARSER_H_
#define PARSER_H_

int numberSize;

/*
    Gets user input from console and performs basic conversionts between systems with different base.
*/
char *getNumberFromConsole();

/*
    Converts hexadecimal string representation to positive two's complement.
*/
unsigned char *hexToBin(char *hexNum);

/*
    Converts up to hexadecimal digit to its binary value.
*/
unsigned char asciiToByte(char digit);

/*
    Negates all bits in the provided table.
*/
void onesComplement(unsigned char *number);

/*
    Increments the binary number in the provided table.
*/
void increment(unsigned char *number);

/*
    Prints out the binary number in hex symbols from the provided table,
    uses the numberSize variable to determine its length.
*/
void printNumber(char *number);

/*
    Returns length of provided hex number in binary representation, increased by 1 byte (extension).
*/
int lengthOfHexToBin(char *hexNum);

/*
    Converts octal string representation to positive two's complement.
*/
unsigned char *octToBin(char *octNum);

unsigned char *octToBinTest(char *octNum);

#endif