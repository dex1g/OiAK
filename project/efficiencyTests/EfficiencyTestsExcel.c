#include "EfficiencyTests.h"

int main()
{
    // prepare data
    TCNumber *firstNumber = getNumberFromBinaryFile(firstNumber100MBPath, 0);
    TCNumber *secondNumber = getNumberFromBinaryFile(secondNumber100MBPath, 0);

    clock_t t;         //stores the time before measurment
    double time_taken; // holds calculated value

    // Display header in file for current tests
    printf(";100MB NUMBERS;1MBx1KB; Optimalization flag O0\n");
    printf("add_pure_asm;add_pure_c;add_asm_scale;add_c_scale;sbb_pure_asm;sbb_c_scale;sbb_scale_asm;mul_asm;divide\n");

    // Test pure asm algorithm for addition
    t = clock();
    for (int i = 0; i < numberOfTries; i++)
    {
        testAdditionAlgoAsm(firstNumber->number, secondNumber->number, MB100);
    }
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    time_taken /= numberOfTries;
    printf("%f;", time_taken);

    time_taken = 0;
    // Test pure C algorithm for addition
    unsigned char *resultAdd = calloc(MB100, sizeof(char));
    for (int i = 0; i < numberOfTries; i++)
    {
        t = clock();
        testAdditionAlgoC(firstNumber->number, secondNumber->number, resultAdd, MB100);
        t = clock() - t;
        time_taken += ((double)t) / CLOCKS_PER_SEC; // in seconds
    }
    time_taken /= numberOfTries;
    printf("%f;", time_taken);
    free(resultAdd);

    time_taken = 0;
    TCNumber *temp = NULL;
    // Test whole addition with scalling with asm implementation inside
    for (int i = 0; i < numberOfTries; i++)
    {
        t = clock();
        temp = add_asm(firstNumber, secondNumber);
        t = clock() - t;
        time_taken += ((double)t) / CLOCKS_PER_SEC; // in seconds
        delete (temp);
        firstNumber = getNumberFromBinaryFile(firstNumber100MBPath, 0);
        secondNumber = getNumberFromBinaryFile(secondNumber100MBPath, 0);
    }
    time_taken /= numberOfTries;
    printf("%f;", time_taken);

    time_taken = 0;
    temp = NULL;
    // Test addition with scaling which uses C implementation inside.
    for (int i = 0; i < numberOfTries; i++)
    {
        t = clock();
        temp = add_C(firstNumber, secondNumber);
        t = clock() - t;
        time_taken += ((double)t) / CLOCKS_PER_SEC; // in seconds
        delete (temp);
        firstNumber = getNumberFromBinaryFile(firstNumber100MBPath, 0);
        secondNumber = getNumberFromBinaryFile(secondNumber100MBPath, 0);
    }
    time_taken /= numberOfTries;
    printf("%f;", time_taken);

    time_taken = 0;
    // Test pure assembly algorithm for substraction
    for (int i = 0; i < numberOfTries; i++)
    {
        t = clock();
        testSubstractionAlgoAsm(firstNumber->number, secondNumber->number, MB100);
        t = clock() - t;
        time_taken += ((double)t) / CLOCKS_PER_SEC; // in seconds
    }
    time_taken /= numberOfTries;
    printf("%f;", time_taken);

    time_taken = 0;
    // Test whole substraction in C
    for (int i = 0; i < numberOfTries; i++)
    {
        t = clock();
        temp = subtract_C(firstNumber, secondNumber);
        t = clock() - t;
        time_taken += ((double)t) / CLOCKS_PER_SEC; // in seconds
        delete (temp);
        firstNumber = getNumberFromBinaryFile(firstNumber100MBPath, 0);
        secondNumber = getNumberFromBinaryFile(secondNumber100MBPath, 0);
    }
    time_taken /= numberOfTries;
    printf("%f;", time_taken);

    time_taken = 0;
    // Test whole substraction which uses assembly inside
    for (int i = 0; i < numberOfTries; i++)
    {
        t = clock();
        temp = subtract_asm(firstNumber, secondNumber);
        t = clock() - t;
        time_taken += ((double)t) / CLOCKS_PER_SEC; // in seconds
        delete (temp);
        firstNumber = getNumberFromBinaryFile(firstNumber100MBPath, 0);
        secondNumber = getNumberFromBinaryFile(secondNumber100MBPath, 0);
    }
    time_taken /= numberOfTries;
    printf("%f;", time_taken);
    delete (firstNumber);
    delete (secondNumber);

    // Recreate structures
    firstNumber = getNumberFromBinaryFile(firstNumber1KBPath, 0);
    secondNumber = getNumberFromBinaryFile(firstNumber1MBPath, 0);

    time_taken = 0;
    // Test multiplication which uses assembly inside
    for (int i = 0; i < numberOfTries; i++)
    {
        t = clock();
        temp = multiply_asm(secondNumber, firstNumber);
        t = clock() - t;
        time_taken += ((double)t) / CLOCKS_PER_SEC; // in seconds
        delete (temp);
        firstNumber = getNumberFromBinaryFile(firstNumber1KBPath, 0);
        secondNumber = getNumberFromBinaryFile(firstNumber1MBPath, 0);
    }
    time_taken /= numberOfTries;
    printf("%f;", time_taken);

    // Test division implemented in c
    for (int i = 0; i < numberOfTries; i++)
    {
        t = clock();
        temp = divide(secondNumber, firstNumber, 0);
        t = clock() - t;
        time_taken += ((double)t) / CLOCKS_PER_SEC; // in seconds
        delete (temp);
        firstNumber = getNumberFromBinaryFile(firstNumber1KBPath, 0);
        secondNumber = getNumberFromBinaryFile(firstNumber1MBPath, 0);
    }
    time_taken /= numberOfTries;
    printf("%f", time_taken);
    delete (firstNumber);
    delete (secondNumber);

    return 0;
}
