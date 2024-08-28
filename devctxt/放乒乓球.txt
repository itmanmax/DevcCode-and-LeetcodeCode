#include <stdio.h>

// 递归函数来计算放法总数
int countWays(int n, int m) {
    // 如果没有球或者只有一个盒子，只有一种放法
    if (n == 0 || m == 1) {
        return 1;
    }
    // 如果球的数量小于盒子的数量，就不能保证所有盒子都有球
    // 相当于有些盒子一定是空的，问题简化为n个球放入n个盒子
    if (n < m) {
        return countWays(n, n);
    }
    // 两种情况的总和
    // 第一种情况：至少有一个盒子是空的
    // 第二种情况：所有的盒子都至少有一个球
    return countWays(n, m - 1) + countWays(n - m, m);
}

int main() {
    int T, n, m;
    scanf("%d", &T); // 读取测试数据的数目
    while (T--) {
        scanf("%d %d", &n, &m); // 读取每组数据的n和m
        printf("%d\n", countWays(n, m)); // 输出放法总数
    }
    return 0;
}
