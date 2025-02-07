#include <stdio.h>
#include <stdlib.h>
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

void createGraph(Graph *G, char *ves, int arcs[6][6])
{
    for (int i = 0; i < G->vesnum; i++)
    {
        G->ves[i] = ves[i];
        for (int j = 0; j < G->vesnum; j++)
        {
            G->arcs[i][j] = arcs[i][j];
            if (G->arcs[i][j] != 0)
            {
                G->arcsnum++;
            }
        }
    }
    G->arcsnum /= 2;
}

void DFS(Graph *G, int index, int *visited)
{
    printf("v%c\t", G->ves[index]);
    visited[index] = 1;
    for (int i = 0; i < G->vesnum; i++)
    {
        if (G->arcs[index][i] != 0 && visited[i] == 0)
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
            if (G->arcs[i][j] != 0)
            {
                inDegrees[j]++;
            }
        }
    }
    return inDegrees;
}

void toplogicalsort(Graph *G)
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
            if (G->arcs[data][i] != 0)
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
    for (int i = 0; i < index; i++)
    {
        printf("%d\t", top[i]);
    }
    printf("\n");
    for (int i = 0; i < index; i++)
    {
        printf("v%c \t", G->ves[top[i]]);
    }
}

int main()
{
    int vesnum = 6;
    Graph *G = initGraph(vesnum);
    char ves[6] = {'1', '2', '3', '4', '5', '6'};
    int arcs[6][6] = {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0,
                      0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0};
    createGraph(G, ves, arcs);
    int *visited = (int *)malloc(sizeof(int) * vesnum);
    for (int i = 0; i < vesnum; i++)
    {
        visited[i] = 0;
    }
    DFS(G, 0, visited);
    printf("\n");
    /* 测试入度函数写的是否正确 */
    /* int *inDgrees = findInDegrees(G);
    for (int i = 0; i < G->vesnum; i++)
    {
        printf("%d\t", inDgrees[i]);
    } */
    toplogicalsort(G);
    return 0;
}