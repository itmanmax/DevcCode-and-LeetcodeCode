#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 1000

typedef struct Edge {
    int u, v, weight;
} Edge;

int parent[MAX_EDGES];

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void union1(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

int cmp(const void *a, const void *b) {
    Edge *edge1 = (Edge *)a;
    Edge *edge2 = (Edge *)b;
    return edge1->weight - edge2->weight;
}

int main() {
    int n, m, i, j, cost, minCost = 0;
    Edge edges[MAX_EDGES];

    // Input
    scanf("%d %d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    // Initialize parents
    for (i = 1; i <= n; i++) {
        parent[i] = i;
    }

    // Sort edges based on their weight
    qsort(edges, m, sizeof(Edge), cmp);

    // Kruskal's algorithm
    for (i = 0; i < m; i++) {
        int pu = find(edges[i].u);
        int pv = find(edges[i].v);

        if (pu != pv) {
            union1(pu, pv);
            minCost += edges[i].weight;
        }
    }

    // Check if all nodes are connected
    int connected = 1;
    for (i = 1; i < n; i++) {
        if (find(i) != find(i + 1)) {
            connected = 0;
            break;
        }
    }

    if (connected)
        printf("%d\n", minCost);
    else
        printf("no spanning tree\n");

    return 0;
}
