#include <stdio.h>
#include <stdlib.h>

// 每个人的信息元素的重新构造，即变量。此变量与int、char同一个层次。里面包括name数组，sex
typedef struct Person
{
    char name[20];
    char sex;
} Person;

typedef struct Queue /* 创建队列的结构体。包括Persen类型的数组，头尾指针 */
{
    int front;
    int rear;
    Person dancers[20];
} Queue;

/* 队列初始化 */
Queue *initQueue()
{
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->rear = 0;
    Q->front = 0;
    return Q; /* 把男女队列数组的地址返回出去，通过地址来进行操作数组 */
}

/* 判断队列是否为空 */
int isFull(Queue *Q)
{
    if ((Q->rear + 1) % 20 == Q->front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/* 插入 */
int enQueue(Queue *Q, Person everydancer) /* 将相应的Person类型数据插入到男队列或女队列 */
{
    if (isFull(Q))
    {
        return -1;
    }
    else
    {
        Q->dancers[Q->rear] = everydancer;
        Q->rear = (Q->rear + 1) % 20;
        return 1; /* 证明插入成功 */
    }
}
/* 是否为空 */
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
/* 出队列的头元素。注意这里返回的是Person类型数据 */
Person deQueue(Queue *Q)
{

    Person value;
    value = Q->dancers[Q->front];
    Q->front = (Q->front + 1 % 20);
    return value;
}
/* 获得队头元素。注意这里返回的是Person类型数据 */
Person gethead(Queue *Q)
{

    return Q->dancers[Q->front];
}

/* 遍历男女队列中的名字 */
void printQueue(Queue *Q)
{
    int length = (Q->rear - Q->front + 20) % 20;
    int index = Q->front;
    for (int i = 0; i < length; i++)
    {
        printf("%s->", Q->dancers[index].name); /* 因为打印的name是一串字符数组，所以用%s。还要注意，打印的是.name */
        index = (index + 1) % 20;
    }
    printf("NULL ");
    printf("元素个数是%d\n", length);
}

/* 操作函数 */
void dancers(Person p[20], Queue *mq, Queue *fq, int num)
{
    /* 先将信息存储到信息数组p中 */
    for (int i = 0; i < num; i++)
    {
        printf("请输入第%d个舞者的名字:\n", i + 1);
        scanf("%s", &p[i].name); /* 存储第i+1个Person类型数据的name */
        printf("请输入第%d个人的性别(f/m)\n", i + 1);
        scanf("%s", &p[i].sex); /* 存储第i+1个Person类型数据的sex */
    }
    /* 男女信息开始各自往男女队列中插入 */
    for (int i = 0; i < num; i++)
    {
        Person q = p[i]; /* 取Person数组中的每一个Person类型数据 */
        if (q.sex == 'm')
        {
            enQueue(mq, q);
        }
        else
        {
            enQueue(fq, q);
        }
    }
    /* 查看男女队列中情况 */
    printf("当前如下:\n");
    printQueue(mq);
    printQueue(fq);
    /* 查看匹配结果 */
    printf("匹配如下:\n");
    while (isEmpty(mq) == 0 && isEmpty(fq) == 0)
    {
        /* 注意deQueue()函数返回的是每一个Person类型数据，这里需要打印名字，故加上.name，取到Person类型数据里面name项 */
        printf("男生:%s  ", deQueue(mq).name);
        printf("女生:%s\n", deQueue(fq).name);
    }
    if (isEmpty(mq) == 0)
    {
        /* 注意gethead()函数返回的是每一个Person类型数据，这里需要打印名字，故加上.name，取到Person类型数据里面name项 */
        printf("下一个等待匹配的人:%s\n", gethead(mq).name);
    }
    if (isEmpty(fq) == 0)
    {
        printf("下一个等待匹配的人:%s\n", gethead(fq).name);
    }
}

int main()
{
    int num;
    Person p[20];            /* 创建未加处理的信息数组 */
    Queue *mq = initQueue(); /*创建男队 */
    Queue *fq = initQueue(); /*创建女队 */
    printf("请输入总共的男士与女士的总人数：\n");
    scanf("%d", &num);
    if (num > 20)
    {
        exit(0);
    }
    while (num <= 0)
    {
        printf("输入错误，请重新输入\n");
        scanf("%d", &num);
    }
    dancers(p, mq, fq, num); /* 进行操作 */
    return 0;
}