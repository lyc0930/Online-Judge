#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#define N 10000
#define K 1000
#define M 10000
using namespace std;

struct memory
{
    int nextQuery; // 下一次访问此内存的时间
    int number;    // 此内存离散化后的序号

    // 重载操作符，比较两个块内存下次访问的早晚
    bool operator<(const memory that) const
    {
        return this->nextQuery < that.nextQuery;
    }
    bool operator>(const memory that) const
    {
        return this->nextQuery > that.nextQuery;
    }

    memory(int nextquery, int No) : nextQuery(nextquery), number(No) {}
};

int NextSameQuery[M + 1]; // 表示下一个对相同内存的访问，下标是访问的离散化序号
int NextQueryOf[M + 1];   // NextQueryOf[mem]表示下一次对mem的访问，下标是内存的离散化序号

int Query_undiscretized[M + 1]; // 内存访问请求
int Query[M + 1];               // 离散化之后的内存访问请求
bool IfCached[M + 1];           // 这块内存是否已被缓存

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> Query_undiscretized[i];
        Query[i] = Query_undiscretized[i];
    }

    memset(NextQueryOf, N + 1, sizeof(NextQueryOf)); // 下一次访问在无穷远处

    // 离散化，并从后向前建立访问
    sort(Query_undiscretized, Query_undiscretized + n);
    int size = unique(Query_undiscretized, Query_undiscretized + n) - Query_undiscretized;
    for (int i = n - 1; i >= 0; i--)
    {
        Query[i] = lower_bound(Query_undiscretized, Query_undiscretized + size, Query[i]) - Query_undiscretized; // 离散化
        NextSameQuery[i] = NextQueryOf[Query[i]];
        NextQueryOf[Query[i]] = i;
    }

    int miss = 0;                                 // 丢失次数
    priority_queue<memory, vector<memory>> Cache; // 缓存，依据下一次访问时间维护的优先队列

    for (int i = 0; i < n; ++i)
    {
        if (!IfCached[Query[i]]) // 访问的数据未被缓存
        {
            miss++;                // 发生MISS
            if (Cache.size() == k) // Cache已满
            {
                IfCached[Cache.top().number] = false; // 从缓存中移除下次访问最迟的内存 1
                Cache.pop();                          // 从缓存中移除下次访问最迟的内存 2
            }
            IfCached[Query[i]] = true; // 此次访问加入缓存 1
        }
        else // 访问的数据已被缓存
        {
            /*
                需要更新已缓存内存的下次访问时间，但修改优先队列中的元素属性较为困难
                由于对于此内存的NextQuery一定是不断增加的，即
                    NextQueryOf本次访问的内存 >= NextSameQuery上次对此内存访问 = 本次访问
                因此对同一个内存地址的访问重复入队不影响优先队列的出队顺序，进而对贪心结果没有影响。
                需要维护的是将缓存上限虚拟地+1
            */
            k++;
        }
        NextQueryOf[Query[i]] = NextSameQuery[NextQueryOf[Query[i]]];
        Cache.push(memory(NextQueryOf[Query[i]], Query[i])); // 此次访问加入缓存 2 或 更新已缓存内存的下次访问时间
    }
    cout << miss;
    return 0;
}