#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100

/* adjacency‐list node */
typedef struct Adj {
    int          v;
    struct Adj  *next;
} Adj_t;

/* graph: adjacency lists + node count */
static Adj_t *adj[MAXN];
static int    N;

/* global arrays and counters for DFS */
static int  disc[MAXN];    // discovery time
static int  low[MAXN];     // low-link values
static int  parent[MAXN];  // DFS tree parent
static bool art[MAXN];     // is articulation point
static int  dfs_time;

/* add undirected edge u–v */
void addEdge(int u, int v) {
    Adj_t *p = malloc(sizeof *p);
    p->v    = v;
    p->next = adj[u];
    adj[u]  = p;
    p = malloc(sizeof *p);
    p->v    = u;
    p->next = adj[v];
    adj[v]  = p;
}

/* DFS utility to find articulation points */
void APUtil(int u) {
    int children = 0;
    disc[u] = low[u] = ++dfs_time;

    for (Adj_t *p = adj[u]; p; p = p->next) {
        int v = p->v;
        if (disc[v] == 0) {
            /* tree edge */
            children++;
            parent[v] = u;
            APUtil(v);
            low[u] = (low[v] < low[u]) ? low[v] : low[u];

            /* articulation conditions */
            if (parent[u] == -1 && children > 1)
                art[u] = true;
            if (parent[u] != -1 && low[v] >= disc[u])
                art[u] = true;
        }
        else if (v != parent[u]) {
            /* back edge */
            low[u] = (disc[v] < low[u]) ? disc[v] : low[u];
        }
    }
}

/* main procedure to find all articulation points */
void findArticulationPoints() {
    /* initialize */
    for (int i = 0; i < N; i++) {
        disc[i]   = 0;
        low[i]    = 0;
        parent[i] = -1;
        art[i]    = false;
    }
    dfs_time = 0;

    /* run DFS from each unvisited node (handles disconnected graphs) */
    for (int i = 0; i < N; i++) {
        if (disc[i] == 0)
            APUtil(i);
    }

    /* print results */
    printf("Articulation points:\n");
    for (int i = 0; i < N; i++) {
        if (art[i])
            printf("%d\n", i);
    }
}

int main(void) {
    /* example graph from Fig.10.5.2.2.a */
    N = 13;
    for (int i = 0; i < N; i++)
        adj[i] = NULL;

    /* edges (0=A,1=B,…,12=M) */
    addEdge(0,5);   // A–F
    addEdge(0,2);   // A–C
    addEdge(0,1);   // A–B
    addEdge(0,6);   // A–G
    addEdge(5,4);   // F–E
    addEdge(5,3);   // F–D
    addEdge(2,0);   // C–A (duplicate)
    addEdge(6,4);   // G–E
    addEdge(7,8);   // H–I
    addEdge(7,9);   // H–J
    addEdge(7,10);  // H–K
    addEdge(11,12); // L–M

    findArticulationPoints();
    return 0;
}
