# E1-3 弹幕游戏
## 题目描述
某天小明闲着无聊，在寝室玩一款弹幕游戏。现有一个数轴，在该数轴上面有$n$个点，每个点代表一个敌人。小明控制的主角是一个直径为$d$的圆，小明的目标是从数轴的下方移动到数轴的上方，但是不能碰到任何敌人（如果两个敌人之间距离为$1$，主角直径也为$1$，这种情况不算碰到敌人）求主角的直径$d$至多可以达到多少。（不允许主角从所有敌人的最左边，或者所有敌人的最右边穿过数轴）
## 输入格式
一共两行，第一行有一个整数$n$

第二行一共有$n$个整数$a_i$（互不相同），代表了每个敌人在数轴上的坐标（这一行数字是乱序的）
## 输出格式
主角直径$d$最大值
## 数据规模
$0 < n \leq 10000000$

$0 \leq a_i \leq 10^9$
# 解题报告
## 初始思路
这道题的本质是求一个无序数列排序后相邻两数之间的最大差值，为降低时间复杂度，一个简单的想法是将在一个较小范围内的元素放在一起考虑——范围足够小以保证最大差值一定不产生在这个范围内的元素之间，通过各个这样的相邻小范围之间最值的差值计算来减少比较。受到E1-2修改排序算法以实现的启发，联想到桶排序的想法，将元素放入桶中，再在桶间进行比较是一个更为清晰的表述与实现思路。

对于$n$个元素，考虑其中的最大值$max$和最小值$min$，如果这$n$个元素均匀分布，那么相邻元素间的间隔为$\dfrac{max-min}{n}$，进而如果将桶的大小设定为不大于$\left \lfloor \dfrac{max-min}{n}  \right \rfloor$，那么就可以保证相邻元素的最大差值一定不产生在桶内的元素之间。
```c
scanf("%d", &n);
for (i = 0; i < n; i++)
{
    scanf("%d", &A[i]);
    if (A[i] > max)
        max = A[i];
    if (A[i] < min)
        min = A[i];
}

bucketSize = (max - min) / n;                 // 桶的大小
bucketSize = bucketSize > 0 ? bucketSize : 1; // 保证桶的大小是正值
bucketNumber = (max - min) / bucketSize + 1;  // 计算桶的个数
Buckets = (bucket *)malloc((bucketNumber) * sizeof(bucket));

for (i = 0; i < bucketNumber; i++)
{
    Buckets[i].count = 0; // 各桶的成员初始化
    Buckets[i].maximum = INT_MIN;
    Buckets[i].minimum = INT_MAX;
}
```
需要注意的是，由于采用向下取整的方式计算每个桶的大小，对于其是正值的检查是必要的。

和桶排序不同的是，在以上保证下，我们只关心每只桶内元素的最值，而不关心桶内的元素及其排序。在一个循环迭代的过程中，只需要计算并将$a_i$投入对应的桶中，再更新该桶的最值即可
```c
for (i = 0; i < n; i++)
{
    tempIndex = (A[i] - min) / bucketSize;
    Buckets[tempIndex].count++;
    if (A[i] > Buckets[tempIndex].maximum)
        Buckets[tempIndex].maximum = A[i];
    if (A[i] < Buckets[tempIndex].minimum)
        Buckets[tempIndex].minimum = A[i];
}
```
在完成了所有元素的投放也即各桶最值的计算后，进行一次循环以计算一个非空桶的最大值与下一个非空桶的最小值之差，更新题目所求的最大直径。
```c
for (i = 0; (i < n) && (Buckets[i].count <= 0); i++) // 找到第一个非空桶
    ;
for (; i < bucketNumber; i = j)
{
    for (j = i + 1; (j <= bucketNumber) && (Buckets[j].count <= 0); j++) // 找到后一个非空桶
        ;
    if (Buckets[j].minimum - Buckets[i].maximum > maxDiam)
        maxDiam = Buckets[j].minimum - Buckets[i].maximum;
}
```
## 提交过程与修改
整体代码逻辑比较简单，第一次提交即[AC](https://202.38.86.171/status/3f52efcbdd8ce1b23c61b111b094755c)，时间2548ms，内存211MB。

重新审视代码，可以发现对于各桶元素初始化的这个循环是没有必要的，作为代替可以在投放各个元素时增加该桶是否已有元素的判断，例如
```c
for (i = 0; i < n; i++)
{
    tempIndex = (A[i] - min) / bucketSize;
    Buckets[tempIndex].count++;
    if (A[i] > Buckets[tempIndex].maximum)
        Buckets[tempIndex].maximum = A[i];
    if (A[i] < Buckets[tempIndex].minimum || Buckets[tempIndex].minimum == 0)
        Buckets[tempIndex].minimum = A[i];
}
```
遗憾的是，似乎在此循环内增加了一个判断之后，消耗的时间并没有明显减少，甚至在个别提交中有所增加（2600+ms），并没有达到预期的效果，最好的提交结果也仅为2524ms（更可能的原因是受到OJ编译影响）。

内存占用是其他提交的近2倍，主要原因可能是在`main`函数中使用`malloc`动态分配了过于充分的数组，但改为申请长度为$10^7+1$的全局数组之后，出现了Run Time Error的错误，因此这个改动是不合适的。

## 算法分析
### 时间复杂度
算法总共进行了3次循环迭代，分别完成了数据读入并检索最值、各元素向桶的投放与最值计算、检查最大直径，类比桶排序是线性时间的排序，因此时间复杂度很容易看出为$O(n)$。
### 空间复杂度
由于申请的数动态组大小为$O(n)$，定义的全局数组是定长的，因此总的空间复杂度为$O(n)$。
## 总结
在核心为减少比较次数的最值计算问题中，线性时间的排序算法有很强的借鉴意义。具体到本题的实现中，一个可以进一步优化的问题是如何降低过高的空间占用。