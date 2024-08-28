#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getMaxValue(int W, int n, int wt[], int val[]) {
    int i, w;
    int K[n + 1][W + 1];
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = (val[i - 1] + K[i - 1][w - wt[i - 1]] > K[i - 1][w]) ? val[i - 1] + K[i - 1][w - wt[i - 1]] : K[i - 1][w];
            else
                K[i][w] = K[i - 1][w];
        }
    }

    return K[n][W];
}

int main() {
    int n, M;
    scanf("%d %d", &n, &M);
    int arrWeight[n], arrValue[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arrWeight[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &arrValue[i]);
    }

    int maxvalue = getMaxValue(M, n, arrWeight, arrValue);
    printf("%d", maxvalue);

    return 0;
}

