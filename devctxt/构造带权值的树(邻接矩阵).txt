#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// 定义边的结构体
typedef struct {
    int u; // 顶点u
    int v; // 顶点v
    int weight; // 权值
} Edge;

// 邻接矩阵
int adjacency_matrix[MAX_VERTICES][MAX_VERTICES];

// 函数声明
void input_edges(int n, int m);

int main() {
    int n, m;
    
    // 输入顶点数量
    printf("请输入顶点的数量n（n<100）：");
    scanf("%d", &n);
    
    // 输入边数量
    printf("请输入边的数量m：");
    scanf("%d", &m);
    
    // 输入边信息
    input_edges(n, m);
    
    // 输出邻接矩阵，展示结果
    printf("构造的带权值的图的邻接矩阵为：\n");
    for (int i = 1; i <=n; i++) {
        for (int j = 1; j <=n; j++) {
            printf("%d\t", adjacency_matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

// 输入边的函数
void input_edges(int n, int m) {
    Edge edge;
    for (int i = 1; i <= m; i++) {
        printf("请输入第%d条边的两个顶点u和v以及权值weight：", i );
        scanf("%d %d %d", &edge.u, &edge.v, &edge.weight);
        
        // 这里假设图是无向的，所以每条边在邻接矩阵中出现两次
        adjacency_matrix[edge.u][edge.v] = edge.weight;
        adjacency_matrix[edge.v][edge.u] = edge.weight;
    }
}
4 3 1
2 3 6
2 1 3
1 2 6

