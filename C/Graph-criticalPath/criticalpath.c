#include <stdio.h>
#include <stdlib.h>
#define max 9834

typedef struct Graph
{
    char *ves;
    int **arcs;
    int vesnum;
    int arcsnum;
} Graph;

Graph *initGraph(int vesnum)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->ves = (char *)malloc(sizeof(char) * vesnum);
    G->arcs = (int **)malloc(sizeof(int *) * vesnum);
    for (int i = 0; i < vesnum; i++)
    {
        G->arcs[i] = (int *)malloc(sizeof(int) * vesnum);
    }
    G->vesnum = vesnum;
    G->arcsnum = 0;
    return G;
}

void createGraph(Graph *G, char *ves, int arcs[9][9])
{
    for (int i = 0; i < G->vesnum; i++)
    {
        G->ves[i] = ves[i];
        for (int j = 0; j < G->vesnum; j++)
        {
            G->arcs[i][j] = arcs[i][j];
            if (G->arcs[i][j] > 0 && G->arcs[i][j] != max)
            {
                G->arcsnum++;
            }
        }
    }
}

void DFS(Graph *G, int index, int *visited)
{
    printf("v%c\t", G->ves[index]);
    visited[index] = 1;
    for (int i = 0; i < G->vesnum; i++)
    {
        if (G->arcs[index][i] > 0 && G->arcs[index][i] != max && visited[i] == 0)
        {
            DFS(G, i, visited);
        }
    }
}
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *initStack()
{
    Node *stack = (Node *)malloc(sizeof(Node));
    stack->data = 0;
    stack->next = NULL;
    return stack;
}

