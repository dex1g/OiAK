#include "./unity/src/unity.h"
#include "../src/Parser.h"

void test_hextToBinConversion(void)
{
    char numberToConvert[] = "f";
    unsigned char expectedResult[1] = {0x0f};
    TCNumber *convertedValue = hexToBin(numberToConvert);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, convertedValue->number, 1);
    delete (convertedValue);
}

void test_hextToBinConversion_even_digit_number(void)
{
    char numberToConvert[] = "f0A0";
    unsigned char expectedResult[3] = {0x00, 0xf0, 0xa0};
    TCNumber *convertedValue = hexToBin(numberToConvert);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, convertedValue->number, 3);
    delete (convertedValue);
}

void test_hextToBinConversion_odd_digit_number(void)
{
    char numberToConvert[] = "A5b";
    unsigned char expectedResult[2] = {0x0a, 0x5b};
    TCNumber *convertedValue = hexToBin(numberToConvert);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, convertedValue->number, 2);
    delete (convertedValue);
}

void test_convertFromHex(void)
{
    char numberToConvert[] = "FA47C9";
    unsigned char expectedNumber[4] = {0x00, 0xFA, 0x47, 0xC9};
    unsigned int expectedSize = 4;
    int expectedPosition = 0;
    TCNumber *expectedResult = createTCNumber(expectedNumber, expectedSize, expectedPosition);
    TCNumber *convertedValue = convertFromHex(numberToConvert);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult->number, convertedValue->number, 4);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberSize, convertedValue->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberPosition, convertedValue->numberPosition);
    delete (convertedValue);
    delete (expectedResult);
}

void test_convertFromHex_period(void)
{
    char numberToConvert[] = "FA47,C9";
    unsigned char expectedNumber[4] = {0x00, 0xFA, 0x47, 0xC9};
    unsigned int expectedSize = 4;
    int expectedPosition = -2 * 4;
    TCNumber *expectedResult = createTCNumber(expectedNumber, expectedSize, expectedPosition);
    TCNumber *convertedValue = convertFromHex(numberToConvert);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult->number, convertedValue->number, 4);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberSize, convertedValue->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberPosition, convertedValue->numberPosition);
    delete (convertedValue);
    delete (expectedResult);
}

void test_convertFromHex_negative(void)
{
    char numberToConvert[] = "-FA47,C9";
    unsigned char expectedNumber[4] = {0xFF, 0x05, 0xB8, 0x37};
    unsigned int expectedSize = 4;
    int expectedPosition = -2 * 4;
    TCNumber *expectedResult = createTCNumber(expectedNumber, expectedSize, expectedPosition);
    TCNumber *convertedValue = convertFromHex(numberToConvert);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult->number, convertedValue->number, 4);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberSize, convertedValue->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberPosition, convertedValue->numberPosition);
    delete (convertedValue);
    delete (expectedResult);
}

void test_asciiToByteConversion_digit(void)
{
    unsigned char expectedResult = 5;
    unsigned char convertedValue = asciiToByte('5');
    TEST_ASSERT_BITS(255, expectedResult, convertedValue);
}

void test_asciiToByteConversion_small_letter(void)
{
    unsigned char expectedResult = 10;
    unsigned char convertedValue = asciiToByte('a');
    TEST_ASSERT_BITS(255, expectedResult, convertedValue);
}

void test_asciiToByteConversion_big_letter(void)
{
    unsigned char expectedResult = 10;
    unsigned char convertedValue = asciiToByte('A');
    TEST_ASSERT_BITS(255, expectedResult, convertedValue);
}

void test_asciiToByteConversion_wrong_character(void)
{
    unsigned char expectedResult = 0;
    unsigned char convertedValue = asciiToByte('-');
    TEST_ASSERT_BITS(255, expectedResult, convertedValue);
}

void test_scaleUp(void)
{
    unsigned char number[] = {0x00, 0x0a, 0x61, 0x66, 0xef, 0x67, 0x40, 0x00, 0x00};
    unsigned int size = 9;
    int position = -48;
    unsigned char expectedNumber[] = {0x00, 0x0a, 0x61, 0x66, 0xef, 0x67, 0x40};
    unsigned int expectedSize = 7;
    int expectedPosition = -32;
    TCNumber *expectedResult = createTCNumber(expectedNumber, expectedSize, expectedPosition);
    TCNumber *numToScale = createTCNumber(number, size, position);
    TCNumber *result = scaleUp(numToScale);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult->number, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberPosition, result->numberPosition);
    delete (result);
    delete (expectedResult);
}

void test_trimExt(void)
{
    unsigned char number[6] = {0x00, 0x00, 0x00, 0x0a, 0x2b, 0x6e};
    unsigned char expectedNumber[3] = {0x0a, 0x2b, 0x6e};
    TCNumber *expectedResult = createTCNumber(expectedNumber, 3, 0);
    TCNumber *result = createTCNumber(number, 6, 0);
    trimExtension(result);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult->number, result->number, 3);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberPosition, result->numberPosition);
    delete (result);
    delete (expectedResult);
}

void test_trimExt_negative(void)
{
    unsigned char number[6] = {0xff, 0xff, 0xff, 0x0a, 0x2b, 0x6e};
    unsigned char expectedNumber[4] = {0xff, 0x0a, 0x2b, 0x6e};
    TCNumber *expectedResult = createTCNumber(expectedNumber, 4, 0);
    TCNumber *result = createTCNumber(number, 6, 0);
    trimExtension(result);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult->number, result->number, 4);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberPosition, result->numberPosition);
    delete (result);
    delete (expectedResult);
}

