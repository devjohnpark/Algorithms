//
//  2.c
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

typedef struct Graph {
    int n;
    int** adjacency;
    int* visit;
} Graph;

QNode* newNode(int data) {
    QNode* current = (QNode*)malloc(sizeof(QNode));
    current->data = data;
    current->next = NULL;
    return current;
}

void initQueue(Queue* queue) {
    queue->cnt = 0;
    queue->front = queue->rear = NULL;
}

int isEmpty(Queue* queue) {
    if (queue->cnt == 0)
        return 1;
    else
        return 0;
}

void enqueue(Queue* queue, int data)
{
    QNode* current = newNode(data);
    if (isEmpty(queue) == 1)  //비어있다면
    {
        queue->front = queue->rear = current;
        queue->cnt++;
        return;
    }
    queue->rear->next = current;
    queue->rear = queue->rear->next;   //다시 rear은 마지막으로 이동
    queue->cnt++;
}

int dequeue(Queue* queue)
{
    int res;
    if (isEmpty(queue) == 1) {
        return -1;
    }
    QNode* temp = queue->front;
    queue->front = queue->front->next;
    res = temp->data;
    queue->cnt--;
    free(temp);
    return res;
}

void insertEdge(Graph* g, int u, int v) {
    g->adjacency[u][v] = 1;
    g->adjacency[v][u] = 1;
}

void initGraph(Graph* g, int n)
{
    g->n = n;
    g->adjacency = (int**)malloc(sizeof(int*) * (n + 1));
    g->visit = (int*)malloc(sizeof(int) * (n + 1));
    
    for (int i = 1; i <= g->n; i++) {
        g->adjacency[i] = (int*)malloc(sizeof(int) * (n + 1));
    }

    for (int i = 1; i <= g->n; i++) {
        for (int j = 1; j <= g->n; j++) {
            g->adjacency[i][j] = 0;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        g->visit[i] = 0;
    }
}

void BFS(Graph* g, int v)
{
    Queue queue;
    int w;
    initQueue(&queue);
    g->visit[v] = 1;
    enqueue(&queue, v);
    while (isEmpty(&queue) != 1) {
        v = dequeue(&queue);
        printf("%d\n", v);
        for (w = 1; w <= g->n; w++) {
            if (g->adjacency[v][w] == 1 && g->visit[w] == 0) {
                g->visit[w] = 1;
                enqueue(&queue, w);
            }
        }
    }
}

int main()
{
    Graph g;
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    initGraph(&g, n);
    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        insertEdge(&g, u, v);
    }
    BFS(&g, s);
}
