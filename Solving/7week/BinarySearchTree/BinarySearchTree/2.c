#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int key, height;
    struct node *parent;
    struct node *leftChild;
    struct node *rightChild;
} Node;

Node *root = NULL;


int isExternal(Node *w) {
    printf("dfdsaf");
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



Node* reduceExternal(Node *z) {
    Node *w = NULL, *zs = NULL, *g = NULL;

    w = z->parent;
    zs = sibling(z);

    if (w == root) {
        root = zs;
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

void expandExternal(Node *w) {
    Node *leftChildNode = NULL;
    Node *rightChildNode = NULL;
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
}


Node* treeSearch(int k) {
    if (isExternal(root)) {
        return root;
    }
    if (k == root->key) {
        return root;
    }
    else if (k < root->key) {
        return treeSearch(root->leftChild, k);
    }
    else {
        return treeSearch(root->rightChild, k);
    }
}

int updateHeight(Node *w) {
    int height;

    if (w->leftChild->height > w->rightChild->height) {
        height = w->leftChild->height + 1;
    }
    else {
        height = w->rightChild->height + 1;
    }
    if (height != w->height) {
        w->height = height;
        return 1;
    }
    else {
        return 0;
    }

}

int isBalanced(Node *w) {
    if ((-1 <= (w->leftChild->height - w->rightChild->height)) && ((w->leftChild->height - w->rightChild->height) <= 1)) {
        return 1;
    }
    else {
        return 0;
    }
}

Node* restructure(Node *x, Node *y, Node *z) {
    Node *a, *b, *c;
    Node *T0, *T1, *T2, *T3;
    if ((z->key < y->key) && (y->key < x->key)) {
        a = z;
        b = y;
        c = x;
        T0 = a->leftChild;
        T1 = b->leftChild;
        T2 = c->leftChild;
        T3 = c->rightChild;
    }
    else if ((x->key < y->key) && (y->key < z->key)) {
        a = x;
        b = y;
        c = z;
        T0 = a->leftChild;
        T1 = a->rightChild;
        T2 = b->rightChild;
        T3 = c->rightChild;
    }
    else if ((z->key < x->key) && (x->key < y->key)) {
        a = z;
        b = x;
        c = y;
        T0 = a->leftChild;
        T1 = b->leftChild;
        T2 = b->rightChild;
        T3 = c->rightChild;
    }
    else {
        a = y;
        b = x;
        c = z;
        T0 = a->leftChild;
        T1 = b->leftChild;
        T2 = b->rightChild;
        T3 = c->rightChild;
    }
    if (z->parent == NULL) {
        root = b;
        b->parent = NULL;
    }
    else if (z->parent->leftChild == z) {
        z->parent->leftChild = b;
        b->parent = z->parent;
    }
    else if (z->parent->rightChild == z) {
        z->parent->rightChild = b;
        b->parent = z->parent;
    }
    a->leftChild = T0;
    T0->parent = a;
    a->rightChild = T1;
    T1->parent = a;
    updateHeight(a);
    c->leftChild = T2;
    T2->parent = c;
    c->rightChild = T3;
    T3->parent = c;
    updateHeight(c);
    b->leftChild = a;
    a->parent = b;
    b->rightChild = c;
    c->parent = b;
    updateHeight(b);
    return b;
}

void searchAndFixAfterInsertion(Node *w) {
    printf("search");
    Node *x, *y, *z;

    w->leftChild->height = 0;

    w->rightChild->height = 0;

    w->height = 1;

    if (w->parent == NULL) {
        return;
    }
    z = w->parent;
    while (updateHeight(z) && isBalanced(z)) {
        if (z->parent == NULL) {
            return;
        }
        z = z->parent;
    }
    if (isBalanced(z)) {
        return;
    }
    if (z->leftChild->height > z->rightChild->height) {
        y = z->leftChild;
    }
    else {
        y = z->rightChild;
    }
    if (y->leftChild->height > y->rightChild->height) {
        x = y->leftChild;
    }
    else {
        x = y->rightChild;
    }
    restructure( x, y, z);
    return;
}

int insertItem(int k) {
    Node *w = treeSearch(root, k);
    printf("dfdf");
    if (isInternal(w)) {
        return 0;
    }
    else {
        w->key = k;
        expandExternal(w);
        searchAndFixAfterInsertion(w);
        return 1;
    }
}

void searchAndFixAfterRemoval(Node *w) {
    Node *x, *y, *z, *b;
    if (w == NULL) {
        return;
    }
    z = w;
    while (updateHeight(z) && isBalanced(z)) {
        if (z->parent == NULL) {
            return;
        }
        z = z->parent;
    }
    if (isBalanced(z)) {
        return;
    }
    if (z->leftChild->height > z->rightChild->height) {
        y = z->leftChild;
    }
    else {
        y = z->rightChild;
    }
    if (y->leftChild->height > y->rightChild->height) {
        x = y->leftChild;
    }
    else if (y->leftChild->height < y->rightChild->height) {
        x = y->rightChild;
    }
    else {
        if (z->leftChild == y) {
            x = y->leftChild;
        }
        else if (z->rightChild == y) {
            x = y->rightChild;
        }
    }
    b = restructure(x, y, z);
    searchAndFixAfterRemoval(b->parent);
}


int removeElement(int k) {
    Node *w = treeSearch(root, k);
    Node *z, *zs, *y;
    int e;
    if (isExternal(w))
        return -1;
    e = w->key;
    z = w->leftChild;
    if (!isExternal(z)) // 왼쪽 자식 노드 외부노드 아니면
        z = w->rightChild;
    if (isExternal(z)) // 오른쪽 자식노드 외부노드면
        reduceExternal(z);
    else {  // 둘다 내부노드면
        y = inOrderSucc(w);
        z = y->leftChild;
        w->key = y->key;
        zs = reduceExternal(z);
    }
    searchAndFixAfterRemoval(zs->parent);
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
                insertItem(key);
                getchar();
                break;
            case 'd':
                scanf("%d", &key);
                value = removeElement(key);
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



