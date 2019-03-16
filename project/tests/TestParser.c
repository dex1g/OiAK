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

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_hextToBinConversion);
    return UNITY_END();
}