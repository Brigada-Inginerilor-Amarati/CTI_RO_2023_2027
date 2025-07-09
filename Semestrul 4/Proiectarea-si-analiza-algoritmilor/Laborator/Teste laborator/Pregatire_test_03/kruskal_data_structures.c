
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 50
#define MAX_EDGES 100

typedef struct {
    int u, v;
    int cost;
} Edge;

typedef struct {
    int parent[MAX_NODES];
} DisjointSet;

Edge edges[MAX_EDGES];
int edgeCount = 0;
int nodeCount;

int result[MAX_EDGES]; // indexes of edges in MST
int resultCount = 0;

void addEdge(int u, int v, int cost) {
    edges[edgeCount].u = u;
    edges[edgeCount].v = v;
    edges[edgeCount].cost = cost;
    edgeCount++;
}

int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->cost - ((Edge*)b)->cost;
}

// Disjoint Set Operations
void ds_init(DisjointSet* ds, int n) {
    for (int i = 0; i < n; i++) {
        ds->parent[i] = i;
    }
}

int ds_find(DisjointSet* ds, int x) {
    if (ds->parent[x] != x)
        ds->parent[x] = ds_find(ds, ds->parent[x]);
    return ds->parent[x];
}

void ds_union(DisjointSet* ds, int x, int y) {
    int rootX = ds_find(ds, x);
    int rootY = ds_find(ds, y);
    if (rootX != rootY)
        ds->parent[rootY] = rootX;
}

void kruskal() {
    qsort(edges, edgeCount, sizeof(Edge), compareEdges);

    DisjointSet ds;
    ds_init(&ds, nodeCount);

    int totalCost = 0;
    resultCount = 0;

    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (ds_find(&ds, u) != ds_find(&ds, v)) {
            ds_union(&ds, u, v);
            result[resultCount++] = i;
            totalCost += edges[i].cost;
        }
    }

    printf("Edges in the Minimum Spanning Tree (Kruskal):\n");
    for (int i = 0; i < resultCount; i++) {
        Edge e = edges[result[i]];
        printf("%d - %d, cost: %d\n", e.u + 1, e.v + 1, e.cost);
    }
    printf("Total cost: %d\n", totalCost);
}

int main() {
    nodeCount = 6;

    addEdge(0, 1, 6);
    addEdge(0, 2, 1);
    addEdge(0, 3, 5);
    addEdge(1, 2, 5);
    addEdge(1, 4, 3);
    addEdge(2, 3, 5);
    addEdge(2, 4, 6);
    addEdge(2, 5, 4);
    addEdge(3, 5, 2);
    addEdge(4, 5, 6);

    kruskal();

    return 0;
}
