#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <math.h>
using namespace std;

bool Map[150][15];
int F[110][1 << 11][1 << 11];
int height, width;
const int MaxBoundary = 60;
const int bit_Table[MaxBoundary] = {0, 1, 2, 4, 8, 9, 16, 17, 18, 32, 33, 34, 36, 64, 65, 66, 68, 72, 73, 128, 129, 130, 132, 136, 137, 144, 145, 146, 256, 257, 258, 260, 264, 265, 272, 273, 274, 288, 289, 290, 292, 512, 513, 514, 516, 520, 521, 528, 529, 530, 544, 545, 546, 548, 576, 577, 578, 580, 584, 585};


int check(int x, int state)
{
    int cnt = 0;
    if (state >= pow((int)2, width))
        return -1;
    for (int i = 1; i <= width; i++)
    {
        if (((1 << (i - 1)) & state))
            cnt++;
        if (!Map[x][i])
        {
            if (((1 << (width - i)) & state))
                return -1;
        }
    }
    return cnt;
}
int main()
{

    cin >> height >> width;
    for (int i = 1; i <= height; i++)
        for (int j = 1; j <= width; j++)
        {
            char c;
            cin >> c;
            Map[i][j] = (c == 'P');
        }
    int ans = 0, now;
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= MaxBoundary; j++)
        {
            int cnt = check(i, bit_Table[j]);
            if (cnt != -1)
            {
                //cout<<i<<"  "<<bit_Table[j]<<"  "<<cnt<<endl;
                for (int k = 1; k <= MaxBoundary; k++)
                {
                    if (!(bit_Table[k] & bit_Table[j]))
                    {
                        F[i][bit_Table[j]][bit_Table[k]] = cnt;
                        now = 0;
                        for (int q = 1; q <= MaxBoundary; q++)
                        {
                            if (i == 1)
                                ;
                            else
                            {
                                if (!(bit_Table[q] & bit_Table[j]))
                                    now = max(now, F[i - 1][bit_Table[k]][bit_Table[q]]);
                            }
                        }
                    }
                    F[i][bit_Table[j]][bit_Table[k]] += now;
                    if (i == height)
                        ans = max(ans, F[i][bit_Table[j]][bit_Table[k]]);
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}