void push(Node *stack, int index) /* 采用头插法 */
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = index;
    node->next = stack->next;
    stack->next = node;
    stack->data++;
}
int isEmpty(Node *stack)
{
    if (stack->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int pop(Node *stack)
{
    if (isEmpty(stack) == 0)
    {
        Node *p = stack->next;
        stack->next = p->next;
        stack->data--;
        return p->data;
    }
    else
    {
        return -1;
    }
}

int *findInDegrees(Graph *G)
{
    int *inDegrees = (int *)malloc(sizeof(int) * G->vesnum);
    for (int i = 0; i < G->vesnum; i++)
    {
        inDegrees[i] = 0;
    }
    for (int i = 0; i < G->vesnum; i++)
    {
        for (int j = 0; j < G->vesnum; j++)
        {
            if (G->arcs[i][j] > 0 && G->arcs[i][j] != max)
            {
                inDegrees[j]++;
            }
        }
    }
    return inDegrees;
}

int *toplogicalsort(Graph *G)
{
    /* 建立出栈的结点所进入的数组 */
    int index = 0;
    int *top = (int *)malloc(sizeof(int) * G->vesnum);
    /* 建立栈 */
    Node *stack = initStack();

    int *inDegrees = findInDegrees(G); /* 拿到各个结点的入度数 */
    /* 将入度的结点压入栈内 */
    for (int i = 0; i < G->vesnum; i++)
    {
        if (inDegrees[i] == 0)
        {
            push(stack, i);
        }
    }
    while (isEmpty(stack) == 0)
    {
        int data = pop(stack);
        top[index++] = data; /* 将出栈结点的index值传入top数组中 */

        for (int i = 0; i < G->vesnum; i++)
        {
            if (G->arcs[data][i] > 0 && G->arcs[data][i] != max)
            {
                inDegrees[i]--;
                /* 此函数一定要放在G->arcs[data][i]==0的情况下执行判断，否则会出现结点重复入栈 */
                if (inDegrees[i] == 0)
                {
                    push(stack, i);
                }
            }
        }
    }

    printf("\n");
    printf("top数组中各个结点的顺序:\t");
    for (int i = 0; i < index; i++)
    {
        printf("v%c \t", G->ves[top[i]]);
    }
    printf("\n");
    printf("top数组内存储各个结点的index值: ");
    for (int i = 0; i < index; i++)
    {
        printf("%d \t", top[i]);
    }
    printf("\n");
    return top;
}

int getindex(int *top, Graph *G, int index)
{
    int k;
    for (int j = 0; j < G->vesnum; j++)
    {
        if (top[j] == index)
        {
            k = j;
            break;
        }
    }
    return k;
}
void criticalPath(Graph *G)
{
    /* 初始化三个数组 */
    int *top = toplogicalsort(G);
    int *early = (int *)malloc(sizeof(int) * G->vesnum);
    int *late = (int *)malloc(sizeof(int) * G->vesnum);
    for (int i = 0; i < G->vesnum; i++)
    {
        early[i] = 0;
        late[i] = 0;
    }
    for (int i = 0; i < G->vesnum; i++) /* 遍历top数组中每个结点，每次遍历均执行以下操作 */
    {
        int Max = 0;
        for (int j = 0; j < G->vesnum; j++)
        {
            if (G->arcs[j][top[i]] > 0 && G->arcs[j][top[i]] != max)
            {
                int EarlyIndex = getindex(top, G, j); /* 获得起始结点在top数组中的index值，就是获得了该结点在ealry数组中的index值 */
                if (early[EarlyIndex] + G->arcs[j][top[i]] > Max)
                {
                    Max = early[EarlyIndex] + G->arcs[j][top[i]];
                }
            }
        }
        early[i] = Max; /*该拓扑排序的顶点的early值安排上*/
    }

    printf("early数组的情况:");
    for (int i = 0; i < G->vesnum; i++)
    {

        printf("%d\t", early[i]);
    }
    /* 接下来安排late数组 */

    late[(G->vesnum) - 1] = early[(G->vesnum) - 1]; /* late数组里面各个顶点的late值也按照拓扑排序的顺序来 */
    for (int i = (G->vesnum) - 2; i >= 0; i--)
    {
        int min = max;
        for (int j = 0; j < G->vesnum; j++)
        {
            if (G->arcs[top[i]][j] > 0 && G->arcs[top[i]][j] != max)
            {
                int LateIndex = getindex(top, G, j);
                if (min > late[LateIndex] - G->arcs[top[i]][j])
                {
                    min = late[LateIndex] - G->arcs[top[i]][j];
                }
            }
        }
        late[i] = min;
    }
    printf("\n");
    printf("late数组的情况:");
    for (int i = 0; i < G->vesnum; i++)
    {

        printf("%d\t", late[i]);
    }
    printf("\n");
    /* 找出关键路径 */
    for (int i = 0; i < G->vesnum; i++)
    {
        for (int j = 0; j < G->vesnum; j++)
        {
            if (G->arcs[i][j] > 0 && G->arcs[i][j] != max)
            {
                int start = getindex(top, G, i);
                int end = getindex(top, G, j);
                if (late[end] - G->arcs[i][j] - early[start] == 0)
                {
                    printf("start=%d end=%d\n", i, j);
                }
            }
        }
    }
}

int main()
{
    int vesnum = 9;
    Graph *G = initGraph(vesnum);
    char ves[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    int arcs[9][9] = {
        0, 6, 4, 5, max, max, max, max, max,
        max, 0, max, max, 1, max, max, max, max,
        max, max, 0, max, 1, max, max, max, max,
        max, max, max, 0, max, 2, max, max, max,
        max, max, max, max, 0, max, 9, 7, max,
        max, max, max, max, max, 0, max, 4, max,
        max, max, max, max, max, max, 0, max, 2,
        max, max, max, max, max, max, max, 0, 4,
        max, max, max, max, max, max, max, max, 0};
    createGraph(G, ves, arcs);
    int *visited = (int *)malloc(sizeof(int) * vesnum);
    for (int i = 0; i < vesnum; i++)
    {
        visited[i] = 0;
    }
    printf("深度优先结果：");
    DFS(G, 0, visited);
    printf("\n");
    /* 测试入度函数写的是否正确 */
    /* int *inDgrees = findInDegrees(G);
    for (int i = 0; i < G->vesnum; i++)
    {
        printf("%d\t", inDgrees[i]);
    } */

    criticalPath(G);
    return 0;
}