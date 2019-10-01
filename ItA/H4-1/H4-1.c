// 抽奖
// 次序统计量
// 0 < k <= n <= 10^7
// 0 <= A[i] <= 10000

#include <stdio.h>
#include <stdlib.h>

#define N 10000000

typedef unsigned short type;

type A[N + 1] = {0};

void Swap(type *a, type *b)
{
    type temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(type *A, int p, int r)
{
    type x = A[r];
    int i = p - 1, j;
    for (j = p; j < r; j++)
    {
        if (A[j] <= x)
        {
            i++;
            Swap(&A[i], &A[j]);
        }
    }
    Swap(&A[i + 1], &A[r]);
    return i + 1;
}

type Select(type *A, int p, int r, int i)
{
    int q, k;
    if (p == r)
        return A[p];
    q = Partition(A, p, r);
    k = q - p + 1;
    if (i == k)
        return A[q];
    else
    {
        if (i < k)
            return Select(A, p, q - 1, i);
        else
            return Select(A, q + 1, r, i - k);
    }
}

int main()
{
    int k, n;
    int i;

    scanf("%d%d", &n, &k);
    for (i = 0; i < n; i++)
        scanf("%hu", &A[i]);
    printf("%hu", Select(A, 0, n - 1, k));
    return 0;
}
