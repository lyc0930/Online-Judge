// 在线比赛
// 0 < n <= 2000000
// I D K

// Argumenting Red-Black Tree
#include <stdio.h>
#include <stdlib.h>

typedef int Type;

enum Color
{
    RED,
    BLACK
};

// 红黑树的节点
typedef struct RBTreeNode
{
    enum Color color;
    Type key;
    int size;
    struct RBTreeNode *left;
    struct RBTreeNode *right;
    struct RBTreeNode *parent;
} Node;

// 红黑树
typedef struct RBTree
{
    Node *root;
    Node *nil;
} Tree;

// 对红黑树T的节点x进行左旋
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
    y->left = x;                                  // 将x设为y的左孩子
    x->parent = y;                                // 将x的父节点设为y
    y->size = x->size;                            // Order Statistics
    x->size = x->left->size + x->right->size + 1; // Order Statistics
}

// 对红黑树T的节点y进行右旋转
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
    x->right = y;                                 // 将y设为x的右孩子
    y->parent = x;                                // 将y的父节点设为x
    x->size = y->size;                            // Order Statistics
    y->size = y->left->size + y->right->size + 1; // Order Statistics
}

void RB_Insert_Fixup(Tree *T, Node *z);

// 将节点z插入到红黑树T中
void RB_Insert(Tree *T, Node *z)
{
    Node *y = T->nil;
    Node *x = T->root;
    while (x != T->nil)
    {
        y = x;
        y->size++; // Order Statistics
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == T->nil)
        T->root = z; // Case 1：若y是空节点，则将z设为根
    else
    {
        if (z->key < y->key)
            y->left = z; // Case 2：若z的值<y的值，则将z设为y的左孩子
        else
            y->right = z; // Case 3：若z的值>=y所包含的值，则将z设为y的右孩子
    }
    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;
    RB_Insert_Fixup(T, z);
}

// 红黑树插入修正
void RB_Insert_Fixup(Tree *T, Node *z)
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

/*
    返回红黑树T中子树x的最小结点，并对沿途结点的size增/减量c
    c的取值可能为：
    0 简单查询；1 插入时沿途增量； -1 删除时沿途减量
*/
Node *RB_SeekMinimum(Tree *T, Node *x, int c)
{
    while (x->left != T->nil)
    {
        x->size += c;
        x = x->left;
    }
    return x;
}

// 将红黑树中的结点u移植为结点v
void RB_Transplant(Tree *T, Node *u, Node *v)
{
    if (u->parent == T->nil)
        T->root = v;
    else
    {
        if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
    }
    v->parent = u->parent;
}

void RB_Delete_Fixup(Tree *T, Node *x);

