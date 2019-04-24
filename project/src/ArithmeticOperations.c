#include "ArithmeticOperations.h"

TCNumber *add_asm(TCNumber *addend1, TCNumber *addend2)
{
    int highestPos = addend1->numberPosition + (int)addend1->numberSize * 8;
    if (addend2->numberPosition + (int)addend2->numberSize * 8 > highestPos)
        highestPos = addend2->numberPosition + (int)addend2->numberSize * 8;
    int lowestPos = addend1->numberPosition;
    if (addend2->numberPosition < lowestPos)
        lowestPos = addend2->numberPosition;
    unsigned int resultSize = (highestPos - lowestPos) / 8 + 1;

    TCNumber *scaledAddend1 = scaleNumber(addend1, resultSize, lowestPos);
    delete(addend1);
    TCNumber *scaledAddend2 = scaleNumber(addend2, resultSize, lowestPos);
    delete(addend2);

    array_adc(scaledAddend1->number, scaledAddend2->number, resultSize);

    TCNumber *finalResult = createTCNumber_no_realloc(scaledAddend1->number, resultSize, lowestPos);
    free(scaledAddend1);
    delete(scaledAddend2);
    return finalResult;
}

TCNumber *add(TCNumber *addend1, TCNumber *addend2)
{
    int highestPos = addend1->numberPosition + (int)addend1->numberSize * 8;
    if (addend2->numberPosition + (int)addend2->numberSize * 8 > highestPos)
        highestPos = addend2->numberPosition + (int)addend2->numberSize * 8;
    int lowestPos = addend1->numberPosition;
    if (addend2->numberPosition < lowestPos)
        lowestPos = addend2->numberPosition;
    unsigned int resultSize = (highestPos - lowestPos) / 8 + 1;

    TCNumber *scaledAddend1 = scaleNumber(addend1, resultSize, lowestPos);
    delete(addend1);
    TCNumber *scaledAddend2 = scaleNumber(addend2, resultSize, lowestPos);
    delete(addend2);

    unsigned char *result = calloc(resultSize, sizeof(char));

    unsigned char carry = 0;
    for (int i = resultSize - 1; i >= 0; i--)
    {
        result[i] = scaledAddend1->number[i] + scaledAddend2->number[i] + carry;
        if (result[i] < scaledAddend1->number[i] + carry)
            carry = 1;
        else
            carry = 0;
    }

    delete(scaledAddend1);
    delete(scaledAddend2);
    TCNumber *finalResult = createTCNumber_no_realloc(result, resultSize, lowestPos);
    return finalResult;
}

TCNumber *subtract(TCNumber *minuend, TCNumber *subtrahend)
{
    TCNumber *negated = createTCNumber_no_realloc(subtrahend->number, subtrahend->numberSize, subtrahend->numberPosition);
    free(subtrahend);
    onesComplement(negated);
    increment(negated);
    TCNumber *result = add(minuend, negated);
    delete(minuend);
    delete(negated);
    return result;
}

TCNumber *subtract_asm(TCNumber *minuend, TCNumber *subtrahend)
{
    int highestPos = minuend->numberPosition + (int)minuend->numberSize * 8;
    if (subtrahend->numberPosition + (int)subtrahend->numberSize * 8 > highestPos)
        highestPos = subtrahend->numberPosition + (int)subtrahend->numberSize * 8;
    int lowestPos = minuend->numberPosition;
    if (subtrahend->numberPosition < lowestPos)
        lowestPos = subtrahend->numberPosition;
    unsigned int resultSize = (highestPos - lowestPos) / 8 + 1;

    TCNumber *scaledMinuend = scaleNumber(minuend, resultSize, lowestPos);
    delete(minuend);
    TCNumber *scaledSubstrahend = scaleNumber(subtrahend, resultSize, lowestPos);
    delete(subtrahend);

    array_sbb(scaledMinuend->number, scaledSubstrahend->number, resultSize);

    TCNumber *finalResult = createTCNumber_no_realloc(scaledMinuend->number, resultSize, lowestPos);
    free(scaledMinuend);
    delete(scaledSubstrahend);
    return finalResult;
}
