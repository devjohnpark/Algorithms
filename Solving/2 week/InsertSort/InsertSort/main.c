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
    
    int j;
    int tmp;
    
    for (int i=1; i<n; i++) { // element
        j=i-1;
        tmp=p[i];
        while (j>=0 && tmp < p[j]) {
            p[j+1] = p[j];
            j-=1;
        }
        p[j+1] = tmp;
    }
    
    for (int i=0; i<n; i++)
        printf(" %d", p[i]);
    
    free(p);
    return 0;
}
