//
//  main.c
//  BinaryTree
//
//  Created by Junseo Park on 2022/09/12.
//

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct TreeNode {
    element key;
    struct treeNode * left;
    struct treeNode * right;
} treeNode;

treeNode *insetTreeNode(treeNode *p, element x) {
    treeNode *newNode;
    if(p == NULL) {
        newNode = (treeNode*)malloc(sizeof(treeNode));
        newNode->key = x;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    return p;
}

int main() {
    // insert code here...
    treeNode *root = NULL;
    int n, s;
    int l, c, r;
    
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        // center, left, right
        scanf("%d %d %d", &c, &l, &r);
        // search
        
    }
    
    return 0;
}
