#include <stdio.h>
#include <stdlib.h>

#define MAXN 11

// 用于存储皇后位置的结构体
typedef struct {
    int queens[MAXN]; // 存储皇后列位置
    int row;          // 当前行号
} Node;

// 全局变量，存储解的一个实例
int solution[MAXN];

// 检查当前位置是否安全
int isSafe(int queens[], int row, int col) {
    for (int i = 0; i < row; i++) {
        // 检查同列和对角线上是否有冲突
        if (queens[i] == col || abs(queens[i] - col) == abs(i - row)) {
            return 0;
        }
    }
    return 1;
}

// 打印解决方案
void printSolution(int queens[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", queens[i] + 1);
    }
    printf("\n");
}

void nQueens(int n) {
    Node queue[MAXN * MAXN]; // 队列
    int front = 0, rear = 0; // 队列的头和尾

    // 初始结点
    Node initial = { {0}, 0 };
    queue[rear++] = initial;

    while (front < rear) {
        Node current = queue[front++]; // 出队

        if (current.row == n) {
            // 找到一个解
            for (int i = 0; i < n; i++) {
                solution[i] = current.queens[i];
            }
            printSolution(solution, n);
            return; // 只需要一个解
        }

        // 遍历当前行的所有列
        for (int i = 0; i < n; i++) {
            if (isSafe(current.queens, current.row, i)) {
                Node child = current;
                child.queens[child.row] = i; // 放置皇后
                child.row++;
                queue[rear++] = child; // 入队
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    nQueens(n);
    return 0;
}
