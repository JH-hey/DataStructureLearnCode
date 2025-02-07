#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int data;
    struct Node *next;
} Node;
/* 新建队列 */
Node *iniQueue()
{
    Node *Q = (Node *)malloc(sizeof(Node));
    Q->data = 0; /* 记录队列中元素个数 */
    Q->next = NULL;
    return Q;
}
/* 入队——尾插法 */
void enQueue(Node *Q, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    /* 寻找尾结点 */
    Node *q = Q;
    while (q->next != NULL)
    {
        q = q->next;
    }
    /* 操作 */
    node->next = q->next;
    q->next = node;
    q = node;
    Q->data++;
}
/* 判断是否为空 */
int isEmpty(Node *Q)
{
    if (Q->data == 0 || Q->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/* 出队 */
int deQueue(Node *Q)
{
    if (isEmpty(Q))
    {
        return -1;
    }
    else
    {
        Node *q = Q->next;
        int value;
        Q->next = q->next;
        value = q->data;
        free(q);
        Q->data--;
        return value;
    }
}
/* 取对头元素 */
int gethead(Node *Q)
{
    if (isEmpty(Q))
    {
        return -1;
    }
    else
    {
        return Q->next->data;
    }
}
/* 遍历打印 */
void printQueue(Node *Q)
{
    Node *q = Q->next;
    printf("当前队列:\n");
    while (q != NULL)
    {
        printf("%d->", q->data);
        q = q->next;
    }
    printf("NULL ");
    printf("元素个数是%d\n", Q->data);
}

int main()
{
    Node *Q = iniQueue();
    enQueue(Q, 1);
    enQueue(Q, 2);
    enQueue(Q, 3);
    enQueue(Q, 4);
    enQueue(Q, 5);
    printQueue(Q);
    int i = deQueue(Q);
    printf("出队元素=%d\n", i);
    printQueue(Q);
    int head = gethead(Q);
    printf("对头元素是%d\n", head);
    /* 全部出对 */
    i = deQueue(Q);
    i = deQueue(Q);
    i = deQueue(Q);
    i = deQueue(Q);
    printQueue(Q);
    return 0;
}