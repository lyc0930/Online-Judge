// Highest Label Preflow Push
#include <algorithm>
#include <climits>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#define N 501

using namespace std;

// 链式前向星
struct edge
{
    int to;       // 终点
    int capacity; // 容量
    int nextEdge; // 下一条相同起点边的下标
    edge(int to, int capacity, int nextEdge) : to(to), capacity(capacity), nextEdge(nextEdge)
    {
    }
};
vector<edge> Edge_from[N];           // 相同起点的边
vector<int> Nodes_with_Height_of[N]; // 具有同一高度的结点
list<int> _Nodes_with_Height_of[N];  // 具有同一高度的结点，加速插入删除
vector<int> Height;                  // 结点的高度
vector<int> Gap;                     // 同一高度的结点数
vector<int> Queue;                   // 一个以高度为键值的优先队列，每次都推流高度最高的节点。
vector<int> ExcessFlow;              // 超额流
vector<list<int>::iterator> Iterator;

int highest;   // 最高高度
int nowHeight; // 当前高度

int n; // 点数
int m; // 边数
int s; // 源点
int t; // 汇点

/*
    重贴标签，提升处于盆地的结点的高度
    相比于ISAP的层数偏移，一次可以抬高不止一个单位高度，且一般使得其中的流量恰好能流向下一个结点
    并且标签的重贴是全图的，减少了BFS的次数以提高效率，且不需要实际实现优先队列
*/
void Relabel()
{
    Height.assign(n + 1, n + 1);
    Height[t] = 0;
    Gap.assign(n + 1, 0);
    Queue.clear();
    Queue.resize(n + 2);
    int rear = 1;
    Queue[0] = t;
    // 全局的标签重置
    for (int head = 0; head < rear; head++)
    {
        int u = Queue[head];
        for (vector<edge>::iterator i = Edge_from[u].begin(); i != Edge_from[u].end(); i++)
        {
            if (Height[i->to] == n + 1 && Edge_from[i->to][i->nextEdge].capacity > 0)
            {
                Height[i->to] = Height[u] + 1;
                Gap[Height[i->to]]++;
                Queue[rear] = i->to;
                rear++;
            }
        }
    }
    for (int i = 0; i <= n + 1; i++)
    {
        Nodes_with_Height_of[i].clear();
        _Nodes_with_Height_of[i].clear();
    }
    for (int u = 0; u <= n; u++)
    {
        if (Height[u] <= n)
        {
            Iterator[u] = _Nodes_with_Height_of[Height[u]].insert(_Nodes_with_Height_of[Height[u]].begin(), u);
            if (ExcessFlow[u] > 0)
                Nodes_with_Height_of[Height[u]].push_back(u);
        }
    }
    highest = nowHeight = Height[Queue[rear - 1]]; // 队尾此时为最高
}

/*
    将结点u存储的超额流向后向边推送
*/
void Push_to_Edge(int u, edge &e)
{
    int flow = min(ExcessFlow[u], e.capacity);
    e.capacity -= flow;
    Edge_from[e.to][e.nextEdge].capacity += flow;
    ExcessFlow[u] -= flow;
    ExcessFlow[e.to] += flow;
    if (0 < ExcessFlow[e.to] && ExcessFlow[e.to] <= flow)
        Nodes_with_Height_of[Height[e.to]].push_back(e.to);
}

/*
    将一个结点存储的超额流传递给与其直接相邻的结点
    相比于增广路径，侧重于修改当前点的流量，尽量地清空超额流
*/
void Push(int u)
{
    int newHeight = n + 1;
    for (vector<edge>::iterator i = Edge_from[u].begin(); i != Edge_from[u].end(); i++)
    {
        if (i->capacity > 0)
        {
            if (Height[u] == Height[i->to] + 1)
            {
                Push_to_Edge(u, *i);
                if (ExcessFlow[u] == 0)
                    return;
            }
            else
                newHeight = min(newHeight, Height[i->to] + 1);
        }
    }
    if (Gap[Height[u]] == 1) // 断层
    {
        for (int i = Height[u]; i <= highest; i++)
        {
            for (list<int>::iterator j = _Nodes_with_Height_of[i].begin(); j != _Nodes_with_Height_of[i].end(); j++)
            {
                Gap[Height[*j]]--;
                Height[*j] = n + 1;
            }
            _Nodes_with_Height_of[i].clear();
        }
        // 删除从Height[u]一直到当前的最高高度highest之间所有的结点
        highest = Height[u] - 1; // 更新最高高度
    }
    else
    {
        Gap[Height[u]]--;
        Iterator[u] = _Nodes_with_Height_of[Height[u]].erase(Iterator[u]);
        Height[u] = newHeight;
        if (newHeight == n + 1)
            return;
        Gap[newHeight]++;
        Iterator[u] = _Nodes_with_Height_of[newHeight].insert(_Nodes_with_Height_of[newHeight].begin(), u);
        nowHeight = newHeight;
        highest = max(highest, nowHeight);
        Nodes_with_Height_of[newHeight].push_back(u);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> s >> t;
    for (int i = m; i > 0; i--)
    {
        int u, v, l;
        cin >> u >> v >> l;
        Edge_from[u].push_back(edge(v, l, Edge_from[v].size()));     // 添加从u到v容量为l的有向边
        Edge_from[v].push_back(edge(u, 0, Edge_from[u].size() - 1)); // 添加从v到u容量为0的反向边
    }
    int maxFlow;
    if (s == t)
        maxFlow = 0;
    else
    {
        nowHeight = 0;
        highest = 0;
        Height.assign(n + 1, 0);
        Height[s] = n + 1;
        Iterator.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            if (i != s)
                Iterator[i] = _Nodes_with_Height_of[Height[i]].insert(_Nodes_with_Height_of[Height[i]].begin(), i);
        }
        Gap.assign(n + 1, 0);
        Gap[0] = n;
        ExcessFlow.assign(n + 1, 0);
        ExcessFlow[s] = INT_MAX;
        ExcessFlow[t] = -INT_MAX; // 防止溢出
        for (int i = 0; i < (int)Edge_from[s].size(); i++)
            Push_to_Edge(s, Edge_from[s][i]);
        Relabel(); // 重贴标签
        for (int u; nowHeight >= 0;)
        {
            if (Nodes_with_Height_of[nowHeight].empty())
            {
                nowHeight--;
                continue;
            }
            u = Nodes_with_Height_of[nowHeight].back();
            Nodes_with_Height_of[nowHeight].pop_back();
            Push(u);
        }
        maxFlow = ExcessFlow[t] + INT_MAX; // 恢复汇点超额流
    }
    cout << maxFlow;
    return 0;
}