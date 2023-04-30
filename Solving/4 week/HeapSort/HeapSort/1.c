//
//  InsertionhayHeapSort.c
//  HeapSort
//
//  Created by Junseo Park on 2022/09/26.
//

// 제자리 힙정렬
// 상향식 힙정렬
#include <stdio.h>
#include <stdlib.h>

typedef int Key;

Key h[100];
int n = 0;

// 최대 힙 생성
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

// 최대 힙 생성 (root 노드를 tail 노드를 옮기고 tail 노드를 제외하고 힙 생성)
void downheap(int i, int last) {
    // 자식이 부모보다 크면 값 바꿈
    Key tmp;
    int left = i*2;
    int right = i*2+1;
    
    if (left > last)
        return;
    int greater = left;
    if (right<=last)
        if(h[right]>h[greater])
            greater = right;
    if(h[i]>=h[greater])
        return;
    tmp = h[i];
    h[i] = h[greater];
    h[greater] = tmp;
    downheap(greater, last);
}


// 삽입식 힙 생성
void insertHeap(int i, Key x) {
    // input last node
    // upheap
    h[i] = x;
    upheap(i); // 1
}

// 재귀 상향식 최대 힙생성
void rBuildHeap(int i) {
    if (i > n/2) // n = 6, 4 이상
        return;
    rBuildHeap(i*2);
    rBuildHeap(i*2+1);
    downheap(i, n);
}


// 힙 생성
void buildHeap() {
    Key x;
    for (int i=1; i<=n; i++) {
        scanf("%d", &x);
        insertHeap(i, x);
    }
    // 비재귀적 상향식 힙생성
//    for (int i=n/2; i>=1; i--) {
//        downheap(i, n);
//    }
}

void printHeap() {
    int i = 1;
    while (i <= n) {
        printf(" %d", h[i++]);
    }
    printf("\n");
}

// 오름 차순 힙 정렬 (작은순)
void inPlaceHeapSort() {
    Key tmp;
    buildHeap();    // 최대 힙 생성 (upheap)
//    rBuildHeap(1);   // 상향식 (재귀적) 최대 힙 생성 (down heap)
    for (int i=n; i>=2; i--) {
        // 최댓값 tail로
        tmp = h[1];
        h[1] = h[i];
        h[i] = tmp;
        
        // 최대 힙 생성
        downheap(1, i-1); // 꼬리 노드는 최대값 이므로 힙정렬 해줄 필요 없다.
    }
}

int main() {
    scanf("%d", &n);
    inPlaceHeapSort();
    printHeap();
    return 0;
}

//8
//31 10 10 20 31 31 31 10
