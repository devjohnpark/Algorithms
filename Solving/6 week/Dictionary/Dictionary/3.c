//
//  main.c
//  Dictionary
//
//  Created by Junseo Park on 2022/10/14.
//

#include <stdio.h>
#include <stdlib.h>

int binarySearch(char *p, int l, int r) {
    int m = (l + r) / 2; // 중간값
    
    if (l >= r)
        return r;
    if (*p == 'N')
        return binarySearch(++p, l, m);
    else
        return binarySearch(++p, m+1, r);
}

int main() {
    // insert code here...
    int a, b, n;
    char *p = NULL;
    scanf("%d %d %d", &a, &b, &n);
    p = (char*)malloc(sizeof(char)*(n+1));
    scanf("%s", p);
    int result = binarySearch(p, a, b);
    printf("%d", result);
    free(p);
    return 0;
}
