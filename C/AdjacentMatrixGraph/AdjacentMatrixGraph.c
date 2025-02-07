#include <stdio.h>
#include <stdlib.h>

/* 定义结构体 */
typedef struct Graph
{
    char *vexs;  /* 指向顶点数组 */
    int **arcs;  /* 指向一个数组，此数组里面每一个值，都是指向一个数组，这个数组储存着边的情况 */
    int vexsnum; /* 有多少个顶点 */
    int arcsnum; /* 有多少条边 */
} Graph;

/* 初始化出一个图 */
Graph *initGraph(int vexsnum) /* 传入顶点数 */
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->vexs = (char *)malloc(sizeof(char) * vexsnum);
    G->arcs = (int **)malloc(sizeof(int *) * vexsnum);
    for (int i = 0; i < vexsnum; i++)
    {
        G->arcs[i] = (int *)malloc(sizeof(int) * vexsnum);
    }
    G->vexsnum = vexsnum;
    G->arcsnum = 0;
    return G;
}
/* 给图赋值 */
/* 传入的参数：图，字符串数组，边数组 */
void createGraph(Graph *G, char *vexs, int arcs[5][5]) /* 这里如果直接写int **arcs会报错 */
{
    for (int i = 0; i < G->vexsnum; i++)
    {
        G->vexs[i] = vexs[i];
        for (int j = 0; j < G->vexsnum; j++)
        {
            G->arcs[i][j] = arcs[i][j]; /* 边赋值 */
            if (G->arcs[i][j] != 0)
            {
                G->arcsnum++; /* 边计数 */
            }
        }
    }
    G->arcsnum = G->arcsnum / 2;
}
/* 深度优先遍历 */
void DFS(Graph *G, int index, int *visted)
{
    printf("%c ", G->vexs[index]);
    visted[index] = 1;
    for (int i = 0; i < G->vexsnum; i++)
    {
        if (G->arcs[index][i] == 1 && visted[i] == 0)
        {
            DFS(G, i, visted);
        }
    }
}
/* 广度优先遍历，需要队列 */
typedef struct Queue
{
    int num;
    struct Queue *next;
} Queue;
/* 新建队列 */
Queue *initQueue()
{
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->num = 0;
    Q->next = NULL;
    return Q;
}

/* 入队，采用尾插法 */
void enQueue(Queue *Q, int data)
{
    Queue *node = (Queue *)malloc(sizeof(Queue));
    node->num = data;
    /* 寻找尾结点 */
    Queue *q = Q;
    while (q->next != NULL)
    {
        q = q->next;
    }
    node->next = q->next;
    q->next = node;
    q = node;
    Q->num++;
}
/* 判断是否为空 */
int isEmpty(Queue *Q)
{
    if (Q->num == 0 || Q->next == NULL)
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
        Queue *q = Q->next;
        Q->next = q->next;
        int value;
        value = q->num;
        free(q);
        Q->num--;
        return value;
    }
}

/* 这里采用，入队前就是访问完毕 */
void BFS(Graph *G, int index, int *visited)
{
    Queue *Q = initQueue();
    enQueue(Q, index);
    printf("%c ", G->vexs[index]);
    visited[index] = 1;
    while (!isEmpty(Q))
    {
        int i = deQueue(Q);
        for (int j = 0; j < G->vexsnum; j++)
        {
            if (G->arcs[i][j] == 1 && visited[j] == 0)
            {

                enQueue(Q, j);
                printf("%c ", G->vexs[j]);
                visited[j] = 1;
            }
        }
    }
}

int main()
{
    Graph *G = initGraph(5);
    char vexs[5] = {'A', 'B', 'C', 'D', 'E'};
    int arcs[5][5] = {
        {0, 1, 1, 1, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 1},
        {0, 1, 0, 1, 0}};
    createGraph(G, vexs, arcs);
    int *visited = (int *)malloc(sizeof(int) * G->vexsnum);
    for (int i = 0; i < G->vexsnum; i++)
    {
        visited[i] = 0;
    }
    DFS(G, 0, visited);
    printf("\n");
    /* visted函数调0 */
    for (int i = 0; i < G->vexsnum; i++)
    {
        visited[i] = 0;
    }
    BFS(G, 0, visited);
    return 0;
}
/*
输出结果:
ABCDE
ABCDE */