#include <stdio.h>
#include <time.h>
#include "../src/ArithmeticOperations.h"
#include "../src/Parser.h"
#include "./PastImplementations/LessEfficientOperations.h"

#define MB 524288000
#define GB 1073741824
#define firstNumber500MBPath "./data/firstNumber500MB"
#define secondNumber500MBPath "./data/secondNumber500MB"
#define firstNumber1GBPath "./data/firstNumber1GB"
#define secondNumber1GBPath "./data/secondNumber1GB"

void testAdditionAlgoAsm(unsigned char *addend1, unsigned char *addend2, unsigned int length)
{
    array_adc(addend1, addend2, length, 0);
}

void testSubstractionAlgoAsm(unsigned char *minuend, unsigned char *subtrahend, unsigned int length)
{
    array_sbb(minuend, subtrahend, length, 0);
}

void testAdditionAlgoC(unsigned char *addend1, unsigned char *addend2, unsigned char *result, unsigned int resultSize)
{
    unsigned char carry = 0;
    for (int i = resultSize - 1; i >= 0; i--)
    {
        result[i] = addend1[i] + addend2[i] + carry;
        if (result[i] < addend1[i] + carry)
            carry = 1;
        else
            carry = 0;
    }
}

/*
Function was used to output the result of operation into a file in order to check
with diff command if the result was calculated correctly.
*/
void writeToFile(char *filename, unsigned char *array, int size)
{
    FILE *write_ptr;

    write_ptr = fopen(filename, "wb");

    fwrite(array, size, 1, write_ptr);
}

int main()
{
    // prepare data
    TCNumber *firstNumber500MBTC = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    TCNumber *secondNumber500MBTC = getNumberFromBinaryFile(secondNumber1GBPath, 0);

    clock_t t;         //stores the time before measurment
    double time_taken; // holds calculated value

    // Test pure asm algorithm for addition
    t = clock();
    testAdditionAlgoAsm(firstNumber500MBTC->number, secondNumber500MBTC->number, GB);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array addition operation on 500MB numbers in assembly took %f seconds to execute \n", time_taken);

    // Test pure C algorithm for addition
    unsigned char *resultAdd = calloc(GB, sizeof(char));
    t = clock();
    testAdditionAlgoC(firstNumber500MBTC->number, secondNumber500MBTC->number, resultAdd, GB);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array addition operation on 500MB numbers in C took %f seconds to execute \n", time_taken);
    free(resultAdd);

    t = clock();
    TCNumber *temp = add_asm(firstNumber500MBTC, secondNumber500MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Addition operation on 500MB numbers with assembly implementation took %f seconds to execute \n", time_taken);
    delete (temp);

    // Recreate structures
    firstNumber500MBTC = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    secondNumber500MBTC = getNumberFromBinaryFile(secondNumber1GBPath, 0);

    // Test addition with scaling which uses C implementation inside.
    t = clock();
    temp = add_C(firstNumber500MBTC, secondNumber500MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Addition operation on 500MB numbers with C implementation took %f seconds to execute \n", time_taken);
    delete (temp);

    // Recreate structures
    firstNumber500MBTC = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    secondNumber500MBTC = getNumberFromBinaryFile(secondNumber1GBPath, 0);

    // Test pure assembly algorithm for substraction
    t = clock();
    testSubstractionAlgoAsm(firstNumber500MBTC->number, secondNumber500MBTC->number, GB);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array subtraction operation on 500MB numbers in assembly took %f seconds to execute \n", time_taken);

    // Test whole substraction in C
    t = clock();
    temp = subtract_C(firstNumber500MBTC, secondNumber500MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Subtraction operation on 500MB numbers in C took %f seconds to execute \n", time_taken);
    delete (temp);

    // Recreate structures
    firstNumber500MBTC = getNumberFromBinaryFile(firstNumber1GBPath, 0);
    secondNumber500MBTC = getNumberFromBinaryFile(secondNumber1GBPath, 0);

    // Test whole substraction which uses assembly inside
    t = clock();
    temp = subtract_asm(firstNumber500MBTC, secondNumber500MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Subtraction operation on 500MB numbers with assembly implementation took %f seconds to execute \n", time_taken);
    delete (temp);

    // Files for multiplication
    TCNumber *firstNumber1MB = getNumberFromBinaryFile("./data/firstNumber1MB", 0);
    TCNumber *firstNumber20KB = getNumberFromBinaryFile("./data/firstNumber20KB", 0);

    t = clock();
    TCNumber *result1 = multiply_asm(firstNumber1MB, firstNumber20KB);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Multiplication operation on 1MB number with 20KB number with assembly implementation took %f seconds to execute \n", time_taken);
    delete (result1);
    return 0;
}
