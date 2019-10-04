// 股票
// 0 < n <= 1000000
// 0 <= A[i] <= 1000000000

#include <stdio.h>
#include <stdlib.h>

#define N 1000000
#define LIMIT 10000019

int A[N], B[N];

int Merge(int *A, int p, int q, int r)
{
    unsigned long count = 0;
    int i, j, k;
    for (i = p, j = q + 1, k = p; i <= q && j <= r; k++)
    {
        if (A[i] <= A[j])
            B[k] = A[i++];
        else
        {
            B[k] = A[j++];
            count += (j - k - 1) % LIMIT; // 实质的逆序数
        }
    }
    while (i <= q)
        B[k++] = A[i++];
    while (j <= r)
        B[k++] = A[j++];
    for (i = p; i <= r; i++)
        A[i] = B[i];
    return (count % LIMIT);
}

int MergeSort(int *A, int p, int r)
{
    int q;
    unsigned long count = 0;
    if (p < r)
    {
        q = (p + r) / 2;

        count += MergeSort(A, p, q) % LIMIT;
        count += MergeSort(A, q + 1, r) % LIMIT;
        count += Merge(A, p, q, r) % LIMIT;
        return count;
    }
    return 0;
}

int main()
{
    int n;
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);
    printf("%d", MergeSort(A, 0, n - 1) % LIMIT);
    return 0;
}