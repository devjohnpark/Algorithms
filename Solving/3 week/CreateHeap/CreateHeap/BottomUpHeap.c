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

// 재귀 상향식 힙생성
void rBuildHeap(int i) {
    if (i > n/2) // i > 7
        return;
    rBuildHeap(i*2);
    rBuildHeap(i*2+1);
    downheap(i);
}

// 비재귀 상향식 힙생성
void buildHeap() {
    for (int i=n/2; i>=1; i--) {
        downheap(i);
    }
}


void printHeap() {
    int i = 1;
    while (i <= n) {
        printf(" %d", h[i++]);
    }
    printf("\n");
}

int main() {
    scanf("%d", &n);
    for (int i=1; i<=n; i++) {
        scanf("%d", &h[i]);
    }
    rBuildHeap(1);
//    buildHeap();
    printHeap();
    return 0;
}

