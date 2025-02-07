#include <stdio.h>
#include <stdlib.h>

/* 结构体 */
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
    Tree *T; /* 内部容器 */
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
/* 递归前序遍历 */
void preOrder(Tree *T)
{
    if (T != NULL)
    {
        printf("%c ", T->data);
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
    else
    {
        return;
    }
}
/* 线索的具体函数 */
void preThread(Tree *&p, Tree *&pre)
{
    if (p != NULL) /* 起始条件是当前结点不为空，因为为空则说明线索化完成了 */
    {
        /* 先操作中间 */
        if (p->lchild == NULL) /* 建立前驱 */
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
        /* 操作左结点 */
        /* 要注意，我们preThread函数中操作的p->lchild一定是没有被赋值过的。NULL或者有左孩子。如果p->lchild为空，则在上一步函数中已经被赋值给了前驱，不是最初始的值了。因此，要判断如果ltag=1，则p-lchild被重现赋值了，是指向前驱，如果进入了preThread函数是不对的，会发生再次操作前面已经操作的过程。 */
        if (p->ltag == 0)
        {
            preThread(p->lchild, pre);
        }
        /* 这里也要注意，判断p->rtag是否为1，为1，则p->rchild之前被重新赋值了 */
        if (p->rtag == 0)
        {
            preThread(p->rchild, pre);
        }
    }
}
/* 线索总函数 */
void creatPreThread(Tree *T)
{
    Tree *pre = NULL; /* 全局变量pre指针 */
    if (T)
    {
        preThread(T, pre);  /* 进去具体函数 */
        pre->rchild = NULL; /* 最后的prerchild操作 */
        pre->rtag = 1;
    }
}
Tree *getnext(Tree *node)
{
    if (node->ltag == 0) /* 如果该结点有左孩子，则next为该节点的左孩子 */
    {
        return node->lchild;
    }
    else /* 如果该结点没有左孩子，则next是其右孩子或者其后继 */
    {
        return node->rchild;
    }
}

int main()
{
    Tree *T;
    T = creatTree();
    creatPreThread(T);
    for (Tree *node = T; node != NULL; node = getnext(node))
    {
        printf("%c ", node->data);
    }
    printf("\n");
}
/*
输入:AB#D##CE###
结果:ABDCE
 */
