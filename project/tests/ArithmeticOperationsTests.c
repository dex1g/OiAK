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

void test_mul_array_bytes_asm(void)
{
    unsigned char temp1[] = {0xd5, 0x7a, 0x1f};
    unsigned char temp2[] = {0x5d};
    unsigned char expectedResult[] = {0x4d, 0x8d, 0x5d, 0x43};
    unsigned char *result = calloc(4, sizeof(char));
    array_mul_byte(3, temp1, temp2, result);
    TEST_ASSERT_EQUAL_MEMORY(expectedResult + 1, result + 1, 3);
    free(result);
}

int main(void)
{
    UNITY_BEGIN();
    // RUN_TEST(test_increment_no_carry);
    // RUN_TEST(test_increment_single_carry);
    // RUN_TEST(test_increment_multiple_carry);
    // RUN_TEST(test_increment_overflow);
    // RUN_TEST(test_increment_overflow_no_extension);
    // RUN_TEST(test_onesComplement);
    // RUN_TEST(test_add_positive);
    // RUN_TEST(test_add_positive_asm);
    // RUN_TEST(test_add_one_negative);
    // RUN_TEST(test_add_one_negative_asm);
    // RUN_TEST(test_add_both_negative);
    // RUN_TEST(test_add_both_negative_asm);
    // RUN_TEST(test_subtract_positive);
    // RUN_TEST(test_subtract_positive_asm);
    // RUN_TEST(test_subtract_one_negative);
    // RUN_TEST(test_subtract_one_negativ_asm);
    // RUN_TEST(test_subtract_both_negative);
    // RUN_TEST(test_subtract_both_negative_asm);
    RUN_TEST(test_mul_array_bytes_asm);
    return UNITY_END();
}
