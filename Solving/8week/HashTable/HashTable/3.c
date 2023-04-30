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
int M, n, q;

int h(int x) {
    return x % M;
}

int h2(int x) {
    return q - (x % q);
}

int getNextBucket(int v, int i, int k) {
    return(v + i * h2(k) % M) % M;
}

void insertItem(int k) {
    int v = h(k), i = 0, b;
    while (i < M) {
        b = getNextBucket(v, i, k);
        if (hashTable[b] == 0) {
            hashTable[b] = k;
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

void searchItem(int k) {
    int v = h(k), i = 0, b;
    while (i < M) {
        b = getNextBucket(v, i, k);
        if (hashTable[b] == 0) {
            printf("-1\n");
            return;
        }
        else if (hashTable[b] == k) {
            printf("%d %d\n", b, hashTable[b]);
            return;
        }
        else {
            i = i + 1;
        }
    }
    printf("-1\n");
}

void printTable() {
    for (int i = 0; i < M; i++) {
        printf(" %d", hashTable[i]);
    }
    printf("\n");
}


int main() {
    int key;
    char instruction = '\0';
    scanf("%d %d %d", &M, &n, &q);
    
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
                getchar();
                break;
            case 'p':
                printTable();
                break;
            case 'e':
                printTable();
                break;
            default:
                break;
        }
    }
    free(hashTable);
    return 0;
}

