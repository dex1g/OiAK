#include "parser.h"

TCNumber *createTCNumber(unsigned char *number, unsigned int numberSize, int numberPosition)
{
    TCNumber *n = calloc(1, sizeof(TCNumber));
    unsigned char *tmp = calloc(numberSize, sizeof(char));
    for (int i = 0; i < numberSize; i++)
        tmp[i] = number[i];
    n -> number = tmp;
    n -> numberSize = numberSize;
    n -> numberPosition = numberPosition;
    return n;
}

char *getNumberFromConsole()
{
    char *str = NULL;
    scanf("%m[^\n]%*c", &str);
    return str;
}

TCNumber *convertFromHex(char *number)
{
    int inputSize = (int)strlen(number);
    int negative = 0;
    int position = 0;
    if (number[0] == '-')
    {
        negative = 1;
        //number[0] = '0';
    }
    for (int i = 0, size = inputSize - 1; i <= size; i++)
    {
        if (number[size - i] == ',' || number[size - i] == '.')
        {
                position = -i;
            char *temp = calloc(size, sizeof(char));
            for (int j = 0; j < size; j++)
                if (j < (size - i))
                    temp[j] = number[j];
                else
                    temp[j] = number[j + 1];
            number = temp;
            break;
        }
    }
    TCNumber *converted = hexToBin(number);
    converted -> numberPosition = position * 4;
    if (negative)
    {
        onesComplement(converted);
        increment(converted);
    }
    return converted;
}

unsigned char asciiToByte(char digit)
{
    unsigned char ret;
    if (digit >= 'A' && digit <= 'F')
        ret = (unsigned char) digit - 'A' + 10;
    else if (digit >= 'a' && digit <= 'f')
        ret = (unsigned char) digit - 'a' + 10;
    else if (digit >= '0' && digit <= '9')
        ret = (unsigned char) digit - '0';
    else
        return 0;
    return ret;
}

TCNumber *hexToBin(char *hexNum)
{
    int hexNumIndex = strlen(hexNum) - 1;
    unsigned int numberSize = (strlen(hexNum) + 2) / 2;
    unsigned char *binRep = calloc(numberSize, sizeof(char));
    for (int i = numberSize - 1; i >= 0; i--)
    {
        if (hexNumIndex - 1 >= 0)
            binRep[i] = asciiToByte(hexNum[hexNumIndex - 1]);
        binRep[i] = binRep[i] << 4;
        binRep[i] += asciiToByte(hexNum[hexNumIndex]);
        hexNumIndex = hexNumIndex - 2;
    }
    TCNumber *binNum = createTCNumber(binRep, numberSize, 0);
    return binNum;
}

unsigned char *octToBin(char *octNum)
{
    unsigned int octNumLen = strlen(octNum);

    unsigned int newTableLength = strlen(octNum) + 1;               // number of digits + one zero of extension

    if (newTableLength % 8)
        newTableLength += (8 - (newTableLength % 8));               // add extension digits to make total length a multiplication of 8

    unsigned char *bcoNum = calloc(newTableLength + 1, sizeof(char));       // allocating new table to use as input for conversion

    //unsigned int octNumIndex = newTableLength - 1;                        // stores last index of input table

    //int numberLength = ((strlen(octNum)*3)+7)/8;                  // TO DELETE: old calculation of output table size

    unsigned int iterator = newTableLength / 8;                              // number of octal -> byte conversion function calls

    unsigned int numberLength = iterator * 3;                                // byte size of output table

    numberSize = numberLength;                                      // TODO: PUT IT INSIDE HANDLER INSTEAD OF GLOBAL VARIABLE

    unsigned char *binRep = calloc(numberLength, sizeof(char));     // allocating output table

    unsigned int lenDif = newTableLength - octNumLen;

    for (unsigned int i = 0; i < newTableLength; i++)
    {
        if (i < lenDif)
            bcoNum[i] = '0';
        else
            bcoNum[i] = (unsigned char)octNum[i - lenDif];
    }

    for(unsigned int i = 0; i < iterator; i++)
    {
        unsigned char *temp = octToBinTest(bcoNum + (i * 8));
        for(unsigned int j = 0; j < 3; j++)
            binRep[i * 3 + j] = temp[j];
        free(temp);
    }

    //printf("%s\n", binRep);                                         // JUST A TEST

    free(bcoNum);
    return binRep;
}

unsigned char *octToBinTest(unsigned char *octNum)
{
    unsigned char binRep[3] = "xxx";

    asm volatile(
        "mov $0, %%edi;"
        "mov $0, %%eax;"
        "loop: shl $3, %%eax;"
        "movb (%[out],%%edi), %%bl;"
        "sub $'0, %%bl;"
        "add %%bl, %%al;"
        "inc %%edi;"
        "cmp $8, %%edi;"
        "jne loop;"
        "mov %%al, %[rd];"
        "mov %%ah, %[nd];"
        "shr $8, %%eax;"
        "mov %%ah, %[st];"
        : [st] "=m"(binRep[0]), [nd] "=m"(binRep[1]), [rd] "=m"(binRep[2])         /* output */
        : [out] "r"(octNum)                                                        /* input */
        : "memory", "%eax", "%ebx", "%edi"                           /* clobbered register */
    );
    unsigned char *dynBinRep = calloc(3, sizeof(char));
    for (int i = 0; i < 3; i++)
        dynBinRep[i] = binRep[i];
    return dynBinRep;
}

