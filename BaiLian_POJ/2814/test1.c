#include <stdio.h>
#include <string.h>
#define AND &&
#define OR ||
#define NOT !
#define MOD %

int* TentoFour(int n)
{
    int i=9;
    int static resort[10];
    memset(resort, 0, sizeof(resort));
    while (n>=4)
    {
        resort[i] = n MOD 4;
        n /= 4;
        i--;
    }
    resort[i] = n;
    return (resort);
}

int main()
{
    int i,n;
    int* a;
    scanf("%d", &n);
    a = TentoFour(n);
    for (i = 0; i < 10;i++)
    {
        printf("%d", a[i]);
    }
    getchar();
    getchar();
    return (0);

}