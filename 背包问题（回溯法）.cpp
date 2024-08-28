#include <stdio.h>
#include <stdlib.h>

int n;          // 物品数量
int M;          // 背包最大载重
int *w;         // 物品重量数组
int *p;         // 物品收益数组
int *x;         // 当前解（标记物品是否装入背包）
int *bestx;     // 最终解（标记物品是否装入背包）
int bestP = 0;  // 最大收益

// 计算上界函数
int bound(int i, int currentW, int currentP) {
    int maxP = currentP;
    int j, totWeight = currentW;
    // 按单位重量价值降序装入背包
    for (j = i; j < n; j++) {
        if (totWeight + w[j] <= M) { // 能完整装下
            totWeight += w[j];
            maxP += p[j];
        } else { // 不能完整装下，按比例装入
            maxP += (M - totWeight) * p[j] / w[j];
            break;
        }
    }
    return maxP;
}

// 回溯法求解0/1背包问题
void backtrack(int i, int currentW, int currentP) {
    if (i == n) { // 到达叶子节点
        if (currentP > bestP) {
            bestP = currentP;
            for (int j = 0; j < n; j++) {
                bestx[j] = x[j];
            }
        }
        return;
    }
    // 搜索左子树（装入背包）
    if (currentW + w[i] <= M) { // 剪枝条件
        x[i] = 1;
        backtrack(i + 1, currentW + w[i], currentP + p[i]);
    }
    // 搜索右子树（不装入背包）
    if (bound(i + 1, currentW, currentP) > bestP) { // 剪枝条件
        x[i] = 0;
        backtrack(i + 1, currentW, currentP);
    }
}

int main() {
    scanf("%d %d", &n, &M);
    w = (int *)malloc(n * sizeof(int));
    p = (int *)malloc(n * sizeof(int));
    x = (int *)malloc(n * sizeof(int));
    bestx = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }
    
    backtrack(0, 0, 0); // 从根节点开始回溯
    
    // 输出最佳装载方案的总收益
    printf("%d\n", bestP);
    // 输出最佳装载方案
    for (int i = 0; i < n; i++) {
        printf("%d ", bestx[i]);
    }
    printf("\n");
    
    free(w);
    free(p);
    free(x);
    free(bestx);
    
    return 0;
}
