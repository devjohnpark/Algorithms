\//
//  2.c
//  HashTable
//
//  Created by Junseo Park on 2022/11/11.
//

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int key;
    struct node *next;
} Node;

Node *hashTable = NULL;
int M;

int h(int x) {
    return x % M;
}

void insertItem(int x) {
    int k = h(x);
    Node *p = hashTable + k;
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = x;
    newNode->next = NULL;
    if (p->next == NULL) {
        p->next = newNode;
    }
    else {
        newNode->next = p->next;
        p->next = newNode;
    }
}



int searchItem(int x) {
    int k = h(x);
    int cnt = 0;

    Node *p = hashTable + k;
    
    while (p->next != NULL) {
        p = p->next;
        cnt++;
        if (p->key == x) {
            return cnt;
        }
    }
    
    return 0;
}

int deleteItem(int x) {
    int k = h(x), cnt = 0;
    Node *q = hashTable + k, *p = hashTable + k;
    
    while (p->next != NULL) {
        p = p->next;
        cnt++;
        if (p->key == x) {
            while (q->next != p) {
                q = q->next;
            }
            q->next = p->next;
            free(p);
            return cnt;
        }
    }
    return 0;
}



void printHashTable() {
    Node *p = NULL;
    for (int i = 0; i < M; i++) {
        p = hashTable + i;
        while (p->next != NULL) {
            p = p->next;
            printf(" %d", p->key);
        }
    }
    printf("\n");
}



void freeHashTable() {
    Node *p = NULL, *q = NULL;
    for (int i = 0; i < M; i++) {
        p = (hashTable + i)->next;
        if (p != NULL) {
            q = p;
            while (q->next != NULL){
                p = p->next;
                free(q);
                q = p;
            }
        }
    }
    free(hashTable);
}



int main() {
    int key;
    char instruction = '\0';
    scanf("%d", &M);
    
    hashTable = (Node*)malloc(sizeof(Node)*M);
    
    for (int i = 0; i < M; i++) {
        (hashTable + i)->next = NULL;
    }

    while (instruction != 'e') {
        scanf("%c", &instruction);
        switch (instruction) {
            case 'i':
                scanf("%d", &key);
                insertItem(key);
                getchar();
                break;
            case 's':
                scanf("%d", &key);
                printf("%d\n", searchItem(key));
                getchar();
                break;
            case 'd':
                scanf("%d", &key);
                printf("%d\n", deleteItem(key));
                getchar();
                break;
            case 'p':
                printHashTable();
                getchar();
                break;
            case 'e':
                break;
            default:
                break;
        }
    }
    freeHashTable();
    return 0;
}