// 从红黑树T中删除节点z
void RB_Delete(Tree *T, Node *z)
{
    Node *y = z;
    enum Color y_original_color = y->color;

    Node *x = T->root;
    while (x != z) // Order Statistics
    {
        x->size--;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    if (z->left == T->nil)
    {
        x = z->right;
        RB_Transplant(T, z, z->right);
    }
    else
    {
        if (z->right == T->nil)
        {
            x = z->left;
            RB_Transplant(T, z, z->left);
        }
        else
        {
            y = RB_SeekMinimum(T, z->right, -1);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) // y是z的右孩子且没有左孩子
                x->parent = y;
            else // 否则y一定是其父亲的左孩子且没有左孩子
            {
                RB_Transplant(T, y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            RB_Transplant(T, z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
            y->size = y->left->size + y->right->size + 1;
        }
    }
    if (y_original_color == BLACK)
        RB_Delete_Fixup(T, x);
    free(z);

}

// 红黑树删除修正
void RB_Delete_Fixup(Tree *T, Node *x)
{
    while ((x != T->root) && (x->color == BLACK))
    {
        if (x == x->parent->left)
        {
            Node *w = x->parent->right;
            if (w->color == RED) // Case 1:
            {
                w->color = BLACK;
                x->parent->color = RED;
                Left_Rotate(T, x->parent);
                w = x->parent->right;
            }
            if ((w->left->color == BLACK) && (w->right->color == BLACK)) // Case 2:
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK) // Case 3:
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    Right_Rotate(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color; // Case 4:
                x->parent->color = BLACK;
                w->right->color = BLACK;
                Left_Rotate(T, x->parent);
                x = T->root;
            }
        }
        else
        {
            Node *w = x->parent->left;
            if (w->color == RED) // Case 1:
            {
                w->color = BLACK;
                x->parent->color = RED;
                Right_Rotate(T, x->parent);
                w = x->parent->left;
            }
            if ((w->right->color == BLACK) && (w->left->color == BLACK)) // Case 2:
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    Left_Rotate(T, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                Right_Rotate(T, x->parent);
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}

// 查找并返回红黑树T中一个键值为key的结点
Node *RB_Search(Tree *T, Type key)
{
    Node *node = T->root;
    while ((node != T->nil) && (node->key != key))
    {
        if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

// 创建一棵红黑树
Tree *RBTree_Create()
{
    Tree *T = (Tree *)malloc(sizeof(Tree));
    T->nil = (Node *)malloc(sizeof(Node));
    T->nil->key = 0;
    T->nil->left = T->nil;
    T->nil->right = T->nil;
    T->nil->parent = T->nil;
    T->nil->color = BLACK;
    T->nil->size = 0; // Order Statistics
    T->root = T->nil;

    return T;
}

// 新建一个具有键值key的结点，并将其插入到红黑树T中，返回指向该结点的指针
Node *RB_Insert_Key(Tree *T, Type key)
{
    Node *node; // 新建结点

    if ((node = (Node *)malloc(sizeof(Node))) == NULL)
        return NULL;

    node->key = key;
    node->left = T->nil;
    node->right = T->nil;
    node->parent = NULL;
    node->color = RED;
    node->size = 1;

    RB_Insert(T, node);

    return node;
}

// 从红黑树T中查找并删除一个键值为key的结点
void RB_Delete_Key(Tree *T, Type key)
{
    Node *node = RB_Search(T, key);
    if (node != T->nil)
        RB_Delete(T, node);
}

// 查找具有给定秩的元素
Node *OS_Select(Tree *T, int i)
{
    Node *node = T->root;
    int r = node->left->size + 1;
    while (i != r)
    {
        if (i > r)
        {
            node = node->right;
            i = i - r;
        }
        else
            node = node->left;
        r = node->left->size + 1;
    }
    return node;
}

/*
    打印红黑树T中结点node的子树，direction表示node是其父结点的：
    左孩子：-1，右孩子：1
*/
void RB_Print(Tree *T, Node *node, int direction)
{
    if (node != T->nil)
    {
        if (direction == 0)
            printf("\033[40;37m%-3d\033[0m is ROOT, size = %3d\n", node->key, node->size);
        else
        {
            if (node->color == RED)
                printf("\033[41;37m%-3d\033[0mis %3d's %6s child, size = %3d\n", node->key, node->parent->key, direction == 1 ? "right" : "left", node->size);
            else
                printf("\033[40;37m%-3d\033[0mis %3d's %6s child, size = %3d\n", node->key, node->parent->key, direction == 1 ? "right" : "left", node->size);
        }
        RB_Print(T, node->left, -1);
        RB_Print(T, node->right, 1);
    }
}

int main()
{
    Tree *T = RBTree_Create();
    int n;
    int i;
    char command;
    int k;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        getchar();
        scanf("%c %d", &command, &k);
        if (command == 'I')
            RB_Insert_Key(T, k);
        else if (command == 'D')
            RB_Delete_Key(T, k);
        else if (command == 'K')
            printf("%d\n", OS_Select(T, k)->key);
    }

    // while(1)
    // {
    //     scanf("%c %d", &command, &k);
    //     getchar();
    //     if (command == 'I')
    //         RB_Insert_Key(T, k);
    //     else if (command == 'D')
    //         RB_Delete_Key(T, k);
    //     else if (command == 'K')
    //         printf("%d\n", OS_Select(T, k)->key);
    //     RB_Print(T, T->root, 0);
    // }
    return 0;
}