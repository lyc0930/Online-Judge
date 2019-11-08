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
} Relation[M + 1];
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
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    int components = 0, queue = 0;
    int maxIndividualDanger = 0;

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> Relation[queue].i >> Relation[queue].j >> Relation[queue].alpha;
        if (Relation[queue].i != Relation[queue].j)
        {
            if (Parent[Relation[queue].i]==0)
            {
                Parent[Relation[queue].i] = Relation[queue].i;
                components++;
            }
            if (Parent[Relation[queue].j]==0)
            {
                Parent[Relation[queue].j] = Relation[queue].j;
                components++;
            }
            queue++; // |E|++
        }
        else // Individual Dangerous
        {
            if (Relation[queue].alpha > maxIndividualDanger)
                maxIndividualDanger = Relation[queue].alpha;
        }
    }

    sort(Relation, Relation + queue, Compare);

    // for (int i = 0; i <= n; i++)
    //     Parent[i] = i;

    for (queue -= 1; queue >= 0; queue--) // Add edges
    {
        int set_i = Find_Set(Relation[queue].i);
        int set_j = Find_Set(Relation[queue].j);
        if (set_i != set_j)
        {
            Parent[set_i] = set_j;
            components--;
        }
        // cout << Relation[queue].i << ' ' << Relation[queue].j << ' ' << Relation[queue].alpha << endl;
        // cout << "queue: " << queue << endl;
        // cout << "components: " << components << endl;
        if (components <= 1)
            break;
    }
    // cout << Relation[queue + 1].i << ' ' << Relation[queue + 1].j << ' ' << Relation[queue + 1].alpha << endl;
    if (components <= 1)
        cout << ((Relation[queue + 1].alpha > maxIndividualDanger) ? Relation[queue + 1].alpha : maxIndividualDanger);
    else
        cout << maxIndividualDanger;
    return 0;
}