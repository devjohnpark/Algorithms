//
//  main.c
//  MST
//
//  Created by Junseo Park on 2022/12/08.
#include <stdio.h>
#include <stdlib.h>

typedef struct QNode {
    int data;
    struct QNode* next;
}QNode;

typedef struct Queue {
    QNode* front;
    QNode* rear;
    int cnt;
} Queue;

QNode* newNode(int data) {
    QNode* now = (QNode*)malloc(sizeof(QNode));
    now->data = data;
    now->next = NULL;
    return now;
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

void enqueue(Queue* queue, int data) {
    QNode* now = newNode(data);
    if (isEmpty(queue)) {
        queue->front = queue->rear = now;
        queue->cnt++;
        return;
    }
    queue->rear->next = now;
    queue->rear = queue->rear->next;
    queue->cnt++;
}


int dequeue(Queue* queue) {
    if (isEmpty(queue) == 1) {
        printf("비어있음\n");
        return -1;
    }
    QNode* temp = queue->front;
    queue->front = queue->front->next;
    int res = temp->data;
    free(temp);
    queue->cnt--;
    return res;
}

typedef struct Graph {
    int** adjacency;
    int* dist;
    int* selected;
    int n;
} Graph;

void initGraph(Graph* g, int n) {
    g->n = n;
    g->adjacency = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < g->n; i++) {
        g->adjacency[i] = (int*)malloc(sizeof(int) * (n + 1));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->adjacency[i][j] = 0;
        }
    }
    g->dist = (int*)malloc(sizeof(int) * n);
    g->selected = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        g->dist[i] = 10000;
        g->selected[i] = 0;
    }
}

void insert_edge(Graph* g, int u, int v, int w)  {
    g->adjacency[u][v] = w;
    g->adjacency[v][u] = w;
}

int getMinVertex(Graph *g) {
    int v = 0, i;

    for (i = 1; i < g->n; i++) {
        if (g->selected[i] == 0) {
            v = i;
            break;
        }
    }

    for (i = 1; i < g->n; i++) {
        if (g->selected[i] == 0 && g->dist[i] < g->dist[v])
            v = i;
    }
    return v;
}

void primJarmik(Graph* g, int s) {
    int i, u, v;
    g->dist[s] = 0;
    for (i = 1; i < g->n; i++) {
        int u = getMinVertex(g);
        g->selected[u] = 1;
        if (g->dist[u] == 10000)
            return;
        printf("%d ", u);
        for (v = 1; v < g->n; v++) {
            if (g->adjacency[u][v] != 0) {
                if (g->selected[v] == 0 && g->adjacency[u][v] < g->dist[v])
                    g->dist[v] = g->adjacency[u][v];
            }
        }
    }
}

int main()
{
    Graph g;
    int sum = 0;
    int n, m;
    int u, v, w;

    scanf("%d %d", &n, &m);
    initGraph(&g, n + 1);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        insert_edge(&g, u, v, w);
    }
    primJarmik(&g, 1);
    for (int i = 1; i < g.n; i++) {
        sum += g.dist[i];
    }
    printf("\n");
    printf("%d ", sum);
}
