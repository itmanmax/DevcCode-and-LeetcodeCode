#include <stdio.h>

#define MVNum 100 // 假设最大顶点数为1000

typedef char VerTexType; // 顶点的数据类型为字符型
typedef int ArcType;     // 权值类型为整型

#define INT_MAX 202112 // 正无限

int D[MVNum];  // 用于记录最短路的长度
int S[MVNum];  // 标记顶点是否进入 S 集合
int Path[MVNum]; // 用于记录最短路中路径上所经过的顶点序列

typedef struct {
    VerTexType vexs[MVNum]; // 顶点表
    ArcType arcs[MVNum][MVNum]; // 邻接矩阵
    int vexnum, arcnum; // 图的顶点数和边数
} AMGraph;

// 初始化
void initAMGraph(AMGraph *G, int n) {
    G->vexnum = n;
    G->arcnum = 0;
    printf("请依次输入各个顶点");
    for (int i = 0; i < n; i++) {
           char c;
           scanf(" %c",&G->vexs[i]);
        for (int j = 0; j < n; j++) {
            G->arcs[i][j] = INT_MAX;
        } 
		//两点最大距离初始化 
        S[i] = 0;
        D[i] = INT_MAX;
       
    }
}

void input(AMGraph *G, int m) {
    // 录入边信息
    for (int i = 0; i < m; i++) {
        char v1, v2;
        int w, d1, d2;
        scanf(" %c %c %d", &v1, &v2, &w);
        d1 = v1 - 'A';
        d2 = v2 - 'A';
        G->arcs[d1][d2] = w;
        G->arcnum++;
    }
}

// 从尚未包括在最短路径树中的顶点中选择最小距离的顶点
int minDistance(int dist[], int sptSet[], int n) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// 使用Dijkstra算法计算源点到其他所有顶点的最短路径
void Dijkstra(AMGraph *G, int src, int dest) {
    int n = G->vexnum;
    
    // 初始化
    for (int i = 0; i < n; i++) {
        S[i] = 0;
        D[i] = G->arcs[src][i];
        Path[i] = src;
    }
    S[src] = 1;

    // 计算最短路径
    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(D, S, n);

        S[u] = 1;

        // 若找到指定终点则直接返回结果
        if (u == dest) {
            printf("从 %c 到 %c 的最短路径长度是 %d\n", G->vexs[src], G->vexs[dest], D[dest]);

            // 输出最短路径
           printf("最短路径为\n");
            int temp = dest;
           char unfa[n];
           int k=n-1;
           printf("倒着输出是:\n");
           while (temp != src) {
           printf("%c -> ", G->vexs[temp]);
          unfa[k]=G->vexs[temp];
          k--;
          temp = Path[temp];
      }
       printf("%c\n", G->vexs[src]);
        unfa[k]=G->vexs[src];
        printf("正着输出是:\n");
        printf("%c",unfa[k]);
         for(int j=k+1;j<n;j++)    printf(" -> %c",unfa[j]);

            return;
        }

        for (int v = 0; v < n; v++) {
            if (!S[v] && G->arcs[u][v] != INT_MAX &&
                D[u] != INT_MAX && D[u] + G->arcs[u][v] < D[v]) {
                D[v] = D[u] + G->arcs[u][v];
                Path[v] = u;
            }
        }
    }

    // 输出最短路径长度
    printf("从 %c 到 %c 的最短路径长度是 %d\n", G->vexs[src], G->vexs[dest], D[dest]);

    // 输出最短路径
    printf("最短路径为\n");
    int temp = dest;
    char unfa[n];
    int k=n-1;
    printf("倒着输出是:\n");
    while (temp != src) {
    printf("%c -> ", G->vexs[temp]);
     unfa[k]=G->vexs[temp];
     k--;
     temp = Path[temp];
    }
    printf("%c\n", G->vexs[src]);
    unfa[k]=G->vexs[src];
    printf("正着输出是:\n");
    printf("%c ",unfa[k]);
    for(int j=1;j<n;j++)    printf("->%c ",unfa[j]);
}

int main() {
    AMGraph G;
    int n, m;
    printf("请输入城市个数和边数: ");
    // 读取城市个数和路径条数
    scanf("%d %d", &n, &m);

    initAMGraph(&G, n);
    input(&G, m);

    // 读取起点和终点
    char start, end;
    printf("请输入起点和终点: ");
    scanf(" %c %c", &start, &end);

    Dijkstra(&G, start - 'A', end - 'A');

    return 0;
}
