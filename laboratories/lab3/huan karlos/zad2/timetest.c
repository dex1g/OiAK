#include <stdio.h>
unsigned long long proctime();

int main()
{
    for (int i = 0; i < 20; i++)
        printf("%llu\n", proctime());
    return 0;
}
