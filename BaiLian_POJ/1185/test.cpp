#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define AND &&
#define OR ||
#define NOT !
#define N 100
#define M 10

using namespace std;

bool Map[N + 1][M + 1];
int F[N + 1][(1 << M) + 1][(1 << M) + 1];
int height, width;

int main()
{

    cin >> height >> width;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            char c;
            cin >> c;
            Map[i][j] = (c == 'P');
        }
    //=========================above: INPUT=============================

    /* for (int i = 0; i < (1 << 10); i++)
    {
        if ((i & (i << 1)) OR(i & (i << 2)))
            continue;
        bit_Table[t++] = i;
    } */

    const int MaxBoundary = 60;
    const int bit_Table[MaxBoundary] = {0, 1, 2, 4, 8, 9, 16, 17, 18, 32, 33, 34, 36, 64, 65, 66, 68, 72, 73, 128, 129, 130, 132, 136, 137, 144, 145, 146, 256, 257, 258, 260, 264, 265, 272, 273, 274, 288, 289, 290, 292, 512, 513, 514, 516, 520, 521, 528, 529, 530, 544, 545, 546, 548, 576, 577, 578, 580, 584, 585};
    //                                  0, 1, 2, 3, 4, 4,  5,      5,  6,          6,  7,                  7,   8,                                      8,   9,                                                          9,  10,                                                                                       10
    //                                  0, 1, 2, 3, 4,     6,          9,             13,                      19,                                          28,                                                              41,
    /*
    Construct an array of specific binary numbers, which have a total of 60 within the 10-bit binary range,
    and every two adjacent number 1s of which are always separated by two or more number 0s.
    */
    const int BoundaryTable[11] = {1, 2, 3, 4, 6, 9, 13, 19, 28, 41, 60};
    int Boundary = BoundaryTable[width];
    //==================above: Determine Enumeration====================

    int ans = 0;
    for (int i = 0; i < height; i++)//loop of every line
    {
        for (int j = 0, cnt = 0; j < Boundary; j++, cnt = 0)
        {
            for (int k = 0; k < width; k++)//loop of every row
            {
                if (((1 << k) & bit_Table[j])) //if the (k+1)th digit of bit_Table[j] is 1.
                    cnt++;
                if ((NOT(Map[i][k]))AND(((1 << (width - k - 1)) & bit_Table[j])))
                //if the (width - k)th digit of bit_Table[j] is 1, and Map[i][k] is Highland.
                {
                    cnt = -1;
                    break;
                }
            }

            if (cnt != -1) //if the FOR loop was not broken abnormally.
            {
                for (int k = 0, now = 0; k < Boundary; k++)
                {
                    if (NOT(bit_Table[k] & bit_Table[j]))
                    {
                        F[i][bit_Table[j]][bit_Table[k]] = cnt;
                        now = 0;
                        for (int q = 0; q < Boundary; q++)
                        {
                            if ((i != 0) AND(NOT(bit_Table[q] & bit_Table[j])))
                                now = max(now, F[i - 1][bit_Table[k]][bit_Table[q]]);
                        }
                    }
                    F[i][bit_Table[j]][bit_Table[k]] += now;
                    if (i == height - 1)
                        ans = max(ans, F[i][bit_Table[j]][bit_Table[k]]);
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}