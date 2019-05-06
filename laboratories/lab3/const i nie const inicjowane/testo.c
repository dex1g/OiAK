#include <stdio.h>
extern int numb;
extern const int numbc;

int main()
{
    printf("%d %d\n", numb, numbc);
    numb += 10;
    //numbc += 10;
    printf("%d %d\n", numb, numbc);
    return 0;
}
