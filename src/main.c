#include <stdio.h>
#include "Parser.h"
#include "ArithmeticOperations.h"

int main()
{
    unsigned char firstNumber[3] = {0x12, 0x7e, 0x60};
    unsigned char secondNumber[4] = {0x5d, 0x0a, 0x2b, 0x6e};

    TCNumber *number1 = createTCNumber(firstNumber, 3, 8);
    TCNumber *number2 = createTCNumber(secondNumber, 4, -16);

    char *asciiNumber1 = convertToString(number1);
    char *asciiNumber2 = convertToString(number2);

    printf("First number is %s\n", asciiNumber1);
    printf("Second number is %s\n", asciiNumber2);

    free(asciiNumber1);
    free(asciiNumber2);

    TCNumber *result = add(number1, number2);
    char *asciiResult = convertToString(result);
    printf("Sum of the numbers equals %s\n", asciiResult);

    delete (result);
    free(asciiResult);

    number1 = createTCNumber(firstNumber, 3, 8);
    number2 = createTCNumber(secondNumber, 4, -16);

    result = subtract(number1, number2);
    asciiResult = convertToString(result);
    printf("Difference of the numbers equals %s\n", asciiResult);

    delete (result);
    free(asciiResult);

    number1 = createTCNumber(firstNumber, 3, 8);
    number2 = createTCNumber(secondNumber, 4, -16);

    result = multiply(number1, number2);
    asciiResult = convertToString(result);
    printf("Product of the numbers equals %s\n", asciiResult);

    delete (result);
    free(asciiResult);

    number1 = createTCNumber(firstNumber, 3, 8);
    number2 = createTCNumber(secondNumber, 4, -16);

    result = divide(number1, number2, 0);
    asciiResult = convertToString(result);
    printf("Quotient of the numbers equals %s\n", asciiResult);

    delete (result);
    free(asciiResult);

    return 0;
}
