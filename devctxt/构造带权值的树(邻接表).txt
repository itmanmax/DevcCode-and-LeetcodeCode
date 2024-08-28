#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// 定义顶点结构体
typedef struct Vertex {
    int id; // 顶点编号
    struct Edge *edges; // 指向第一条边的指针
} Vertex;

// 定义边结构体
typedef struct Edge {
    int weight; // 权值
    struct Vertex *to; // 指向相邻顶点的指针
    struct Edge *next; // 指向下一条边的指针
} Edge;

// 函数声明
Vertex vertices[MAX_VERTICES];
int vertex_count;
void input_edges(int n, int m);
void add_edge(int u, int v, int weight);

int main() {
    int n, m;
    vertex_count = 0;
    
    // 输入顶点数量
    printf("请输入顶点的数量n（n<100）：");
    scanf("%d", &n);
    
    // 输入边数量
    printf("请输入边的数量m：");
    scanf("%d", &m);
    
    // 初始化顶点
    for (int i = 0; i < n; i++) {
        vertices[i].id = i;
        vertices[i].edges = NULL;
    }
    
    // 输入边信息
    input_edges(n, m);
    
    // 输出邻接链表，展示结果
    printf("构造的带权值的图的邻接链表为：\n");
    for (int i = 0; i < n; i++) {
        Edge *current = vertices[i].edges;
        while (current != NULL) {
            printf("顶点%d到顶点%d的权值为%d\n", i, current->to->id, current->weight);
            current = current->next;
        }
    }
    
    return 0;
}

// 输入边的函数
void input_edges(int n, int m) {
    int u, v, weight;
    for (int i = 0; i < m; i++) {
        printf("请输入第%d条边的两个顶点u和v以及权值weight：", i + 1);
        scanf("%d %d %d", &u, &v, &weight);
        
        // 添加边
        add_edge(u, v, weight);
        add_edge(v, u, weight); // 无向图的对称边
    }
}

// 添加边的函数
void add_edge(int u, int v, int weight) {
    Edge *new_edge = (Edge *)malloc(sizeof(Edge));
    if (new_edge == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    new_edge->weight = weight;
    new_edge->to = &vertices[v];
    new_edge->next = vertices[u].edges;
    vertices[u].edges = new_edge;
}

