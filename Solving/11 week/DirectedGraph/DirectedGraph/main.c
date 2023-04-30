//
//  main.c
//  DirectedGraph
//
//  Created by Junseo Park on 2022/11/30.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct QNode {
    char data;
    struct QNode* next;
} QNode;

typedef struct Queue {
    int cnt;
    QNode* front;
    QNode* rear;
} Queue;

typedef struct node {
    char vertex;
    struct node* next;
} Node;

typedef struct graph {
    int* indegree;
    int n;
    char* name;
    Node** adjacencyList;
} Graph;

void initQueue(Queue* queue);
Node* newNode(char vertex);
int isEmpty(Queue* queue);
void enqueue(Queue* queue, char data);
char dequeue(Queue* queue);
void initGraph(Graph* g, int n);
int findIndex(Graph* g, char v);
void insertEdge(Graph* g, char u, char v);
void inDegree(Graph* g);
int topSort(Graph* g, char* str);
void printIndegree(Graph* g);
void viewAll(Graph* g, char* str, int cnt);

int main() {
    Graph g;
    int n, m;
    char u, v;
    scanf("%d", &n);
    getchar();
    initGraph(&g, n);
    char* str = (char*)malloc(sizeof(char) * n);

    for (int i = 0; i < n; i++) {
        scanf("%c", &g.name[i]);
        getchar();
    }

    scanf("%d", &m);
    getchar();
    
    for (int i = 0; i < m; i++) {
        scanf("%c %c", &u, &v);
        getchar();
        insertEdge(&g, u, v);
    }
    
    int cnt = topSort(&g, str);
    viewAll(&g, str, cnt);

    return 0;
}

Node* newNode(char vertex) {
    Node* current = (Node*)malloc(sizeof(Node));
    current->vertex = vertex;
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

void enqueue(Queue* queue, char data) {
    QNode* current = (QNode*)malloc(sizeof(QNode));
    current->data = data;
    current->next = NULL;

    if (isEmpty(queue)) {
        queue->front = queue->rear = current;
        queue->cnt++;
        return;
    }

    queue->rear->next = current;
    queue->rear = queue->rear->next;   //다시 rear은 마지막으로 이동
    queue->cnt++;
}

char dequeue(Queue* queue) {
    if (isEmpty(queue) == 1)
        return -1;
    QNode* temp = queue->front;
    queue->front = queue->front->next;
    char res = temp->data;
    free(temp);
    queue->cnt--;
    return res;
}

void initGraph(Graph* g, int n) {
    g->n = n;
    g->adjacencyList = (Node**)malloc(sizeof(Node*) * n);
    for (int i = 0; i < n; i++)
        g->adjacencyList[i] = (Node*)malloc(sizeof(Node));
    for (int v = 0; v < n; v++)
        g->adjacencyList[v] = NULL;
    g->indegree = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        g->indegree[i] = 0;
    g->name = (char*)malloc(sizeof(char) * n);
}

int findIndex(Graph* g, char v) {
    int idx = 0;
    for (int i = 0; i < g->n; i++) {
        if (g->name[i] == v) {
            idx = i;
            break;
        }
    }
    return idx;
}

void insertEdge(Graph* g, char u, char v) {
    int idx = findIndex(g, u);
    Node* current = newNode(v);
    current->next = g->adjacencyList[idx];
    g->adjacencyList[idx] = current;
}

void inDegree(Graph* g) {
    for (int i = 0; i < g->n; i++) {
        Node* seek = g->adjacencyList[i];
        while (seek != NULL) {
            int idx = findIndex(g, seek->vertex);
            g->indegree[idx]++;
            seek = seek->next;
        }
    }
}

int topSort(Graph* g, char* str) {
    inDegree(g);
    Queue queue;
    initQueue(&queue);
    int cnt = 0;
    int idx = 0;
    for (int i = 0; i < g->n; i++) {
        if (g->indegree[i] == 0) {
            enqueue(&queue, g->name[i]);
            cnt++;
        }
    }
    while (isEmpty(&queue) != 1) {
        char v = dequeue(&queue);
        str[idx++] = v;
        int idx = findIndex(g, v);
        Node* seek = g->adjacencyList[idx];
        while (seek != NULL) {
            int w = findIndex(g, seek->vertex);
            g->indegree[w]--;
            if (g->indegree[w] == 0) {
                enqueue(&queue, g->name[w]);
                cnt++;
            }
            seek = seek->next;
        }
    }
    return cnt;
}

void printIndegree(Graph* g) {
    for (int i = 0; i < g->n; i++)
        printf("%d ", g->indegree[i]);
    printf("\n");
}

void viewAll(Graph* g, char* str, int cnt) {
    if (cnt == g->n) {
        for (int i = 0; i < g->n; i++)
            printf("%c ", str[i]);
    }
    else
        printf("%d", 0);
}
