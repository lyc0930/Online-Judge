//最佳加法表达式
#include <stdio.h>
#include <string.h>
#define DIGIT 50
#define TRUE 1
#define FALSE 0

char *HAA_Plus(char *_a, char *_b)
{
    int i, j;
    int temp;
    int length = 0;
    int n_a = strlen(_a), n_b = strlen(_b);
    char a[DIGIT + 2], b[DIGIT + 2];
    char reverse[DIGIT + 2];
    char static resort[DIGIT + 2];

    if (n_a > n_b)
    {
        for (i = 0; i < n_a; i++)
            a[i] = _a[n_a - i - 1];
        for (i = 0; i < n_b; i++)
            b[i] = _b[n_b - i - 1];
    }

    else
    {
        for (i = 0; i < n_a; i++)
            b[i] = _a[n_a - i - 1];
        for (i = 0; i < n_b; i++)
            a[i] = _b[n_b - i - 1];
        temp = n_a;
        n_a = n_b;
        n_b = temp;
    }

    memset(reverse, 0, sizeof(reverse));

    for (i = 0; i < n_b; i++)
        reverse[i] += a[i] + b[i] - 2 * '0';

    for (; i < n_a; i++)
        reverse[i] += a[i] - '0';

    for (j = 0; j < n_a; j++)
    {
        if (reverse[j] >= 10)
        {
            reverse[j + 1] += reverse[j] / 10;
            reverse[j] %= 10;
        }
    }

    if (reverse[i] != 0)
        length = i + 1;
    else
        length = i;

    for (i = 0; i < length; i++)
        resort[i] = reverse[length - i - 1] + '0';
    resort[i] = '\0';
    return (resort);
}

int Compare(char *a, char *b) //a>b?
{
    int i = 0;
    if (strlen(a) != strlen(b))
    {
        if (strlen(a) > strlen(b))
            return (1);
        else
            return (-1);
    }
    else
    {
        for (i = 0; i < strlen(a); i++)
        {
            if (a[i] > b[i])
                return (1);
            if (a[i] < b[i])
                return (-1);
        }
    }
    return (0);
}

int main()
{
    int i, j, k;
    // int x, y;
    int m, n;
    char Sequence[DIGIT + 2];
    char s_temp1[DIGIT + 2];
    char F[DIGIT + 2][DIGIT + 2][DIGIT + 2];
    char *s_temp2;



    while (scanf("%d", &m) != EOF)
    {
        memset(F, 0, sizeof(F));
        scanf("%s", Sequence);
        n = strlen(Sequence);

        for (i = 0; i < n; i++)
        {
            memcpy(F[i][0], Sequence + i, n - i);
            F[i][0][n - i] = '\0';
        }

        for (i = n - 1; i >= 0; i--)
        {
            for (j = 1; j < n - i; j++)
            {
                for (k = 1; ((i + k) + (j - 1)) < n; k++)
                {
                    memcpy(s_temp1, Sequence + i, k);
                    s_temp1[k] = '\0';
                    s_temp2 = HAA_Plus(F[i + k][j - 1], s_temp1);
                    // printf("i=%d, j=%d, k=%d, %s + %s = %s\n", i, j, k, F[i + k][j - 1], s_temp1, s_temp2);
                    // for (x = 0; x < n; x++)
                    // {
                    //     for (y = 0; y <= m; y++)
                    //     {
                    //         printf("F[%d][%d]=%s ", x, y, F[x][y]);
                    //     }
                    //     putchar('\n');
                    // }

                    if (F[i][j][0] == '\0')
                        memcpy(F[i][j], s_temp2, (DIGIT+2)*sizeof(char));
                    else if (Compare(s_temp2, F[i][j]) < 0)
                        memcpy(F[i][j], s_temp2, (DIGIT+2)*sizeof(char));
                }
            }
        }

        // for (i = 0; i < n; i++)
        // {
        //     for (j = 0; j <= m; j++)
        //     {
        //         if (i+j>=n)
        //             continue;
        //         printf("F[%d][%d]=%s ", i, j, F[i][j]);
        //     }
        //     putchar('\n');
        // }
        puts(F[0][m]);
    }
    return (0);
}