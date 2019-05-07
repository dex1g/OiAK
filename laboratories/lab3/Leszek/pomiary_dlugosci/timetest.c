#include <stdio.h>
void processorTimeCounter(long *);
void registryOperation();
void memoryOperation();
void writeOperation();

int main()
{
    long startTime;
    long endTime;
    processorTimeCounter(&startTime);
    registryOperation();
    processorTimeCounter(&endTime);
    long duration = endTime - startTime;
    printf("Operation on registry took %ld\n", duration);
    processorTimeCounter(&startTime);
    memoryOperation();
    processorTimeCounter(&endTime);
    duration = endTime - startTime;
    printf("Operation on memory took %ld\n", duration);
    processorTimeCounter(&startTime);
    writeOperation();
    processorTimeCounter(&endTime);
    duration = endTime - startTime;
    printf("Write operation took %ld\n", duration);
    processorTimeCounter(&startTime);
    printf("Hello world from C !\n");
    processorTimeCounter(&endTime);
    duration = endTime - startTime;
    printf("Printf operation took %ld\n", duration);
    return 0;
}

// compile this with
// gcc -m32 -o test timetest.c registryOperation.s processorTimeCounter.s memoryOperation.s writeOperation.s
