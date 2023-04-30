#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int key;
    struct node *parent;
    struct node *leftChild;
    struct node *rightChild;
} Node;



int isExternal(Node *w) {
    if ((w->leftChild == NULL) && (w->rightChild == NULL)) {
        return 1;
    }
    else {
        return 0;
    }
}



int isInternal(Node *w) {
    if ((w->leftChild != NULL) && (w->rightChild != NULL)) {
        return 1;
    }
    else {
        return 0;
    }
}

Node* sibling(Node *w) {
    if (w->parent == NULL) {
        exit(1);
    }
    if (w->parent->leftChild == w) {
        return w->parent->rightChild;
    }
    else {
        return w->parent->leftChild;
    }
}



Node* inOrderSucc(Node *w) {
    w = w->rightChild;
    if (isExternal(w)) {
        exit(1);
    }
    while (isInternal(w->leftChild)) {
        w = w->leftChild;
    }
    return w;
}



Node* reduceExternal(Node **root, Node *z) {
    Node *w = NULL, *zs = NULL, *g = NULL;

    w = z->parent;
    zs = sibling(z);

    if (w == *root) {
        *root = zs;
        zs->parent = NULL;
    }
    else {
        g = w->parent;
        zs->parent = g;
        if (w == g->leftChild) {
            g->leftChild = zs;
        }
        else if (w == g->rightChild) {
            g->rightChild = zs;
        }
    }
    free(z);
    free(w);
    return zs;
}



Node* treeSearch(Node *v, int k) {
    if (isExternal(v)) {
        return v;
    }
    if (k == v->key) {
        return v;
    }
    else if (k < v->key) {
        return treeSearch(v->leftChild, k);
    }
    else {
        return treeSearch(v->rightChild, k);
    }
}


int insertItem(Node *root, int k) {
    Node *leftChildNode = NULL;
    Node *rightChildNode = NULL;
    Node *w = treeSearch(root, k);
    if (isInternal(w)) {
        return 0;
    }
    else {
        w->key = k;
        leftChildNode = (Node*)malloc(sizeof(Node));
        rightChildNode = (Node*)malloc(sizeof(Node));
        leftChildNode->leftChild = NULL;
        leftChildNode->rightChild = NULL;
        leftChildNode->parent = w;
        rightChildNode->leftChild = NULL;
        rightChildNode->rightChild = NULL;
        rightChildNode->parent = w;
        w->leftChild = leftChildNode;
        w->rightChild = rightChildNode;
        return 1;
    }
}



int removeElement(Node **root, int k) {
    Node *w = treeSearch(*root, k);
    Node *z, *y;
    int e;
    if (isExternal(w))
        return -1;
    e = w->key;
    z = w->leftChild;
    if (!isExternal(z)) // 왼쪽 자식 노드 외부노드 아니면
        z = w->rightChild;
    if (isExternal(z)) // 오른쪽 자식노드 외부노드면
        reduceExternal(root, z);
    else {  // 둘다 내부노드면
        y = inOrderSucc(w);
        z = y->leftChild;
        w->key = y->key;
        reduceExternal(root, z);
    }
    return e;
}



void printTree(Node *w) {
    if (isExternal(w)) {
        return;
    }
    else {
        printf(" %d", w->key);
        printTree(w->leftChild);
        printTree(w->rightChild);
    }
}



void freeTree(Node *w) {
    if (isExternal(w)) { // Null
        return;
    }
    else {
        freeTree(w->leftChild); // Null
        freeTree(w->rightChild);
        free(w);
    }
}



int main() {
    char instruction = '\0';
    int key, value;
    Node *root = (Node*)malloc(sizeof(Node));
    root->parent = NULL;
    root->leftChild = NULL;
    root->rightChild = NULL;
    while (instruction != 'q') {
        scanf("%c", &instruction);
        switch (instruction) {
            case 'i':
                scanf("%d", &key);
                insertItem(root, key);
                getchar();
                break;
            case 'd':
                scanf("%d", &key);
                value = removeElement(&root, key);
                if (value == -1) {
                    printf("X\n");
                }
                else {
                    printf("%d\n", value);
                }
                getchar();
                break;
            case 's':
                scanf("%d", &key);
                if (treeSearch(root, key)->key != key) {
                    printf("X\n");
                }
                else {
                    printf("%d\n", treeSearch(root, key)->key);
                }
                getchar();
                break;
            case 'p':
                printTree(root);
                printf("\n");
                break;
            case 'q':
                break;
            default:
                break;
        }
    }
    freeTree(root);
    return 0;
}



