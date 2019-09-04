//01����
#include <stdio.h>

#define N 3402
#define M 12880
struct Item
{
    int volume;
    int value;
};

int Max(int x, int y)
{
    if (x > y)
        return (x);
    else
        return (y);
}

int main()
{
    int i, j;
    int n, total_volume;
    struct Item Items[N + 1];
    int F[M + 1];

    scanf("%d%d", &n, &total_volume);
    for (i = 0; i < n; i++)
    {
        scanf("%d%d", &Items[i].volume, &Items[i].value);
    }

    for (j = 1; j <= total_volume; j++)
    {
        if (Items[0].volume <= j)//0对应的是哪一个并不重�?
            F[j] = Items[0].value;
        else
            F[j] = 0;
    }

    for (i = 1; i < n; i++)
    {
        for (j = total_volume; j > 0; j--)
        {
            if (Items[i].volume <= j)
                F[j] = Max(F[j], F[j - Items[i].volume] + Items[i].value);
        }
    }

    printf("%d", F[total_volume]);
    getchar();
    getchar();
    return (0);
}