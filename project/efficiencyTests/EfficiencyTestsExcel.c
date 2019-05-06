#include "EfficiencyTests.h"

int main()
{
    // prepare data
    TCNumber *firstNumber = getNumberFromBinaryFile(firstNumber100MBPath, 0);
    TCNumber *secondNumber = getNumberFromBinaryFile(secondNumber100MBPath, 0);

    clock_t t;         //stores the time before measurment
    double time_taken; // holds calculated value

    // Display header in file for current tests
    printf(";100MB NUMBERS; Optimalization flag O1\n");
    printf("add_pure_asm;add_pure_c;add_asm_scale;add_c_scale;sbb_pure_asm;sbb_c_scale;sbb_scale_asm\n");

    // Test pure asm algorithm for addition
    t = clock();
    testAdditionAlgoAsm(firstNumber->number, secondNumber->number, MB100);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("%f;", time_taken);

    // Test pure C algorithm for addition
    unsigned char *resultAdd = calloc(MB100, sizeof(char));
    t = clock();
    testAdditionAlgoC(firstNumber->number, secondNumber->number, resultAdd, MB100);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("%f;", time_taken);
    free(resultAdd);

    // Test whole addition with scalling with asm implementation inside
    t = clock();
    TCNumber *temp = add_asm(firstNumber, secondNumber);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("%f;", time_taken);
    delete (temp);

    // Recreate structures
    firstNumber = getNumberFromBinaryFile(firstNumber100MBPath, 0);
    secondNumber = getNumberFromBinaryFile(secondNumber100MBPath, 0);

    // Test addition with scaling which uses C implementation inside.
    t = clock();
    temp = add_C(firstNumber, secondNumber);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("%f;", time_taken);
    delete (temp);

    // Recreate structures
    firstNumber = getNumberFromBinaryFile(firstNumber100MBPath, 0);
    secondNumber = getNumberFromBinaryFile(secondNumber100MBPath, 0);

    // Test pure assembly algorithm for substraction
    t = clock();
    testSubstractionAlgoAsm(firstNumber->number, secondNumber->number, MB100);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("%f;", time_taken);

    // Test whole substraction in C
    t = clock();
    temp = subtract_C(firstNumber, secondNumber);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("%f;", time_taken);
    delete (temp);

    // Recreate structures
    firstNumber = getNumberFromBinaryFile(firstNumber100MBPath, 0);
    secondNumber = getNumberFromBinaryFile(secondNumber100MBPath, 0);

    // Test whole substraction which uses assembly inside
    t = clock();
    temp = subtract_asm(firstNumber, secondNumber);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("%f", time_taken);
    delete (temp);

    return 0;
}
