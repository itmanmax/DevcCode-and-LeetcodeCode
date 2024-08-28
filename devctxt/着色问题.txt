#include <stdio.h>
#include <stdlib.h>

int n, e, m;               
int *x;                    
int **a;

void nextValue(int k) {
       int j;
       while (1)
       {
        x[k] = (x[k] + 1) % (m + 1);
        if (x[k] == 0) return;
        for (j = 0; j < k; j++) {
            if(a[k][j] && x[k] == x[j]) break;
        }
        if (j == k) return;
       }
}

void printSolution() {
    for (int i = 0; i < n; ++i) {
        printf("%d ", x[i]);
    }
    printf("\n");
}

void mColoring(int k) {
   while (1)
   {
    nextValue(k);
    if (x[k] == 0) return;
    if (k == n - 1) {
        printSolution();
    } else {
        x[k + 1] = 0;
        mColoring(k + 1);
    }
   }
}

int main() {
    scanf("%d %d %d", &n, &e, &m);
    x = (int *)malloc(n * sizeof(int));
    a = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        a[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j) {
            a[i][j] = 0; 
        }
    }
    int start, end;
    for (int i = 0; i < e; ++i) {
        scanf("%d %d", &start, &end);
        a[start][end] = 1;	
        a[end][start] = 1; 
    }
    for (int i = 0; i < n; ++i) {
        x[i] = 0;
    }
    mColoring(0);
    for (int i = 0; i < n; ++i) {
        free(a[i]);
    }
    free(a);
    free(x);
    return 0;
}
