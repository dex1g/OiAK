#include <stdio.h>
unsigned long long processorCounter();

int main()
{
    unsigned long long startTime;
    unsigned long long endTime;
    startTime = processorCounter();
    int b = 123;
    for (int i = 0; i < 100; i++)
    {
        b += 2;
        printf("%d\n", b);
    }
    endTime = processorCounter();
    unsigned long long duration = endTime - startTime;
    printf("\n%lu\n", duration);
    return 0;
}

// Compile this with
// gcc -m32 -O3 -std=c99 processorCounter.s timetest.c -o test
