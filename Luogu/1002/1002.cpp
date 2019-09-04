//¹ýºÓ×ä
#include <iostream>
#include <cstring>
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
        {-1, -2}
    };

int Map[N + 1][M + 1];
long long ans = 0;
int n, m;
void Initialize(int x, int y)
{
    memset(Map, 0, sizeof(Map));
    Map[x][y] = 1;
    for (int i = 0; i < 8;i++)
    {
        if ((x+Jump[i][0]>=0) AND (x + Jump[i][0] <= n) AND(y + Jump[i][1] >= 0) AND (y + Jump[i][1] <= m))
            Map[x + Jump[i][0]][y + Jump[i][1]] = 1;
    }
    return;
}

void Solve(int x,int y)
{
    if ((x==n) AND (y==m))
    {
        ans++;
        return;
    }
    if (Map[x][y]==1)
        return;
    if (x<n)
        Solve(x + 1, y);
    if (y<m)
        Solve(x, y + 1);
    return;
}
int main()
{
    int x, y;
    cin >> n >> m >> x >> y;
    Initialize(x, y);
    Solve(0, 0);
    cout << ans;
    getchar();
    getchar();
    return (0);
}