#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    int weight;
    int profit;
} Item;

Item *items;
int *x, *bestx;
int n, M, maxp = 0, cp = 0, cw = 0;

// 辅助函数，用于找到上界
int Bound(int i) {
    int cleft = M - cw, b = cp;
     // 贪心算法寻找上界
    while (i < n && items[i].weight <= cleft) {
        cleft -= items[i].weight;
        b += items[i].profit;
        i++;
    }
  // 取下一个物品的一部分
    if (i < n) b += items[i].profit * cleft / items[i].weight;
    return b;
}

void Backtrack(int i) {
    if (i >= n) {
        if (cp > maxp) {
            maxp = cp;
            for (int j = 0; j < n; j++) bestx[j] = x[j];
        }
        return;
    }
    if (cw + items[i].weight <= M) {
        x[i] = 1;
        cw += items[i].weight;
        cp += items[i].profit;
        Backtrack(i + 1);
        cw -= items[i].weight;
        cp -= items[i].profit;
    }
    if (Bound(i + 1) > maxp) {
        x[i] = 0;
        Backtrack(i + 1);
    }
}

int main() {
    scanf("%d %d", &n, &M);

    items = (Item *)malloc(n * sizeof(Item));
    x = (int *)malloc(n * sizeof(int));
    bestx = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) scanf("%d", &items[i].profit);
    for (int i = 0; i < n; i++) scanf("%d", &items[i].weight);

    Backtrack(0);

    printf("%d\n", maxp);
    for (int i = 0; i < n; i++) {
        printf("%d ", bestx[i]);
    }
    printf("\n");

    free(items);
    free(x);
    free(bestx);

    return 0;
}