void test_trimExt_minus_one(void)
{
    unsigned char number[2] = {0xff, 0xff};
    unsigned char expectedNumber[1] = {0xff};
    TCNumber *expectedResult = createTCNumber(expectedNumber, 1, 0);
    TCNumber *result = createTCNumber(number, 2, 0);
    trimExtension(result);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult->number, result->number, 1);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberPosition, result->numberPosition);
    delete (result);
    delete (expectedResult);
}

void test_trimExt_zero(void)
{
    unsigned char number[1] = {0x00};
    unsigned char expectedNumber[1] = {0x00};
    TCNumber *expectedResult = createTCNumber(expectedNumber, 1, 0);
    TCNumber *result = createTCNumber(number, 1, 0);
    trimExtension(result);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult->number, result->number, 1);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberPosition, result->numberPosition);
    delete (result);
    delete (expectedResult);
}

void test_trimExt_zero_long(void)
{
    unsigned char number[3] = {0x00, 0x00, 0x00};
    unsigned char expectedNumber[1] = {0x00};
    TCNumber *expectedResult = createTCNumber(expectedNumber, 1, 0);
    TCNumber *result = createTCNumber(number, 3, 0);
    trimExtension(result);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult->number, result->number, 1);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberPosition, result->numberPosition);
    delete (result);
    delete (expectedResult);
}

void test_scaleNumber(void)
{
    unsigned char number[4] = {0xff, 0x0a, 0x2b, 0x6e};
    TCNumber *temp = createTCNumber(number, 4, 16);
    unsigned char expectedResult[10] = {0xff, 0xff, 0xff, 0x0a, 0x2b, 0x6e, 0x00, 0x00, 0x00, 0x00};
    unsigned int expectedSize = 10;
    int expectedPosition = -16;
    TCNumber *scaled = scaleNumber(temp, 10, -16);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, scaled->number, 10);
    TEST_ASSERT_EQUAL_INT(expectedSize, scaled->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, scaled->numberPosition);
    delete (scaled);
}

void test_getHexNumberFromTxtFile(void)
{
    char filename[] = "FileWithNumber.txt";
    unsigned char expectedNumber[4] = {0x00, 0xFA, 0x47, 0xC9};
    unsigned int expectedSize = 4;
    int expectedPosition = 0;
    TCNumber *expectedResult = createTCNumber(expectedNumber, expectedSize, expectedPosition);
    TCNumber *convertedValue = getHexNumberFromTxtFile(filename);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult->number, convertedValue->number, 4);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberSize, convertedValue->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberPosition, convertedValue->numberPosition);
    free(convertedValue);
    free(expectedResult);
}

void test_convertToString(void)
{
    char expectedResult[] = "24FA47C9";
    unsigned char array[4] = {0x24, 0xFA, 0x47, 0xC9};
    unsigned int size = 4;
    int position = 0;
    TCNumber *number = createTCNumber(array, size, position);
    char *convertedNum = convertToString(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, convertedNum);
    free(convertedNum);
    delete (number);
}

void test_convertToString_pospos(void)
{
    char expectedResult[] = "24FA47C90000";
    unsigned char array[4] = {0x24, 0xFA, 0x47, 0xC9};
    unsigned int size = 4;
    int position = 16;
    TCNumber *number = createTCNumber(array, size, position);
    char *convertedNum = convertToString(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, convertedNum);
    free(convertedNum);
    delete (number);
}

void test_convertToString_negpos(void)
{
    char expectedResult[] = "24FA,47C9";
    unsigned char array[4] = {0x24, 0xFA, 0x47, 0xC9};
    unsigned int size = 4;
    int position = -16;
    TCNumber *number = createTCNumber(array, size, position);
    char *convertedNum = convertToString(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, convertedNum);
    free(convertedNum);
    delete (number);
}

void test_convertToString_verynegpos(void)
{
    char expectedResult[] = "0,0024FA47C9";
    unsigned char array[4] = {0x24, 0xFA, 0x47, 0xC9};
    unsigned int size = 4;
    int position = -40;
    TCNumber *number = createTCNumber(array, size, position);
    char *convertedNum = convertToString(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, convertedNum);
    free(convertedNum);
    delete (number);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_hextToBinConversion);
    RUN_TEST(test_asciiToByteConversion_digit);
    RUN_TEST(test_asciiToByteConversion_small_letter);
    RUN_TEST(test_asciiToByteConversion_big_letter);
    RUN_TEST(test_asciiToByteConversion_wrong_character);
    RUN_TEST(test_hextToBinConversion_even_digit_number);
    RUN_TEST(test_hextToBinConversion_odd_digit_number);
    RUN_TEST(test_convertFromHex);
    RUN_TEST(test_convertFromHex_period);
    RUN_TEST(test_convertFromHex_negative);
    RUN_TEST(test_scaleUp);
    RUN_TEST(test_trimExt);
    RUN_TEST(test_trimExt_negative);
    RUN_TEST(test_trimExt_minus_one);
    RUN_TEST(test_trimExt_zero);
    RUN_TEST(test_trimExt_zero_long);
    RUN_TEST(test_scaleNumber);
    RUN_TEST(test_getHexNumberFromTxtFile);
    RUN_TEST(test_convertToString);
    RUN_TEST(test_convertToString_pospos);
    RUN_TEST(test_convertToString_negpos);
    RUN_TEST(test_convertToString_verynegpos);
    return UNITY_END();
}
