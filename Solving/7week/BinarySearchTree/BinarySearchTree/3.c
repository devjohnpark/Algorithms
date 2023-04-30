
#include<stdio.h>

#include<stdlib.h>



typedef struct node {
    int key, height;
    struct node *parent;
    struct node *leftChild;
    struct node *reftChild;
} Node;

Node *root;


int isExternal(Node *w) {

    if ((w->leftChild == NULL) && (w->reftChild == NULL)) {

        return 1;

    }

    else {

        return 0;

    }

}



int isInternal(Node *w) {

    if ((w->leftChild != NULL) && (w->reftChild != NULL)) {

        return 1;

    }

    else {

        return 0;

    }

}



Node* sibling(Node *w) {

    if (w->parent == NULL) {

        return NULL;

    }

    if (w->parent->leftChild == w) {

        return w->parent->reftChild;

    }

    else {

        return w->parent->leftChild;

    }

}



Node* inOrderSucc(Node *w) {

    w = w->reftChild;

    if (isExternal(w)) {

        return NULL;

    }

    while (isInternal(w->leftChild)) {

        w = w->leftChild;

    }

    return w;

}



void expandExternal(Node *w) {

    Node *leftnode = (Node*)malloc(sizeof(Node));

    Node *rightnode = (Node*)malloc(sizeof(Node));

    leftnode->leftChild = NULL;

    leftnode->reftChild = NULL;

    leftnode->height = 0;

    leftnode->parent = w;

    rightnode->leftChild = NULL;

    rightnode->reftChild = NULL;

    rightnode->height = 0;

    rightnode->parent = w;

    w->leftChild = leftnode;

    w->reftChild = rightnode;

    w->height = 1;

    return;

}



Node *reduceExternal(Node *z) {

    Node *p, *zs, *g;

    p = z->parent;

    zs = sibling(z);

    if (p->parent == NULL) {

        root = zs;

        zs->parent = NULL;

    }

    else {

        g = p->parent;

        zs->parent = g;

        if (p == g->leftChild)

            g->leftChild = zs;

        else if (p == g->reftChild)

            g->reftChild = zs;

    }

    free(z);

    free(p);

    return zs;

}



Node* treeSearch(Node *w, int k) {

    if (isExternal(w))

        return w;

    if (w->key == k)

        return w;

    else if (w->key > k)

        return treeSearch(w->leftChild, k);

    else

        return treeSearch(w->reftChild, k);

}



int updateHeight(Node *w) {

    int height;

    if (w->leftChild->height > w->reftChild->height) {

        height = w->leftChild->height + 1;

    }

    else {

        height = w->reftChild->height + 1;

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

    if ((-1 <= (w->leftChild->height - w->reftChild->height)) && ((w->leftChild->height - w->reftChild->height) <= 1)) {

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

        T3 = c->reftChild;

    }

    else if ((x->key < y->key) && (y->key < z->key)) {

        a = x;

        b = y;

        c = z;

        T0 = a->leftChild;

        T1 = a->reftChild;

        T2 = b->reftChild;

        T3 = c->reftChild;

    }

    else if ((z->key < x->key) && (x->key < y->key)) {

        a = z;

        b = x;

        c = y;

        T0 = a->leftChild;

        T1 = b->leftChild;

        T2 = b->reftChild;

        T3 = c->reftChild;

    }

    else {

        a = y;

        b = x;

        c = z;

        T0 = a->leftChild;

        T1 = b->leftChild;

        T2 = b->reftChild;

        T3 = c->reftChild;

    }



    if (z->parent == NULL) {

        root = b;

        b->parent = NULL;

    }

    else if (z->parent->leftChild == z) {

        z->parent->leftChild = b;

        b->parent = z->parent;

    }

    else if (z->parent->reftChild == z) {

        z->parent->reftChild = b;

        b->parent = z->parent;

    }



    a->leftChild = T0;

    T0->parent = a;

    a->reftChild = T1;

    T1->parent = a;

    updateHeight(a);



    c->leftChild = T2;

    T2->parent = c;

    c->reftChild = T3;

    T3->parent = c;

    updateHeight(c);



    b->leftChild = a;

    a->parent = b;

    b->reftChild = c;

    c->parent = b;

    updateHeight(b);



    return b;

}



void searchAndFixAfterInsertion(Node *w) {

    Node *x, *y, *z;

    w->leftChild->height = 0;

    w->reftChild->height = 0;

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

    if (z->leftChild->height > z->reftChild->height) {

        y = z->leftChild;

    }

    else {

        y = z->reftChild;

    }

    if (y->leftChild->height > y->reftChild->height) {

        x = y->leftChild;

    }

    else {

        x = y->reftChild;

    }

    restructure(x, y, z);

    return;

}



void insertItem(Node *w, int k) {

    Node *p = treeSearch(w, k);

    if (isInternal(p)) {

        return;

    }

    else {

        p->key = k;

        expandExternal(p);

        searchAndFixAfterInsertion(p);

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

    if (z->leftChild->height > z->reftChild->height) {

        y = z->leftChild;

    }

    else {

        y = z->reftChild;

    }

    if (y->leftChild->height > y->reftChild->height) {

        x = y->leftChild;

    }

    else if (y->leftChild->height < y->reftChild->height) {

        x = y->reftChild;

    }

    else {

        if (z->leftChild == y) {

            x = y->leftChild;

        }

        else if (z->reftChild == y) {

            x = y->reftChild;

        }

    }

    b = restructure(x, y, z);

    searchAndFixAfterRemoval(b->parent);

}



int removeElement(Node *w, int k) {

    Node *p = treeSearch(w, k);

    Node *z, *zs, *y;

    int e;

    if (isExternal(p)) {

        return -1;

    }

    e = p->key;

    z = p->leftChild;

    if (!isExternal(z)) {

        z = p->reftChild;

    }

    if (isExternal(z)) {

        zs = reduceExternal(z);

    }

    else {

        y = inOrderSucc(p);

        z = y->leftChild;

        p->key = y->key;

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

        printTree(w->reftChild);

    }

}



void freeTree(Node *w) {

    if (isExternal(w)) {

        return;

    }

    else {

        freeTree(w->leftChild);

        freeTree(w->reftChild);

        free(w);

    }

}



int main() {
    char text;
    int key, value;
    root = (Node*)malloc(sizeof(Node));
    root->parent = NULL;
    root->leftChild = NULL;
    root->reftChild = NULL;
    while (1) {
        scanf("%c", &text);
        if (text == 'i') {
            scanf("%d", &key);
            insertItem(root, key);
            getchar();
        }
        else if (text == 'd') {
            scanf("%d", &key);
            value = removeElement(root, key);
            if (value == key) {
                printf("%d\n", value);
            }
            else {
                printf("X\n");
            }
            getchar();
        }

        else if (text == 's') {
            scanf("%d", &key);

            if (treeSearch(root, key)->key != key) {

                printf("X\n");

            }

            else {

                printf("%d\n", treeSearch(root, key)->key);

            }

            getchar();

        }

        else if (text == 'p') {

            printTree(root);

            printf("\n");

        }

        else if (text == 'q') {

            break;

        }

    }

    freeTree(root);

}

