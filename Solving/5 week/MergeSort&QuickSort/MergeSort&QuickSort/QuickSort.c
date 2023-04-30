#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(a, b) {int tmp=a; a=b; b=tmp;}

// 퀵정렬
// 특징: 분할과 동시에 정렬 (제자리 가능)

// 로직
// 임의의 피봇 지정
// 피봇을 기준으로 작은 값들과 큰 값들로 분할
// 위 과정을 재귀


typedef int Key;

typedef struct partIdx {
    int front;
    int rear;
} PartIdx;

int findPivot(Key L[], int l, int r) {
    return rand() % (r - l + 1) + l;
}

// l과 r에서
PartIdx inPlacePartition(Key L[], int l, int r, int k) {
    swap(L[k], L[r]); // pivot value is L[r]
    int i = l;
    int j = r - 1; // 피봇값 꼬리값 스왑후 피봇값 전의 인덱스
    while (i<=j) {
        while (i<=j && L[i] <= L[r])
            i++;
        while(j>=i && L[j] >= L[r])
            j--;
        if(i < j)
            swap(L[i], L[j]);
    }
    swap(L[i], L[r]);
    // j 왼쪽 분할 끝 = rear
    // i 오른쪽 분할 시작 = front
    PartIdx partIdx;
    partIdx.front = j;
    partIdx.rear = i;
    return partIdx;
}

void inPlaceQuickSort(Key L[], int l, int r) {
    if (l >= r)
        return;
    int k = findPivot(L, l, r);
    PartIdx partIdx = inPlacePartition(L, l, r, k);
    inPlaceQuickSort(L, l, partIdx.rear - 1);
    inPlaceQuickSort(L, partIdx.front + 1, r);
}

int main() {
    Key *L = NULL;
    int n;
    scanf("%d", &n);
    L = (Key*)malloc(sizeof(Key)*n);
    for (int i=0; i<n; i++)
        scanf("%d", &L[i]);
    srand(time(NULL));
    inPlaceQuickSort(L, 0, n-1);
    for (int i=0; i<n; i++)
        printf(" %d", L[i]);
    free(L);
    return 0;
}
