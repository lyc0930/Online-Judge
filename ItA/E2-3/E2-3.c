// 内存分配
// 0 < n <= 10^6
// 0 <= a_i <= b_i <= 2^30

#include <stdio.h>
#include <stdlib.h>

typedef struct Interval
{
    int low;
    int high;
} Interval;

enum Color
{
    RED,
    BLACK
};

// 区间树的节点
typedef struct IntervalTreeNode
{
    enum Color color;
    Interval interval;
    int max;
    struct IntervalTreeNode *left;
    struct IntervalTreeNode *right;
    struct IntervalTreeNode *parent;
} Node;

// 区间树
typedef struct IntervalTree
{
    Node *root;
    Node *nil;
} Tree;

// 返回A、B、C中的最大值
int Max(int A, int B, int C)
{
    if (A < B)
        return (B > C) ? B : C;
    else
        return (A > C) ? A : C;
}

// 判断区间i与区间j是否重叠
int Overlap(Interval i, Interval j)
{
    return (i.low <= j.high && j.low <= i.high);
}

// 对区间树T的节点x进行左旋
void Left_Rotate(Tree *T, Node *x)
{
    Node *y = x->right; // 设置x的右孩子为y
    x->right = y->left; // 将y的左孩子设为x的右孩子
    if (y->left != T->nil)
        y->left->parent = x; // 如果y的左孩子非空，将x设为y的左孩子的父亲
    y->parent = x->parent;   // 将x的父亲设为y的父亲

    if (x->parent == T->nil)
        T->root = y; // 如果x的父亲是空节点，则将y设为根节点
    else
    {
        if (x == x->parent->left)
            x->parent->left = y; // 如果x是它父节点的左孩子，则将y设为x的父节点的左孩子
        else
            x->parent->right = y; // 如果x是它父节点的左孩子，则将y设为x的父节点的左孩子
    }
    y->left = x;   // 将x设为y的左孩子
    x->parent = y; // 将x的父节点设为y
    x->max = Max(x->interval.high, x->left->max, x->right->max);
    y->max = Max(y->interval.high, x->max, y->right->max);
}

// 对区间树T的节点y进行右旋转
void Right_Rotate(Tree *T, Node *y)
{
    Node *x = y->left;  // 设置y的左孩子为x
    y->left = x->right; // 将x的右孩子设为y的左孩子
    if (x->right != T->nil)
        x->right->parent = y; // 如果x的右孩子非空，将y设为x的右孩子的父亲
    x->parent = y->parent;    // 将y的父亲设为x的父亲

    if (y->parent == T->nil)
        T->root = x; // 如果 y的父亲是空节点，则将x设为根节点
    else
    {
        if (y == y->parent->right)
            y->parent->right = x; // 如果y是它父节点的右孩子，则将x设为y的父节点的右孩子
        else
            y->parent->left = x; // 如果y是它父节点的左孩子，则将x设为y的父节点的左孩子
    }
    x->right = y;  // 将y设为x的右孩子
    y->parent = x; // 将y的父节点设为x
    y->max = Max(y->interval.high, y->left->max, y->right->max);
    x->max = Max(x->interval.high, x->left->max, y->max);
}

// 区间树插入修正
void Interval_Insert_Fixup(Tree *T, Node *z)
{
    while (z->parent->color == RED) // 父节点存在，并且父节点的颜色是红色
    {
        if (z->parent == z->parent->parent->left) //若父节点是祖父节点的左孩子
        {
            Node *y = z->parent->parent->right;
            if (y->color == RED) // Case 1：叔叔节点是红色
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right) // Case 2：叔叔是黑色，且当前节点是右孩子
                {
                    z = z->parent;
                    Left_Rotate(T, z);
                }
                // Case 3：叔叔是黑色，且当前节点是左孩子。
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                Right_Rotate(T, z->parent->parent);
            }
        }
        else //若父节点是祖父节点的右孩子
        {
            Node *y = z->parent->parent->left;
            if (y->color == RED) // Case 1：叔叔节点是红色
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left) // Case 2：叔叔是黑色，且当前节点是左孩子
                {
                    z = z->parent;
                    Right_Rotate(T, z);
                }
                // Case 3：叔叔是黑色，且当前节点是右孩子。
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                Left_Rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK; // 将根节点设为黑色
}

