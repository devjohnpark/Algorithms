#include <stdio.h>
#include <stdlib.h>


void initGraph(int g[][7]);
int isEmpty(int g[][7], int u, int v);
void insertEdge(int g[][7], int u, int v, int w);
void printEdge(int g[][7], int v);

int main()
{
    int u, v, w;
    char oper = '\0';
    int g[7][7];   //정점 값 1~6
    initGraph(g);
    {
        insertEdge(g, 1, 6, 2);
        insertEdge(g, 1, 4, 1);
        insertEdge(g, 1, 3, 1);
        insertEdge(g, 1, 2, 1);
        insertEdge(g, 2, 3, 1);
        insertEdge(g, 2, 1, 1);
        insertEdge(g, 3, 5, 4);
        insertEdge(g, 3, 2, 1);
        insertEdge(g, 3, 1, 1);
        insertEdge(g, 4, 1, 1);
        insertEdge(g, 5, 6, 3);
        insertEdge(g, 5, 5, 4);
        insertEdge(g, 5, 3, 4);
        insertEdge(g, 6, 5, 3);
        insertEdge(g, 6, 1, 2);
    }
    while (oper != 'q')
    {
        scanf("%c", &oper);
        getchar();

        if (oper == 'a')
        {
            scanf("%d", &v);
            getchar();
            printEdge(g, v);
        }
        else if (oper == 'm')
        {
            scanf("%d %d %d", &u, &v, &w);
            getchar();
            insertEdge(g, u, v, w);
        }
    }

}

void initGraph(int g[][7])
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            g[i][j] = 0;
        }
    }
}

void insertEdge(int g[][7], int u, int v, int w)
{
    if (u < 1 || u> 6 || v < 1 || v>6)
    {
        printf("%d\n", -1);
        return;
    }

    if (w == 0)
    {
        g[u][v] = 0;
        g[v][u] = 0;
    }
    else if (isEmpty(g, u, v) == 1)
    {
        g[u][v] = w;
        g[v][u] = w;
    }
    else
    {
        g[u][v] = w;
        g[v][u] = w;
    }
}

int isEmpty(int g[][7], int u, int v)
{
    if (g[u][v] == 0)
        return 1;   //비어있음
    else return 0;
}

void printEdge(int g[][7], int v)
{
    if (v < 1 || v>6)
    {
        printf("%d\n", -1);
        return;
    }
    for (int i = 1; i < 7; i++)
    {
        if (isEmpty(g, v, i) == 0)
            printf(" %d %d", i, g[v][i]);
    }
    printf("\n");
}
