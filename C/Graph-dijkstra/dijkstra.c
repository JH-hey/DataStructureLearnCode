#include <stdio.h>
#include <stdlib.h>
#define MAX 7345

typedef struct Graph
{
    char *ves;  /* 边的合集 */
    int **arcs; /* 权值合集 */
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
void createGraph(Graph *G, char *ves, int arcs[7][7])
{
    for (int i = 0; i < G->vesnum; i++)
    {
        G->ves[i] = ves[i];
        for (int j = 0; j < G->vesnum; j++)
        {
            G->arcs[i][j] = arcs[i][j];
            if (G->arcs[i][j] != 0 && G->arcs[i][j] != MAX)
            {
                G->arcsnum++;
            }
        }
    }
    G->arcsnum /= 2;
}
int getmin(Graph *G, int *d, int *s)
{
    int min = MAX;
    int index;
    for (int i = 0; i < G->vesnum; i++)
    {
        if (s[i] != 1 && d[i] < min)
        {
            min = d[i];
            index = i;
        }
    }
    return index;
}
void Dijkstra(Graph *G, int index)
{
    /* 建立三个辅助数组 */
    int *s = (int *)malloc(sizeof(int) * G->vesnum);
    for (int i = 0; i < G->vesnum; i++)
    {
        /* 目标结点的值设为1 */
        if (i == index)
        {
            s[i] = 1;
        }
        else
        {
            s[i] = 0;
        }
    }
    int *p = (int *)malloc(sizeof(int) * G->vesnum);
    for (int i = 0; i < G->vesnum; i++)
    {
        if (G->arcs[index][i] != 0 && G->arcs[index][i] != MAX)
        {
            p[i] = 0;
        }
        else
        {
            p[i] = -1;
        }
    }
    int *d = (int *)malloc(sizeof(int) * G->vesnum);
    for (int i = 0; i < G->vesnum; i++)
    {
        if (i == index)
        {
            d[i] = 0;
        }
        else if (G->arcs[index][i] != 0 && G->arcs[index][i] != MAX)
        {
            d[i] = G->arcs[index][i];
        }
        else
        {
            d[i] = MAX;
        }
    }
    /* 测试，辅助函数是否正确 ,结果显示：测试成功*/
    /* for (int i = 0; i < G->vesnum; i++)
    {
        printf("%d,%d,%d\n", s[i], p[i], d[i]);
    } */
    for (int i = 0; i < G->vesnum - 1; i++)
    {
        int minIndex = getmin(G, d, s); /* 先找到目前d值最短的那个index值 */
        s[minIndex] = 1;                /* 使得他的s值为1 */
        for (int j = 0; j < G->vesnum; j++)
        {
            if (s[j] != 1 && d[minIndex] + G->arcs[minIndex][j] < d[j])
            {
                d[j] = d[minIndex] + G->arcs[minIndex][j];
                p[j] = minIndex;
            }
        }
    }
    /* 测试打印结果 */
    for (int i = 0; i < G->vesnum; i++)
    {
        printf("%d,%d,%d\n", s[i], p[i], d[i]);
    }
}

void DFS(Graph *G, int *visited, int index)
{
    printf("%c\t", G->ves[index]);
    visited[index] = 1;
    for (int i = 0; i < G->vesnum; i++)
    {
        if (G->arcs[index][i] != 0 && G->arcs[index][i] != MAX && visited[i] == 0)
        {
            DFS(G, visited, i);
        }
    }
}

int main()
{
    int vesnum = 7; /* 有7个结点 */
    char ves[7] = {'1', '2', '3', '4', '5', '6', '7'};
    int arcs[7][7] = {0, 12, MAX, MAX, MAX, 16, 14,
                      12, 0, 10, MAX, MAX, 7, MAX,
                      MAX, 10, 0, 3, 5, 6, MAX,
                      MAX, MAX, 3, 0, 4, MAX, MAX,
                      MAX, MAX, 5, 4, 0, 2, 8,
                      16, 7, 6, MAX, 2, 0, 9,
                      14, MAX, MAX, MAX, 8, 9, 0};
    Graph *G = initGraph(vesnum);
    createGraph(G, ves, arcs);
    int *visited = (int *)malloc(sizeof(int) * vesnum);
    for (int i = 0; i < vesnum; i++)
    {
        visited[i] = 0;
    }
    DFS(G, visited, 0);
    printf("\n");
    Dijkstra(G, 0);
}
