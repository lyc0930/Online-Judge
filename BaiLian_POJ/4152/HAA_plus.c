#include <stdio.h>
#include <string.h>
#define DIGIT 50

char *HAA_Plus(char *_a, char *_b)
{
    int i, j;
    int temp;
    int length = 0;
    int n_a = strlen(_a), n_b = strlen(_b);
    char a[DIGIT + 2], b[DIGIT + 2];
    char reverse[DIGIT + 2];
    char static resort[DIGIT + 2];

    if (n_a >= n_b)
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

int main()
{
    char a[DIGIT + 2], b[DIGIT + 2];
    scanf("%s%s", a, b);
    printf("%s + %s = %s", a, b, HAA_Plus(a, b));
    return (0);
}