#include <stdio.h>
unsigned long long registryOperation();
unsigned long long memoryOperation();
unsigned long long writeOperation();
unsigned long long printfOperation();

int main()
{
    for (int i = 0; i < 10; i++)
    {
        printf("Operation on registry took %lu\n", registryOperation());
        printf("Operation on memory took %lu\n", memoryOperation());
        printf("Write operation took %lu\n", writeOperation());
        printf("Pritnf operation took %lu\n", printfOperation());
    }
    return 0;
}

// compile this with
// gcc -m32 -O3 -std=c99 -o test timetest.c registryOperation.s memoryOperation.s writeOperation.s printfOperation.s
