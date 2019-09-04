//´«Ö½Ìõ
#include <cstring>
#include <iostream>

using namespace std;

int Max(int a, int b, int c, int d)
{
    int temp = a;
    if (b > temp)
        temp = b;
    if (c > temp)
        temp = c;
    if (d > temp)
        temp = d;
    return (temp);
}

int main()
{
    int n, m;
    cin >> m >> n;

    int Matrix[101][101];
    memset(Matrix, 0, sizeof(Matrix));
    int F[101][101][101];
    memset(F, 0, sizeof(F));

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> Matrix[i][j];

    for (int k = 3; k < m + n; k++)
        for (int x = 1; x <= k; x++)
            for (int p = 1; p <= k; p++)
            {
                if (p == x)
                    continue;
                F[k][x][p] = Max(F[k - 1][x - 1][p - 1], F[k - 1][x - 1][p], F[k - 1][x][p - 1], F[k - 1][x][p]) + Matrix[x][k - x] + Matrix[p][k - p];
                // printf("(%d,%d) (%d,%d) %d\n", x, k - x, p, k - p, F[k][x][p]);
            }
    cout << F[m + n-1][m - 1][m];
    return (0);
}