//
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

int *hashTable;
int M, n;

int h(int x) {
    return (x % M) ;
}

int getNextBucket(int k, int i) {
    return (k + i) % M;
}

void insertItem(int x) {

    int v = h(x), i = 0, b;
    while (i < M) {
        b = getNextBucket(v, i);
        if (hashTable[b] == 0) {
            hashTable[b] = x;
            for (int j = 0; j < i; j++) {
                printf("C");
            }
            printf("%d\n", b);
            return;
        }
        else {
            i = i + 1;
        }
    }
}

void searchItem(int x) {
    int k = h(x), i = 0, b;
    while (i < M) {
        b = getNextBucket(k, i);
        if (hashTable[b] == 0) {
            printf("-1\n");
            return;
        }
        else if (hashTable[b] == x) {
            printf("%d %d\n", b, hashTable[b]);
            return;
        }
        else {
            i = i + 1;
        }
    }
    printf("-1\n");
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

int main() {
    int key;
    char instruction = '\0';
    scanf("%d %d", &M, &n);
    
    hashTable = (int*)malloc(sizeof(int)*M);
    
    for (int i = 0; i < M; i++) {
        *(hashTable + i) = 0;
    }
    getchar();
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
                searchItem(key);
                break;
            case 'e':
                break;
            default:
                break;
        }
    }
    free(hashTable);
    return 0;
}
