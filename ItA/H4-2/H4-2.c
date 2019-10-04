//数组排序
//1 <= n <= 10^7
//0 <= a[i] <= 10^9

#include <stdio.h>

#define AND &&
#define OR ||
#define NOT !
#define MOD %
#define N 10000000

typedef int type;

int A[N];

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

void Max_Heapify(type *A, int i, int heap_size, int length)
{
    int l = Left(i);
    int r = Right(i);
    int largest = 0;
    if ((l < heap_size) AND(A[l] > A[i]))
        largest = l;
    else
        largest = i;
    if ((r < heap_size) AND(A[r] > A[largest]))
        largest = r;
    if (largest != i)
    {
        Swap(&A[i], &A[largest]);
        Max_Heapify(A, largest, heap_size, length);
    }
}

void Build_Max_Heap(type *A, int *heap_size, int length)
{
    int i;
    *heap_size = length;
    for (i = length / 2; i >= 0; i--)
        Max_Heapify(A, i, *heap_size, length);
    return;
}

void HeapSort(type *A, int *heap_size, int length)
{
    int i;
    Build_Max_Heap(A, heap_size, length);
    for (i = length - 1; i > 0; i--)
    {
        Swap(&A[0], &A[i]);
        (*heap_size)--;
        Max_Heapify(A, 0, *heap_size, length);
    }
}

int main()
{
    int i, n;
    int A_heap_size;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);
    // QuickSort(A, 0, n - 1);
    HeapSort(A, &A_heap_size, n);
    for (i = 0; i < n; i++)
        printf("%d ", A[i]);
}