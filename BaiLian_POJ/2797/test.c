#include<stdio.h>
int main()
{
    int i;
    for (i = 0; i < 65536;i++)
        printf("%d  ", i & 0x7FFFFFFF);
    getchar();
    return (0);
}