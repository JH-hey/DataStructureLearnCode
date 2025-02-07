#include <stdio.h>
#include <stdlib.h>
/* 定义树 */
typedef struct Tree
{
    struct Tree *lchild;
    char data;
    struct Tree *rchild;
} Tree;
/* 定义队列 */
typedef struct Queue
{
    Tree *data;
    struct Queue *next;
} Queue;

/* 初始化树 */
Tree *initTree()
{
    Tree *T = NULL;
    char ch;
    scanf("%c", &ch);
    if (ch != '#')
    {
        T = (Tree *)malloc(sizeof(Tree));
        T->data = ch;
        T->lchild = initTree();
        T->rchild = initTree();
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
    if (T)
    {
        printf("%c ", T->data);
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}
/* 创建队列 ,单链表*/
Queue *initQueue()
{
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->data = NULL;
    Q->next = NULL;
    return Q;
}
/* 入队 */
void enQueue(Tree *data, Queue *Q)
{
    /* 先找到最后一个结点 */
    Queue *p = Q;
    while (p->next != NULL)
    {
        p = p->next;
    }
    /* 开辟新节点空间 */
    Queue *node = (Queue *)malloc(sizeof(Queue));
    node->data = data;
    node->next = p->next;
    p->next = node;
    p = node;
}
/* 判断队列是否为空 */
int isEmpty(Queue *Q)
{
    if (Q->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* 出队 */
Queue *deQueue(Queue *Q)
{
    if (isEmpty(Q))
    {
        return NULL;
    }
    else
    {
        Queue *node = Q->next;
        Q->next = node->next;
        return node;
    }
}
/* 判断队列中的个数 */
int conutQueue(Queue *Q)
{
    Queue *node = Q->next; /* node指向首元结点 */
    int count = 0;
    while (node)
    {
        count++;
        node = node->next;
    }
    return count;
}

/*层序遍历 ,都在一行打印*/
void LevelTranverse(Tree *T)
{
    Tree *node = T;         /* 接受一下 */
    Queue *Q = initQueue(); /* 创立队列 */
    /* 根节点入队 */
    if (node)
    {
        enQueue(node, Q);
    }
    /* 开始遍历 */
    while (isEmpty(Q) == 0) /* 整个遍历的终止条件就是队列为空，因为空了，就没有需要打印的了，也就结束了 */
    {
        node = deQueue(Q)->data;   /* node指向出队的树结点 */
        printf("%c ", node->data); /* 打印 */
        if (node->lchild)          /* 如果出队的树结点的左孩子存在，则进入 */
        {
            enQueue(node->lchild, Q);
        }
        if (node->rchild) /* 如果出队的树结点的右孩子存在，则进入 */
        {
            enQueue(node->rchild, Q);
        }
    }
}

/* 层序遍历，分行打印 */
void LevelTranverse1(Tree *T)
{
    Tree *node = T;
    Queue *Q = initQueue();
    if (node)
    {
        enQueue(node, Q);
    }
    while (isEmpty(Q) == 0)
    {
        int size = conutQueue(Q);
        while (size != 0)
        {

            node = deQueue(Q)->data;
            printf("%c ", node->data);
            if (node->lchild)
            {
                enQueue(node->lchild, Q);
            }
            if (node->rchild)
            {
                enQueue(node->rchild, Q);
            }
            size--; /* 别忘了 */
        }
        printf("\n"); /* 此行打印完毕 */
    }
}

int main()
{
    Tree *T = initTree();
    preOrder(T);
    printf("\n");
    LevelTranverse(T);
    printf("\n");
    LevelTranverse1(T);
    return 0;
}
