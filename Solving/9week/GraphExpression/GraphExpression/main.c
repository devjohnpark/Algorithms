#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int vertex;
    int weight;
    struct node* next;
} Node;

typedef struct Graph {
    int n;
    Node** adj_List;
} Graph;

void initGraph(Graph* g, int n);
Node* newNode(int vertex);
Node* findNode(Node* head, int vertex);
void addVertex(Node** head, int vertex, int weight);
void deleteNode(Node** head, int v);
void insertEdge(Graph* g, int u, int v, int w);
void printEdge(Graph* g, int v);

int main()
{
    Graph g;
    char oper = '\0';
    int u, v, w, n;
    initGraph(&g, 7);

    {
        insertEdge(&g, 1, 6, 2);
        insertEdge(&g, 1, 4, 1);
        insertEdge(&g, 1, 3, 1);
        insertEdge(&g, 1, 2, 1);
        insertEdge(&g, 2, 3, 1);
        insertEdge(&g, 2, 1, 1);
        insertEdge(&g, 3, 5, 4);
        insertEdge(&g, 3, 2, 1);
        insertEdge(&g, 3, 1, 1);
        insertEdge(&g, 4, 1, 1);
        insertEdge(&g, 5, 6, 3);
        insertEdge(&g, 5, 5, 4);
        insertEdge(&g, 5, 3, 4);
        insertEdge(&g, 6, 5, 3);
        insertEdge(&g, 6, 1, 2);
    }

    while (oper != 'q')
    {
        scanf("%c", &oper);
        getchar();

        if (oper == 'a')
        {
            scanf("%d", &v);
            getchar();
            printEdge(&g, v);
        }
        else if (oper == 'm')
        {
            scanf("%d %d %d", &u, &v, &w);
            getchar();
            insertEdge(&g, u, v, w);
        }
    }
}

void initGraph(Graph* g, int n)
{
    g->n = n;
    g->adj_List = (Node**)malloc(sizeof(Node*) * n);
    for (int i = 0; i < n; i++)
    {
        g->adj_List[i] = (Node*)malloc(sizeof(Node));
    }
    for (int v = 0; v < n; v++)
    {
        g->adj_List[v] = NULL;
    }
}

Node* newNode(int vertex)
{
    Node* now = (Node*)malloc(sizeof(Node));
    now->vertex = vertex;
    now->next = NULL;
    return now;
}

Node* findNode(Node* head, int vertex)
{
    Node* seek = head;
    while (seek != NULL)
    {
        if (seek->vertex == vertex)
            return seek;
        seek = seek->next;
    }
    return seek;
}

void insertEdge(Graph* g, int u, int v, int w)
{
    if (u < 1 || u > 6 || v < 1 || v > 6)
    {
        printf("%d\n", -1);
        return;
    }

    Node* seek = findNode(g->adj_List[u], v);
    if (seek == NULL)
    {
        if (u != v)
            addVertex(&g->adj_List[u], v, w);
        addVertex(&g->adj_List[v], u, w);
    }
    else if (w == 0)
    {
        if (u != v)
            deleteNode(&g->adj_List[u], v);
        deleteNode(&g->adj_List[v], u);
    }
    else
    {
        seek = findNode(g->adj_List[u], v);
        seek->weight = w;
        seek = findNode(g->adj_List[v], u);
        seek->weight = w;
    }
}

void addVertex(Node** head, int vertex, int weight)
{
    Node* now = newNode(vertex);
    now->weight = weight;

    Node* seek = *head;
    Node* prev = NULL;
    while (seek != NULL)
    {
        if (seek->vertex > vertex)
            break;
        prev = seek;
        seek = seek->next;
    }
    if (prev == NULL)   //맨 앞에 삽입해야함
    {
        now->next = *head;
        *head = now;
    }
    else
    {
        prev->next = now;
        now->next = seek;
    }
}

//인접리스트 헤드노드에서 v정점 삭제
void deleteNode(Node** head, int v)
{
    if (*head == NULL)
        return;
    Node* seek = *head;
    Node* prev = NULL;
    while (seek != NULL)
    {
        if (seek->vertex == v)
            break;
        prev = seek;
        seek = seek->next;
    }
    if (prev == NULL)
    {
        *head = (*head)->next;
    }
    else
    {
        prev->next = seek->next;
    }
    free(seek);
}

void printEdge(Graph* g, int v)
{
    if (v < 1 || v > 6)
    {
        printf("%d\n", -1);
        return;
    }

    Node* seek = g->adj_List[v];
    while (seek != NULL)
    {
        printf("%d %d ", seek->vertex, seek->weight);
        seek = seek->next;
    }
    printf("\n");
}

