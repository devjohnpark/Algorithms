//
//  InsertionhayHeapSort.c
//  HeapSort
//
//  Created by Junseo Park on 2022/09/26.
//

// max heap hay version
#include <stdio.h>
#include <stdlib.h>

typedef int Key;

Key h[100];
int n = 0;

void upheap(int i) {
    // 자식이 부모보다 크면 값 바꿈
    Key tmp;
    
    if (i < 2)
        return;
    if (h[i/2] >= h[i])
        return;
    tmp = h[i/2];
    h[i/2] = h[i];
    h[i] = tmp;
    upheap(i/2);
}

void downheap(int i) {
    // 자식이 부모보다 크면 값 바꿈
    Key tmp;
    int bigger = i*2;
    
    if (i*2<=n) {
        if (i*2+1<=n && h[bigger] < h[i*2+1])
            bigger=i*2+1;
    }
    else
        return;
    
    if (h[i] >= h[bigger])
        return;
    
    tmp = h[i];
    h[i] = h[bigger];
    h[bigger] = tmp;
    downheap(bigger);
}

void insertHeap(Key x) {
    // input last node
    // upheap
    h[++n] = x;
    upheap(n); // 1
    printf("0\n");
}

Key removeMax() {
    Key tmp = -1;
    if (n > 0) {
        tmp = h[1];
        h[1] = h[n--];
        downheap(1);
    }
    return tmp;
}

void printHeap() {
    int i = 1;
    while (i <= n) {
        printf(" %d", h[i++]);
    }
    printf("\n");
}

int main() {
    Key x;
    char instruction = '\0';

    while (instruction != 'q') {
        scanf("%c", &instruction);
        switch (instruction) {
            case 'i':
                scanf("%d", &x);
                insertHeap(x);
                break;
            case 'd':
                printf("%d\n", removeMax());
                break;
            case 'p':
                printHeap();
                break;
            default:
                break;
        }
        getchar();
    }
    return 0;
}
