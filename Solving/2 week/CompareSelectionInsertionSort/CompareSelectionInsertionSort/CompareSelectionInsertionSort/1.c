//
//  main.c
//  CompareSelectionInsertionSort
//
//  Created by Junseo Park on 2022/09/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    int *pa = NULL, *pb = NULL;
    clock_t start1, end1, start2, end2;
    
    scanf("%d", &n);
    
    pa = (int*)malloc(sizeof(int)*n);
    pb = (int*)malloc(sizeof(int)*n);
    
    srand(time(NULL));
    
    int tmp;
    int maxIdx;
    
    for (int i=0; i<n; i++) {
        tmp = rand();
        pa[i]=tmp;
        pb[i]=tmp;
    }
    
    // selection sort
    start1 = clock();
    for (int i=n-1; i>0; i--) {
        maxIdx = i;
        for (int j=0; j<i; j++) {
            if (pa[maxIdx] < pa[j])
                maxIdx = j;
        }
        tmp = pa[i];
        pa[i] = pa[maxIdx];
        pa[maxIdx] = tmp;
    }
    end1 = clock();
    
    // insertion sort
    start2 = clock();
    for (int i=1; i<n; i++) {
         int j = i-1;
         tmp=pb[i];
         while (j>=0 && tmp < pb[j]) {
             pb[j+1] = pb[j];
             j-=1;
         }
         pb[j+1] = tmp;
    }
    end2 = clock();
    

    printf("%f\n", (float)(end1 - start1)/CLOCKS_PER_SEC);
    printf("%f\n", (float)(end2 - start2)/CLOCKS_PER_SEC);
    
    free(pa);
    free(pb);
    return 0;
}
