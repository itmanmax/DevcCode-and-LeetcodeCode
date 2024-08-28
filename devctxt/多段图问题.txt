#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
#define MAX_VERTICES 100
 
// 定义图的邻接矩阵
int adjacency_matrix[MAX_VERTICES][MAX_VERTICES];
 
// 初始化图
void initializeGraph(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adjacency_matrix[i][j] = INT_MAX;
        }
    }
}
 
// Dijkstra 算法实现
void dijkstra(int n, int start) {
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int nextVertex[MAX_VERTICES];
 
    // 初始化距离数组和访问数组
    for (int i = 0; i <n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        nextVertex[i] = -1;
    }
 
    // 设置起始顶点的距离为 0
    dist[start] = 0;
 
    // 遍历所有顶点
    for (int i = 0; i < n; i++) {
        // 找到未访问顶点中距离最小的顶点
        int minDist = INT_MAX;
        int u;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }
 
        // 标记 u 为已访问
        visited[u] = 1;
 
        // 更新 u 的所有邻居的距离
        for (int v = 0; v < n; v++) {
            if (!visited[v] && adjacency_matrix[u][v] != INT_MAX) {
                int alt = dist[u] + adjacency_matrix[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    nextVertex[v] = u;
                }
            }
        }
    }
    
    
  
        printf("%d ",dist[n-1]);
    
}
void input_edges(int n, int m) {
    for (int i = 0; i < m; i++) {
        int n1,n2,weight;
        scanf("%d %d %d", &n1, &n2, &weight);
        adjacency_matrix[n1][n2] =weight;
        adjacency_matrix[n2][n1] =weight;
    }
}
int main() {
    int n, m;
    int k=0;
    scanf("%d", &n);
    scanf("%d", &m);
    initializeGraph(n);
    input_edges(n, m);
    dijkstra(n, k);
 
    
 
    
    return 0;
}
