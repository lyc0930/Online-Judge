# E1-1 数据库查询v1
## 题目描述
勤奋的小明为了预习下学期的数据库课程，决定亲自实现一个简单的数据库系统。该数据库系统需要处理用户的数据库插入和查询语句，并输出相应的输出。具体来说，用户的输入共包含若干条插入语句和查询语句。其中每条插入语句包含一个主键（唯一标识）$id$和一个非负整数$a_{id}$，表示在数据库中插入一个主键为$id$，属性值为$a_{id}$的条目。每条查询语句包含一个非负整数$k$，表示在数据库总查询是否有条目属性值为$k$，若存在条目属性值为$k$，则输出该条目对应的主键（输入保证至多有一个条目满足要求），否则输出一个$-1$表示不存在这样的条目。

## 输入格式
首先是若干行插入语句，每行的格式为：

INSERT $id$ $a_{id}$

紧接着若干行查询语句，每行的格式为：

FIND $k$

最后单独的一行

EXIT

表示输入结束。

## 输出格式
对每条查询语句输出一行，每行输出一个数字，表示查询的结果。

若存在满足条件的条目，则输出该条目的主键，否则该行输出一个$-1$表示没有满足条件的条目。

## 数据规模：

插入语句和查询语句分别不超过$10^6$条。

$0\leq id, a_{id}, k \leq 10^9$



# 解题报告

## 初始思路

数据库查询的问题自然而然想到了Hash表，通过建立基类型`type`为
```c
typedef struct
{
    int key;   // a_id
    int value; // id
} type;
```
的Hash表`hashTable`
```c
typedef struct
{
    type *element; // 表中元素的基址
    int count;     // 当前表中元素数
} HashTable;
```
注意到题目要求的查询功能是通过属性值查询主键值，因此实际上属性值$a_{id}$对应的是Hash表键值对中的“键”，而主键$id$对应键值对中的“值”。

代码主要实现了Hash表的初始化、插入、查询功能，考虑数据规模和复杂程度后选择使用**除留余数法**实现哈希函数，用**开放定址的线性探测法**解决冲突

```c
Status Initialize(HashTable *hashTable)                                  // Status表示函数返回状态，与算法无关
{
    int i;
    hashTableLength = HASHSIZE;                                          // HASHSIZE = 1E6, 对应最大条目数
    hashTable->element = (type *)malloc(hashTableLength * sizeof(type)); // 分配基址空间
    hashTable->count = 0;
    for (i = 0; i < hashTableLength; i++)
    {
        hashTable->element[i].key = NULLKEY;                             // 置空Hash表
    }
    return OK;
}
```
```c
int Hash(int key)
{
    return key % hashTableLength; // 除留余数法
}
```
```c
Status Insert(HashTable *hashTable, type data)
{
    int hashAddress = Hash(data.key);
    while (hashTable->element[hashAddress].key != NULLKEY)
    {
        hashAddress = (++hashAddress) % hashTableLength;   // 利用开放定址的线性探测法解决冲突
    }
    hashTable->element[hashAddress] = data;
    hashTable->count++;
    return OK;
}
```
```c
int Search(HashTable *hashTable, int key) //return the value
{
    int hashAddress = Hash(key);
    while (hashTable->element[hashAddress].key != key)
    {
        hashAddress = (++hashAddress) % hashTableLength;
        if (hashTable->element[hashAddress].key == NULLKEY || hashAddress == Hash(key))
            return -1; // 没有找到则直接返回
    }
    return hashTable->element[hashAddress].value;
}
```
由于本题要求较为简单，因此将总表长`hashTableLength`设置为最大插入数$10^6$后，没有再去实现扩充表和删除键值对等功能。
## 提交与修改过程
因为本题较为简单，第一次提交即[AC](https://202.38.86.171/status/184e0b0ae69a04213d8969a861daedf5)，耗时Time: 712ms，内存占用Memory: 9MB
## 算法分析
### 时间复杂度
对于输入中的插入语句，由于使用开放定址的线性探测法，设$\alpha$是哈希表最终所有条目的装填因子，则每条插入语句都可认为是在装填因子变动情况下的一次成功查找，平均查找长度为
$$
    S \approx \frac{1}{2}\left( 1+\frac{1}{1-x} \right),\ x \in [0,\alpha]
$$
则平均情况下插入语句消耗的时间约为
$$
\begin{align*}
T_{\text{INSERT}} &= \int_{x=0}^{\alpha}{\frac{1}{2}\left( 1+\frac{1}{1-x} \right)} \\
    &= \frac{1}{2}\left( \alpha - \log{(1-\alpha)} \right)
\end{align*}
$$
对于输入中的查找语句，假设查找成功的概率为$p$，单次查找消耗的时间即平均查找长度为
$$
\begin{align*}
t_{\text{FIND}} &= p \cdot \frac{1}{2}\left( 1+\frac{1}{1-\alpha} \right) + (1-p) \cdot \frac{1}{2}\left( 1+\frac{1}{(1-\alpha)^2} \right) \\
    &= \frac{1}{2}+\frac{p(1-\alpha)+(1-p)}{(1-\alpha)^2} \\
    &= \frac{1}{2}+\frac{1-p\alpha}{(1-\alpha)^2}
\end{align*}
$$
设查找语句共有$n_{\text{FIND}}$条，则平均情况下总的算法时间复杂度为
$$
\begin{align*}
    T(\alpha, n_{\text{FIND}},p) &= T_{\text{INSERT}} + T_{\text{FIND}}\\
    &= T_{\text{INSERT}} + n_{\text{FIND}} \cdot t_{\text{FIND}} \\
    &= \frac{1}{2}\left( \alpha - \log{(1-\alpha)} \right) + n_{\text{FIND}} \cdot \left( \frac{1}{2}+\frac{1-p\alpha}{(1-\alpha)^2} \right) \\
    &= O\left(\alpha+n_{\text{FIND}} \cdot \left( 1+\frac{2-2p\alpha}{(1-\alpha)^2} \right) \right) \\
    &= O\left(\alpha + n_{\text{FIND}} + \frac{n_{\text{FIND}}}{(1-\alpha)^2}\right) \\
    &= O\left( \alpha + 2 \cdot n_{\text{FIND}} \right) \\
    &= O(n_{\text{FIND}})
\end{align*}
$$
### 空间复杂度
因为没有涉及Hash表的扩展，因此算法执行时消耗的空间是固定的，即一个大小为$10^6$的结构体数组与其余常数个变量
$$
    S = \Theta(2*10^6)
$$
> 这点可以从提交记录上各数据点消耗的空间均为9MB得到印证
## 总结
决定使用散列表实现之后，本题的解题过程总体没有什么曲折，在完成提交之后，目前考虑的可优化的部分有：将插入命令全部读入后视数据数量及分布情况选择更为合适的表长以节省空间甚至优化时间复杂度（可能），采取链地址法等方式代替线性探测法以优化算法执行时间。