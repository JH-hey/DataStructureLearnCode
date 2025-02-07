#include <stdio.h>
#include <stdlib.h>

/* 定义结构体 */
typedef struct Tree
{
    struct Tree *lchild;
    int data;
    struct Tree *rchild;
} Tree;

/* 查找算法 */
Tree *BstSearch(Tree *T, int key) /* 这里主函数中传入根节点T */
{
    if (T)
    {
        if (T->data == key)
        {
            return T;
        }
        else if (T->data > key)
        {
            return BstSearch(T->lchild, key);
        }
        else
        {
            return BstSearch(T->rchild, key);
        }
    }
    else
    {
        return NULL; /*  递归终止的逻辑*/
    }
}

/* 创建BST，创建也是排序的过程 */
/* 这个函数需要用到引用 */
/* 由于主函数要传进来根节点，且根节点要通过此函数进行改变其值（lchild,rchild），不只是像平常一样仅需要借鉴根节点的值而不需要对其进行改变。因此这里用引用类型，来使得在函数内改变主函数的T。（因为想要改变主函数的值，必须在主函数中改变，在函数中改变无效，除非用引用）。
除此之外，此函数是递归操作，后面的递归函数也要改变前面递归函数传进来的变量值，因此要用引用*/
/* 判断函数是否要用引用：
在此函数（下级函数）中要对主函数（上一级函数）中某变量值进行改变&&这个变量要传入到此函数（下级函数）中作为形参 */
void BstInsert(Tree *&T, int key)
{
    if (T == NULL)
    {
        /* 递归终止 */
        /* 当此处结点不存在时，就可以插入了 */
        T = (Tree *)malloc(sizeof(Tree));
        T->data = key;
        T->lchild = NULL;
        T->rchild = NULL;
    }
    else
    {
        if (T->data > key)
        {
            BstInsert(T->lchild, key);
        }
        else if (T->data < key)
        {
            BstInsert(T->rchild, key);
        }
        else /* 当T->data==key时 */
        {
            return; /* 直接此key不用插入了 */
        }
    }
}

/* 前序遍历 */
void preOrder(Tree *T)
{
    if (T) /* 递归终止条件是：此节点存在 */
    {
        printf("%d ", T->data);
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}

int main()
{
    Tree *T = NULL;
    int num[7] = {4, 5, 2, 3, 6, 5, 8};
    for (int i = 0; i < 7; i++)
    {
        BstInsert(T, num[i]);
    }
    preOrder(T);
    printf("\n");
    Tree *node = BstSearch(T, 6);
    printf("%d", node->data);
}
