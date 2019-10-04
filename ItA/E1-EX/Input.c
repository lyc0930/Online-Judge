#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000000
#define M 1000000000
int main()
{
    int n, k;
    int i;
    srand(time(NULL));
    n = rand() % (N - 2) + 2;
    k = rand() % (n - 1) + 1;
    printf("%d %d\n", n, k);
    for (i = 0; i < n; i++)
        printf("%d ", rand() % M);
}