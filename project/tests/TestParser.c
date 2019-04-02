#include "./unity/src/unity.h"
#include "../src/parser.h"
#include <stdlib.h>

void test_hextToBinConversion(void)
{
    char *numberToConvert = "f";
    unsigned char expectedResult[2] = {0x0000, 0x00f0};
    unsigned char *convertedValue = hexToBin(numberToConvert);
    TEST_ASSERT_EQUAL_STRING(expectedResult, convertedValue);
    free(convertedValue);
}

void test_hextToBinConversion_even_digit_number(void)
{
    char *numberToConvert = "f0A0";
    unsigned char expectedResult[3] = {0x00, 0xf0, 0xa0};
    unsigned char *convertedValue = hexToBin(numberToConvert);
    TEST_ASSERT_EQUAL_STRING(expectedResult, convertedValue);
    free(convertedValue);
}

void test_hextToBinConversion_odd_digit_number(void)
{
    char *numberToConvert = "A5b";
    unsigned char expectedResult[3] = {0x00, 0x0a, 0x5b};
    unsigned char *convertedValue = hexToBin(numberToConvert);
    TEST_ASSERT_EQUAL_STRING(expectedResult, convertedValue);
    free(convertedValue);
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
void test_increment_no_carry(void)
{
    unsigned char number[3] = {0x00, 0x5d, 0xa3};
    unsigned char expectedResult[3] = {0x00, 0x5d, 0xa4};
    increment(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, number);
}

void test_increment_single_carry(void)
{
    unsigned char number[3] = {0x00, 0x5d, 0xff};
    unsigned char expectedResult[3] = {0x00, 0x5e, 0x00};
    increment(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, number);
}

void test_increment_multiple_carry(void)
{
    unsigned char number[5] = {0x00, 0xca, 0xff, 0xff, 0xff};
    unsigned char expectedResult[5] = {0x00, 0xcb, 0x0, 0x0, 0x0};
    increment(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, number);
}

void test_increment_overflow(void)
{
    unsigned char number[5] = {0x00, 0xff, 0xff, 0xff, 0xff};
    unsigned char expectedResult[5] = {0x01, 0x00, 0x00, 0x00, 0x00};
    increment(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, number);
}

void test_increment_overflow_no_extension(void)
{
    unsigned char number[4] = {0xff, 0xff, 0xff, 0xff};
    unsigned char expectedResult[4] = {0x00, 0x00, 0x00, 0x00};
    increment(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, number);
}

void test_onesComplement(void)
{
    unsigned char number[4] = {0x00, 0xfa, 0x81, 0xaf};
    unsigned char expectedResult[4] = {0xff, 0x05, 0x7e, 0x50};
    onesComplement(number);
    TEST_ASSERT_EQUAL_HEX(expectedResult[0], number[0]);
}

void test_octToBin_even_digits(void)
{
    char *numberToConvert = "5371";
    unsigned char expectedResult[2] = {0x0a, 0xf9};
    unsigned char *convertedValue = octToBin(numberToConvert);
    TEST_ASSERT_EQUAL_STRING(expectedResult, convertedValue);
    free(convertedValue);
}

void test_octToBin_odd_digits(void)
{
    char *numberToConvert = "537";
    unsigned char expectedResult[2] = {0x01, 0x5f};
    unsigned char *convertedValue = octToBin(numberToConvert);
    TEST_ASSERT_EQUAL_STRING(expectedResult, convertedValue);
    free(convertedValue);
}

void test_octToBin_test(void)
{
    char *numberToConvert = "53715371";
    unsigned char expectedResult[3] = {0xAF, 0x9A, 0xF9};
    unsigned char *convertedValue = octToBinTest(numberToConvert);
    TEST_ASSERT_EQUAL_STRING(expectedResult, convertedValue);
    free(convertedValue);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_hextToBinConversion);
    RUN_TEST(test_increment_no_carry);
    RUN_TEST(test_increment_single_carry);
    RUN_TEST(test_increment_multiple_carry);
    RUN_TEST(test_increment_overflow);
    RUN_TEST(test_increment_overflow_no_extension);
    RUN_TEST(test_onesComplement);
    RUN_TEST(test_asciiToByteConversion_digit);
    RUN_TEST(test_asciiToByteConversion_small_letter);
    RUN_TEST(test_asciiToByteConversion_big_letter);
    RUN_TEST(test_asciiToByteConversion_wrong_character);
    RUN_TEST(test_hextToBinConversion_even_digit_number);
    RUN_TEST(test_hextToBinConversion_odd_digit_number);
    RUN_TEST(test_octToBin_test);
    //RUN_TEST(test_octToBin_even_digits);
    //RUN_TEST(test_octToBin_odd_digits);
    return UNITY_END();
}