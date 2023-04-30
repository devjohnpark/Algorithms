//
//  main.c
//  SelectionSort
//
//  Created by Junseo Park on 2022/09/15.
//

#include <stdio.h>
#include <stdlib.h>

int main() {
    // insert code here...
    int n, *p = NULL;
    scanf("%d", &n);
    p = (int*)malloc(sizeof(int)*n);
    
    for (int i=0; i<n; i++) {
        scanf("%d", &p[i]);
    }
    
    int maxIdx;
    int tmp;
    
    for (int i=n-1; i>0; i--) { // element
        maxIdx = i;
        for (int j=0; j<i; j++) {
            if (p[maxIdx] < p[j])
                maxIdx = j;
        }
        tmp = p[i];
        p[i] = p[maxIdx];
        p[maxIdx] = tmp;
    }
    
//    for (int i=0; i<n-1; i++) { // element
//        minIdx = i;
//        for (int j=i+1; j<n; j++) {
//            if (p[j] < p[minIdx])
//                minIdx = j;
//        }
//        tmp = p[i];
//        p[i] = p[minIdx];
//        p[minIdx] = tmp;
//    }
    
    for (int i=0; i<n; i++)
        printf(" %d", p[i]);
    
    free(p);
    return 0;
}
