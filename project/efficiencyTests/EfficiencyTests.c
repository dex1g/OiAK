#include <stdio.h>
#include <time.h>
#include "../src/ArithmeticOperations.h"
#include "../src/Parser.h"
#include "./PastImplementations/LessEfficientOperations.h"

#define GB 1073741824
#define MB 524288000

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

int main()
{
    // prepare data
    //unsigned char *firstNumber1GB = getNumberFromBinaryFile("./data/firstNumber1GB");
    //unsigned char *secondNumber1GB = getNumberFromBinaryFile("./data/secondNumber1GB");
    unsigned char *firstNumber500MB = getNumberFromBinaryFile("./data/firstNumber500MB");
    unsigned char *secondNumber500MB = getNumberFromBinaryFile("./data/secondNumber500MB");

    TCNumber *addend1MBTC = createTCNumber_no_realloc(firstNumber500MB, MB, 0);
    TCNumber *addend2MBTC = createTCNumber_no_realloc(secondNumber500MB, MB, 0);

    clock_t t;         //stores the time before measurment
    double time_taken; // holds calculated value

    // Test pure asm algorithm for addition
    t = clock();
    testAdditionAlgoAsm(firstNumber500MB, secondNumber500MB, MB);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array addition operation on 500MB numbers in assembly took %f seconds to execute \n", time_taken);

    // Test pure C algorithm for addition
    unsigned char *resultAdd = calloc(MB, sizeof(char));
    t = clock();
    testAdditionAlgoC(firstNumber500MB, secondNumber500MB, resultAdd, MB);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array addition operation on 500MB numbers in C took %f seconds to execute \n", time_taken);
    free(resultAdd);

    // Test addition with scaling which uses asm inside.

    t = clock();
    TCNumber *temp = add_asm(addend1MBTC, addend2MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Addition operation on 500MB numbers with assembly implementation took %f seconds to execute \n", time_taken);
    free(temp);

    // Recreate structures
    firstNumber500MB = getNumberFromBinaryFile("./data/firstNumber500MB");
    secondNumber500MB = getNumberFromBinaryFile("./data/secondNumber500MB");
    addend1MBTC = createTCNumber_no_realloc(firstNumber500MB, MB, 0);
    addend2MBTC = createTCNumber_no_realloc(secondNumber500MB, MB, 0);

    // Test addition with scaling which uses C implementation inside.
    t = clock();
    temp = add_C(addend1MBTC, addend2MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Addition operation on 500MB numbers with C implementation took %f seconds to execute \n", time_taken);
    free(temp);

    // Recreate structures
    firstNumber500MB = getNumberFromBinaryFile("./data/firstNumber500MB");
    secondNumber500MB = getNumberFromBinaryFile("./data/secondNumber500MB");
    addend1MBTC = createTCNumber_no_realloc(firstNumber500MB, MB, 0);
    addend2MBTC = createTCNumber_no_realloc(secondNumber500MB, MB, 0);

    // Test pure assembly algorithm for substraction
    t = clock();
    testSubstractionAlgoAsm(firstNumber500MB, secondNumber500MB, MB);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array subtraction operation on 500MB numbers in assembly took %f seconds to execute \n", time_taken);

    // Test whole substraction in C
    t = clock();
    subtract_C(addend1MBTC, addend2MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Subtraction operation on 500MB numbers in C took %f seconds to execute \n", time_taken);

    // Recreate files
    firstNumber500MB = getNumberFromBinaryFile("./data/firstNumber500MB");
    secondNumber500MB = getNumberFromBinaryFile("./data/secondNumber500MB");

    addend1MBTC = createTCNumber_no_realloc(firstNumber500MB, MB, 0);
    addend2MBTC = createTCNumber_no_realloc(secondNumber500MB, MB, 0);

    // Test whole substraction which uses assembly inside
    t = clock();
    subtract_asm(addend1MBTC, addend2MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Subtraction operation on 500MB numbers with assembly implementation took %f seconds to execute \n", time_taken);

    return 0;
}
