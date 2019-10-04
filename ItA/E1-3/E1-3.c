// 弹幕游戏
// 0 < n <= 10^7
// 0 <= a[i] <= 10^9

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10000000

typedef struct
{
    int maximum, minimum; // 桶内元素最值
    unsigned int count;   // 桶内元素数
} bucket;

int A[N];

int main()
{
    bucket *Buckets;
    unsigned int n;
    int i, j;
    int max = INT_MIN, min = INT_MAX;
    int bucketSize;
    int bucketNumber;
    int tempIndex;
    int maxDiam = INT_MIN; // 题所求最大直径

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
        if (A[i] > max)
            max = A[i];
        if (A[i] < min)
            min = A[i];
    }
    bucketSize = (max - min) / n;                 // 桶的大小
    bucketSize = bucketSize > 0 ? bucketSize : 1; // 保证桶的大小是正值
    bucketNumber = (max - min) / bucketSize + 1;  // 计算桶的个数
    Buckets = (bucket *)malloc((bucketNumber) * sizeof(bucket));

    // for (i = 0; i < bucketNumber; i++)
    // {
    //     Buckets[i].count = 0; // 各桶的成员初始化
    //     Buckets[i].maximum = INT_MIN;
    //     Buckets[i].minimum = INT_MAX;
    // }

    for (i = 0; i < n; i++)
    {
        tempIndex = (A[i] - min) / bucketSize;
        Buckets[tempIndex].count++;
        if (A[i] > Buckets[tempIndex].maximum)
            Buckets[tempIndex].maximum = A[i];
        if (A[i] < Buckets[tempIndex].minimum || Buckets[tempIndex].minimum == 0)
            Buckets[tempIndex].minimum = A[i];
    }
    for (i = 0; (i < n) && (Buckets[i].count <= 0); i++) // 找到第一个非空桶
        ;
    for (; i < bucketNumber; i = j)
    {
        for (j = i + 1; (j <= bucketNumber) && (Buckets[j].count <= 0); j++) // 找到后一个非空桶
            ;
        if (Buckets[j].minimum - Buckets[i].maximum > maxDiam)
            maxDiam = Buckets[j].minimum - Buckets[i].maximum;
    }
    printf("%d", maxDiam);
    return 0;
}