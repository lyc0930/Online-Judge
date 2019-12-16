// Kruskal
#include <algorithm>
#include <iostream>
#define N 100000
#define M 1000000

using namespace std;

struct edge
{
    int u, v, w;

    bool operator<(const struct edge that) const
    {
        return this->w < that.w;
    }
} Edge[M + 1];

int Parent[N + 1];

int Find_Set(int x)
{
    if (x != Parent[x])
        Parent[x] = Find_Set(Parent[x]);
    return Parent[x];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, answer = 0;

    cin >> n >> m;

    for (int i = 0; i < m; i++)
        cin >> Edge[i].u >> Edge[i].v >> Edge[i].w;

    for (int i = 1; i <= n; i++) // 注意到城市的表示从1到N
        Parent[i] = i;

    sort(Edge, Edge + m);

    for (int i = 0, edgeCount = 0; i < m; i++)
    {
        int set_u = Find_Set(Edge[i].u), set_v = Find_Set(Edge[i].v);
        if (set_u == set_v) // 出现环
            continue;
        edgeCount++;
        answer += Edge[i].w;
        Parent[set_v] = set_u;  // 合并set_u与set_v
        if (edgeCount == n - 1) // 生成树边数为结点数减1
            break;
    }

    cout << answer;
    return 0;
}