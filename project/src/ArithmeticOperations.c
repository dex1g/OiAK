#include "ArithmeticOperations.h"

TCNumber *add_asm(TCNumber *addend1, TCNumber *addend2)
{
    int highestPos = addend1->numberPosition + addend1->numberSize * 8;
    if (addend2->numberPosition + addend2->numberSize * 8 > highestPos)
        highestPos = addend2->numberPosition + addend2->numberSize * 8;
    int lowestPos = addend1->numberPosition;
    if (addend2->numberPosition < lowestPos)
        lowestPos = addend2->numberPosition;
    unsigned int resultSize = (highestPos - lowestPos) / 8 + 1;

    TCNumber *scaledAddend1 = scaleNumber(addend1, resultSize, lowestPos);
    TCNumber *scaledAddend2 = scaleNumber(addend2, resultSize, lowestPos);

    unsigned char *result = calloc(resultSize, sizeof(char));

    array_adc(scaledAddend1->number, scaledAddend2->number, resultSize);

    TCNumber *finalResult = createTCNumber(scaledAddend1->number, resultSize, lowestPos);
    delete (scaledAddend1);
    delete (scaledAddend2);
    return finalResult;
}

TCNumber *add(TCNumber *addend1, TCNumber *addend2)
{
    int highestPos = addend1->numberPosition + addend1->numberSize * 8;
    if (addend2->numberPosition + addend2->numberSize * 8 > highestPos)
        highestPos = addend2->numberPosition + addend2->numberSize * 8;
    int lowestPos = addend1->numberPosition;
    if (addend2->numberPosition < lowestPos)
        lowestPos = addend2->numberPosition;
    unsigned int resultSize = (highestPos - lowestPos) / 8 + 1;

    TCNumber *scaledAddend1 = scaleNumber(addend1, resultSize, lowestPos);
    TCNumber *scaledAddend2 = scaleNumber(addend2, resultSize, lowestPos);

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

    TCNumber *finalResult = createTCNumber(result, resultSize, lowestPos);
    delete (scaledAddend1);
    delete (scaledAddend2);
    return finalResult;
}

TCNumber *subtract(TCNumber *minuend, TCNumber *subtrahend)
{
    TCNumber *negated = createTCNumber(subtrahend->number, subtrahend->numberSize, subtrahend->numberPosition);
    onesComplement(negated);
    increment(negated);
    TCNumber *result = add(minuend, negated);
    delete (negated);
    return result;
}

TCNumber *subtract_asm(TCNumber *minuend, TCNumber *subtrahend)
{
    int highestPos = minuend->numberPosition + minuend->numberSize * 8;
    if (subtrahend->numberPosition + subtrahend->numberSize * 8 > highestPos)
        highestPos = subtrahend->numberPosition + subtrahend->numberSize * 8;
    int lowestPos = minuend->numberPosition;
    if (subtrahend->numberPosition < lowestPos)
        lowestPos = subtrahend->numberPosition;
    unsigned int resultSize = (highestPos - lowestPos) / 8 + 1;

    TCNumber *scaledMinuend = scaleNumber(minuend, resultSize, lowestPos);
    TCNumber *scaledSubstrahend = scaleNumber(subtrahend, resultSize, lowestPos);

    unsigned char *result = calloc(resultSize, sizeof(char));

    array_sbb(minuend->number, subtrahend->number, resultSize);

    TCNumber *finalResult = createTCNumber(minuend->number, resultSize, lowestPos);
    delete (scaledMinuend);
    delete (scaledSubstrahend);
    return finalResult;
}