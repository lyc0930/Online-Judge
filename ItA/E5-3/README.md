# E5-3 货物运输
## 题目描述
在一个工厂货物运输系统中共有$N$个节点，编号为$1,2,3，\cdots ,N$，节点之间有传送带（单向）连接，每个传送带都有使用寿命，传送带的寿命为一个数字LL，表示在传送完LL个单位的货物后，传送带就会破损无法使用。现在需要从节点$S$向节点$T$传送货物，求在当前传输系统中，最多可以顺利传输多少单位的货物从节点$S$到节点$T$

## 输入格式
第一行为4个整数，$N\ M\ S\ T$，分别代表节点个数、传送带数目、起点标号$S$、目标点标号$T$

接下来$M$行，每行表述一条传送带的信息，表述为$U_i$$V_i$$L_i$的形式，表示一条从节点$U_i$到节点$V_i$，寿命为$L_i$的传送带

## 输出格式
输出一个整数，表示在当前传输系统中，最多可以顺利传输多少单位的货物从节点$S$到节点$T$

## 数据规模：
对于所有数据，满足$1 \leq U_i \leq N$，$1 \leq V_i \leq N$，$1 \leq L_i \leq 100$

$40\%$的数据，$2 \leq N \leq 50$，$2 \leq M \leq 500$
$100\%$的数据，$2 \leq N \leq 500$，$2 \leq M \leq 20000$

# 解题报告
## 初始思路
这是一道网络中的最大流问题，源点和汇点已经给出了，每条传送带的寿命对应网络流中每条边的容量。

在权衡了各种最大流算法的代码量和性能，考虑使用由Tarjan提出的最高标号预流推进算法，对于一个以高度为键的结点优先队列，算法中每次推送高度最高结点的超额流量。

为提高性能，只进行一次重贴标签操作，在一遍BFS中将除源点$S$外的每个点初始高度设置为其到汇点$T$的最短距离。而且，对于一个被重贴标签后的结点，如果其所在高度没有其他点了，那么没有必要再对于高于它的结点进行推流了，这一点在算法中由记录同一高度结点数的`Gap`数组实现。

## 提交与修改过程
首次提交即[Accepted](https://202.38.86.171/status/fb49e7d3574ff6caed336434b492442a)

## 算法分析
### 时间复杂度
基于链式前向星的BFS时间复杂度为$O(N)$，算法在最坏情况下的时间复杂度为$O(N^2 \sqrt{M})$。
### 空间复杂度
由于为提高算法性能，使用了向量数组的形式实现链式前向星的存图，因此额外消耗的空间是$O(NM)$的。

## 总结
在算法导论第26章中基于预流推进的前置重贴标签算法是$O(V^3)$的，注记中作者提及了在渐进意义上表现最快的最大流算法：

> The asymptotically fastest algorithm to date for the maximum-flow problem, by Goldberg and Rao, runs in time $O(\min{(V^{2/3},E^{1/2})}E\lg{(V^2/E+2)}\lg{C})$, where $C = \max_{(u,v)\in E}{c(u,v)}$.This algorithm does not use the push-relabel method but instead is based on finding blocking flows. All previous maximum flow algorithms, including the ones in this chapter, use some notion of distance (the push-relabel algorithms use the analogous notion of height), with a length of 1 assigned implicitly to each edge. This new algorithm takes a different approach and assigns a length of 0 to high-capacity edges and a length of 1 to low-capacity edges. Informally, with respect to these lengths, shortest paths from the source to the sink tend have high capacity, which means that fewer iterations need be performed

这是由 Goldberg 和 Rao 提出的 Binary 阻塞流算法，阻塞流的思想其实在 *Dinic* 阻塞流算法中就有体现。事实上，有向网络最大流的算法时间上界已经由 James B Orlin 降至了$O(VE)$，他提出的算法能够在$O(VE)$时间内解决满足$E \leq O(V^{\frac{16}{15} - \varepsilon})$的网络中的最大流，结合此前 King、Rao 和 Tarjan 提出的能够在$O(VE)$时间内解决满足$E > V^{1 + \varepsilon}$的网络中最大流的 *KRT* 算法，对于任意的网络，其最大流都可以在$O(VE)$时间内求得。

而在李贤达和 Aaron Sidford 于2015年发表的论文中，这一上界被降低到了$\widetilde{O}(E\sqrt{V})$。但随着算法上界的不断降低，在简单网络中的表现差异并不大，而在极端稠密的网络中，仅降低顶点数的幂次显得有些差强人意。

因此，在实际题目的解决中，*Dinic* 和优化后的増广路算法 *Improved Shortest Augmenting Path(ISAP)* 都是相对较优的。而基于预流推进的思想，Tarjan指出在每次推流最高结点时会有更好的性能表现，即本题实现的最高标号预流推进 *Highest Label Preflow Push(HLPP)* 算法。

预流推进的思想其实是很易于理解和接受的：流量从高处向低处转移，而*HLPP*算法通过重贴标签以更改地势，使得流量能够顺畅的流向汇点，因此代码的实现也并不困难。而基于STL的链式前向星为算法提供了优秀的数据结构基础。