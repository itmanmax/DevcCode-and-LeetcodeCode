#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// ����ߵĽṹ��
typedef struct {
    int u; // ����u
    int v; // ����v
    int weight; // Ȩֵ
} Edge;

// �ڽӾ���
int adjacency_matrix[MAX_VERTICES][MAX_VERTICES];

// ��������
void input_edges(int n, int m);

int main() {
    int n, m;
    
    // ���붥������
    printf("�����붥�������n��n<100����");
    scanf("%d", &n);
    
    // ���������
    printf("������ߵ�����m��");
    scanf("%d", &m);
    
    // �������Ϣ
    input_edges(n, m);
    
    // ����ڽӾ���չʾ���
    printf("����Ĵ�Ȩֵ��ͼ���ڽӾ���Ϊ��\n");
    for (int i = 1; i <=n; i++) {
        for (int j = 1; j <=n; j++) {
            printf("%d\t", adjacency_matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

// ����ߵĺ���
void input_edges(int n, int m) {
    Edge edge;
    for (int i = 1; i <= m; i++) {
        printf("�������%d���ߵ���������u��v�Լ�Ȩֵweight��", i );
        scanf("%d %d %d", &edge.u, &edge.v, &edge.weight);
        
        // �������ͼ������ģ�����ÿ�������ڽӾ����г�������
        adjacency_matrix[edge.u][edge.v] = edge.weight;
        adjacency_matrix[edge.v][edge.u] = edge.weight;
    }
}
4 3 1
2 3 6
2 1 3
1 2 6

