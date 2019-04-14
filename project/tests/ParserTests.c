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
    free(convertedValue);
    free(expectedResult);
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
    free(convertedValue);
    free(expectedResult);
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
    free(convertedValue);
    free(expectedResult);
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
    unsigned char number[6] = {0x0a, 0x2b, 0x6e, 0x00, 0x00, 0x00};
    unsigned int size = 6;
    int position = -4;
    unsigned char expectedNumber[3] = {0x0a, 0x2b, 0x6e};
    unsigned int expectedSize = 3;
    int expectedPosition = 20;
    TCNumber *expectedResult = createTCNumber(expectedNumber, expectedSize, expectedPosition);
    TCNumber *result = createTCNumber(number, size, position);
    scaleUp(result);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult->number, result->number, 3);
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
    delete (temp);
    delete (scaled);
}

void test_GetNumberFromFile(void)
{
    char filename[] = "FileWithNumber.txt";
    unsigned char expectedNumber[4] = {0x00, 0xFA, 0x47, 0xC9};
    unsigned int expectedSize = 4;
    int expectedPosition = 0;
    TCNumber *expectedResult = createTCNumber(expectedNumber, expectedSize, expectedPosition);
    TCNumber *convertedValue = getNumberFromFile(filename);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult->number, convertedValue->number, 4);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberSize, convertedValue->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedResult->numberPosition, convertedValue->numberPosition);
    free(convertedValue);
    free(expectedResult);
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
    RUN_TEST(test_GetNumberFromFile);
    return UNITY_END();
}
