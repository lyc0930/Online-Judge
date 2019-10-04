#include <limits.h>
#include <stdio.h>
#define N 1000000

int Sequence[N];

int main()
{
    int n, k;
    int i, j;
    int max;
    scanf("%d%d", &n, &k);
    for (i = 0; i < n; i++)
        scanf("%d", &Sequence[i]);
    for (i = 0; i <= n - k; i++)
    {
        max = INT_MIN;
        for (j = i; j < i + k; j++)
        {
            if (Sequence[j] > max)
                max = Sequence[j];
        }
        printf("%d ", max);
    }
    return 0;
}