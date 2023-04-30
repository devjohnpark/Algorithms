//
//  main.c
//  cexample
//
//  Created by Junseo Park on 2022/09/02.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct __node {
    char element;
    struct __node *prev;
    struct __node *next;
} Node;

typedef struct {
    Node *head;
    int cnt;
} LinkedList;

/*--- create node dynamically ---*/
static Node* AllocDNode(void)
{
    return calloc(1, sizeof(Node));
}

void listInit(LinkedList *list) {
    list->head = NULL;
    list->cnt = 0;
}

void setNode(Node *node, char element, Node *prev, Node *next) {
    node->element = element;
    node->prev = prev;
    node->next = next;
}

int verifyListCount(LinkedList *list, int rank, char instruction) {
    switch (instruction) {
        case 'A':
            if (list->cnt + 1 >= rank) {
                list->cnt++;
                return 1;
            }
            break;
        case 'D':
            if (list->cnt >= rank) {
                list->cnt--;
                return 1;
            }
            break;
        case 'G':
            if (list->cnt >= rank)
                return 1;
            break;
        default:
            break;
    }
    return 0;
}

void add(LinkedList *list, int rank, char element) {
    Node *pre = list->head;
    
    // search pre node
    for (int i=0; i<rank-2; i++) // 0, 1, 2
        pre = pre->next;
    
    Node *new = AllocDNode(); // allcate memory
    
    if (list->head == pre && rank == 1) {
        if (list->head == NULL) {   // first head node
            list->head = new;
            setNode(list->head, element, NULL, NULL);
        }
        else {  // already exist first head node
            setNode(new, element, NULL, list->head);
            pre->prev = new;
            list->head = new;
        }
    }
    else if (pre->next != NULL) { // mid node
        setNode(new, element, pre, pre->next);
        pre->next->prev = new;
        pre->next = new;
    }
    else if (pre->next == NULL) { // tail node
        setNode(new, element, pre, pre->next);
        pre->next = new;
    }
}

void delete(LinkedList *list, int rank) {
    Node *p = list->head;
    
    // search the node to delete
    for (int i=0; i<rank-1; i++)
        p = p->next;
    
    if (list->head == p) { // head node
        if (list->head->next != NULL) // head node and not tail node
            p->next->prev = NULL;
        list->head = list->head->next;  // head node and tail node
    }
    else {
        if (p->next != NULL) // mid node
            p->next->prev = p->prev;
        p->prev->next = p->next; // mid node and tail node
    }
    
    free(p);
}

void get(LinkedList *list, int rank) {
    Node *p = list->head;
    for (int i=0; i<rank-1; i++)
        p = p->next;
    printf("%c\n", p->element);
}

void printAll(LinkedList *list) {
    Node *p = list->head;
    while (p != NULL) {
        printf("%c", p->element);
        p = p->next;
    }
    printf("\n");
}

void terminate(LinkedList *list) {
    Node *p = list->head;
    Node *q = NULL;
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q);
    }
}

int main() {
    int n, rank;
    char instruction, element;
    LinkedList list;
    
    listInit(&list);
    
    scanf("%d", &n);
    
    for (int i=0; i<n; i++) {
        getchar();
        scanf("%c", &instruction);
        
        switch (instruction) {
            case 'A':
                scanf("%d %c", &rank, &element);
                verifyListCount(&list, rank, instruction) ? add(&list, rank, element) : printf("invalid position\n");
                break;
            case 'D':
                scanf("%d", &rank);
                verifyListCount(&list, rank, instruction) ? delete(&list, rank) : printf("invalid position\n");
                break;
            case 'G':
                scanf("%d", &rank);
                verifyListCount(&list, rank, instruction) ? get(&list, rank) : printf("invalid position\n");
                break;
            case 'P':
                printAll(&list);
                break;
            default:
                break;
        }
    }
    
    terminate(&list);
    
    return 0;
}
