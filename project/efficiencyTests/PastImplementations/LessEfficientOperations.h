#ifndef LESSEFFICIENTOPERATIONS_H_
#define LESSEFFICIENTOPERATIONS_H_

#include "../src/Parser.h"

/*
    Performs addition on numbers given in parameters and returns the result as new instance of TCNumber.
    Uses inside the C implementation of add with carry. (Carry is not handled by processor)
    Parameters are deallocated during the process of addition. Inefficien implementation in C.
*/
TCNumber *add_C(TCNumber *addend1, TCNumber *addend2);

/*
    Performs substraction on numbers given in parameters and returns the result as new instance of TCNumber.
    Calculates the additive inverse of second number and then uses add function in C implementation.
    Usues many loops inside which affects the speed of the algorithm.
*/
TCNumber *subtract_C(TCNumber *minuend, TCNumber *subtrahend);

#endif
