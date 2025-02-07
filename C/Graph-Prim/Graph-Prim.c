#include <stdio.h>
#include <stdlib.h>

#define max 3217

/* 图的struct */
typedef struct Graph
{
    char *ves;   /* 顶点的一维数组 */
    int **arcs;  /* 边的权值的二维数组 */
    int vesnum;  /* 顶点数 */
    int arcsnum; /* 边的数量 */
} Graph;

Graph *initGraph(int vesnum) /* 给图开辟出各个空间 */
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

void createGraph(Graph *G, char ves[6], int arcs[6][6]) /* 将graph的各项值赋进去 */
{
    for (int i = 0; i < G->vesnum; i++)
    {
        G->ves[i] = ves[i];
        for (int j = 0; j < G->vesnum; j++)
        {
            G->arcs[i][j] = arcs[i][j];
            if (G->arcs[i][j] != 0 && G->arcs[i][j] != max)
            {
                G->arcsnum++;
            }
        }
    }
    G->arcsnum = G->arcsnum / 2;
}

void DFS(Graph *G, int *visited, int index) /* 深度优先遍历 */
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

/* 建立边的struct */
typedef struct Edge
{
    char ves;
    int weight;
} Edge;
/* 建立初始的Edge，将节点1的边值传入 */
Edge *initEdge(Graph *G, int index)
{
    Edge *edge = (Edge *)malloc(sizeof(Edge) * G->vesnum);
    for (int i = 0; i < G->vesnum; i++)
    {
        edge[i].ves = G->ves[index];
        edge[i].weight = G->arcs[index][i];
    }
    return edge;
}
/* 获得edge中边值最小的那个index */
int getminEdge(Graph *G, Edge *edge)
{
    int min = max;
    int index;
    for (int i = 0; i < G->vesnum; i++)
    {
        if (edge[i].weight < min && edge[i].weight != 0 && edge[i].weight != max)
        {
            min = edge[i].weight;
            index = i;
        }
    }
    return index;
}
void prim(Graph *G, int index)
{
    int minindex;
    Edge *edge = initEdge(G, index);
    for (int i = 0; i < G->vesnum - 1; i++)
    {
        minindex = getminEdge(G, edge);
        printf("v%c----->v%c,weight=%d\n", edge[minindex].ves, G->ves[minindex], edge[minindex].weight);
        edge[minindex].weight = 0;
        for (int j = 0; j < G->vesnum; j++)
        {
            if (G->arcs[minindex][j] < edge[j].weight)
            {
                edge[j].weight = G->arcs[minindex][j];
                edge[j].ves = G->ves[minindex];
            }
        }
    }
}

int main()
{
    Graph *G = initGraph(6);
    char ves[6] = {'1', '2', '3', '4', '5', '6'};
    int arcs[6][6] =
        {0, 6, 1, 5, max, max,
         6, 0, 5, max, 3, max,
         1, 5, 0, 5, 6, 4,
         5, max, 5, 0, max, 2,
         max, 3, 6, max, 0, 6,
         max, max, 4, 2, 6, 0};
    createGraph(G, ves, arcs); /* 只需要传入地址 ,不要传入ves[6]*/
    int *visited = (int *)malloc(sizeof(int) * 6);
    for (int i = 0; i < 6; i++)
    {
        visited[i] = 0;
    }
    DFS(G, visited, 0);
    printf("\n");
    prim(G, 0);
    return 0;
}