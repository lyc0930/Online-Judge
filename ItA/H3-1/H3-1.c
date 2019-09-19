// Êý×ÖÍ³¼Æ
// 1 ¡Ü n ¡Ü 1000
// 1 ¡Ü a[i] ¡Ü 10^9

#include <stdio.h>

#define AND &&
#define OR ||
#define NOT !
#define MOD %
#define N 1000
#define M 1000000000

int A[N] = {0};

void QuickSort(int array[], int left, int right)
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
    QuickSort(array, left, i - 1);
    QuickSort(array, i + 1, right);
    return;
}

int main()
{
    int n, i, j, currentNumber, count;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);

    QuickSort(A, 0, n - 1);

    for (i = n; i >= 0; i--)
    {
        currentNumber = A[0];
        count = 1;
        for (j = 1; j < n; j++)
        {
            if (A[j] != currentNumber)
            {
                if (count == i)
                    printf("%d %d\n", currentNumber, count);
                count = 0;
            }
            currentNumber = A[j];
            count++;
        }
        if (count == i)
            printf("%d %d\n", currentNumber, count);
    }
    return 0;
}