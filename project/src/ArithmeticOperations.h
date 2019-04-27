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

*/
TCNumber *add_asm_no_realloc(TCNumber *addend1, TCNumber *addend2);

/*
    Performs multiplication on numbers given in parameters and returns the result as new instance of TCNumber.
    Uses inside assembler implementation stored in array_mul.s
*/
// TCNumber *multiply_asm(TCNumber *multiplicand, TCNumber *multiplier);

/*
    Performs addition with carry on numbers given in parameters.
    The result is stored in the first parameter.
*/
extern void array_adc(unsigned char *addend1, unsigned char *addend2, unsigned int length);

/*
    Performs subtraction with carry on numbers given in parameters.
    The result is stored in the first parameter.
*/
extern void array_sbb(unsigned char *minuend, unsigned char *subtrahend, unsigned int length);

/*
    Performs multiplication using mul instruction from the processor instructions list.
*/
extern void array_mul(unsigned int multiplicandSize, unsigned char *multiplicand, unsigned int multiplierSize, unsigned char *multiplier, unsigned char *product);

#endif
