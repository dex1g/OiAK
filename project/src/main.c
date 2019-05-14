#include <stdio.h>

#include "Parser.h"
#include "ArithmeticOperations.h"

int main()
{
    unsigned char firstNumber[3] = {0x12, 0x7e, 0x60};
    unsigned char secondNumber[4] = {0x5d, 0x0a, 0x2b, 0x6e};

    TCNumber *number1 = createTCNumber(firstNumber, 3, 8);
    TCNumber *number2 = createTCNumber(secondNumber, 4, -16);
    TCNumber *result = add_asm(number1, number2);
    delete (result);

    number1 = createTCNumber(firstNumber, 3, 8);
    number2 = createTCNumber(secondNumber, 4, -16);
    result = subtract_asm(number1, number2);
    delete (result);

    number1 = createTCNumber(firstNumber, 3, 8);
    number2 = createTCNumber(secondNumber, 4, -16);
    result = multiply_asm(number1, number2);
    delete (result);

    number1 = createTCNumber(firstNumber, 3, 8);
    number2 = createTCNumber(secondNumber, 4, -16);
    result = divide(number1, number2, 0);
    delete (result);

    return 0;
}
