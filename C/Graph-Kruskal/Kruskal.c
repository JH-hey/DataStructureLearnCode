#include <stdio.h>
#include <stdlib.h>
#define max 3217

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

void createGraph(Graph *G, char *ves, int arcs[6][6], int vesnum)
{
    for (int i = 0; i < vesnum; i++)
    {
        G->ves[i] = ves[i];
        for (int j = 0; j < vesnum; j++)
        {
            G->arcs[i][j] = arcs[i][j];
            if (G->arcs[i][j] != 0 && G->arcs[i][j] != max)
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
typedef struct Edge
{
    int startindex;
    int weight;
    int endindex;
} Edge;

Edge *initEdge(Graph *G)
{
    int index = 0;
    Edge *edge = (Edge *)malloc(sizeof(Edge) * G->arcsnum);

    for (int i = 0; i < G->vesnum; i++)
    {
        for (int j = i + 1; j < G->vesnum; j++)
        {
            if (G->arcs[i][j] != max)
            {
                edge[index].startindex = i;
                edge[index].weight = G->arcs[i][j];
                edge[index].endindex = j;
                index++;
            }
        }
    }
    return edge;
}
/* 冒泡排序一下 */
void sortEdge(Edge *edge, Graph *G)
{
    Edge temp;
    for (int i = 0; i < G->arcsnum - 1; i++)
    {
        for (int j = 0; j < G->arcsnum - i - 1; j++)
        {
            if (edge[j].weight > edge[j + 1].weight)
            {
                temp = edge[j];
                edge[j] = edge[j + 1];
                edge[j + 1] = temp;
            }
        }
    }
}

/* 算法 */
void kruskal(Graph *G)
{
    /* 建立connected数组，即连通分量 */
    int *connected = (int *)malloc(sizeof(int) * G->vesnum);
    for (int i = 0; i < G->vesnum; i++)
    {
        connected[i] = i;
    }
    Edge *edge = initEdge(G);
    sortEdge(edge, G);
    /* 试验打印出排序后的edge ,测试后发现排序后的edge没有问题*/
    /*  for (int i = 0; i < G->arcsnum; i++)
     {
         printf("v%c,%d,v%c\n", G->ves[edge[i].startindex], edge[i].weight, G->ves[edge[i].endindex]);
     } */

    /* 错误代码*/
    /* for (int i = 0; i < G->arcsnum; i++)
    {

        if (connected[edge[i].startindex] != connected[edge[i].endindex])
        {
            printf("v%c---->v%c,weight=%d\n", G->ves[edge[i].startindex], G->ves[edge[i].endindex], edge[i].weight);
            for (int j = 0; j < G->vesnum; j++)
            {
                if (connected[j] == connected[edge[i].endindex])
                {
                    connected[j] = connected[edge[i].startindex];
                }
            }
        }
    } */

    for (int i = 0; i < G->arcsnum; i++)
    {
        /* 这里之所以要把当前edge的起始节点&终止节点的连通分量先提取出来，是为了后面“比较每个结点的分量与当前终止结点的分量相同与否”的时候避免出现错误。出现“终止结点分量先被改变为起始结点的分量，导致后面与终止结点比较且应该被改变分量的结点错过比较机会。” 这种错误*/
        /* 称此错误是：因为被比较的值被改变了，导致后面应该与其比较且改变的值错失改变机会 */
        int startindex_ing = connected[edge[i].startindex];
        int endindex_ing = connected[edge[i].endindex];
        if (startindex_ing != endindex_ing)
        {
            printf("v%c---->v%c,weight=%d\n", G->ves[edge[i].startindex], G->ves[edge[i].endindex], edge[i].weight);
            for (int j = 0; j < G->vesnum; j++)
            {
                if (connected[j] == endindex_ing)
                {
                    connected[j] = startindex_ing;
                }
            }
        }
    }
}

int main()
{
    int vesnum = 6;
    Graph *G = initGraph(vesnum);
    char ves[6] = {'1', '2', '3', '4', '5', '6'};
    int arcs[6][6] =
        {0, 6, 1, 5, max, max,
         6, 0, 5, max, 3, max,
         1, 5, 0, 5, 6, 4,
         5, max, 5, 0, max, 2,
         max, 3, 6, max, 0, 6,
         max, max, 4, 2, 6, 0};
    createGraph(G, ves, arcs, vesnum);
    int *visited = (int *)malloc(sizeof(int) * vesnum);
    for (int i = 0; i < vesnum; i++)
    {
        visited[i] = 0;
    }
    DFS(G, visited, 0);
    printf("\n");

    kruskal(G);
}
