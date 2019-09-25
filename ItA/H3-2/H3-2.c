// 考试成绩
// 1 <= n <= 2500000
// 0 <= id[i] <= 2500000
// 0 <= math[i] <= 100
// 0 <= english[i] <= 100

#include <stdio.h>

#define AND &&
#define OR ||
#define NOT !
#define MOD %
#define N 2500000

typedef struct StudentScore
{
    int ID;
    unsigned short total;
    unsigned short math;
    unsigned short english;
} Student;

Student A[N];

void QuickSort_Records(Student array[], int left, int right)
{
    int i = left;
    int j = right;
    Student key = array[left];
    if (left >= right)
        return;
    while (i < j)
    {
        while (
            (i < j)
                AND(
                    (key.total < array[j].total)
                        OR(
                            (key.total == array[j].total)
                                AND(
                                    (key.math < array[j].math)
                                        OR(
                                            (key.math == array[j].math)
                                                AND(
                                                    (key.english < array[j].english)
                                                        OR(
                                                            (key.english == array[j].english)
                                                                AND(key.ID <= array[j].ID))))))))
            j--;
        array[i] = array[j];
        while (
            (i < j)
                AND(
                    (array[i].total < key.total)
                        OR(
                            (array[i].total == key.total)
                                AND(
                                    (array[i].math < key.math)
                                        OR(
                                            (array[i].math == key.math)
                                                AND(
                                                    (array[i].english < key.english)
                                                        OR(
                                                            (array[i].english == key.english)
                                                                AND(array[i].ID <= key.ID))))))))
            i++;
        array[j] = array[i];
    }
    array[i] = key;
    QuickSort_Records(array, left, i - 1);
    QuickSort_Records(array, i + 1, right);
    return;
}

int main()
{
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d %hu %hu", &A[i].ID, &A[i].math, &A[i].english);
        A[i].total = A[i].math + A[i].english;
    }
    // for (i = n; i > 0; i--)
    // {
    //     printf("%d ", A[i - 1].ID);
    //     printf("%hu %hu %hu\n", A[i - 1].total, A[i - 1].math, A[i - 1].english);
    // }
    QuickSort_Records(A, 0, n - 1);
    for (i = n; i > 0; i--)
    {
        printf("%d ", A[i - 1].ID);
        // printf("%hu %hu %hu\n", A[i - 1].total, A[i - 1].math, A[i - 1].english);
    }
}