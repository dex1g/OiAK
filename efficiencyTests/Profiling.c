#include "EfficiencyTests.h"

/*
    File is used only for profiling purposes.
    Performs all four operations on big numbers.
    Uses data stored in data folder.
*/
int main()
{
    TCNumber *firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    TCNumber *secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);
    TCNumber *result;

    // Run add operation
    result = add(firstNumber, secondNumber);
    delete (result);

    // Recreate structures
    firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);

    // Run subtraction operation
    result = subtract(firstNumber, secondNumber);
    delete (result);

    // Files for multiplication
    firstNumber = getNumberFromBinaryFile(firstNumber1MBPath, 0);
    secondNumber = getNumberFromBinaryFile(firstNumber20KBPath, 0);

    // Test multiplication algorithm
    result = multiply(firstNumber, secondNumber);
    delete (result);

    // Files for division
    firstNumber = getNumberFromBinaryFile(secondNumber50KBPath, 0);
    secondNumber = getNumberFromBinaryFile(firstNumber20KBPath, 0);

    result = divide(firstNumber, secondNumber, 0);
    delete (result);

    return 0;
}
