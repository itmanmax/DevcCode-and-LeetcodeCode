#include <stdio.h>
 
void generateCombinations(int n, int k, int start, int depth, int *combination) {
    // 当前组合中已经有k个数时，输出组合
    if (depth == k) {
        for (int i = 0; i < k; ++i) {
            printf("%d ", combination[i]);
        }
        printf("\n");
        return;
    }
 
    // 从start开始，尝试每个可能的数字
    for (int i = start; i <= n; ++i) {
        combination[depth] = i;
        generateCombinations(n, k, i + 1, depth + 1, combination);
    }
}
 
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
 
    // 存储当前组合的数组
    int combination[k];
    generateCombinations(n, k, 1, 0, combination);
 
    return 0;
}