void onesComplement(TCNumber *number)
{
    for (int i = 0; i < number -> numberSize; i++)
    {
        *(number -> number+i) = ~(number -> number[i]);
    }
}

void increment(TCNumber *number)
{
    unsigned int numberLength =  number -> numberSize;
    int carry = 1;
    for (int i = numberLength - 1; i >= 0; i--)
    {
        if (!carry)
            break;
        if (++number -> number[i])
            carry = 0;
    }
}

void scaleUp(TCNumber *n)
{
    int cnt = 0;
    for(int i = (int) n -> numberSize - 1; i >= 0; i--)
    {
        if(n -> number[i])
            break;
        ++cnt;
    }
    unsigned int newSize = n -> numberSize - cnt;
    int newPos = n -> numberPosition + (cnt * 8);
    unsigned char *ptr = calloc(newSize, sizeof(char));
    for (int i = 0; (unsigned) i < newSize; i++)
        ptr[i] = n -> number[i];
    free(n -> number);
    n -> number = ptr;
    n -> numberSize = newSize;
    n -> numberPosition = newPos;
}

void trimExtension(TCNumber *n)
{
    unsigned int cnt = 0;
    unsigned char extByte;

    switch(n -> number[0])
    {
        case 0:
            extByte = 0;
            break;
        case 255:
            extByte = 255;
            break;
        default:
            return;
    }

    for (int i = 1; i < n -> numberSize; i++)
    {
        if (n -> number[i] == extByte)
        {
            ++cnt;
            continue;
        }
        if ((n -> number[i] < 128 && extByte == 0) || (n -> number[i] > 127 && extByte == 255))
            ++cnt;
        break;
    }
    if (!cnt)
        return;
    unsigned int newSize = n -> numberSize - cnt;
    unsigned char *newNum = calloc(newSize, sizeof(char));
    for (unsigned int i = 0; i < newSize; i++)
        newNum[i] = n -> number[i + cnt];
    free(n -> number);
    n -> number = newNum;
    n -> numberSize = newSize;
}

void delete(TCNumber *n)
{
    if (n == NULL)
        return;
    if (n -> number != NULL)
        free(n -> number);
    free(n);
}

void printNumber(TCNumber *n)
{
    unsigned int numberLength = n -> numberSize;
    for (int i = 0; i < numberLength; i++)
    {
        printf("%hhx ", n -> number[i]);
    }
    printf("\n");
}

TCNumber *scaleNumber(TCNumber *num, unsigned int targetSize, int targetPosition)
{
    unsigned char *temp = calloc(targetSize, sizeof(char));
    int zeros = (num -> numberPosition - targetPosition) / 8;
    int numstart = targetSize - zeros - 1;
    int extstart = numstart - num -> numberSize;
    unsigned char extension = 0;
    if (num -> number[0] >= 128)
        extension = 255;
    for (int i = numstart; i >= 0; i--)
        if (i > extstart)
            temp[i] = num -> number[i - extstart - 1];
        else
            if (extension)
                temp[i] = extension;
            else
                break;
    TCNumber *result = createTCNumber(temp, targetSize, targetPosition);
    free(temp);
    return result;
}

TCNumber *add(TCNumber *addend1, TCNumber *addend2)
{
    int highestPos = addend1 -> numberPosition + addend1 -> numberSize * 8;
    if (addend2 -> numberPosition + addend2 -> numberSize * 8 > highestPos)
        highestPos = addend2 -> numberPosition + addend2 -> numberSize * 8;
    int lowestPos = addend1 -> numberPosition;
    if (addend2 -> numberPosition < lowestPos)
        lowestPos = addend2 -> numberPosition;
    unsigned int resultSize = (highestPos - lowestPos) / 8 + 1;

    TCNumber *scaledAddend1 = scaleNumber(addend1, resultSize, lowestPos);
    TCNumber *scaledAddend2 = scaleNumber(addend2, resultSize, lowestPos);

    unsigned char *result = calloc(resultSize, sizeof(char));

    unsigned char carry = 0;
    for (int i = resultSize - 1; i >= 0; i--)
    {
        result[i] = scaledAddend1 -> number[i] + scaledAddend2 -> number[i] + carry;
        if (result[i] < scaledAddend1 -> number[i] + carry)
            carry = 1;
        else
            carry = 0;
    }

    TCNumber *finalResult = createTCNumber(result, resultSize, lowestPos);
    delete(scaledAddend1);
    delete(scaledAddend2);
    return finalResult;
}

TCNumber *subtract(TCNumber *minuend, TCNumber *subtrahend)
{
    TCNumber *negated = createTCNumber(subtrahend -> number, subtrahend -> numberSize, subtrahend -> numberPosition);
    onesComplement(negated);
    increment(negated);
    TCNumber *result = add(minuend, negated);
    delete(negated);
    return result;
}
