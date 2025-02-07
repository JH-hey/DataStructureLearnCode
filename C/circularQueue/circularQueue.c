#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 5
/* 初始化结构体 */
typedef struct Queue
{
    int front; /* 代表头指针，偏移数 */
    int rear;  /* 代表尾指针，偏移数 */
    int data[MAXSIZE];
} Queue;

/* 初始化 */
Queue *iniQueue()
{
    Queue *Q = (Queue *)malloc(sizeof(Queue)); /* 和链表一样，把数组的地址赋给一个指针，通过操纵指针来操纵数组 */
    Q->front = 0;
    Q->rear = 0; /*头指针和尾指针，偏移数都为0，即都指向数组的第一位data[0] */
    return Q;
}
/* 判断是否满了？ */
int isFull(Queue *Q)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)
    {
        return 1; /* 满了 */
    }
    else
    {
        return 0;
    }
}
/* 插入 */
int enQueue(Queue *Q, int data)
{
    if (isFull(Q))
    {
        return -1; /* 满了，这里默认，插入的都是正数 */
    }
    else
    {
        Q->data[Q->rear] = data;
        Q->rear = (Q->rear + 1) % MAXSIZE;
        return 1; /* 证明插入成功 */
    }
}

int isEmpty(Queue *Q)
{
    if (Q->rear == Q->front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/* 出队 */
int deQueue(Queue *Q)
{
    if (isEmpty(Q))
    {
        return -1;
    }
    else
    {
        int value;
        value = Q->data[Q->front];
        Q->front = (Q->front + 1) % MAXSIZE;
        return value;
    }
}
/* 返回队列头元素 */
int gethead(Queue *Q)
{
    if (isEmpty(Q))
    {
        return -1;
    }
    else
    {
        return Q->data[Q->front];
    }
}
/* 遍历打印 */
void printQueue(Queue *Q)
{
    int length = (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
    int index = Q->front;
    for (int i = 0; i < length; i++)
    {
        printf("%d->", Q->data[index]);
        index = (index + 1) % MAXSIZE;
    }
    printf("NULL ");
    printf("元素个数是%d\n", length);
}
int main()
{
    Queue *Q = iniQueue();
    enQueue(Q, 1);
    enQueue(Q, 2);
    enQueue(Q, 3);
    enQueue(Q, 4);
    printQueue(Q);
    printf("出列:\n");
    printf("出列元素:%d\n", deQueue(Q));
    printf("当前队列:\n");
    printQueue(Q);
    printf("队头元素:\n");
    printf("%d\n", gethead(Q));
    return 0;
}