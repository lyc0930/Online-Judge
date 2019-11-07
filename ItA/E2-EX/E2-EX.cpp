// 危险品放置
// 0 < n <= 100000
// 0 < m <= 1000000

#include <algorithm>
#include <iostream>
#define N 100000
#define M 1000000
using namespace std;

struct DangerousRelation
{
    int i;
    int j;
    int alpha;
} Edge[M + 1];

int Parent[N + 1];

int Compare(const DangerousRelation &x, const DangerousRelation &y)
{
    return x.alpha > y.alpha;
}

int Find_Set(int x)
{
    if (x != Parent[x])
        Parent[x] = Find_Set(Parent[x]);
    return Parent[x];
}

int main()
{
    int n, m;
    int components = 0, edges = 0;
    int maxDanger = 0;
    bool Component[N + 1];
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> Edge[edges].i >> Edge[edges].j >> Edge[edges].alpha;
        if (Edge[edges].i != Edge[edges].j)
        {
            if (!Component[Edge[edges].i])
            {
                Component[Edge[edges].i] = true;
                components++;
            }
            if (!Component[Edge[edges].j])
            {
                Component[Edge[edges].j] = true;
                components++;
            }
            edges++; // |E|++
        }
        else // Individual Dangerous
        {
            if (Edge[edges].alpha > maxDanger)
                maxDanger = Edge[edges].alpha;
        }
    }
    sort(Edge, Edge + edges, Compare);
    for (int i = 0; i <= n; i++)
        Parent[i] = i;
    for (edges -= 1; edges >= 0; edges--)
    {
        int set_i = Find_Set(Edge[edges].i);
        int set_j = Find_Set(Edge[edges].j);
        if (set_i != set_j)
        {
            Parent[set_i] = set_j;
            components--;
        }
        if (components <= 1)
            break;
    }
    if (components <= 1)
        cout << ((Edge[edges + 1].alpha > maxDanger) ? Edge[edges + 1].alpha : maxDanger);
    else
        cout << maxDanger;
    return 0;
}