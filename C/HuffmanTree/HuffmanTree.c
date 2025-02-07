#include <stdio.h>
#include <stdlib.h>

/* 定义第一个结构体 */
/* 数组里面每一个的内容 */
typedef struct Tree
{
    int weight;
    int parent;
    int lchild;
    int rchild;
} Tree;
/* 定义第二个结构体 */
typedef struct HuffmanTree
{
    struct Tree *data; /* data是数组的首地址，去指向数组 */
    int length;        /* 记录当前数组里面有几个东西 */
} HuffmanTree;

/* 将数值先一起输入到数组中去 */
HuffmanTree *initTree(int *weight, int length)
{
    HuffmanTree *T = (HuffmanTree *)malloc(sizeof(HuffmanTree));
    T->length = length;
    T->data = (Tree *)malloc(sizeof(Tree) * (2 * length - 1));
    for (int i = 0; i < T->length; i++)
    {
        T->data[i].weight = weight[i];
        T->data[i].parent = -1;
        T->data[i].lchild = -1;
        T->data[i].rchild = -1;
    }
    return T;
}

int *selectMin(HuffmanTree *T)
{
    int min = 1000;
    int secondMin = 1000;
    int minIndex;
    int secondMinIndex;
    for (int i = 0; i < T->length; i++)
    {
        if (T->data[i].parent == -1) /* 说明之前没有被比较过 */
        {
            if (T->data[i].weight < min)
            {
                min = T->data[i].weight;
                minIndex = i;
            }
        }
    }

    for (int i = 0; i < T->length; i++)
    {
        if (T->data[i].parent == -1 && i != minIndex)
        {
            if (T->data[i].weight < secondMin)
            {
                secondMin = T->data[i].weight;
                secondMinIndex = i;
            }
        }
    }
    int *res = (int *)malloc(sizeof(int) * 2);
    res[0] = minIndex;
    res[1] = secondMinIndex;
    return res;
}

void createHuffmanTree(HuffmanTree *T)
{
    int minIndex;
    int secondMinIndex;
    int *res;
    int boundary = T->length * 2 - 1;
    for (int i = T->length; i < boundary; i++)
    {
        res = selectMin(T);
        minIndex = res[0];
        secondMinIndex = res[1];
        T->data[i].weight = T->data[minIndex].weight + T->data[secondMinIndex].weight;
        T->data[i].parent = -1;
        T->data[i].lchild = minIndex;
        T->data[i].rchild = secondMinIndex;
        T->data[minIndex].parent = i;
        T->data[secondMinIndex].parent = i;
        T->length++;
    }
}

void preOrder(HuffmanTree *T, int index)
{
    if (index != -1)
    {
        printf("%d ", T->data[index].weight);
        preOrder(T, T->data[index].lchild);
        preOrder(T, T->data[index].rchild);
    }
}

int main()
{
    int weight[7] = {5, 1, 3, 6, 11, 2, 4};
    HuffmanTree *T;
    T = initTree(weight, 7);
    createHuffmanTree(T);
    preOrder(T, T->length - 1);
}

/*
输入：上述
输出：32 12 6 6 3 3 1 2 20 9 4 5 11
输入:int weight[4]=1,2,3,4;
输出:10 4 6 3 3 1 2
 */
