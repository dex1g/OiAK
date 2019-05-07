#include <stdio.h>
void processorTimeCounter(long *);

int main()
{
    long startTime;
    long endTime;
    processorTimeCounter(&startTime);
    int a = 567;
    int b = 123;
    int c = a + b;
    int d = a * b;
    for (int i = 0; i < 50000; i++)
        b += b;

    processorTimeCounter(&endTime);
    long duration = endTime - startTime;
    printf("%ld\n", duration);
    return 0;
}

// Compile this with
// gcc -m32 processorTimeCounter.s timetest.c -o test