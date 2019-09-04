//À„24µ„
#include <math.h>
#include <stdio.h>

#define AND &&
#define OR ||
#define NOT !
#define MOD %
#define TRUE 1
#define FALSE 0

double Plus(double x, double y)
{
    return (x + y);
}

double Minus_1(double x, double y)
{
    return (x - y);
}

double Minus_2(double x, double y)
{
    return (y - x);
}

double Times(double x, double y)
{
    return (x * y);
}

double Divide_1(double x, double y)
{
    if ((y - 0) < 1E-6)
        return (-1);
    else
        return (x / y);
}

double Divide_2(double x, double y)
{
    if ((x - 0) < 1E-6)
        return (-1);
    else
        return (y / x);
}

double (*p_Function[6])(double, double) = {&Plus, &Minus_1, &Minus_2, &Times, &Divide_1, &Divide_2};

int Judge(double *Numbers, int n)
{
    int i, j, k, m;
    double Next_Numbers[4];

    // printf("%d: ", n);
    // for (t = 0; t < n; t++)
    // {
    //     printf("%.2lf ", Numbers[t]);
    // }
    // putchar('\n');
    // putchar('\n');

    if (n == 1)
    {
        if (fabs(Numbers[0] - 24) <= 1E-6)
            return (TRUE);
        else
            return (FALSE);
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            for (k = 0, m = 0; k < n; k++)
            {
                if ((k != i) AND(k != j))
                {
                    Next_Numbers[m] = Numbers[k];
                    m++;
                }
            }
            for (k = 0; k < 6; k++)
            {
                if (((k == 4) AND((Numbers[j] - 0) < 1E-6)) OR((k == 5) AND((Numbers[i] - 0) < 1E-6)))
                    break;

                Next_Numbers[m] = p_Function[k](Numbers[i], Numbers[j]);
                // printf("%d: %.2lf %.2lf=%.2lf\n", m+1,Numbers[i], Numbers[j], Next_Numbers[m]);

                if (Judge(Next_Numbers, m + 1) == TRUE)
                    return (TRUE);
            }
        }
    }
    return (FALSE);
}

int main()
{
    int i;
    double flag = 0;
    double Numbers[4];
    for (i = 0; i < 4; i++)
    {
        scanf("%lf", &Numbers[i]);
        flag += Numbers[i];
    }
    while (NOT((flag - 0) <= 1E-6))
    {
        if (Judge(Numbers, 4) == TRUE)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
        flag = 0;
        for (i = 0; i < 4; i++)
        {
            scanf("%lf", &Numbers[i]);
            flag += Numbers[i];
        }
    }
}
