#include <stdio.h>
#include <time.h>
#include "../src/ArithmeticOperations.h"
#include "../src/Parser.h"

void testAdditionAlgoAsm(unsigned char *addend1, unsigned char *addend2)
{
    array_adc(addend1, addend2, 1024 * 1024 * 1024 + 1);
}

void testAdditionAlgoC(unsigned char *addend1, unsigned char *addend2, unsigned char *result)
{
    unsigned int resultSize = 1024 * 1024 * 1024 + 1;
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
    unsigned char *addend1GB = getNumberFromBinaryFile("./data/addend1GB");
    unsigned char *addend2GB = getNumberFromBinaryFile("./data/addend2GB");
    unsigned char *addend1MB = getNumberFromBinaryFile("./data/addend1MB");
    unsigned char *addend2MB = getNumberFromBinaryFile("./data/addend2MB");

    TCNumber *addend1MBTC = createTCNumber(addend1MB, 1024 * 1024 * 100, 0);
    TCNumber *addend2MBTC = createTCNumber(addend2MB, 1024 * 1024 * 100, 0);

    // Test assembly addition on 1 GB numbers
    clock_t t = clock();
    testAdditionAlgoAsm(addend1GB, addend2GB);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array addition operation on 1GB numbers in assembly took %f seconds to execute \n", time_taken);

    // Test C addition on 1 GB numbers
    unsigned char *result = calloc(1024 * 1024 * 1024 + 1, sizeof(char));
    t = clock();
    testAdditionAlgoC(addend1GB, addend2GB, result);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Array addition operation on 1GB numbers in C took %f seconds to execute \n", time_taken);

    // Test whole addition function which uses assembly inside on 100 MB numbers
    t = clock();
    add_asm(addend1MBTC, addend2MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Addition operation in assembly on 100MB numbers took %f seconds to execute \n", time_taken);

    // Test whole addition function which uses assembly inside on 100 MB numbers
    t = clock();
    add(addend1MBTC, addend2MBTC);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Addition operation in C on 100MB numbers took %f seconds to execute \n", time_taken);
    return 0;
}
