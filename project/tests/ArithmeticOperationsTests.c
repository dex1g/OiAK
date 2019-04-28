#include "./unity/src/unity.h"
#include "../src/ArithmeticOperations.h"
#include "../efficiencyTests/PastImplementations/LessEfficientOperations.h"

void test_increment_no_carry(void)
{
    unsigned char number[3] = {0x00, 0x5d, 0xa3};
    unsigned char expectedResult[3] = {0x00, 0x5d, 0xa4};
    TCNumber *n = createTCNumber(number, 3, 0);
    increment(n);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, n->number, 3);
    delete (n);
}

void test_increment_single_carry(void)
{
    unsigned char number[3] = {0x00, 0x5d, 0xff};
    unsigned char expectedResult[3] = {0x00, 0x5e, 0x00};
    TCNumber *n = createTCNumber(number, 3, 0);
    increment(n);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, n->number, 3);
    delete (n);
}

void test_increment_multiple_carry(void)
{
    unsigned char number[5] = {0x00, 0xca, 0xff, 0xff, 0xff};
    unsigned char expectedResult[5] = {0x00, 0xcb, 0x0, 0x0, 0x0};
    TCNumber *n = createTCNumber(number, 5, 0);
    increment(n);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, n->number, 5);
    delete (n);
}

void test_increment_overflow(void)
{
    unsigned char number[5] = {0x00, 0xff, 0xff, 0xff, 0xff};
    unsigned char expectedResult[5] = {0x01, 0x00, 0x00, 0x00, 0x00};
    TCNumber *n = createTCNumber(number, 5, 0);
    increment(n);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, n->number, 5);
    delete (n);
}

void test_increment_overflow_no_extension(void)
{
    unsigned char number[4] = {0xff, 0xff, 0xff, 0xff};
    unsigned char expectedResult[4] = {0x00, 0x00, 0x00, 0x00};
    TCNumber *n = createTCNumber(number, 4, 0);
    increment(n);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, n->number, 4);
    delete (n);
}

void test_onesComplement(void)
{
    unsigned char number[] = {0x00, 0xfa, 0x81, 0xaf};
    unsigned char expectedResult[] = {0xff, 0x05, 0x7e, 0x50};
    TCNumber *n = createTCNumber(number, 4, 0);
    onesComplement(n);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, n->number, 4);
    delete (n);
}

