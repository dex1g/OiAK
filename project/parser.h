#ifndef PARSER_H_
#define PARSER_H_

extern const char binaryToHexSymbols[19][5];
extern const char hexSymbols[];

extern const char binaryToOctSymbols[11][5];
extern const char octSymbols[];

/*
    Gets user input from console and performs basic conversionts between systems with different base.
*/
char *getNumberFromConsole();

/*
    Converts a string containing a binary number in standrd binary system into two's complement.

    This function operates on strings so the most convinient method to calculate two's complement is to traverse the
    given binaryNumber from end until the first occurance of 1 is present which is not traversed and from that point filp all bits (negate them) until 
    the beginning of the string.

    * Function also handles the case when not a single 1 is present in given number.
      In this case append 1 at the beginning of the string.
*/
char *convertBinaryToTwosComplement(char *binaryNumber);

/*
    Converts hexadecimal string representation to binary representation.
*/
char *convertHexadecimalToBinary(char *hexadecimalNumber);

/*
    Converts octal string representation to binary representation.
*/
char *convertOctalToBinary(char *octalNumber);


char *hexToBin(char *hexNum);
#endif