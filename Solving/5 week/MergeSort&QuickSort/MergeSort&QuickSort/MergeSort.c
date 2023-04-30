//
//  main.c
//  MergeSort&QuickSort
//
//  Created by Junseo Park on 2022/10/10.
//

#include <stdio.h>
#include <stdlib.h>

typedef int Key;

typedef struct node {
    Key key;
    struct node *next;
} Node;

typedef struct list {
    int cnt;
    struct node *head;
} List;

typedef struct listTuple {
    List *L1;
    List *L2;
} ListTuple;

// List init
List *initList(void) {
    List *L = NULL;
    L = (List*)malloc(sizeof(List));
    L->head = NULL;
    L->cnt = 0;
    return L;
}

// addLastNode
void addLastNode(List *L, Key x) {
    Node *newNode = NULL;
    newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->key = x;
    L->cnt++;
    if (L->head == NULL) {
        L->head = newNode;
        return;
    }
    Node *pre = L->head;
    while (pre->next != NULL) {
        pre = pre->next;
    }
    pre->next = newNode;
}

// removeFirstNode
Key removeFirstNode(List *L) {
    if (L->head != NULL)    {
        Node *p = L->head->next;
        Key key = L->head->key;
        free(L->head);
        L->head = p;
        L->cnt--;
        return key;
    }
    return -1;
}

// printList
void printList(List *L) {
    Node *p = L->head;
    while (p) {
        printf(" %d", p->key);
        p = p->next;
    }
}

// divide
ListTuple partition(List *L, int k) {
    ListTuple LT;
    LT.L1 = initList();
    LT.L2 = initList();
    Node *p = L->head;
    LT.L1->head = p;
    for (int i=0; i<k-1; i++) // 5 >> k=2, 0 1 2 3 4
        p = p->next;
    LT.L2->head = p->next;
    p->next = NULL; // 첫번재 리스트 잘라줌
    return LT;
}

// merge (실제 정렬)
List *merge(List *L1, List *L2) {
    List *L = initList();
    // 값 비교후 작은값 리스트에 넣는다.
    while (L1->head != NULL && L2->head != NULL) {
        if(L1->head->key < L2->head->key)
            addLastNode(L, removeFirstNode(L1));
        else
            addLastNode(L, removeFirstNode(L2));
    }
    while (L1->head != NULL)
        addLastNode(L, removeFirstNode(L1));
    while (L2->head != NULL)
        addLastNode(L, removeFirstNode(L2));
    free(L1);
    free(L2);
    return L;
}

// 오름차순 합병 정렬
void mergeSort(List **L) {
    // 분할 (partition)
    // 분할 반복 (recur)
    // 합병 (merge)
    if ((*L)->cnt > 1) {
        ListTuple LT;
        LT = partition(*L, (*L)->cnt/2); // copy
        LT.L1->cnt = LT.L2->cnt = (*L)->cnt/2;
        if ((*L)->cnt % 2 == 1)
            LT.L2->cnt++;
        mergeSort(&LT.L1); // L1 recur
        mergeSort(&LT.L2); // L2 recur
        *L = merge(LT.L1, LT.L2);
    }
}

int main(int argc, const char * argv[]) {
    int n;
    Key x;
    List *L = initList();
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        scanf("%d", &x);
        addLastNode(L, x);
    }
    
    mergeSort(&L);
    printList(L);
    
    for (int i=0; i<n; i++)
        removeFirstNode(L);
    
    free(L);
    return 0;
}
