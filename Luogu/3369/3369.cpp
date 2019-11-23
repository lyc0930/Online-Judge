#include <iostream>

using namespace std;

template <class Type>
class SBTreeNode
{
public:
    Type key;           // 键值
    int size;           // 子树大小
    SBTreeNode *left;   // 左孩子
    SBTreeNode *right;  // 右孩子
    SBTreeNode *parent; // 父亲结点

    SBTreeNode(Type value, int size, SBTreeNode *leftChild, SBTreeNode *rightChild, SBTreeNode *parent) : key(value), size(size), left(leftChild), right(rightChild), parent(parent) {}
};

template <class Type>
class SBTree
{
private:
    SBTreeNode<Type> *root; // 树根
    SBTreeNode<Type> *nil;  // 哨兵结点，代替NULL
    // 左旋
    void Left_Rotate(SBTreeNode<Type> *x);
    // 右旋
    void Right_Rotate(SBTreeNode<Type> *y);
    /*
        插入
        由于需要两趟计算，改为递归实现
    */
    void SB_Insert(SBTreeNode<Type> *T, SBTreeNode<Type> *z);
    // 删除
    void SB_Delete(SBTreeNode<Type> *T, SBTreeNode<Type> *z);
    /*
        Size Balanced Tree 维护
            Case 1): z->left->left->size   > z->right->size
            Case 2): z->left->right->size  > z->right->size
            Case 3): z->right->right->size > z->left->size
            Case 4): z->right->left->size  > z->left->size

        flag: (z->left->size < z->right->size)
            added to avoid meaningless checking
            - false: Case 1) & 2) will be checked
            - true: Case 3) & 4) will be checked
    */
    void SB_Maintain(SBTreeNode<Type> *z, bool flag);
    // 查找
    SBTreeNode<Type> *SB_Search(SBTreeNode<Type> *T, Type key) const;
    // 查找最小结点
    SBTreeNode<Type> *SB_SeekMinimum(SBTreeNode<Type> *T, SBTreeNode<Type> *x, int c);
    // 查找最大结点
    SBTreeNode<Type> *SB_SeekMaximum(SBTreeNode<Type> *T, SBTreeNode<Type> *x, int c);

public:
    SBTree();
    ~SBTree();
    // 查找并返回键值为key的结点
    SBTreeNode<Type> *search(Type key);
    // 插入一个键值为key的结点
    void insert(Type key);
    // 删除一个键值为key的结点
    void remove(Type key);
    // 返回最小键值
    Type *minimum();
    // 返回最大键值
    Type *maximum();
    // 返回结点x的前驱结点，即键值小于x.key且最大的结点
    SBTreeNode<Type> *predecessor(SBTreeNode<Type> *x);
    // 返回结点x的后继结点，即键值大于x.key且最小的结点
    SBTreeNode<Type> *successor(SBTreeNode<Type> *x);
    // 查找并返回秩为rank的结点，即排名为rank的结点
    SBTreeNode<Type> *select(int rank);
    // 返回键值为key的结点对应的秩，即key的排名
    int rank(Type key);
    // 销毁SBT树
    void destroy();
    // 打印SBT树
    void print();
};

template <class Type>
SBTree<Type>::SBTree()
{
    root = new SBTreeNode<Type>(0, 0, NULL, NULL, NULL);
    nil = new SBTreeNode<Type>(0, 0, NULL, NULL, NULL);
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;
    root = nil;
}

template <class Type>
SBTree<Type>::~SBTree()
{
    destroy();
}

