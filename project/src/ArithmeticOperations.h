#ifndef ARITHMETICOPERATIONS_H_
#define ARITHMETICOPERATIONS_H_

#include <stdbool.h>
#include "Parser.h"

/*
    Performs substraction on numbers given in parameters and returns the result as new instance of TCNumber.
    Uses inside assembler implementation stored in array_subb.s
*/
TCNumber *subtract_asm(TCNumber *minuend, TCNumber *subtrahend);

/*

*/
TCNumber *add_asm(TCNumber *addend1, TCNumber *addend2);

/*
    Performs multiplication on numbers given in parameters and returns the result as new instance of TCNumber.
    Uses inside assembler implementation stored in array_mul.s
*/
TCNumber *multiply_asm(TCNumber *multiplicand, TCNumber *multiplier);

/*
    Performs multiplication on numbers given in parameters and returns the result as new instance of TCNumber.
    The division algorithm is based on multiple substraction of dividend.
*/
TCNumber *divide(TCNumber *dividend, TCNumber *divisor, unsigned precision);

/*
    Performs addition with carry on numbers given in parameters.
    The result is stored in the first parameter.
*/
void array_adc(unsigned char *addend1, unsigned char *addend2, unsigned int length, unsigned numberDifference);

/*
    Performs subtraction with carry on numbers given in parameters.
    The result is stored in the first parameter.
*/
void array_sbb(unsigned char *minuend, unsigned char *subtrahend, unsigned int length, unsigned numberDifference);

/*
    Performs multiplication using mul instruction from the processor instructions list.
*/
void array_mul(unsigned int multiplicandSize, unsigned char *multiplicand, unsigned char *multiplier, unsigned char *product, unsigned int additionalProductSize);

/*
    Shifts the given number by number of positions specified in amount field.
*/
void shift_left(TCNumber *num, unsigned amount);

/*
    Shifts the given array by one position to the left.
    Used in shift_left algorithm.
*/
void array_shift_left(unsigned char *array, unsigned size);

#endif
