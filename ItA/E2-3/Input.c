#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000000
#define M (1<<30)

int main()
{
    int n, a,b;
    int i;
    srand(time(NULL));
    n = rand() % N + 1;
    printf("%d\n", n);
    for (i = 0; i < n; i++)
    {
        a = rand() % M + 1;
        b = rand() % (M - a + 1) + a;
        printf("%d %d\n", a, b);
    }
    return 0;
}