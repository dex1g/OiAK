#include <stdio.h>
#include <time.h>
#include "../src/ArithmeticOperations.h"
#include "../src/Parser.h"
#include "./PastImplementations/LessEfficientOperations.h"

#define MB100 104857600
#define MB250 262144000
#define MB500 524288000
#define MB750 786432000
#define GB 1073741824
#define numberOfTries 10
#define firstNumber20KBPath "./data/firstNumber20KB"
#define firstNumber1MBPath "./data/firstNumber1MB"
#define firstNumber100MBPath "./excelData/firstNumber100MB"
#define secondNumber100MBPath "./excelData/secondNumber100MB"
#define firstNumber250MBPath "./excelData/firstNumber250MB"
#define secondNumber250MBPath "./excelData/secondNumber250MB"
#define firstNumber500MBPath "./excelData/firstNumber500MB"
#define secondNumber500MBPath "./excelData/secondNumber500MB"
#define firstNumber750MBPath "./excelData/firstNumber750MB"
#define secondNumber750MBPath "./excelData/secondNumber750MB"
#define firstNumber1GBPath "./data/firstNumber1GB"
#define secondNumber1GBPath "./data/secondNumber1GB"
#define firstNumber1KBPath "./excelData/firstNumber1KB"
#define firstNumber5KBPath "./excelData/firstNumber5KB"
#define firstNumber10KBPath "./excelData/firstNumber10KB"
#define firstNumber15KBPath "./excelData/firstNumber15KB"
#define firstNumber20KBPath "./data/firstNumber20KB"

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
