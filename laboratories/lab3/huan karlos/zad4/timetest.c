#include <stdio.h>
unsigned long long proctime();
unsigned long long registryOperationTime();
unsigned long long memoryOperationTime();
unsigned long long writeOperationTime();

int main()
{
    unsigned long long startTime;
    unsigned long long endTime;
    unsigned long long duration;
    for (int i = 0; i < 10; i++)
    {
        printf("Operation on registry took %llu\n", registryOperationTime());
        printf("Operation on memory took %llu\n", memoryOperationTime());
        printf("Write operation took %llu\n", writeOperationTime());
        startTime = proctime();
        printf("Hello world from C!\n");
        endTime = proctime();
        duration = endTime - startTime;
        printf("Printf operation took %llu\n", duration);
    }
    return 0;
}
