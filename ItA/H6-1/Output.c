#include <limits.h>
#include <stdio.h>
#define N 2000000

int A[N];
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
        while ((i < j) && (key <= array[j]))
            j--;
        array[i] = array[j];
        while ((i < j) && (array[i] <= key))
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
    int n;
    int i, j;
    char command;
    int k;
    scanf("%d", &n);
    int m = 0, number_zero = 0;
    for (i = 0; i < n; i++)
    {
        getchar();
        scanf("%c %d", &command, &k);
        if (command == 'I')
        {
            A[m] = k;
            QuickSort(A, number_zero, m);
            m++;
        }
        else if (command == 'D')
        {
            for (j = 0; j < m && A[j] != k; j++)
                ;
            A[j] = 0;
            QuickSort(A, number_zero, m - 1);
            number_zero++;
        }
        else if (command == 'K')
            printf("%d\n", A[k - 1 + number_zero]);
    }
    return 0;
}