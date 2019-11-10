// 危险品放置
// 0 < n <= 100000
// 0 < m <= 1000000

#include <algorithm>
#include <iostream>
#define N 100000
#define M 1000000
using namespace std;

// 危险关系，下标是边序号 edges
struct DangerousRelation
{
    int i;     // 危险关系中的危险品 i
    int j;     // 危险关系中的危险品 j
    int alpha; // 危险系数 alpha(i,j)
} Relation[M + 1];

// 顶点属性，下标是点 i j
struct Node
{
    int set;       // 所在集合
    bool polarity; // 极性
} Node[N + 1];

/*
    极性是否翻转，下标是集合 set
    若为true，则将其与集合内顶点极性异或^之后，得到相反极性
*/
bool PolarityReverse[N + 1];

// 并查集祖先，下标是集合 set
int Parent[N + 1];

// 并查集检索集合s所在并查集，并路径压缩
int Find_Set(int s)
{
    if (s != Parent[s])
        Parent[s] = Find_Set(Parent[s]);
    return Parent[s];
}

// 返回顶点x所在集合
int Set(int x)
{
    return Find_Set(Node[x].set);
}

/*
    并查集检查集合s的极性是否翻转，并路径压缩
    用异或和实现
*/
bool IfPolarityReverse(int s)
{
    if (s != Parent[s])
        PolarityReverse[s] ^= IfPolarityReverse(Parent[s]);
    return PolarityReverse[s];
}

/*
    返回顶点x的实际极性
*/
bool Polarity(int x)
{
    return (IfPolarityReverse(Node[x].set) ^ Node[x].polarity);
}

/*
    供sort函数调用的比较函数
    比较两个危险关系的危险系数大小
*/
int Compare(const DangerousRelation &x, const DangerousRelation &y)
{
    return x.alpha < y.alpha;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    int edges = 0;               // 非自相关的危险关系的数量
    int maxIndividualDanger = 0; // 最大的自相关危险系数

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> Relation[edges].i >> Relation[edges].j >> Relation[edges].alpha;
        if (Relation[edges].i != Relation[edges].j) // Update Edges
            edges++;                                // |E|++
        else                                        // Individual Dangerous
            if (Relation[edges].alpha > maxIndividualDanger)
            maxIndividualDanger = Relation[edges].alpha; // Update Maximum
    }

    // Sort Relations by alpha: less -> greater
    sort(Relation, Relation + edges, Compare);

    // Initialize the Disjoint Set
    for (int i = 0; i <= n; i++)
        Parent[i] = i;

    int sets = 0; // 集合的数量

    for (edges -= 1; edges >= 0; edges--)
    {
        // cout << Relation[edges].i << ' ' << Relation[edges].j << ' ' << Relation[edges].alpha << endl; // Debug Output

        if (Node[Relation[edges].i].set == 0) // i未被分配
        {
            if (Node[Relation[edges].j].set == 0) // 两者均未分配
            {
                sets++;
                Node[Relation[edges].i].set = sets;
                Node[Relation[edges].i].polarity = Relation[edges].i < Relation[edges].j;
                Node[Relation[edges].j].set = sets;
                Node[Relation[edges].j].polarity = Relation[edges].i >= Relation[edges].j;
            }
            else // j 已被分配
            {
                Node[Relation[edges].i].set = Set(Relation[edges].j);                 // 放入同一个集合中
                Node[Relation[edges].i].polarity = !Node[Relation[edges].j].polarity; // 极性相反
            }
        }
        else // i 已被分配
        {
            if (Node[Relation[edges].j].set == 0) // j 未被分配
            {
                Node[Relation[edges].j].set = Set(Relation[edges].i);                 // 放入同一个集合中
                Node[Relation[edges].j].polarity = !Node[Relation[edges].i].polarity; // 极性相反
            }
            else // 两者均已分配
            {
                int polarity_i = Polarity(Relation[edges].i);
                int polarity_j = Polarity(Relation[edges].j);
                // 先计算极性防止路径压缩
                int set_i = Set(Relation[edges].i);
                int set_j = Set(Relation[edges].j);

                // cout << set_i << ' ' << set_j << endl;           // Debug Output
                // cout << polarity_i << ' ' << polarity_j << endl; // Debug Output

                if (set_j == set_i) // 在同一个集合中
                {
                    if (polarity_i == polarity_j) // 极性相同
                        break;
                }
                else // 不在同一个集合中
                {
                    if (polarity_i == polarity_j) // 极性相同 -> 极性翻转
                    {
                        if (set_i < set_j) // 向小合并（并不是按秩合并）
                        {
                            PolarityReverse[Node[Relation[edges].j].set] ^= 1; // 集合j中的极性全部翻转
                            Parent[set_j] = set_i;                             // 将所在集合j向i所在集合合并
                        }
                        else // 将所在集合j向i所在集合合并
                        {
                            PolarityReverse[Node[Relation[edges].i].set] ^= 1; // 集合i中的极性全部翻转
                            Parent[set_i] = set_j;                             // 将所在集合i向j所在集合合并
                        }
                    }
                    else // 极性相反
                    {
                        if (set_i < set_j)         // 向小合并 （并不是按秩合并）
                            Parent[set_j] = set_i; // 将所在集合j向i所在集合合并
                        else
                            Parent[set_i] = set_j; // 将所在集合i向j所在集合合并
                    }
                }
            }
        }
        // for (int i = 1; i <= n; i++)                                           // Debug Output
        // cout << (char)(Set(i) + 64) << ' ' << (bool)(Polarity(i)) << ", "; // Debug Output
        // cout << endl;                                                          // Debug Output
    }

    cout << ((Relation[edges].alpha > maxIndividualDanger) ? Relation[edges].alpha : maxIndividualDanger);

    return 0;
}