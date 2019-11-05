// 内存分配
// 0 < n <= 10^6
// 0 < a_i <= b_i <= 2^30

#include <stdio.h>
#include <stdlib.h>
#define N 1000000

typedef struct Interval
{
    int low;
    int high;
} Interval;

Interval interval[N];

// 判断区间i与区间j是否重叠
int Overlap(Interval i, Interval j)
{
    return (i.low <= j.high && j.low <= i.high);
}

int main()
{
    int i, j, k = 0;
    int n;
    Interval temp;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d%d", &temp.low, &temp.high);
        for (j = 0; j < k; j++)
        {
            if (Overlap(temp,interval[j]))
                break;
        }
        if (j==k)
        {
            interval[k++] = temp;
            printf("0\n");
        }
        else
            printf("-1\n");
    }
    return 0;
}