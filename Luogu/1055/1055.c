// ISBN号码

#include <stdio.h>

int main()
{
    int m, n = 0, i;
    char s[14];
    scanf("%s", s);
    for (i = 1, m = 0; m < 12; m++)
    {
        if (s[m] != '-')
        {
            n = n + i * (s[m] - '0');
            i = i + 1;
        }
    }
    m = n % 11;
    if (m == 10 && s[12] == 'X')
        printf("Right");
    else if (s[12] - '0' == m)
        printf("Right");
    else
    {
        s[12] = '\0';
        if (m == 10)
            printf("%sX", s);
        else
            printf("%s%d", s, m);
    }
    return 0;
}