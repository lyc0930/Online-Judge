// 数字排序1
#include <stdio.h>

#define AND &&
#define OR ||
#define NOT !
#define MOD %
#define N 5000

void QSort(int array[], int left, int right)
{
    int i = left;
    int j = right;
    int key;
    key = array[left];
    if (left >= right)
        return;
    while (i < j)
    {
        while ((i < j) AND(key <= array[j]))
            j--;
        array[i] = array[j];
        while ((i < j) AND(array[i] <= key))
            i++;
        array[j] = array[i];
    }
    array[i] = key;
    QSort(array, left, i - 1);
    QSort(array, i + 1, right);
    return;
}

int main()
{
    int i, n;
    int A[N];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);
    QSort(A, 0, n - 1);
    for (i = 0; i < n; i++)
        printf("%d ", A[i]);
}