// 将节点z插入到区间树T中
void Interval_Insert(Tree *T, Node *z)
{
    Node *y = T->nil;
    Node *x = T->root;
    while (x != T->nil)
    {
        y = x;
        if (y->max < z->interval.high)
            y->max = z->interval.high;
        if (z->interval.low < x->interval.low)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == T->nil)
        T->root = z; // Case 1：若y是空节点，则将z设为根
    else
    {
        if (z->interval.low < y->interval.low)
            y->left = z; // Case 2：若z的值<y的值，则将z设为y的左孩子
        else
            y->right = z; // Case 3：若z的值>=y所包含的值，则将z设为y的右孩子
    }
    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;
    Interval_Insert_Fixup(T, z);
}

// 新建一个具有键值interval的结点，并将其插入到区间树T中，返回指向该结点的指针
Node *Interval_Insert_interval(Tree *T, int low, int high)
{
    Node *node; // 新建结点

    if ((node = (Node *)malloc(sizeof(Node))) == NULL)
        return NULL;

    node->interval.low = low;
    node->interval.high = high;
    node->max = high;
    node->left = T->nil;
    node->right = T->nil;
    node->parent = NULL;
    node->color = RED;

    Interval_Insert(T, node);

    return node;
}

// 查找并返回区间树T中一个键值为interval的结点
Node *Interval_Search(Tree *T, Interval i)
{
    Node *node = T->root;
    while ((node != T->nil) && !Overlap(i, node->interval))
    {
        if (node->left != T->nil && node->left->max >= i.low)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

Node *Interval_Search_interval(Tree *T, int low, int high)
{
    Interval i;
    i.low = low;
    i.high = high;
    return Interval_Search(T, i);
}

// 创建一棵区间树
Tree *IntervalTree_Create()
{
    Tree *T = (Tree *)malloc(sizeof(Tree));
    T->nil = (Node *)malloc(sizeof(Node));
    T->nil->interval.low = 0;
    T->nil->interval.high = 0;
    T->nil->max = 0;
    T->nil->left = T->nil;
    T->nil->right = T->nil;
    T->nil->parent = T->nil;
    T->nil->color = BLACK;
    T->root = T->nil;

    return T;
}

/*
    打印区间树T中结点node的子树，direction表示node是其父结点的：
    左孩子：-1，右孩子：1
*/
void IntervalTree_Print(Tree *T, Node *node, int direction)
{
    if (node != T->nil)
    {
        if (direction == 0)
            printf("\033[40;37m[%-2d,%2d]\033[0m is ROOT, max: %2d\n", node->interval.low, node->interval.high, node->max);
        else
        {
            if (node->color == RED)
                printf("\033[41;37m[%-2d,%2d]\033[0mis [%-2d,%2d]'s %6s child, max: %2d\n", node->interval.low, node->interval.high, node->parent->interval.low, node->parent->interval.high, direction == 1 ? "right" : "left", node->max);
            else
                printf("\033[40;37m[%-2d,%2d]\033[0mis [%-2d,%2d]'s %6s child, max: %2d\n", node->interval.low, node->interval.high, node->parent->interval.low, node->parent->interval.high, direction == 1 ? "right" : "left", node->max);
        }
        IntervalTree_Print(T, node->left, -1);
        IntervalTree_Print(T, node->right, 1);
    }
}

int main()
{
    Tree *T = IntervalTree_Create();
    int a, b;
    int i;
    int n;
    Node *node;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        if ((node = Interval_Search_interval(T, a, b)) != T->nil)
        {
            // printf("Search Return [%-2d,%2d]\n", node->interval.low, node->interval.high);
            printf("-1\n");
        }
        else
        {
            Interval_Insert_interval(T, a, b);
            printf("0\n");
        }
        // IntervalTree_Print(T, T->root, 0);
    }
    return 0;
}