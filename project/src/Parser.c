#include "Parser.h"

TCNumber *createTCNumber(unsigned char *number, unsigned int numberSize, int numberPosition)
{
    TCNumber *n = calloc(1, sizeof(TCNumber));
    unsigned char *tmp = calloc(numberSize, sizeof(char));
    for (int i = 0; i < numberSize; i++)
        tmp[i] = number[i];
    n->number = tmp;
    n->numberSize = numberSize;
    n->numberPosition = numberPosition;
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
    converted->numberPosition = position * 4;
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
        ret = (unsigned char)digit - 'A' + 10;
    else if (digit >= 'a' && digit <= 'f')
        ret = (unsigned char)digit - 'a' + 10;
    else if (digit >= '0' && digit <= '9')
        ret = (unsigned char)digit - '0';
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

void onesComplement(TCNumber *number)
{
    for (int i = 0; i < number->numberSize; i++)
    {
        *(number->number + i) = ~(number->number[i]);
    }
}

void increment(TCNumber *number)
{
    unsigned int numberLength = number->numberSize;
    int carry = 1;
    for (int i = numberLength - 1; i >= 0; i--)
    {
        if (!carry)
            break;
        if (++number->number[i])
            carry = 0;
    }
}

void scaleUp(TCNumber *n)
{
    int cnt = 0;
    for (int i = (int)n->numberSize - 1; i >= 0; i--)
    {
        if (n->number[i])
            break;
        ++cnt;
    }
    unsigned int newSize = n->numberSize - cnt;
    int newPos = n->numberPosition + (cnt * 8);
    unsigned char *ptr = calloc(newSize, sizeof(char));
    for (int i = 0; (unsigned)i < newSize; i++)
        ptr[i] = n->number[i];
    free(n->number);
    n->number = ptr;
    n->numberSize = newSize;
    n->numberPosition = newPos;
}

void trimExtension(TCNumber *n)
{
    unsigned int cnt = 0;
    unsigned char extByte;

    switch (n->number[0])
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

    for (int i = 1; i < n->numberSize; i++)
    {
        if (n->number[i] == extByte)
        {
            ++cnt;
            continue;
        }
        if ((n->number[i] < 128 && extByte == 0) || (n->number[i] > 127 && extByte == 255))
            ++cnt;
        break;
    }
    if (!cnt)
        return;
    unsigned int newSize = n->numberSize - cnt;
    unsigned char *newNum = calloc(newSize, sizeof(char));
    for (unsigned int i = 0; i < newSize; i++)
        newNum[i] = n->number[i + cnt];
    free(n->number);
    n->number = newNum;
    n->numberSize = newSize;
}

void delete (TCNumber *n)
{
    if (n == NULL)
        return;
    if (n->number != NULL)
        free(n->number);
    free(n);
}

void printNumber(TCNumber *n)
{
    unsigned int numberLength = n->numberSize;
    for (int i = 0; i < numberLength; i++)
    {
        printf("%hhx ", n->number[i]);
    }
    printf("\n");
}

TCNumber *scaleNumber(TCNumber *num, unsigned int targetSize, int targetPosition)
{
    unsigned char *temp = calloc(targetSize, sizeof(char));
    int zeros = (num->numberPosition - targetPosition) / 8;
    int numstart = targetSize - zeros - 1;
    int extstart = numstart - num->numberSize;
    unsigned char extension = 0;
    if (num->number[0] >= 128)
        extension = 255;
    for (int i = numstart; i >= 0; i--)
        if (i > extstart)
            temp[i] = num->number[i - extstart - 1];
        else if (extension)
            temp[i] = extension;
        else
            break;
    TCNumber *result = createTCNumber(temp, targetSize, targetPosition);
    free(temp);
    return result;
}

TCNumber *getNumberFromFile(char *filename)
{
    FILE *handle;
    int len = 0;
    char c;
    char *buffer = NULL;

    handle = fopen(filename, "r");

    if (handle == NULL)
        return NULL;

    // find the length of the line in file
    while ((c = fgetc(handle)) != EOF)
    {
        if (c == '\n')
        {
            break;
        }
        len++;
    }

    // allocate memory for number based on calculated length
    buffer = malloc(sizeof(char) * len);

    // move to the beginning of file
    fseek(handle, 0, SEEK_SET);

    fread(buffer, sizeof(char), len, handle);

    // create TCNumber object
    TCNumber *convertedValue = convertFromHex(buffer);

    fclose(handle);
    free(buffer);
    return convertedValue;
}
