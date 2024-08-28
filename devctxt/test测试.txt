#include <stdio.h>

#define MAX_NODES 100
#define INF 999999

int minKey(int key[], bool mstSet[], int n) {
    int min = INF, min_index;
    for (int v = 0; v < n; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

int minCostSpanningTree(int graph[MAX_NODES][MAX_NODES], int n) {
    int parent[MAX_NODES];
    int key[MAX_NODES];
    bool mstSet[MAX_NODES];

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    int minCost = 0;
    for (int i = 1; i < n; i++) {
        minCost += graph[i][parent[i]];
    }

    return minCost;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int graph[MAX_NODES][MAX_NODES];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, cost;
        scanf("%d %d %d", &u, &v, &cost);
        graph[u - 1][v - 1] = cost;
        graph[v - 1][u - 1] = cost;
    }

    int minCost = minCostSpanningTree(graph, n);
    if (minCost == 0) {
        printf("no spanning tree\n");
    } else {
        printf("%d\n", minCost);
    }

    return 0;
}

