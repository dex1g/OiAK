#include "EfficiencyTests.h"

int main()
{
    // prepare data
    TCNumber *firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    TCNumber *secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);

    clock_t t;         //stores the time before measurment
    double time_taken; // holds calculated value

    // Display header in file for current tests
    printf("\n;1GB NUMBERS;20KBx1MB; Optimalization flag O3\n");
    printf("add_pure_asm;add_pure_c;add_asm_scale;add_c_scale;sbb_pure_asm;sbb_c_scale;sbb_scale_asm;mul_asm;divide\n");

    // Test pure asm algorithm for addition
    t = clock();
    for (int i = 0; i < numberOfTries; i++)
    {
        testAdditionAlgoAsm(firstNumber->number, secondNumber->number, GB);
    }
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    time_taken /= numberOfTries;
    printf("%f;", time_taken);

    time_taken = 0;
    // Test pure C algorithm for addition
    //unsigned char *resultAdd = calloc(MB750, sizeof(char));
    for (int i = 0; i < numberOfTries; i++)
    {
        t = clock();
        testAdditionAlgoC(firstNumber->number, secondNumber->number, firstNumber->number, GB);
        t = clock() - t;
        time_taken += ((double)t) / CLOCKS_PER_SEC; // in seconds
    }
    time_taken /= numberOfTries;
    printf("%f;", time_taken);
    //free(resultAdd);

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
        firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
        secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);
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
        firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
        secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);
    }
    time_taken /= numberOfTries;
    printf("%f;", time_taken);

    time_taken = 0;
    // Test pure assembly algorithm for substraction
    t = clock();
    for (int i = 0; i < numberOfTries; i++)
    {

        testSubstractionAlgoAsm(firstNumber->number, secondNumber->number, GB);
    }
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
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
        firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
        secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);
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
        firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
        secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);
    }
    time_taken /= numberOfTries;
    printf("%f;", time_taken);
    delete (firstNumber);
    delete (secondNumber);

    // Recreate structures
    firstNumber = getNumberFromBinaryFile(firstNumber20KBPath, 0);
    secondNumber = getNumberFromBinaryFile(firstNumber1MBPath, 0);

    time_taken = 0;
    // Test multiplication which uses assembly inside
    for (int i = 0; i < numberOfTries - 90; i++)
    {
        t = clock();
        temp = multiply_asm(firstNumber, secondNumber);
        t = clock() - t;
        time_taken += ((double)t) / CLOCKS_PER_SEC; // in seconds
        delete (temp);
        firstNumber = getNumberFromBinaryFile(firstNumber20KBPath, 0);
        secondNumber = getNumberFromBinaryFile(firstNumber1MBPath, 0);
    }
    time_taken /= numberOfTries - 90;
    printf("%f;", time_taken);
    delete (firstNumber);
    delete (secondNumber);

    firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);

    // Test division implemented in c
    for (int i = 0; i < numberOfTries - 90; i++)
    {
        t = clock();
        temp = divide(firstNumber, secondNumber, 0);
        t = clock() - t;
        time_taken += ((double)t) / CLOCKS_PER_SEC; // in seconds
        delete (temp);
        firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
        secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);
    }
    time_taken /= numberOfTries - 90;
    printf("%f", time_taken);
    delete (firstNumber);
    delete (secondNumber);

    return 0;
}
