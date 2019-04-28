#include "ArithmeticOperations.h"

TCNumber *add_asm(TCNumber *addend1, TCNumber *addend2)
{
    long long highestPos = addend1->numberPosition + (long long)addend1->numberSize * 8;
    if (addend2->numberPosition + (long long)addend2->numberSize * 8 > highestPos)
        highestPos = addend2->numberPosition + (long long)addend2->numberSize * 8;
    int lowestPos = addend1->numberPosition;
    if (addend2->numberPosition < lowestPos)
        lowestPos = addend2->numberPosition;
    unsigned int resultSize = (highestPos - lowestPos) / 8 + 1;

    // Index of the highest position of the second number in first array
    unsigned int startIndex = ((highestPos - (addend2->numberPosition + (long long)(addend2->numberSize * 8))) / 8) + 1;

    TCNumber *scaledAddend1 = scaleNumber(addend1, resultSize, lowestPos);
    delete (addend1);

    unsigned char one = 1;
    if (addend2->number[0] > 127)
        array_sbb(scaledAddend1->number + startIndex - 1, &one, 1, startIndex - 1);

    array_adc(scaledAddend1->number + startIndex, addend2->number, addend2->numberSize, startIndex);

    delete (addend2);
    return scaledAddend1;
}

TCNumber *subtract_asm(TCNumber *minuend, TCNumber *subtrahend)
{
    long long highestPos = minuend->numberPosition + (long long)minuend->numberSize * 8;
    if (subtrahend->numberPosition + (int)subtrahend->numberSize * 8 > highestPos)
        highestPos = subtrahend->numberPosition + (long long)subtrahend->numberSize * 8;
    int lowestPos = minuend->numberPosition;
    if (subtrahend->numberPosition < lowestPos)
        lowestPos = subtrahend->numberPosition;
    unsigned int resultSize = (highestPos - lowestPos) / 8 + 1;

    // Index of the highest position of the second number in first array
    unsigned int startIndex = ((highestPos - (subtrahend->numberPosition + (long long)(subtrahend->numberSize * 8))) / 8) + 1;

    TCNumber *scaledMinuend = scaleNumber(minuend, resultSize, lowestPos);
    delete (minuend);

    unsigned char one = 1;
    if (subtrahend->number[0] > 127)
        array_adc(scaledMinuend->number + startIndex - 1, &one, 1, startIndex - 1);

    array_sbb(scaledMinuend->number + startIndex, subtrahend->number, subtrahend->numberSize, startIndex);

    delete (subtrahend);
    return scaledMinuend;
}

TCNumber *multiply_asm(TCNumber *multiplicand, TCNumber *multiplier)
{
    int lowestPos = multiplicand->numberPosition;
    if (multiplier->numberPosition < lowestPos)
        lowestPos = multiplier->numberPosition;
    
    int resultSize = multiplicand->numberSize + multiplier->numberSize;
    unsigned char *result = calloc(resultSize, sizeof(char));

    array_mul(multiplicand->numberSize, multiplicand->number, multiplier->number, result);
    delete(multiplicand);
    delete(multiplier);

    return createTCNumber_no_realloc(result, resultSize, lowestPos);
}