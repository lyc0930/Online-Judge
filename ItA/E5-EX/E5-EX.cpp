#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

#define N 5000
#define M 100000

struct edge
{
    int from;     // 起点
    int to;       // 终点
    int nextEdge; // 下一条相同起点边的下标
};

edge Edge[M];        // 原图的边
edge _Edge[M];       // 缩点后的边
int Edges_from[N];   // 原图中相同起点的边
int _Edges_from[N];  // 缩点后相同起点的边
int DFSStamp_of[N];  // 结点的时间戳：结点被访问时的DFS次数
int Lowest_in[N];    // 结点子树中最早的时间戳
int timeStamp;       // DFS次数
int Stack[N];        // DFS过程中关于结点的栈
int top;             // 栈顶指针
bool If_in_Stack[N]; // 结点是否在栈中
int Component_of[N]; // 缩点后结点所属的强连通分量
int Size[N];         // 强连通分量中的结点数
int InDegree[N];     // 结点的入度
int Distance[N];     // 距离
int n;               // 原图点数
int m;               // 原图边数
int _n;              // 缩点后点（强连通分量）数
int _m;              // 缩点后边数

// 从结点u向下DFS，确定以u为代表的强连通分量
void Tarjan(int u)
{
    timeStamp++;
    DFSStamp_of[u] = Lowest_in[u] = timeStamp;
    Stack[++top] = u;
    If_in_Stack[u] = true;
    for (int i = Edges_from[u]; i != 0; i = Edge[i].nextEdge)
    {
        if (DFSStamp_of[Edge[i].to] == 0) // 未访问过
        {
            Tarjan(Edge[i].to); // DFS
            Lowest_in[u] = min(Lowest_in[u], Lowest_in[Edge[i].to]);
        }
        else // 已访问过
        {
            if (If_in_Stack[Edge[i].to]) // 在栈中：Edge[i] 是后向边
                Lowest_in[u] = min(Lowest_in[u], DFSStamp_of[Edge[i].to]);
            // 不在栈中：Edge[i].to 与 u 无拓扑关系，Edge[i] 是横叉边
        }
    }
    if (Lowest_in[u] == DFSStamp_of[u]) // 确定到最早DFS的结点，作为强连通分量的代表元素
    {
        for (; Stack[top] != 0; top--)
        {
            If_in_Stack[Stack[top]] = false; // 退栈
            Component_of[Stack[top]] = u;    // 出栈元素归入 u
            Size[u]++;
            if (Stack[top] == u)
                break;
        }
    }
}

// 拓扑排序，确定以各结点起始的最长距离
void TopoSort()
{
    queue<int> Queue;
    for (int i = 1; i <= n; i++)
    {
        if (Component_of[i] == i && InDegree[i] == 0) // 强连通分量的代表元素，且入度为 0
        {
            Queue.push(i);         // 入队
            Distance[i] = Size[i]; // 最长可以遍历分量中所有点
        }
    }
    while (Queue.size() != 0)
    {
        int u = Queue.front();
        Queue.pop(); // 出队
        for (int i = _Edges_from[u]; i != 0; i = _Edge[i].nextEdge)
        {
            Distance[_Edge[i].to] = max(Distance[_Edge[i].to], Distance[u] + Size[_Edge[i].to]); // 更新最长轨
            InDegree[_Edge[i].to]--;
            if (InDegree[_Edge[i].to] == 0)
                Queue.push(_Edge[i].to);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        Edge[i].nextEdge = Edges_from[u];
        Edge[i].from = u;
        Edge[i].to = v;
        Edges_from[u] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        if (DFSStamp_of[i] == 0) // 未被访问过
            Tarjan(i);
    }
    // 缩点
    for (int i = 1; i <= m; i++)
    {
        if (Component_of[Edge[i].from] != Component_of[Edge[i].to])
        {
            _m++;
            _Edge[_m].nextEdge = _Edges_from[Component_of[Edge[i].from]];
            _Edge[_m].to = Component_of[Edge[i].to];
            _Edge[_m].from = Component_of[Edge[i].from];
            _Edges_from[Component_of[Edge[i].from]] = _m;
            InDegree[Component_of[Edge[i].to]]++;
        }
    }
    TopoSort();
    int answer = 0;
    for (int i = 1; i <= n; i++)
    {
        if (Component_of[i] == i)
            answer = max(answer, Distance[i]);
    }
    cout << answer;
}