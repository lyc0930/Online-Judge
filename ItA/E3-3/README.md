# E3-3 多重背包
## 题目描述
现有一个背包可以容纳总重量为$W$的物品，有$n$种物品可以放入背包，其中每种物品单个重量为$w_i$，价值为$v_i$，可选数量为$num_i$。

输出可以放入背包的物品的最大总价值。

## 输入格式
第一行两个整数$n,\,W$，分别表示物品件数和背包容量。

然后$n$行数据描述每种物品的重量、价值和可选数量。

每行的格式为$w_i \quad v_i \quad num_i$。

## 输出格式
输出一个整数表示可以装入背包的最大价值。

## 数据规模：
$1 \leq n \leq 200$

$1 \leq W \leq 10000$

$1 \leq w_i \leq 1000$

$1 \leq v_i \leq 1000$

$1 \leq num_i \leq 10000$

所有输入数据均为整数。

# 解题报告
## 初始思路
对于一个多重背包的模板题，状态转移方程是可以直接写出来的

$$
F_j &= \max{\{ F_{j - k \times w_i } + k \times v_i \}},\qquad 0 \leq k \leq num_i ,\, k \times w_i \leq j
$$

采用基于**单调队列**的优化方法。
可以看出，如果$j \mod w_i$取不同值时的方程式是**相互独立**的，设$j \equiv d \mod w_i $，$s = \left \lfloor \frac{j}{w_i} \right \rfloor$。**枚举$d$**：

$$
\begin{align*}
F_{j} =& \max{ \{ F_{j - k \times w_i} + k \times v_i \} },\qquad k \leq s, k \leq num_i \\
=& \max{ \{ F_{d + (s - k) \times w_i} - (s - k) \times v_i \} } + s \times v_i ,\qquad k \leq s, k \leq num_i \\
=& \max{ \{ F_{d + k \times w_i} - k \times v_i \} } + s \times v_i ,\qquad s - num_i \leq k \leq s
\end{align*}
$$

用单调队列记录$F_{d + k \times w_i} - k \times v_i$，在一个**滑动窗口**中，维护左指针指向单调队列的最大值。当元素入队时，向左移动右指针以删除所有比该元素小的元素，并存入该元素；当元素出队时，若是最大值，向右移动左指针使得最大值离队。入队的操作保证了当前队列一定是单调递减的，则左指针指向最大值。

```c++
// 出队较小元素
while ((left < right) && (F[j + k * w] - k * v > PriorityQueue[right - 1].value))
    right--;

// 元素入队
PriorityQueue[right].number = k;
PriorityQueue[right].value = F[j + k * w] - k * v;
right++;

// 出队
if (num < k - PriorityQueue[left].number)
    left++;

// 状态转移
F[j + k * w] = PriorityQueue[left].value + k * v;
```

除此之外，维护物品拿取的数量是必须的，因此队列的元素还需要包括其对应的$k$值。

## 提交与修改过程
首次提交即[AC](https://202.38.86.171/status/3623e1e44c09c5455778304e7d0eee55)

## 算法分析
### 时间复杂度
使用了单调队列后，内层循环中：入队元素并移出较小元素、出队元素、状态转移的摊还时间是常数的，外层循环遍历$n$次，内两层循环受$W$制约，因此总的时间复杂度是$O(nW)$。

### 空间复杂度
对于每一个物品采用随读随用的方式，但采用了大数组的方式实现动态规划状态与单调队列，因此空间复杂度为$O(W)$

## 总结
本题是一道多重背包的模板题，多重背包除了在完全背包上增加条件外还可以使用二进制转换为01背包，或采用单调队列以降低摊还时间，通过本题还练习了单调队列的一种实现方法。