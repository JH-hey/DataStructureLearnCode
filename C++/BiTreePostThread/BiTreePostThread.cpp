#include <stdio.h>
#include <stdlib.h>
/* 定义结构体，此时用三叉树 */
typedef struct Tree
{
    struct Tree *lchild;
    int ltag;

    char data;
    struct Tree *parent;

    struct Tree *rchild;
    int rtag;
} Tree;

Tree *creatTree(Tree *parent) /* 每次建立新的结点时，要把其parent传进去 */
{
    Tree *T; /* 内部容器 */
    char ch;
    scanf("%c", &ch);
    if (ch != '#')
    {
        T = (Tree *)malloc(sizeof(Tree));
        T->data = ch;
        T->ltag = 0;
        T->rtag = 0;
        T->parent = parent;
        T->lchild = creatTree(T); /* 传进来的parent，就是指向刚刚被新建结点的指针 */
        T->rchild = creatTree(T);
    }
    else
    {
        return NULL;
    }
    return T;
}

/* 线索化具体函数 */
/* 要用引用类型，因为此函数要对上一级函数传入的结点p做出改变其值 */
void postThread(Tree *&p, Tree *&pre)
{
    if (p)
    {

        /* 仅仅置换顺序，无太大差异 */
        /* 先处理左 */
        postThread(p->lchild, pre);
        /* 处理右 */
        postThread(p->rchild, pre);
        /* 处理当前结点 */
        if (p->lchild == NULL)
        {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL)
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
    }
}
/* 线索化主函数 */
void creatPostThread(Tree *T)
{
    Tree *pre = NULL;
    if (T)
    {
        postThread(T, pre);
        /* pre->rchild=NULL;
        pre->rtag=1
        这两行不要了，因为后序遍历的最后一个是根节点 */
    }
}

/* 开始遍历操作 */
Tree *getfirst(Tree *node)
{
    /* 先找到最左边 */
    while (node->ltag == 0)
    {
        node = node->lchild;
    }
    /* 执行判断 */
    if (node->rtag == 0)
    {
        return getfirst(node->rchild);
    }
    else
    {
        return node;
    }
}
Tree *getnext(Tree *node)
{
    if (node->rtag == 1)
    {
        return node->rchild;
    }
    else
    { /* 如果是根节点 */
        if (node->parent == NULL)
        {
            return NULL;
        }
        /* 如果此结点是右孩子 */
        else if (node->parent->rchild == node)
        {
            return node->parent;
        }
        else /*如果此结点是左孩子  */
        {    /* 如果此结点的parent的右孩子不为空 */
            if (node->parent->rtag == 0)
            {
                return getfirst(node->parent->rchild);
            }
            else
            {
                return node->parent;
            }
        }
    }
}

int main()
{
    Tree *T;
    T = creatTree(NULL);

    creatPostThread(T);
    for (Tree *node = getfirst(T); node != NULL; node = getnext(node))
    {
        printf("%c ", node->data);
    }
    printf("\n");
    return 0;
}

/*
输入：AB#D##CE###
结果：DBECA
 */