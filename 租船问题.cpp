#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
#define MAX_VERTICES 100
int count(int n)
{   n=n-1;
    int count =0;
	while(n!=0)
	{ count=count+n;
	  n--;
	}
	
	
}
// ����ͼ���ڽӾ���
int adjacency_matrix[MAX_VERTICES][MAX_VERTICES];
 
// ��ʼ��ͼ
void initializeGraph(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adjacency_matrix[i][j] = INT_MAX;
        }
    }
}
 
// Dijkstra �㷨ʵ��
void dijkstra(int n, int start) {
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int nextVertex[MAX_VERTICES];
 
    // ��ʼ����������ͷ�������
    for (int i = 0; i <n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        nextVertex[i] = -1;
    }
 
    // ������ʼ����ľ���Ϊ 0
    dist[start] = 0;
 
    // �������ж���
    for (int i = 0; i < n; i++) {
        // �ҵ�δ���ʶ����о�����С�Ķ���
        int minDist = INT_MAX;
        int u;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }
 
        // ��� u Ϊ�ѷ���
        visited[u] = 1;
 
        // ���� u �������ھӵľ���
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
void input_edges(int n) {
    for (int i = 1; i <n; i++) {
       for(int j=n-i;j>0;j--)
       { 
	    int n1,n2,weight;
        scanf("%d", &weight);
        adjacency_matrix[n1][n2] =weight;
	   }
	   
    }
}
int main() {
    int n, m;
    int k=0;
    scanf("%d", &n);
    initializeGraph(n);
    input_edges(n);
    dijkstra(n, k);
 
    
 
    
    return 0;
}
