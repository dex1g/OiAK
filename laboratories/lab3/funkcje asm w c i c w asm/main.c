#include <stdio.h>

int nmb;
void doit();

char mun;
char* nyg = "%d %c\n";

int main()
{
    mun = 'C';
    printf(nyg, nmb, mun);
    doit();
    printf(nyg, nmb, mun);
    return 0;
}
