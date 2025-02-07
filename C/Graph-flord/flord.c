#include <stdio.h>
#include <stdlib.h>
#define max 357

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

void createGraph(Graph *G, char *ves, int arcs[4][4])
{
    for (int i = 0; i < G->vesnum; i++)
    {
        G->ves[i] = ves[i];
        for (int j = 0; j < G->vesnum; j++)
        {
            G->arcs[i][j] = arcs[i][j];
            if (G->arcs[i][j] != max && G->arcs[i][j] != 0)
            {
                G->arcsnum++;
            }
        }
    }
    G->arcsnum /= 2;
}

void DFS(Graph *G, int *visited, int index)
{
    printf("%c\t", G->ves[index]);
    visited[index] = 1;
    for (int i = 0; i < G->vesnum; i++)
    {
        if (G->arcs[index][i] != 0 && G->arcs[index][i] != max && visited[i] == 0)
        {
            DFS(G, visited, i);
        }
    }
}

/* 算法核心 */
void Floyd(Graph *G)
{
    /* 建立辅助数组两个 */
    int d[G->vesnum][G->vesnum];
    int p[G->vesnum][G->vesnum];
    for (int i = 0; i < G->vesnum; i++)
    {
        for (int j = 0; j < G->vesnum; j++)
        {
            d[i][j] = G->arcs[i][j]; /* 初始路径传进去 */
        }
    }
    for (int i = 0; i < G->vesnum; i++)
    {
        for (int j = 0; j < G->vesnum; j++)
        {
            if (G->arcs[i][j] != 0 && G->arcs[i][j] != max)
            {
                p[i][j] = i;
            }
            else
            {
                p[i][j] = -1;
            }
        }
    }

    /* 算法开始 */
    for (int i = 0; i < G->vesnum; i++)
    {
        for (int j = 0; j < G->vesnum; j++)
        {
            for (int k = 0; k < G->vesnum; k++)
            {
                if (d[j][i] + d[i][k] < d[j][k])
                {
                    d[j][k] = d[j][i] + d[i][k];
                    p[j][k] = p[i][k];
                }
            }
        }
    }
    /* 测试两个准备函数是否正确&&以及打印结果 */
    for (int i = 0; i < G->vesnum; i++)
    {
        for (int j = 0; j < G->vesnum; j++)
        {
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < G->vesnum; i++)
    {
        for (int j = 0; j < G->vesnum; j++)
        {
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int vesnum = 4;
    Graph *G = initGraph(vesnum);
    char ves[4] = {'1', '2', '3', '4'};
    int arcs[4][4] = {0, 1, max, 3,
                      1, 0, 2, 2,
                      max, 2, 0, 8,
                      3, 2, 8, 0};
    int *visited = (int *)malloc(sizeof(int) * vesnum);
    for (int i = 0; i < vesnum; i++)
    {
        visited[i] = 0;
    }
    createGraph(G, ves, arcs);
    DFS(G, visited, 0);
    printf("\n");
    Floyd(G);
}
