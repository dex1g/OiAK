#include "EfficiencyTests.h"

int main()
{
    // prepare data
    TCNumber *firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    TCNumber *secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);

    clock_t t;         //stores the time before measurment
    double time_taken; // holds calculated value

    // Test pure asm algorithm for addition
    t = clock();
    testAdditionAlgoAsm(firstNumber->number, secondNumber->number, GB);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array addition operation on 1GB numbers in assembly took %f seconds to execute \n", time_taken);

    // Test pure C algorithm for addition
    t = clock();
    unsigned char *resultAdd = calloc(GB, sizeof(char));
    testAdditionAlgoC(firstNumber->number, secondNumber->number, resultAdd, GB);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array addition operation on 1GB numbers in C took %f seconds to execute \n", time_taken);

    free(resultAdd);
    delete (firstNumber);
    delete (secondNumber);

    firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);

    // Test whole addition with scalling with asm implementation inside
    t = clock();
    TCNumber *temp = add_asm(firstNumber, secondNumber);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Addition operation on 1GB numbers with assembly implementation took %f seconds to execute \n", time_taken);
    delete (temp);

    // Recreate structures
    firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);

    // Test addition with scaling which uses C implementation inside.
    t = clock();
    temp = add_C(firstNumber, secondNumber);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Addition operation on 1GB numbers with C implementation took %f seconds to execute \n", time_taken);
    delete (temp);

    // Recreate structures
    firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);

    // Test pure assembly algorithm for substraction
    t = clock();
    testSubstractionAlgoAsm(firstNumber->number, secondNumber->number, GB);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array subtraction operation on 1GB numbers in assembly took %f seconds to execute \n", time_taken);

    // Test whole substraction in C
    t = clock();
    temp = subtract_C(firstNumber, secondNumber);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Subtraction operation on 1GB numbers in C took %f seconds to execute \n", time_taken);
    delete (temp);

    // Recreate structures
    firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);

    // Test whole substraction which uses assembly inside
    t = clock();
    temp = subtract_asm(firstNumber, secondNumber);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Subtraction operation on 1GB numbers with assembly implementation took %f seconds to execute \n", time_taken);
    delete (temp);

    // Files for multiplication
    TCNumber *firstNumber1MB = getNumberFromBinaryFile(firstNumber1MBPath, 0);
    TCNumber *firstNumber20KB = getNumberFromBinaryFile(firstNumber20KBPath, 0);

    // Test multiplication algorithm
    t = clock();
    TCNumber *result1 = multiply_asm(firstNumber1MB, firstNumber20KB);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Multiplication operation on 1MB number with 20KB number with assembly implementation took %f seconds to execute \n", time_taken);
    delete (result1);

    // Files for division
    firstNumber = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    secondNumber = getNumberFromBinaryFile(secondNumber1GBPath, 0);

    // Test division algorithm
    t = clock();
    result1 = divide(firstNumber, secondNumber, 0);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Division operation on 1GB number by 1GB number took %f seconds to execute \n", time_taken);
    delete (result1);

    return 0;
}
