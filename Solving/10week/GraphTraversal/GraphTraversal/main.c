//
//  main.c
//  GraphTraversal
//
//  Created by Junseo Park on 2022/11/24.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct QNode {
    int data;
    struct QNode* next;
} QNode;

typedef struct Queue {
    QNode* front;
    QNode* rear;
    int cnt;
} Queue;

void initQueue(Queue* queue) {
    queue->front = queue->rear = NULL;
    queue->cnt = 0;
}

int isEmpty(Queue* queue) {
    if (queue->cnt == 0)
        return 1;
    else return 0;
}


void enqueue(Queue* queue, int data) {
    QNode* current = (QNode*)malloc(sizeof(QNode));
    current->data = data;
    current->next = NULL;

    if (isEmpty(queue) == 1) {
        queue->front = current;
        queue->rear = current;
        queue->cnt++;
        return;
    }
    queue->rear->next = current;
    queue->rear = queue->rear->next;
    queue->cnt++;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue) == 1)
        return -1;

    QNode* temp = queue->front;
    queue->front = queue->front->next;
    int res = temp->data;
    free(temp);
    queue->cnt--;
    return res;
}

typedef struct node {
    int vertex;
    struct node* next;
} Node;

typedef struct Graph {
    Node** adjacencyList;
    int n;
    int* visit;
} Graph;

void initGraph(Graph* g, int n)
{
    g->n = n;
    g->adjacencyList = (Node**)malloc(sizeof(Node*) * n);
    for (int i = 0; i < n; i++) {
        g->adjacencyList[i] = (Node*)malloc(sizeof(Node));
    }
    g->visit = (int*)malloc(sizeof(int) * n);
    for (int v = 0; v < n; v++) {
        g->adjacencyList[v] = NULL;
        g->visit[v] = 0;
    }
}

Node* newNode(int vertex)
{
    Node* current = (Node*)malloc(sizeof(Node));
    current->vertex = vertex;
    current->next = NULL;
    return current;
}

void addEdge(Node** head, int vertex)
{
    Node* seek = *head;
    Node* prev = NULL;
    Node* current = newNode(vertex);
    
    while (seek != NULL) {
        if (seek->vertex > vertex)
            break;
        prev = seek;
        seek = seek->next;
    }
    
    if (prev == NULL)   {
        current->next = *head;
        *head = current;
    }
    else {
        prev->next = current;
        current->next = seek;
    }
}

void insertEdge(Graph* g, int u, int v) {
    addEdge(&g->adjacencyList[u], v);
    addEdge(&g->adjacencyList[v], u);
}

void DFS(Graph* g, int v) {
    g->visit[v] = 1;
    printf("%d\n", v);
    Node* seek = g->adjacencyList[v];
    int w;
    while (seek != NULL) {
        w = seek->vertex;
        if (g->visit[w] == 0)
            DFS(g, w);
        seek = seek->next;
    }
}

void BFS(Graph* g, int v)
{
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, v);
    g->visit[v] = 1;

    while (isEmpty(&queue) != 1) {
        v = dequeue(&queue);
        printf("%d\n", v);
        Node* seek = g->adjacencyList[v];
        while (seek != NULL) {
            int w = seek->vertex;
            if (g->visit[w] == 0) {
                g->visit[w] = 1;
                enqueue(&queue, w);
            }
            seek = seek->next;
        }
    }
}

void printEdge(Graph* g, int v) {
    Node* seek = g->adjacencyList[v];
    while (seek != NULL) {
        printf("%d ", seek->vertex);
        seek = seek->next;
    }
    printf("\n");
}

int main()
{
    Graph g;
    int u, v, s;
    int n, m;
    scanf("%d %d %d", &n, &m, &s);
    initGraph(&g, n + 1);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        insertEdge(&g, u, v);
    }
    DFS(&g, s);
}
