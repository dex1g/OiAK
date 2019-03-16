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

void test_increment_no_carry(void)
{
    unsigned char number[3] = { 0x00, 0x5d, 0xa3 };
    unsigned char expectedResult[3] = { 0x00, 0x5d, 0xa4 };
    increment(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, number);
}

void test_increment_single_carry(void)
{
    unsigned char number[3] = { 0x00, 0x5d, 0xff };
    unsigned char expectedResult[3] = { 0x00, 0x5e, 0x00 };
    increment(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, number);
}

void test_increment_multiple_carry(void)
{
    unsigned char number[5] = { 0x00, 0xca, 0xff, 0xff, 0xff };
    unsigned char expectedResult[5] = { 0x00, 0xcb, 0x0, 0x0, 0x0 };
    increment(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, number);
}

void test_increment_overflow(void)
{
    unsigned char number[5] = { 0x00, 0xff, 0xff, 0xff, 0xff };
    unsigned char expectedResult[5] = { 0x01, 0x00, 0x00, 0x00, 0x00 };
    increment(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, number);
}

void test_increment_overflow_no_extension(void)
{
    unsigned char number[4] = { 0xff, 0xff, 0xff, 0xff };
    unsigned char expectedResult[4] = { 0x00, 0x00, 0x00, 0x00 };
    increment(number);
    TEST_ASSERT_EQUAL_STRING(expectedResult, number);
}

void test_onesComplement(void)
{
    unsigned char number[4] = { 0x00, 0xfa, 0x81, 0xaf };
    unsigned char expectedResult[4] = { 0xff, 0x05, 0x7e, 0x50 };
    onesComplement(number);
    TEST_ASSERT_EQUAL_HEX(expectedResult[0], number[0]);
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
    return UNITY_END();
}