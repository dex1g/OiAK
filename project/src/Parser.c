#include "Parser.h"

TCNumber *createTCNumber(unsigned char *number, unsigned int numberSize, int numberPosition)
{
    TCNumber *n = calloc(1, sizeof(TCNumber));
    unsigned char *tmp = calloc(numberSize, sizeof(char));
    memcpy(tmp, number, numberSize);
    n->number = tmp;
    n->numberSize = numberSize;
    n->numberPosition = numberPosition;
    return n;
}

TCNumber *createTCNumber_no_realloc(unsigned char *number, unsigned int numberSize, int numberPosition)
{
    TCNumber *n = calloc(1, sizeof(TCNumber));
    n->number = number;
    n->numberSize = numberSize;
    n->numberPosition = numberPosition;
    return n;
}

char *getNumberFromSTDIN()
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
    TCNumber *binNum = createTCNumber_no_realloc(binRep, numberSize, 0);
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

TCNumber *scaleUp(TCNumber *n)
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
    memcpy(ptr, n->number, newSize);
    delete (n);
    return createTCNumber_no_realloc(ptr, newSize, newPos);
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
    memcpy(newNum, n->number + cnt, newSize);
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
    int zeros = (num->numberPosition - targetPosition) / 8; // number of zero bytes after the number
    int numstart = targetSize - zeros - 1;                  // index of last byte of the number
    int extstart = numstart - num->numberSize;              // index of last byte of extension
    unsigned char extension = 0;

    if (num->number[0] >= 128)
    {
        extension = 255;
        for (int i = 0; i <= extstart; i++)
            temp[i] = extension;
    }
    if (extstart >= 0)
        memcpy(temp + extstart + 1, num->number, num->numberSize);
    else
    {
        if (num->numberSize <= targetSize)
            memcpy(temp, num->number, num->numberSize);
        else
            memcpy(temp, num->number, targetSize);
    }

    delete (num);

    TCNumber *result = createTCNumber_no_realloc(temp, targetSize, targetPosition);
    return result;
}

TCNumber *getHexNumberFromTxtFile(char *filename)
{
    FILE *handle;
    unsigned int len = 0;
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

TCNumber *getNumberFromBinaryFile(char *filename, int numberPosition)
{
    FILE *handle;
    unsigned char *buffer;

    handle = fopen(filename, "rb");

    if (handle == NULL)
        return NULL;

    //Get file length
    fseek(handle, 0, SEEK_END);
    unsigned long fileLen = ftell(handle);
    fclose(handle);

    //fseek(handle, 0, SEEK_SET);
    handle = fopen(filename, "rb");

    // allocate memory for number based on calculated length
    buffer = malloc(fileLen);

    //Read file contents into buffer
    fread(buffer, fileLen, 1, handle);

    fclose(handle);

    TCNumber *num = createTCNumber_no_realloc(buffer, fileLen, numberPosition);
    return num;
}
