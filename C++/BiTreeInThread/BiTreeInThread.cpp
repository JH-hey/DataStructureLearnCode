#include <stdio.h>
#include <stdlib.h>

/* 定义结构体 */
typedef struct Tree
{
    struct Tree *lchild;
    int ltag;
    char data;
    struct Tree *rchild;
    int rtag;
} Tree;
/* 初始化树 */
Tree *creatTree()
{
    Tree *T;
    char ch;
    scanf("%c", &ch);
    if (ch != '#')
    {
        T = (Tree *)malloc(sizeof(Tree));
        T->data = ch;
        T->ltag = 0;
        T->rtag = 0;
        T->lchild = creatTree();
        T->rchild = creatTree();
    }
    else
    {
        T = NULL;
    }
    return T;
}

/* 线索化的具体函数,由于下面的线索化主函数需要调用此具体函数，所以先写具体函数 */
void InThread(Tree *&p, Tree *&pre) /* p这里传进来的是当前操作的结点，pre代表p前面的结点 */
{
    if (p != NULL)
    {
        InThread(p->lchild, pre); /* 递归其左孩子 */
        if (p->lchild == NULL)    /* 当前结点，建立前驱 */
        {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) /* 当前结点前的结点，建立后驱 */
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;                  /* pre挪到p的位置 */
        InThread(p->rchild, pre); /* 递归其右孩子 */
    }
}

/* 线索化的主函数 */
void creatInThread(Tree *T)
{
    Tree *pre = NULL; /* 全局变量pre */
    if (T != NULL)
    {
        InThread(T, pre);
        pre->rchild = NULL; /* 处理最后的一个结点的后继 */
        pre->rtag = 1;
    }
}

/* 找到第一个结点 */
Tree *getfirst(Tree *T)
{
    Tree *node = T;
    while (node->ltag == 0)
    {
        node = node->lchild;
    }
    return node;
}
/* 获得当前结点的下一个结点 */
Tree *getnext(Tree *node)
{
    if (node->rtag == 1) /* node->rtag=1，说明下一个结点就是node->rchild */
    {
        return node->rchild;
    }
    else /* 否则，则下一个结点应该是以node->rchild为根节点的getfirst */
    {
        return getfirst(node->rchild);
    }
}

int main()
{
    Tree *T;
    T = creatTree();

    printf("\n");
    creatInThread(T);
    /* 打印 */
    for (Tree *node = getfirst(T); node != NULL; node = getnext(node))
    {
        printf("%c ", node->data);
    }
    printf("\n");
}

/*
输入AB#D##CE###
结果:BDAEC
 */
