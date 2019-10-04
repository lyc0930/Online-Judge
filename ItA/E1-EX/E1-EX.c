// E1 - EX 银行卡 0 < k < n <= 1000000

#include <stdio.h>
#define N 1000000
typedef struct
{
    int value;
    int index;
} type;

type Sequence[N];
type PriorQueue[N];
int n, k, heap_size;

void Swap(type *a, type *b)
{
    type temp = *a;
    *a = *b;
    *b = temp;
    return;
}

int Parent(int i)
{
    return ((i - 1) / 2);
}

int Left(int i)
{
    return (2 * i + 1);
}

int Right(int i)
{
    return (2 * i + 2);
}

type Heap_Maximum(type *A)
{
    return A[0];
}

void Max_Heapify(type *A, int i)
{
    int l = Left(i);
    int r = Right(i);
    int largest = 0;
    if ((l < heap_size) && (A[l].value > A[i].value))
        largest = l;
    else
        largest = i;
    if ((r < heap_size) && (A[r].value > A[largest].value))
        largest = r;
    if (largest != i)
    {
        Sequence[A[i].index].index = largest;
        Sequence[A[largest].index].index = i;

        Swap(&A[i], &A[largest]);

        Max_Heapify(A, largest);
    }
    return;
}

void Build_Max_Heap(type *A)
{
    int i;
    for (i = k / 2; i >= 0; i--)
        Max_Heapify(A, i);
    return;
}

void Heap_Change_Key(type *A, int i, type key)
{
    if (A[i].value == key.value)
        return;
    else if (key.value < A[i].value)
    {
        A[i].value = key.value;
        Max_Heapify(A, i);
    }
    else
    {
        A[i].value = key.value;
        while (i > 0 && A[Parent(i)].value < A[i].value)
        {
            Sequence[A[i].index].index = Parent(i);
            Sequence[A[Parent(i)].index].index = i;

            Swap(&A[i], &A[Parent(i)]);

            i = Parent(i);
        }
    }
    return;
}

int main()
{
    int i;
    scanf("%d%d", &n, &k);
    heap_size = k;
    for (i = 0; i < k; i++)
    {
        scanf("%d", &Sequence[i].value);
        Sequence[i].index = i;
        PriorQueue[i] = Sequence[i];
    }

    Build_Max_Heap(PriorQueue);
    printf("%d ", Heap_Maximum(PriorQueue).value);
    for (; i < n; i++)
    {
        scanf("%d", &Sequence[i].value);
        Sequence[i].index = Sequence[i - k].index;
        PriorQueue[Sequence[i - k].index].index = i;
        Heap_Change_Key(PriorQueue, Sequence[i - k].index, Sequence[i]);
        printf("%d ", Heap_Maximum(PriorQueue).value);
    }
    return 0;
}