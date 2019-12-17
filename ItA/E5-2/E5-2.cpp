// Dijkstra
#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#define N 100000
#define M 1000000

using namespace std;

struct edge
{
    int to;       // 终点
    int length;   // 边的长度
    int nextEdge; // 下一条相同起点边的下标
} Edge[M];        // 边

int FirstEdgeFrom[N]; // 以结点作为起点的边的下标
int Distance[N];      // s到结点的距离
bool IfVisited[N];

struct queueNode
{
    int position; // 结点
    int distance; // 距离

    // 重载操作符，权重和距离成反比
    bool operator<(const queueNode &that) const
    {
        return this->distance > that.distance;
    }
};

priority_queue<queueNode> Q;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, s, t;
    cin >> n >> m >> s >> t;

    for (int i = 1; i <= n; ++i)
        Distance[i] = INT_MAX;

    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        Edge[i].length = w;
        Edge[i].to = v;
        Edge[i].nextEdge = FirstEdgeFrom[u]; // 下一条以u为起点的边
        FirstEdgeFrom[u] = i;                // 更新以u为起点的边
    }

    Distance[s] = 0;
    Q.push((queueNode){s, 0});
    while (!Q.empty())
    {
        int x = Q.top().position; // 队头结点
        Q.pop();
        if (IfVisited[x]) // 已被访问过
            continue;
        IfVisited[x] = true;
        for (int i = FirstEdgeFrom[x]; i != 0; i = Edge[i].nextEdge) // 遍历以x为起点的边
        {
            int y = Edge[i].to; // 边的终点
            if (Distance[y] > Distance[x] + Edge[i].length)
            {
                Distance[y] = Distance[x] + Edge[i].length;
                if (!IfVisited[y])
                    Q.push((queueNode){y, Distance[y]});
            }
        }
    }

    if (Distance[t] == INT_MAX)
        cout << -1;
    else
        cout << Distance[t];

    return 0;
}