// 实数高精度加法
#include <stdio.h>
#include <string.h>
#define AND &&
#define OR ||
#define NOT !
#define MOD %
#define DIGIT 100

char* HAA_Plus(char* a,char* b)
{
    int i,j;
    int n_a = strlen(a), n_b = strlen(b);
    char static resort[DIGIT + 2];

    memset(resort, 0, sizeof(resort));

    for (i = 0; i < n_b; i++)//resort[0]用于存储长度
        resort[i + 1] += a[i] + b[i] - 2 * '0';

    for (; i < n_a; i++)
        resort[i + 1] += a[i] - '0';

    for (j = 1; j <= n_a;j++)
    {
        if (resort[j]>=10)
        {
            resort[j + 1] += resort[j] / 10;
            resort[j] %= 10;
        }
    }
    if (resort[i+1])
        resort[0] = i;
    else
        resort[0] = i - 1;
    return (resort);
}

char* HAA_Plus_f(char* a,char* b)
{
    int i;
    int n_a = strlen(a), n_b = strlen(b);
    char static resort[DIGIT + 2];

    for (i = 0; i < n_b; i++)
        resort[i] = a[i] + b[i] - 2 * '0';

    for (; i < n_a; i++)
        resort[i] = a[i] - '0';

    for (i = n_a - 1; i > 0; i--)
    {
        if (resort[i]>=10)
        {
            resort[i-1]++;
            resort[i]-=10;
        }
    }
    return (resort);
}

int main()
{
    int i,j,n_Alength,n_maxofdec;
    int n_1int, n_2int;
    int n_1dec, n_2dec;
    char c_temp;
    char s_1integer[DIGIT + 2] = "", s_2integer[DIGIT + 2] = "";
    char s_integer_temp[DIGIT + 2] = "";
    char s_1decimal[DIGIT + 2] = "", s_2decimal[DIGIT + 2] = "";
    char* s_AInteger;
    char* s_ADecimal;

    //分节输入
    for (n_1int = 0; (c_temp=getchar()) != '.'; n_1int++)
        s_integer_temp[n_1int] = c_temp;
    for (i = n_1int - 1, j = 0; i >= 0; i--)
        s_1integer[j++] = s_integer_temp[i];
    gets(s_1decimal);
    n_1dec = strlen(s_1decimal);

    for (n_2int = 0; (c_temp=getchar()) != '.'; n_2int++)
        s_integer_temp[n_2int] = c_temp;
    for (i = n_2int - 1, j = 0; i >= 0; i--)
        s_2integer[j++] = s_integer_temp[i];
    gets(s_2decimal);
    n_2dec = strlen(s_2decimal);
/*
    putchar('\n');
    puts(s_1integer);
    puts(s_1decimal);
    puts(s_2integer);
    puts(s_2decimal);
    putchar('\n');
*/
    //整数部分相加
    if (n_1int>=n_2int)
        s_AInteger=HAA_Plus(s_1integer, s_2integer);
    else
        s_AInteger=HAA_Plus(s_2integer, s_1integer);


    //小数部分相加
    if (n_1dec>=n_2dec)
    {
        n_maxofdec = n_1dec;
        s_ADecimal=HAA_Plus_f(s_1decimal, s_2decimal);
    }
    else
    {
        n_maxofdec = n_2dec;
        s_ADecimal=HAA_Plus_f(s_2decimal, s_1decimal);
    }

    if (s_ADecimal[0]>=10)
        {
            s_AInteger[1]++;//flag
            s_ADecimal[0]-=10;
        }

    for (i=1;s_AInteger[i]>=10;i++)
    {
        s_AInteger[i+1]++;
        s_AInteger[i]-=10;
    }

    n_Alength = (s_AInteger[0] > i - 1) ? s_AInteger[0] : (i - 1);

    for (j = n_Alength; j >= 0;j--)
        putchar(s_AInteger[j + 1]+'0');
    putchar('.');

    for (j = n_maxofdec - 1; j >= 0;j--)
        if (s_ADecimal[j])
            break;
    for (i = 0; i <= j;i++)
        putchar(s_ADecimal[i] + '0');

//    getchar();
    return (0);
}