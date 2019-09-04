//¹ýºÓ×ä
#include <cstring>
#include <iostream>
#define N 20
#define M 20
#define AND &&

using namespace std;

const int Jump[8][2] =
    {
        {1, -2},
        {2, -1},
        {2, 1},
        {1, 2},
        {-1, 2},
        {-2, 1},
        {-2, -1},
        {-1, -2}};

int Map[N + 1][M + 1];
int n, m;
void Initialize(int x, int y)
{
    memset(Map, 0, sizeof(Map));
    Map[x][y] = 1;
    for (int i = 0; i < 8; i++)
    {
        if ((x + Jump[i][0] >= 0) AND(x + Jump[i][0] <= n) AND(y + Jump[i][1] >= 0) AND(y + Jump[i][1] <= m))
            Map[x + Jump[i][0]][y + Jump[i][1]] = 1;
    }
    return;
}
int main()
{
    int x, y;
    long long  F[N + 1][M + 1];
    cin >> n >> m >> x >> y;
    Initialize(x, y);
    Map[0][0] = 1;
    memset(F, 0, sizeof(F));
    F[0][0] = 1;
    for (int i = 0; i <= n;i++)
    {
        for (int j = 0; j <= m;j++)
        {
            if (!Map[i][j])
                F[i][j] = F[i == 0 ? 0 : i - 1][j] + F[i][j == 0 ? 0 : j - 1];
        }
    }
    cout << F[n][m];
    return (0);
}