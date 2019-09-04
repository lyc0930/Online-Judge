//≤¶÷”Œ Ã‚
#include <stdio.h>
#include <string.h>
#define AND &&
#define OR ||
#define NOT !
#define MOD %

int Clock1[10] = {0};
int Clock2[10] = {0};
int Operations[10][10] =
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0 for number of every operations
                                        //   0, A, B, C, D, E, F, G, H, I
        {0, 1, 1, 0, 1, 1, 0, 0, 0, 0}, // 1 ABDE
        {0, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 2 ABC
        {0, 0, 1, 1, 0, 1, 1, 0, 0, 0}, // 3 BCEF
        {0, 1, 0, 0, 1, 0, 0, 1, 0, 0}, // 4 ADG
        {0, 0, 1, 0, 1, 1, 1, 0, 1, 0}, // 5 BDEFH
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 1}, // 6 CFI
        {0, 0, 0, 0, 1, 1, 0, 1, 1, 0}, // 7 DEGH
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1}, // 8 GHI
        {0, 0, 0, 0, 0, 1, 1, 0, 1, 1}, // 9 EFHI
};

void Poke(int number, int times)
{
    int i;
    for (i = 1; i <= 9; i++)
    {
        Clock2[i] += times * Operations[number][i];
        Clock2[i] %= 4;
    }
    return;
}

int *TentoFour(int n)
{
    int i = 9;
    int static resort[10];
    memset(resort, 0, sizeof(resort));
    while (n >= 4)
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
    int i, j;
    int min_times = 28; //Minimum number of operations
    int min_operations[10] = {0};
    int temp = 0; //temptation number of operations
    int flag = 0; //the final check
    for (i = 1; i < 10; i++)
        scanf("%d", &Clock1[i]);

    for (i = 0; i < 262144; i++)
    {
        memcpy(Operations[0], TentoFour(i), 10 * sizeof(int));
        memcpy(Clock2, Clock1, 10 * sizeof(int));
        temp = 0;
        flag = 0;
        for (j = 1; j < 10; j++) //loop of operations
        {
            Poke(j, Operations[0][j]);
            temp += Operations[0][j];
        }

        for (j = 1; j < 10; j++) //loop of clocks
            flag += Clock2[j];

        if ((flag == 0) AND(temp < min_times))
        {
            min_times = temp;
            memcpy(min_operations, Operations[0], 10 * sizeof(int));
        }
    }
    flag = min_times;
    for (i = 1; i < 10; i++)
    {
        for (j = 0; j < min_operations[i]; j++)
        {
            if (flag == min_times)
                printf("%d", i);
            else
                printf(" %d", i);
            flag--;
        }
    }
    putchar('\n');
    getchar();
    getchar();
    return (0);
}