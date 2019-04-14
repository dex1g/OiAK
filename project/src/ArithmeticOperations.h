#ifndef ARITHMETICOPERATIONS_H_
#define ARITHMETICOPERATIONS_H_

#include "Parser.h"

/*
    Performs addition on numbers given in parameters and returns the result as new instance of TCNumber.
*/
TCNumber *add(TCNumber *addend1, TCNumber *addend2);

/*
    Performs substraction on numbers given in parameters and returns the result as new instance of TCNumber.
*/
TCNumber *subtract(TCNumber *minuend, TCNumber *subtrahend);

#endif
