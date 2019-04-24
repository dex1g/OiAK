#include <stdio.h>
#include <time.h>
#include "../src/ArithmeticOperations.h"
#include "../src/Parser.h"

void testAdditionAlgoAsm(unsigned char *addend1, unsigned char *addend2)
{
    array_adc(addend1, addend2, 1024 * 1024 * 500 + 1);
}

void testSubstractionAlgoAsm(unsigned char *minuend, unsigned char *subtrahend)
{
    array_sbb(minuend, subtrahend, 1024 * 1024 * 500 + 1);
}

void testAdditionAlgoC(unsigned char *addend1, unsigned char *addend2, unsigned char *result)
{
    unsigned int resultSize = 1024 * 1024 * 500 + 1;
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

    TCNumber *addend1MBTC = createTCNumber_no_realloc(firstNumber500MB, 1024 * 1024 * 500, 0);
    TCNumber *addend2MBTC = createTCNumber_no_realloc(secondNumber500MB, 1024 * 1024 * 500, 0);

    // Test assembly addition on 1 GB numbers
    clock_t t = clock();
    testAdditionAlgoAsm(firstNumber500MB, secondNumber500MB);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array addition operation on 500MB numbers in assembly took %f seconds to execute \n", time_taken);

    // Test C addition on 1 GB numbers
    unsigned char *resultAdd = calloc(1024 * 1024 * 500 + 1, sizeof(char));
    t = clock();
    testAdditionAlgoC(firstNumber500MB, secondNumber500MB, resultAdd);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array addition operation on 500MB numbers in C took %f seconds to execute \n", time_taken);
    free(resultAdd);

    // Test whole addition function which uses assembly inside on 500 MB numbers
    t = clock();
    TCNumber *temp = add_asm(addend1MBTC, addend2MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Addition operation in assembly on 500MB numbers took %f seconds to execute \n", time_taken);
    delete (temp);

    // Recreate files
    firstNumber500MB = getNumberFromBinaryFile("./data/firstNumber500MB");
    secondNumber500MB = getNumberFromBinaryFile("./data/secondNumber500MB");

    addend1MBTC = createTCNumber_no_realloc(firstNumber500MB, 1024 * 1024 * 500, 0);
    addend2MBTC = createTCNumber_no_realloc(secondNumber500MB, 1024 * 1024 * 500, 0);

    // Test whole addition function which uses C inside on 500 MB numbers
    t = clock();
    TCNumber *temp1 = add(addend1MBTC, addend2MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Addition operation in C on 500MB numbers took %f seconds to execute \n", time_taken);
    free(temp1);

    // Recreate files
    firstNumber500MB = getNumberFromBinaryFile("./data/firstNumber500MB");
    secondNumber500MB = getNumberFromBinaryFile("./data/secondNumber500MB");

    addend1MBTC = createTCNumber_no_realloc(firstNumber500MB, 1024 * 1024 * 500, 0);
    addend2MBTC = createTCNumber_no_realloc(secondNumber500MB, 1024 * 1024 * 500, 0);

    // Test assembly substraction on 1Gb numbers
    t = clock();
    testAdditionAlgoAsm(firstNumber500MB, secondNumber500MB);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array subtraction operation on 500MB numbers in assembly took %f seconds to execute \n", time_taken);

    // Test whole substraction in C on 1 GB numbers
    t = clock();
    subtract(addend1MBTC, addend2MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Subtraction operation on 500MB numbers in C took %f seconds to execute \n", time_taken);

    // Recreate files
    firstNumber500MB = getNumberFromBinaryFile("./data/firstNumber500MB");
    secondNumber500MB = getNumberFromBinaryFile("./data/secondNumber500MB");

    addend1MBTC = createTCNumber_no_realloc(firstNumber500MB, 1024 * 1024 * 500, 0);
    addend2MBTC = createTCNumber_no_realloc(secondNumber500MB, 1024 * 1024 * 500, 0);

    // Test whole substraction which uses assembly on 1 GB numbers
    t = clock();
    subtract_asm(addend1MBTC, addend2MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Subtraction operation in assembly on 500MB numbers took %f seconds to execute \n", time_taken);

    return 0;
}
