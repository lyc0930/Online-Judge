// 正方形计数
// 0 < n, m <= 2000

#include <algorithm>
#include <iostream>
#define N 2000
#define M 2000
using namespace std;

struct DynamicProgram
{
    int number;    // 以点(i,j)为右下角，可构成的正方形个数
    int column; // 从(i,j)向上连续的0的个数
    int row;    // 从(i,j)向左连续的0的个数
    int total;  // (0,0)->(i,j) 范围内正方形个数
} F[N + 1][M + 1];

int A[N + 1][M + 1];

int Min(const int &x, const int &y, const int &z)
{
    if (y < z)
        return (x < y) ? x : y;
    else
        return (x < z) ? x : z;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    // 下标从1开始，F 0行0列全部为0

    for (int j = 1; j <= m; j++)
    {
        cin >> A[1][j];
        F[1][j].total = F[1][j - 1].total + (1 - A[1][j]);
        F[1][j].number = 1 - A[1][j];
        F[1][j].column = 1 - A[1][j];
        F[1][j].row = (A[1][j] == 1) ? 0 : F[1][j - 1].row + 1;
    }

    for (int i = 2; i <= n; i++)
    {
        cin >> A[i][1];
        F[i][1].total = F[i - 1][1].total + (1 - A[i][1]);
        F[i][1].number = 1 - A[i][1];
        F[i][1].column = (A[i][1] == 1) ? 0 : F[i - 1][1].column + 1;
        F[i][1].row = 1 - A[i][1];

        for (int j = 2; j <= m; j++)
        {
            cin >> A[i][j];
            if (A[i][j] == 0)
            {
                F[i][j].number = Min(F[i - 1][j - 1].number, F[i - 1][j].column, F[i][j - 1].row) + 1;
                F[i][j].column = F[i - 1][j].column + 1;
                F[i][j].row = F[i][j - 1].row + 1;
                F[i][j].total = F[i - 1][j].total + F[i][j - 1].total - F[i - 1][j - 1].total + F[i][j].number;
            }
            else
            {
                F[i][j].number = 0;
                F[i][j].column = 0;
                F[i][j].row = 0;
                F[i][j].total = F[i - 1][j].total + F[i][j - 1].total - F[i - 1][j - 1].total;
            }
        }
    }

    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= m; j++)
    //         cout << F[i][j].total << ' ';
    //     cout << endl;
    // }
    cout << F[n][m].total;

    return 0;
}
