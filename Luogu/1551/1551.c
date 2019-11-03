// 亲戚

#include <stdio.h>
#include <stdlib.h>
#define N 5000000

int Parent[N + 1];

int Find_Set(int x)
{
    if (x != Parent[x])
        Parent[x] = Find_Set(Parent[x]);
    return Parent[x];
}

int main()
{
    int n, m, p;
    int i;
    int x, y;
    scanf("%d%d%d", &n, &m, &p);
    for (i = 1; i <= n; i++)
        Parent[i] = i;
    for (i = 0; i < m; i++)
    {
        scanf("%d%d", &x, &y);
        Parent[Find_Set(x)] = Find_Set(y);
    }
    for (i = 0; i < p; i++)
    {
        scanf("%d%d", &x, &y);
        if (Find_Set(x) == Find_Set(y))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}