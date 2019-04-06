#include "parser.h"

TCNumber *createTCNumber(unsigned char *number, unsigned int numberSize, int numberPosition)
{
    TCNumber *n = malloc(sizeof(TCNumber));
    n -> number = number;
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
    int position;
    if (number[0] == '-')
    {
        negative = 1;
        number[0] = 0;
    }
    for (int i = 0; i < inputSize; i++)
    {
        if (number[i] == ',' || number[i] == '.')
        {
                position = - (inputSize - i);
            char *temp = calloc(--inputSize, sizeof(char));
            for (int j = 0; j < inputSize; j++)
                if (j < i)
                    temp[j] = number[i];
                else
                    temp[j] = number[i + 1];
            number = temp;
            break;
        }
    }
    TCNumber *converted = hexToBin(number);
    converted -> numberPosition = position * 4;
    {
        onesComplement(converted -> number);
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
    unsigned int numberSize = (strlen(hexNum) + 1) / 2 + 1;
    unsigned char *binRep = malloc(numberSize * sizeof(char));
    binRep[0] = 0;
    for (int i = numberSize - 1; i > 0; i--)
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
    unsigned int numberLength = number -> numberSize;
    for (int i = 0; i < numberLength; i++)
    {
        number -> number[i] = ~(number -> number[i]);
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
