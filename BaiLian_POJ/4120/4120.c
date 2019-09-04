//硬币
#include <stdio.h>
#include <string.h>
#define N 200
#define M 10000

int F[M + 1]; //F[i]表示凑成i元有几种组合

int CalculateTimes(int x, int v) //返回凑成x元，v要用几次
{
    if (x < 0)
        return (0);
    else
        return (F[x] - CalculateTimes(x - v, v));
}

int main()
{
    int i, j, k;
    int n, x;
    int number = 0;
    int a[N + 1], Essential[N + 1];

    scanf("%d%d", &n, &x);

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    F[0] = 1;

    for (i = 0; i < n; i++)
    {
        for (j = x; j >= a[i]; j--)
            F[j] += F[j - a[i]];
        // for (k = 0; k <= x; k++)
        //     printf("%2d ", k);
        // putchar('\n');
        // for (k = 0; k <= x; k++)
        //     printf("%2d ", F[k]);
        // putchar('\n');
    }

    // for (i = 0; i < n;i++)
    //     printf("%2d ", i);
    // putchar('\n');
    // for (i = 0; i < n;i++)
    //     printf("%2d ", CalculateTimes(x - a[i], a[i]));
    // putchar('\n');

    for (i = 0; i < n; i++)
    {
        if (F[x] == CalculateTimes(x - a[i], a[i]))
        {
            Essential[number] = a[i];
            number++;
        }
    }

    printf("%d\n", number);
    for (i = 0; i < number; i++)
        printf("%d ", Essential[i]);

    return (0);
}