template <class Type>
void SBTree<Type>::Left_Rotate(SBTreeNode<Type> *x)
{
    SBTreeNode<Type> *y = x->right; // x的右孩子
    x->right = y->left;             // 将y的左孩子设为x的右孩子
    if (y->left != nil)
        y->left->parent = x; // 如果y的左孩子非空，将x设为y的左孩子的父亲
    y->parent = x->parent;   // 将x的父亲设为y的父亲

    if (x->parent == nil)
        root = y; // 如果x的父亲是空节点，则将y设为根节点
    else
    {
        if (x == x->parent->left)
            x->parent->left = y; // 如果x是它父节点的左孩子，则将y设为x的父节点的左孩子
        else
            x->parent->right = y; // 如果x是它父节点的左孩子，则将y设为x的父节点的左孩子
    }
    y->left = x;                                  // 将x设为y的左孩子
    x->parent = y;                                // 将x的父节点设为y
    y->size = x->size;                            // 调整size
    x->size = x->left->size + x->right->size + 1; // 调整size
    return;
}

template <class Type>
void SBTree<Type>::Right_Rotate(SBTreeNode<Type> *y)
{
    SBTreeNode<Type> *x = y->left; // y的左孩子
    y->left = x->right;            // 将x的右孩子设为y的左孩子
    if (x->right != nil)
        x->right->parent = y; // 如果x的右孩子非空，将y设为x的右孩子的父亲
    x->parent = y->parent;    // 将y的父亲设为x的父亲

    if (y->parent == nil)
        root = x; // 如果 y的父亲是空节点，则将x设为根节点
    else
    {
        if (y == y->parent->right)
            y->parent->right = x; // 如果y是它父节点的右孩子，则将x设为y的父节点的右孩子
        else
            y->parent->left = x; // 如果y是它父节点的左孩子，则将x设为y的父节点的左孩子
    }
    x->right = y;                                 // 将y设为x的右孩子
    y->parent = x;                                // 将y的父节点设为x
    x->size = y->size;                            // 调整size
    y->size = y->left->size + y->right->size + 1; // 调整size
    return;
}

template <class Type>
void SBTree<Type>::SB_Insert(SBTreeNode<Type> *T, SBTreeNode<Type> *z)
{
    T->size++; // 沿途调整size
    if (z->size < T->size)
    {
        if (T->left != nil)
            SB_Insert(T->left, z);
        else // T->left == nil
        {
            z->parent = T;
            T->left = z;
            z->left = nil;
            z->right = nil;
        }
    }
    else
    {
        if (T->right != nil)
            SB_Insert(T->right, z);
        else
        {
            z->parent = T;
            T->right = z;
            z->left = nil;
            z->right = nil;
        }
    }
    SB_Maintain(T, z >= T->size);
    return;
}

template <class Type>
void SBTree<Type>::SB_Delete(SBTreeNode<Type> *T, SBTreeNode<Type> *z)
{
    T->size--;
    if ((z->key = T->key) || ((z->key < T->key) && (T->left == nil)) || ((z->key > T->key) && (T->right == nil)))
    {
        return T;
        if (T->left==nil)
            T = T->right;
        else
        {
            if (T->right==nil)
                T = T->left;
            else
                T = Delete(T->left,)
        }
    }
}

    template <class Type>
    void SBTree<Type>::SB_Maintain(SBTreeNode<Type> *z, bool flag)
{
    if (flag == false) // z->left->size >= z->right->size
    {
        if (z->left->left->size > z->right->size) // Case 1
            Right_Rotate(z);
        else
        {
            if (z->left->right->size > z->right->size) // Case 2
            {
                Left_Rotate(z->left);
                Right_Rotate(z);
            }
            else
                return;
        }
    }
    else // z->left->size <= z->right->size
    {
        if (z->right->right->size > z->left->size) // Case 3
            Left_Rotate(z);
        else
        {
            if (z->right->left->size > z->left->size) // Case 4
            {
                Right_Rotate(z->right);
                Left_Rotate(z);
            }
            else
                return;
        }
    }
    SB_Maintain(z->left, false);
    SB_Maintain(z->right, true);
    SB_Maintain(z, false);
    SB_Maintain(z, true);
    return;
}

int main()
{
    return 0;
}