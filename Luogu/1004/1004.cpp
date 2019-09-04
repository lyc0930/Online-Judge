//方格取数
#include <cstring>
#include <iostream>
#define N 9
using namespace std;

int Max(int a, int b, int c, int d)
{
    int temp=a;
    if (b>temp)
        temp = b;
    if (c>temp)
        temp = c;
    if (d>temp)
        temp = d;
    return (temp);
}

int main()
{
    int n;
    cin >> n;
    int Map[n + 1][n + 1];
    memset(Map, 0, sizeof(Map));
    int F[n + 1][n + 1][n + 1][n + 1];
    memset(F, 0, sizeof(F));

    for (int x, y, z;;)
    {
        cin >> x >> y >> z;
        if (x + y + z == 0) break;
        Map[x][y] = z;
    }
    F[1][1][1][1] = Map[1][1];

    for (int x = 1; x <= n;x++)
        for (int y = 1; y <= n; y++)
            for (int p = 1; p < x + y;p++)
            {
                int q = x + y - p;
                F[x][y][p][q] = Max(F[x - 1][y][p - 1][q], F[x - 1][y][p][q - 1], F[x][y - 1][p - 1][q], F[x][y - 1][p][q - 1]);
                if (x==p)
                    F[x][y][p][q] += Map[x][y];
                else
                    F[x][y][p][q] += Map[x][y] + Map[p][q];
            }
    cout << F[n][n][n][n];
    return (0);
}