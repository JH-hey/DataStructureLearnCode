#include <stdio.h>
#include <stdlib.h>
typedef struct Tree
{
    struct Tree *lchild;
    char data;
    struct Tree *rchild;
} Tree;

/* 这里面的返回，可以想象成在主函数有个容器等着，在函数内部有相应的容器去拿这个值，最后通过return，把内部容器内的值返回到函数外面等待承接的那个容器 */
Tree *initTree()
{
    Tree *T = NULL; /* 函数内部的头指针，内部的指针容器盛放头指针 */
    char ch;
    scanf("%c", &ch);
    if (ch != '#')
    {
        /* 需注意，树的头指针直接指向第一个结点，无头结点 */
        T = (Tree *)malloc(sizeof(Tree)); /* 当字符可以时，指针指向新建的结点 */
        T->data = ch;                     /* 给结点的data进行赋值 */
        T->lchild = initTree();           /* 左孩子进行递归 */
        T->rchild = initTree();           /* 右边孩子进行递归 */
    }
    else
    {
        T = NULL; /* 如果字符是#，则到头了，指针容器赋值NULL */
    }
    return T; /* 返回指针容器内的值 */
}
/* 前序遍历 */
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
/*  中序遍历*/
void inOrder(Tree *T)
{
    if (T != NULL)
    {

        inOrder(T->lchild);
        printf("%c ", T->data);
        inOrder(T->rchild);
    }
    else
    {
        return; /* 终止时的操作 */
    }
}
/* 后序遍历 */
void backOrder(Tree *T)
{
    if (T != NULL)
    {

        backOrder(T->lchild);
        backOrder(T->rchild);
        printf("%c ", T->data);
    }
    else
    {
        return;
    }
}
int main()
{
    Tree *T = initTree();
    preOrder(T);
    printf("\n");
    inOrder(T);
    printf("\n");
    backOrder(T);
    printf("\n");
    return 0;
}
/*
输入:AB#D##CE###
结果:
A B D C E
B D A E C
D B E C A
 */