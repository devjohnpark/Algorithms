//
//  2.c
//  MST
//
//  Created by Junseo Park on 2022/12/08.
//

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int a, b;
    int weight;
} Node;

typedef struct Graph {
    Node* head;
} Graph;

void initGraph(Graph* g, int size) {
    g->head = (Node*)malloc(sizeof(Node) * size);
    return;
}

void initPQueue(int* pq, int size) {
    int i;
    for (i = 0; i < size; i++) {
        pq[i] = i;
    }
    return;
}

int qCheck(int* pq, int qSize) {
    int i;
    int temp = pq[1];
    for (i = 2; i < qSize; i++) {
        if (temp == pq[i])
            temp = pq[i];
        else
            return 1;
    }
    return 0;
}

void printQueue(int* q, int size) {
    int i;
    for (i = 1; i < size; i++) {
        printf(" %d", q[i]);
    }
    printf("\n");
}

int getParent(int* parent, int name) {
    if (parent[name] == name)
        return name;
    return parent[name] = getParent(parent, parent[name]);
}

void unionParent(int* parent, int u, int v) {
    u = getParent(parent, u);
    v = getParent(parent, v);
    if (u > v)
        parent[u] = v;
    else
        parent[v] = u;
}

int Kruskal(Graph* v, int* q, int size, int qSize) {
    int total = 0;
    int i, j;
    int min, minIndex;
    for (i = 0; i < qSize - 2; i++) {
        min = 99999;
        minIndex = 0;
        for (j = 0; j < size; j++) {
            if (min > v->head[j].weight && (getParent(q, v->head[j].a) != getParent(q, v->head[j].b))) {
                min = v->head[j].weight;
                minIndex = j;
            }
        }
        printf(" %d", min);
        total += min;
        unionParent(q, v->head[minIndex].a, v->head[minIndex].b);
    }
    return total;
}


int main() {
    int n, m;
    int total;
    int* pq;
    Graph g;

    scanf("%d %d", &n, &m);
    pq = (int*)malloc(sizeof(int) * (n + 1));
    initPQueue(pq, n + 1);
    initGraph(&g, m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &g.head[i].a, &g.head[i].b, &g.head[i].weight);
    }
    total = Kruskal(&g, pq, m, n + 1);
    printf("\n%d", total);
    return 0;
}
