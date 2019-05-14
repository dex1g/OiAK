#ifndef LESSEFFICIENTOPERATIONS_H_
#define LESSEFFICIENTOPERATIONS_H_

#include "../../src/Parser.h"
#include "../../src/ArithmeticOperations.h"

/*
    Performs addition on numbers given in parameters and returns the result as new instance of TCNumber.
    Uses inside the C implementation of add with carry. (Carry is not handled by processor)
    Parameters are deallocated during the process of addition. 
    Inefficien implementation in C.
*/
TCNumber *add_C(TCNumber *addend1, TCNumber *addend2);

/*
    Performs substraction on numbers given in parameters and returns the result as new instance of TCNumber.
    Calculates the additive inverse of second number and then uses add_C function with C implementation.
    Uses many loops inside which affects the speed of the algorithm.
    Inefficien implementation in C.
*/
TCNumber *subtract_C(TCNumber *minuend, TCNumber *subtrahend);

/*
    Performs addition on numbers given in parameters and returns the result as new instance of TCNumber.
    Uses inside the function specified in array_adc.s file.
    Function is inefficient because scales both numbers to same size. 
    Reallocates both parameters which affects performance.
*/
TCNumber *add_asm_realloc(TCNumber *addend1, TCNumber *addend2);

/*
    Performs subtraction on numbers given in parameters and returns the result as new instance of TCNumber.
    Uses inside the function specified in array_sbb.s file.
    Function is inefficient because scales both numbers to same size.
    Reallocates both parameters which affects performance.
*/
TCNumber *subtract_asm_realloc(TCNumber *minuend, TCNumber *subtrahend);
#endif
