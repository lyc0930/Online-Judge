#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

void operate(int Operations[10][10], int Clock2[10], int opNum, int opCount)
{
    for (int i = 1; i <= 9; i++)
    {
        Clock2[i] += Operations[opNum][i] * opCount;
        Clock2[i] %= 4;
    }
}

int main(void)
{
    int Clock1[10];
    int Clock2[10];
    int minTimes = 28;
    int OperateTimes[10];
    int minOperateTimes[10];
    int Move_123[64][3];
    int Operations[10][10] =
        {
            {0},
            //  A, B, C, D, E, F, G, H, I
            {0, 1, 1, 0, 1, 1, 0, 0, 0, 0}, // ABDE
            {0, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // ABC
            {0, 0, 1, 1, 0, 1, 1, 0, 0, 0}, // BCEF
            {0, 1, 0, 0, 1, 0, 0, 1, 0, 0}, // ADG
            {0, 0, 1, 0, 1, 1, 1, 0, 1, 0}, // BDEFH
            {0, 0, 0, 1, 0, 0, 1, 0, 0, 1}, // CFI
            {0, 0, 0, 0, 1, 1, 0, 1, 1, 0}, // DEGH
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 1}, // GHI
            {0, 0, 0, 0, 0, 1, 1, 0, 1, 1}, // EFHI
        };

    for (int i = 0; i < 64; i++)
    {
        int num = i;
        for (int j = 2; j >= 0; j--)
        {
            Move_123[i][j] = num % 4;
            num = num / 4;
        }
    }//对123这三种操作进行枚举

    for (int x = 1; x <= 9; x++)
        cin >> Clock1[x];

    for (int i = 0; i < 64; i++)
    {

        memcpy(Clock2, Clock1, sizeof(int) * 10);

        memset(OperateTimes, 0, sizeof(int) * 10);

        for (int j = 1; j <= 3; j++)
        {
            OperateTimes[j] = Move_123[i][3 - j];
            operate(Operations, Clock2, j, OperateTimes[j]);
        }

        for (int j = 4; j <= 6; j++)
        {
            OperateTimes[j] = (4 - Clock2[j - 3]) % 4;
            operate(Operations, Clock2, j, OperateTimes[j]);
        }

        OperateTimes[7] = (4 - Clock2[4]) % 4;
        operate(Operations, Clock2, 7, OperateTimes[7]);

        OperateTimes[9] = (4 - Clock2[6]) % 4;
        operate(Operations, Clock2, 9, OperateTimes[9]);

        if (Clock2[5] == 0 && Clock2[7] == Clock2[8] && Clock2[8] == Clock2[9])
        {
            OperateTimes[8] = (4 - Clock2[7]) % 4;
            int tem = 0;
            for (int i = 1; i <= 9; i++)
                tem += OperateTimes[i];
            if (tem < minTimes)
            {
                minTimes = tem;
                memcpy(minOperateTimes, OperateTimes, sizeof(int) * 10);
            }
        }
    }

    vector<int> result;
    for (int i = 1; i <= 9; i++)
    {
        while (minOperateTimes[i]--)
        {
            result.push_back(i);
        }
    }
    sort(result.begin(), result.end());
    vector<int>::iterator it;
    for (it = result.begin(); it != result.end(); it++)
        cout << *it << ' ';
    cout << endl;

    getchar();
    getchar();

    return 0;
}