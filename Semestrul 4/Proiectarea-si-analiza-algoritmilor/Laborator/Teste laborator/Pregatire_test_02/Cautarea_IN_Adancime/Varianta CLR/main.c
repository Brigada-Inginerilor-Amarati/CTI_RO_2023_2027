#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100   // capacitatea maximă a grafului

typedef int Key_t;
typedef int Info_t;

// culorile pentru DFS CLR
typedef enum { WHITE, GRAY, BLACK } Color_t;

// lista de adiacență: stochează cheia vecinului
typedef struct Adj {
    Key_t        key_adj;
    struct Adj  *next;
} Adj_t;

// nodul din lista principală
typedef struct Node {
    Key_t        key;
    Info_t       info;
    struct Node *next_node;
    Adj_t       *adjacency_list;
} Node_t, *Graph_t;

// variabile globale pentru DFS CLR
static Color_t color[MAXN];
static Key_t   parent[MAXN];
static int     dtime[MAXN];
static int     ftime[MAXN];
static int     dfs_time;

// utilitar: găsește nodul cu cheia k
static Node_t *IndicaNod(Graph_t g, Key_t k) {
    for (Node_t *p = g; p; p = p->next_node)
        if (p->key == k)
            return p;
    return NULL;
}

// adaugă un arc neorientat k1–k2
static void InserArc(Graph_t g, Key_t k1, Key_t k2) {
    Node_t *n1 = IndicaNod(g, k1);
    Node_t *n2 = IndicaNod(g, k2);
    if (!n1 || !n2) return;
    // k2 în lista lui n1
    Adj_t *a1 = malloc(sizeof *a1);
    a1->key_adj = k2;
    a1->next    = n1->adjacency_list;
    n1->adjacency_list = a1;
    // k1 în lista lui n2
    Adj_t *a2 = malloc(sizeof *a2);
    a2->key_adj = k1;
    a2->next    = n2->adjacency_list;
    n2->adjacency_list = a2;
}

// DFS CLR recursiv
static void DFS_Visit(Graph_t g, Node_t *u) {
    int k = u->key;
    color[k] = GRAY;
    dfs_time++;
    dtime[k] = dfs_time;

    for (Adj_t *a = u->adjacency_list; a; a = a->next) {
        int v = a->key_adj;
        if (color[v] == WHITE) {
            parent[v] = k;
            Node_t *vn = IndicaNod(g, v);
            DFS_Visit(g, vn);
        }
    }

    color[k] = BLACK;
    dfs_time++;
    ftime[k] = dfs_time;
}

// Traversare în adâncime, varianta CLR
void DFS(Graph_t g, int n_nodes) {
    // inițializare
    for (int i = 0; i < n_nodes; i++) {
        color[i]  = WHITE;
        parent[i] = -1;
    }
    dfs_time = 0;

    // pentru fiecare nod
    for (int i = 0; i < n_nodes; i++) {
        if (color[i] == WHITE) {
            Node_t *ui = IndicaNod(g, i);
            if (ui) DFS_Visit(g, ui);
        }
    }
}

// construiește un graf cu nodurile 0..n-1
Graph_t build_graph(int n) {
    Graph_t g = NULL;
    // inserare noduri la cap (ordinea internă va fi inversă)
    for (int i = 0; i < n; i++) {
        Node_t *new = malloc(sizeof *new);
        new->key = i;
        new->info = 0;
        new->adjacency_list = NULL;
        new->next_node = g;
        g = new;
    }
    return g;
}

// afișează rezultatele DFS CLR
void print_dfs_results(int n) {
    printf("nod | d[u]  f[u]  p[u]\n");
    printf("----+----------------\n");
    for (int i = 0; i < n; i++) {
        printf("%3d | %3d   %3d   %3d\n", i, dtime[i], ftime[i], parent[i]);
    }
}

int main(void) {
    int n = 6;  // exemplu: 6 noduri 0..5
    Graph_t g = build_graph(n);

    // adăugăm câteva arce
    InserArc(g, 0, 1);
    InserArc(g, 0, 2);
    InserArc(g, 1, 3);
    InserArc(g, 1, 4);
    InserArc(g, 2, 4);
    InserArc(g, 3, 5);
    InserArc(g, 4, 5);

    // rulăm DFS CLR
    DFS(g, n);

    // afișăm timestamp-urile și părinții
    print_dfs_results(n);

    return 0;
}
