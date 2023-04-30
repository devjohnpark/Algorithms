//
//  main.c
//  Dictionary
//
//  Created by Junseo Park on 2022/10/14.
//

#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int l, int r, int k) {
    while (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid] < k) {
            l = mid + 1;
        }
        else if (arr[mid] > k) {
            r = mid - 1;
        }
        else
            return mid;
    }
    return l;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int *p = NULL;
    int n, k;
    scanf("%d %d", &n, &k);
    p =(int*)malloc(sizeof(int)*n);
    for (int i=0; i<n; i++)
        scanf("%d", &p[i]);
    int maxIdx = binarySearch(p, 0, n-1, k);
    printf(" %d", maxIdx);
    free(p);
    return 0;
}
