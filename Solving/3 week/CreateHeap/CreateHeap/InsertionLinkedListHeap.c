//
//  main.c
//  HeapSort
//
//  Created by Junseo Park on 2022/09/22.
//

#include <stdio.h>
#include <stdlib.h>

// priority queue (heap sort)
// linked list

typedef int Key;

typedef struct heapNode {
    Key key;
    struct heapNode *parent;
    struct heapNode *childLeft;
    struct heapNode *childRight;
} HeapNode;

HeapNode *root;
HeapNode *tail;


void initRootNode(HeapNode *root);
HeapNode* getHeapNode(HeapNode *parent, Key key);
HeapNode * insertHeap(HeapNode *node, Key key);
void upHeap(HeapNode *lastNode);
void printHeap(HeapNode *p);
void quit(HeapNode *root);
//int deleteHeap(HeapNode *p);
//int searchHeap(HeapNode *p, Key key);

int main() {
    int n;
    Key key;
    char instruction = '\0';

    while (instruction != 'q') {
        scanf("%c", &instruction);
        switch (instruction) {
            case 'i':
                scanf("%d", &key);
                root = insertHeap(root, key);
                printf("root %p\n", root);
                break;
//            case 'd':
//                deleteHeap(root);
//                break;
            case 'p':
                printHeap(root);
                printf("\n");
                break;
//            case 's':
//                scanf("%d", &key);
//                searchHeap(root, key);
//                break;
            case 'q':
                quit(root);
                break;
            default:
                break;
        }
        getchar();
    }
    return 0;
}

//void initRootNode(HeapNode *root) {
//    HeapNode *newNode;
//    newNode = (HeapNode*)malloc(sizeof(HeapNode));
//    newNode->parent = NULL;
//    root = newNode;
//}

// save a top node(tail node) location
// find to be a tail node
// insert the key to tail node
// bottom to the top recover heap sequence
HeapNode * insertHeap(HeapNode *parent, Key key) {
    // find last node
    HeapNode *newNode = NULL;
    if (parent == NULL) {
        newNode = getHeapNode(NULL, key);
        return newNode;
//        upHeap(newNode);
//        return newNode;
//        HeapNode *newNode = NULL;
//        newNode = (HeapNode*)malloc(sizeof(HeapNode));
//        newNode->childLeft = NULL;
//        newNode->childRight = NULL;
//        newNode->key = key;
//        newNode->parent = pt;
//        // up heap (bottom to the top recover heap sequence)
//        upHeap(newNode);
//        p = newNode;
    }
    else if (parent->childLeft == NULL) {
        newNode = getHeapNode(parent, key);
        // up heap (bottom to the top recover heap sequence)

//        parent->childLeft = newNode;
        parent->childLeft =  insertHeap(parent->childLeft, key);
    }
    else if (parent->childRight == NULL) {
        newNode = getHeapNode(parent, key);
        // up heap (bottom to the top recover heap sequence)
        parent = newNode;
        parent->childRight = newNode;
        parent->childRight = insertHeap(parent->childRight, key);
    }
    
    return parent;
}

HeapNode* getHeapNode(HeapNode *parent, Key key) {
    HeapNode *newNode;
    newNode = (HeapNode*)malloc(sizeof(HeapNode));
    newNode->parent = parent;
    newNode->childLeft = NULL;
    newNode->childRight = NULL;
    newNode->key = key;
    return newNode;
}

void upHeap(HeapNode *lastNode) {
    if(lastNode->parent != NULL) {
        printf("upheap\n");
        if(lastNode->key > lastNode->parent->key) {
            Key tmp = lastNode->parent->key;
            lastNode->parent->key = lastNode->key;
            lastNode->key = tmp;
            upHeap(lastNode->parent);
        }
    }
}

//Key deleteHeap(HeapNode *root) {
//
//}
//
void printHeap(HeapNode *p) {
    if(p != NULL) {
        printf("%d ", p->key);
        printHeap(p->childLeft);
        printHeap(p->childRight);
    }
}
//int searchHeap(HeapNode *root, Key key) {
//
//}

void quit(HeapNode *root) {
    HeapNode *p = root;
    if(p != NULL) {
        printHeap(p->childLeft);
        printHeap(p->childRight);
        free(p);
    }
}