void test_add_positive(void)
{
    unsigned char temp1[3] = {0x12, 0x7e, 0x60};
    unsigned char temp2[4] = {0x5d, 0x0a, 0x2b, 0x6e};
    TCNumber *number1 = createTCNumber(temp1, 3, 8);
    TCNumber *number2 = createTCNumber(temp2, 4, -16);
    unsigned char expectedResult[7] = {0x00, 0x12, 0x7e, 0xbd, 0x0a, 0x2b, 0x6e};
    unsigned int expectedSize = 7;
    int expectedPosition = -16;
    TCNumber *result = add_C(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

void test_add_positive_asm(void)
{
    unsigned char temp1[3] = {0x12, 0x7e, 0x60};
    unsigned char temp2[4] = {0x5d, 0x0a, 0x2b, 0x6e};
    TCNumber *number1 = createTCNumber(temp1, 3, 8);
    TCNumber *number2 = createTCNumber(temp2, 4, -16);
    unsigned char expectedResult[7] = {0x00, 0x12, 0x7e, 0xbd, 0x0a, 0x2b, 0x6e};
    unsigned int expectedSize = 7;
    int expectedPosition = -16;
    TCNumber *result = add_asm(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

void test_add_one_negative(void)
{
    unsigned char temp1[3] = {0x12, 0x7e, 0x60};
    unsigned char temp2[4] = {0xad, 0x0a, 0x2b, 0x6e};
    TCNumber *number1 = createTCNumber(temp1, 3, 8);
    TCNumber *number2 = createTCNumber(temp2, 4, -16);
    unsigned char expectedResult[7] = {0x00, 0x12, 0x7e, 0x0d, 0x0a, 0x2b, 0x6e};
    unsigned int expectedSize = 7;
    int expectedPosition = -16;
    TCNumber *result = add_C(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

void test_add_one_negative_asm(void)
{
    unsigned char temp1[3] = {0x12, 0x7e, 0x60};
    unsigned char temp2[4] = {0xad, 0x0a, 0x2b, 0x6e};
    TCNumber *number1 = createTCNumber(temp1, 3, 8);
    TCNumber *number2 = createTCNumber(temp2, 4, -16);
    unsigned char expectedResult[7] = {0x00, 0x12, 0x7e, 0x0d, 0x0a, 0x2b, 0x6e};
    unsigned int expectedSize = 7;
    int expectedPosition = -16;
    TCNumber *result = add_asm(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

void test_add_both_negative(void)
{
    unsigned char temp1[3] = {0xb2, 0x7e, 0x60};
    unsigned char temp2[4] = {0xfd, 0x0a, 0x2b, 0x6e};
    TCNumber *number1 = createTCNumber(temp1, 3, 8);
    TCNumber *number2 = createTCNumber(temp2, 4, -16);
    unsigned char expectedResult[7] = {0xff, 0xb2, 0x7e, 0x5d, 0x0a, 0x2b, 0x6e};
    unsigned int expectedSize = 7;
    int expectedPosition = -16;
    TCNumber *result = add_C(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

void test_add_both_negative_asm(void)
{
    unsigned char temp1[3] = {0xb2, 0x7e, 0x60};
    unsigned char temp2[4] = {0xfd, 0x0a, 0x2b, 0x6e};
    TCNumber *number1 = createTCNumber(temp1, 3, 8);
    TCNumber *number2 = createTCNumber(temp2, 4, -16);
    unsigned char expectedResult[7] = {0xff, 0xb2, 0x7e, 0x5d, 0x0a, 0x2b, 0x6e};
    unsigned int expectedSize = 7;
    int expectedPosition = -16;
    TCNumber *result = add_asm(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

void test_subtract_positive(void)
{
    unsigned char temp1[3] = {0x12, 0x7e, 0x60};
    unsigned char temp2[4] = {0x5d, 0x0a, 0x2b, 0x6e};
    TCNumber *number1 = createTCNumber(temp1, 3, 8);
    TCNumber *number2 = createTCNumber(temp2, 4, -16);
    unsigned char expectedResult[7] = {0x00, 0x12, 0x7e, 0x02, 0xf5, 0xd4, 0x92};
    unsigned int expectedSize = 7;
    int expectedPosition = -16;
    TCNumber *result = subtract_C(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

void test_subtract_positive_asm(void)
{
    unsigned char temp1[3] = {0x12, 0x7e, 0x60};
    unsigned char temp2[4] = {0x5d, 0x0a, 0x2b, 0x6e};
    TCNumber *number1 = createTCNumber(temp1, 3, 8);
    TCNumber *number2 = createTCNumber(temp2, 4, -16);
    unsigned char expectedResult[7] = {0x00, 0x12, 0x7e, 0x02, 0xf5, 0xd4, 0x92};
    unsigned int expectedSize = 7;
    int expectedPosition = -16;
    TCNumber *result = subtract_asm(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

void test_subtract_one_negative(void)
{
    unsigned char temp1[3] = {0x12, 0x7e, 0x60};
    unsigned char temp2[4] = {0xad, 0x0a, 0x2b, 0x6e};
    TCNumber *number1 = createTCNumber(temp1, 3, 8);
    TCNumber *number2 = createTCNumber(temp2, 4, -16);
    unsigned char expectedResult[7] = {0x00, 0x12, 0x7e, 0xB2, 0xF5, 0xD4, 0x92};
    unsigned int expectedSize = 7;
    int expectedPosition = -16;
    TCNumber *result = subtract_C(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

void test_subtract_one_negativ_asm(void)
{
    unsigned char temp1[3] = {0x12, 0x7e, 0x60};
    unsigned char temp2[4] = {0xad, 0x0a, 0x2b, 0x6e};
    TCNumber *number1 = createTCNumber(temp1, 3, 8);
    TCNumber *number2 = createTCNumber(temp2, 4, -16);
    unsigned char expectedResult[7] = {0x00, 0x12, 0x7e, 0xB2, 0xF5, 0xD4, 0x92};
    unsigned int expectedSize = 7;
    int expectedPosition = -16;
    TCNumber *result = subtract_asm(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

void test_subtract_both_negative(void)
{
    unsigned char temp1[3] = {0xb2, 0x7e, 0x60};
    unsigned char temp2[4] = {0xfd, 0x0a, 0x2b, 0x6e};
    TCNumber *number1 = createTCNumber(temp1, 3, 8);
    TCNumber *number2 = createTCNumber(temp2, 4, -16);
    unsigned char expectedResult[7] = {0xff, 0xb2, 0x7e, 0x62, 0xf5, 0xd4, 0x92};
    unsigned int expectedSize = 7;
    int expectedPosition = -16;
    TCNumber *result = subtract_C(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

void test_subtract_both_negative_asm(void)
{
    unsigned char temp1[3] = {0xb2, 0x7e, 0x60};
    unsigned char temp2[4] = {0xfd, 0x0a, 0x2b, 0x6e};
    TCNumber *number1 = createTCNumber(temp1, 3, 8);
    TCNumber *number2 = createTCNumber(temp2, 4, -16);
    unsigned char expectedResult[7] = {0xff, 0xb2, 0x7e, 0x62, 0xf5, 0xd4, 0x92};
    unsigned int expectedSize = 7;
    int expectedPosition = -16;
    TCNumber *result = subtract_asm(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

void test_array_mul_asm(void)
{
    unsigned char temp1[] = {0xd5, 0x7a, 0x1f};
    unsigned char temp2[] = {0x5d};
    unsigned char expectedResult[] = {0x4d, 0x8d, 0x5d, 0x43};
    unsigned char *result = calloc(4, sizeof(char));
    array_mul(3, temp1, temp2, result, 0);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result, 4);
    free(result);
}

void test_mul_asm_one_negativ(void)
{
    unsigned char temp1[] = {0xd5, 0x7a, 0x1f};
    unsigned char temp2[] = {0x12, 0xc4};
    TCNumber *number1 = createTCNumber(temp1, 3, 0);
    TCNumber *number2 = createTCNumber(temp2, 2, 0);
    unsigned char expectedResult[] = {0x0f, 0xa6, 0x07, 0xad, 0xbc};
    unsigned int expectedSize = 5;
    int expectedPosition = 0;
    TCNumber *result = multiply_asm(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 5);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

void test_mul_asm_positiv(void)
{
    unsigned char temp1[] = {0x00, 0xd5, 0xfc};
    unsigned char temp2[] = {0x0c, 0x6b, 0x2e, 0x30};
    TCNumber *number1 = createTCNumber(temp1, 3, -24);
    TCNumber *number2 = createTCNumber(temp2, 4, -8);
    unsigned char expectedResult[] = {0x00, 0x0a, 0x61, 0x66, 0xef, 0x67, 0x40};
    unsigned int expectedSize = 7;
    int expectedPosition = -32;
    TCNumber *result = multiply_asm(number1, number2);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult, result->number, 7);
    TEST_ASSERT_EQUAL_INT(expectedSize, result->numberSize);
    TEST_ASSERT_EQUAL_INT(expectedPosition, result->numberPosition);
    delete (result);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_increment_no_carry);
    RUN_TEST(test_increment_single_carry);
    RUN_TEST(test_increment_multiple_carry);
    RUN_TEST(test_increment_overflow);
    RUN_TEST(test_increment_overflow_no_extension);
    RUN_TEST(test_onesComplement);
    RUN_TEST(test_add_positive);
    RUN_TEST(test_add_positive_asm);
    RUN_TEST(test_add_one_negative);
    RUN_TEST(test_add_one_negative_asm);
    RUN_TEST(test_add_both_negative);
    RUN_TEST(test_add_both_negative_asm);
    RUN_TEST(test_subtract_positive);
    RUN_TEST(test_subtract_positive_asm);
    RUN_TEST(test_subtract_one_negative);
    RUN_TEST(test_subtract_one_negativ_asm);
    RUN_TEST(test_subtract_both_negative);
    RUN_TEST(test_subtract_both_negative_asm);
    RUN_TEST(test_array_mul_asm);
    RUN_TEST(test_mul_asm_one_negativ);
    RUN_TEST(test_mul_asm_positiv);
    return UNITY_END();
}
