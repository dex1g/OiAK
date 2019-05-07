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
    unsigned int startIndex = ((highestPos - (addend2->numberPosition + ((long long)addend2->numberSize * 8))) / 8) + 1;

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
    unsigned int startIndex = ((highestPos - (subtrahend->numberPosition + ((long long)subtrahend->numberSize * 8))) / 8) + 1;
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
    int lowestPos = multiplicand->numberPosition + multiplier->numberPosition;

    int resultSize = multiplicand->numberSize + multiplier->numberSize;
    unsigned char *result = calloc(resultSize, sizeof(char));

    for (int i = multiplier->numberSize - 1; i >= 0; i--)
        array_mul(multiplicand->numberSize, multiplicand->number, multiplier->number + i, result, i);

    delete (multiplicand);
    delete (multiplier);

    return createTCNumber_no_realloc(result, resultSize, lowestPos);
}

TCNumber *shift_left(TCNumber *num, unsigned amount)
{
    if (amount == 0)
        return num;

    unsigned char extension[8] = {255, 254, 252, 248, 240, 224, 192, 128};

    int bitAmount = amount % 8;
    int byteAmount = amount / 8;

    unsigned char *number = num->number;
    unsigned int size = num->numberSize;
    int position = num->numberPosition;
    free(num);

    if (bitAmount)
    {
        unsigned char *shifted = calloc(size + 1, sizeof(char));

        memcpy(shifted + 1, number, size);

        for (int i = 1; i < size; i++)
        {
            number[i] = number[i] >> (8 - bitAmount);
        }

        if (number[0] > 127)
        {
            number[0] = number[0] >> (8 - bitAmount);
            number[0] += extension[bitAmount];
        }
        else
        {
            number[0] = number[0] >> (8 - bitAmount);
        }

        shifted[size] = shifted[size] << bitAmount;

        for (int i = 0; i < size; i++)
        {
            shifted[i] = shifted[i] << bitAmount;
            shifted[i] += number[i];
        }
        free(number);
        number = shifted;
        ++size;
    }

    if (byteAmount)
    {
        unsigned char *temp = calloc(size + byteAmount, sizeof(char));
        memcpy(temp, number, size);
        free(number);
        number = temp;
        size += byteAmount;
    }

    TCNumber *result = createTCNumber_no_realloc(number, size, position);
    return result;
}