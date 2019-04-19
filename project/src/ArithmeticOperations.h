#ifndef ARITHMETICOPERATIONS_H_
#define ARITHMETICOPERATIONS_H_

#include "Parser.h"

/*
    Performs addition on numbers given in parameters and returns the result as new instance of TCNumber.
    Uses inside the C implementation of add with carry. (Carry is not handled by processor)
*/
TCNumber *add(TCNumber *addend1, TCNumber *addend2);

/*
    Performs addition on numbers given in parameters and returns the result as new instance of TCNumber.
    Uses inside the function specified in array_adc.s file
*/
TCNumber *add_asm(TCNumber *addend1, TCNumber *addend2);

/*
    Performs substraction on numbers given in parameters and returns the result as new instance of TCNumber.
    Calculates the additive inverse of second number and then usues add function in C implementation.
*/
TCNumber *subtract(TCNumber *minuend, TCNumber *subtrahend);

/*
    Performs substraction on numbers given in parameters and returns the result as new instance of TCNumber.
    Uses inside assembler implementation stored in array_subb.s
*/
TCNumber *subtract_asm(TCNumber *minuend, TCNumber *subtrahend);

/*
    Performs addition with carry on numbers given in parameters.
*/
extern void array_adc(unsigned char *addend1, unsigned char *addend2, int length);

/*
    Performs subtraction with carry on numbers given in parameters.
*/
extern void array_sbb(unsigned char *minuend, unsigned char *subtrahend, int length);

#endif
