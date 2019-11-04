//数据库查询v1
//插入语句和查询语句yi一共不超过2000000条。
//0 <= key <= 10^9

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
    y->left = x;   // 将x设为y的左孩子
    x->parent = y; // 将x的父节点设为y
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
    x->right = y;  // 将y设为x的右孩子
    y->parent = x; // 将y的父节点设为x
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

    RB_Insert(T, node);

    return node;
}

// 返回结点x的直接前驱
Node *RB_Predecessor(Tree *T, Node *x)
{
    if (x->left == T->nil) // x没有左孩子
    {
        while (x->parent != T->nil && x->parent->left == x) // 向上查找直到x是某个结点的右子树的成员
            x = x->parent;
        x = x->parent;
    }
    else
    {
        x = x->left; // 直接前驱是x左子树中的最大值
        while (x->right!=T->nil)
        {
            x=x->right;
        }
    }
    return x;
}

// 查找并返回红黑树T中一个键值为key的结点，若没有这样的结点则返回键值比key小的最大结点
Node *RB_Search_Alternative(Tree *T, Type key)
{
    Node *node = T->root;
    while ((node != T->nil) && (node->key != key))
    {
        if (key < node->key)
        {
            if (node->left != T->nil)
                node = node->left;
            else // 没有再比node小的结点了
            {
                node = RB_Predecessor(T, node); // 返回node的直接前驱
                break;
            }
        }
        else
        {
            if (node->right != T->nil) // 没有再比node大的结点
                node = node->right; // node即满足要求
            else
                break;
        }
    }
    return node;
}

int main()
{
    Tree *T = RBTree_Create();
    int n;
    int i;
    char command[7];
    Type key;

    while (scanf("%s", command) == 1 && command[0] != 'E')
    {
        if (command[0] == 'I') //INSERT
        {
            scanf("%d", &key);
            RB_Insert_Key(T, key);
        }
        else if (command[0] == 'F') //FIND
        {
            scanf("%d", &key);
            printf("%d\n", RB_Search_Alternative(T, key)->key);
        }
        else
            printf("ERROR");
    }
    return 0;
}