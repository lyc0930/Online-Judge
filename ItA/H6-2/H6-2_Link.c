// 朋友圈
// 0 < n, m, k <= 5000000

#include <stdio.h>
#include <stdlib.h>
#define N 5000000

typedef int Type;

typedef struct DisjointSetObject
{
    struct DisjointSetObject *parent;
    Type value;
    int rank;
} Object;

Object *A[5000000];

Object *Make_Set(Type x)
{
    Object *o = (Object *)malloc(sizeof(Object));
    o->parent = o;
    o->value = x;
    o->rank = 0;
    return o;
}

void Link(Object *x, Object *y)
{
    if (x->rank > y->rank)
        y->parent = x;
    else
    {
        x->parent = y;
        if (x->rank == y->rank)
            y->rank++;
    }
}

Object *Find_Set(Object *x)
{
    if (x != x->parent)
        x->parent = Find_Set(x->parent);
    return x->parent;
}

void Union(Object *x, Object *y)
{
    Link(Find_Set(x), Find_Set(y));
}

int main()
{
    int n, m, k;
    int i;
    int p, q;
    scanf("%d%d%d", &n, &k, &m);
    for (i = 0; i < m; i++)
    {
        scanf("%d%d", &p, &q);
        A[p] = Make_Set(p);
        A[q] = Make_Set(q);
        Union(A[p], A[q]);
    }
    for (i = 0; i < k; i++)
    {
        scanf("%d%d", &p, &q);
        if ((A[p] != NULL) && (A[q] != NULL) && (Find_Set(A[p]) == Find_Set(A[q])))
            printf("%d ", 1);
        else
            printf("%d ", 0);
    }
    return 0;
}
