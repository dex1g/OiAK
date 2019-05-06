#include <stdio.h>
void proctime(long*);

int main()
{
    long stime;
    long etime;
    proctime(&stime);
    int a = 10;
    int b = -1;
    int c = a + b;
    int d = a * b;
    for (int i = 0; i < 10000; i++)
    {
        a *= a;
    }

    proctime(&etime);
    long dur = etime - stime;
    printf("%ld", dur);
    return 0;
}
