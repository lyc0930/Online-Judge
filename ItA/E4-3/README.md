# E4-3 数据缓存
## 题目描述
现有一个长为$N$的数据访问序列和一块大小为$K$的缓存，请设计算法使数据访问的MISS次数最少。

假设所有可能访问的数据在一个确定的范围内，这里用整数来表示存放数据的地址。

假设无论是否命中，这次访问的数据都需要存放在缓存内。

## 输入格式
第一行两个整数$N,K$表示共有$N$个数据访问的请求，缓存大小为$K$。

接下来的$N$行每行一个整数$i$，表示访问内存地址为$i$的数据。

## 输出格式
输出一个整数表示最少的MISS次数。

## 数据规模：
$ N \leq 10000$

$ K \leq 1000$

内存地址的范围为$0 \sim 10000$

# 解题报告
## 初始思路
类似于E4-2，本题借鉴于操作系统概念中交换缓存的概念设计**贪心**算法：可以证明，在最优方案下，当缓存已满时，每一次从缓存中换出的内存地址一定是下次访问最迟的。因此可以根据缓存的下一次访问时间维护一个优先队列来模拟缓存。
```c++
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
```
```c++
priority_queue<memory, vector<memory>> Cache;
```
对于从前向后的每一次访问，模拟缓存换出过程：若访问内存未被缓存且缓存已满，则优先队列出队，表示将下次访问最迟的内存从缓存中删除，否则直接加入缓存即可；若访问内存已被缓存，需要更新已缓存内存的下次访问时间，但修改优先队列中的元素属性较为困难，由于对于此内存的NextQuery一定是不断增加的，即
$$
\begin{align*}
    \text{NextQueryOf本次访问的内存} \geq \text{NextSameQuery上次对此内存访问} = \text{本次访问}
\end{align*}
$$
因此对同一个内存地址的访问重复入队不影响优先队列的出队顺序，可以认为是将前一个访问压入了队底，进而对贪心结果没有影响。需要维护的是将缓存上限虚拟地+1。


## 提交与修改过程
首次提交即[Accepted](https://202.38.86.171/status/bf48f828e931e6a84cdb6d38844f2b6a)。

## 算法分析
### 时间复杂度
算法对于内存访问进行了两次次数为$N$的迭代，在后一个循环每次迭代中，优先队列处理1个入队操作和最多1个出队操作，而对于大小为$K$缓存优先队列，入队消耗的时间是$O(\lg{K})$的，但在算法的具体实现中，此前被访问的内存并不会真的出队，在最坏情况下，每一次入队的摊还时间应当为
$$
\begin{align*}
    T = & \frac{1}{N} \cdot \sum_{k = 1}^{N}{\lg{k}} \\
      = & \frac{1}{N} \cdot \lg{\prod_{k = 1}^{N}{k}} \\
      = & \frac{\lg{N!}}{N} \\
      = & O( \lg{\sqrt{N}} )
\end{align*}
$$
因此算法的时间复杂度是$O(N \lg{\sqrt{N}} )$。

### 空间复杂度
从模拟的角度来看，算法除了存放了$N$次内存访问请求，并维护了优先队列以模拟大小为$K$缓存，算法消耗的空间是$O(N + K)$的，但在算法的具体实现中，此前被访问的内存并不会真的出队且实际上一定有$K \leq N$，因此算法的空间复杂度是$O(N)$

## 总结
本题使用**贪心**$+$**模拟**的算法解决，原理上较为简单，借助于优先队列每次换出下次访问最迟的缓存即可。使用到的技术是以访问和内存均为下标有效定位，以及以空间换时间，回避了优先队列较为复杂的修改问题。

由于本题的输入数据中，数据访问请求数$N$和内存地址的规模相同，因此可以将内存地址直接作为数组下标。而若内存地址有着较高量级的规模，考虑到我们只关心对于内存地址的访问相对先后，内存地址的绝对数值没有实际含义，可以对内存访问进行离散化处理以降低数组下标的上限，进而降低算法的空间复杂度
```c++
sort(Query_undiscretized, Query_undiscretized + n);
int size = unique(Query_undiscretized, Query_undiscretized + n) - Query_undiscretized;
for (int i = n - 1; i >= 0; i--)
    Query[i] = lower_bound(Query_undiscretized, Query_undiscretized + size, Query[i]) - Query_undiscretized;
```