#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100

/* culori pentru BFS CLR */
typedef enum { WHITE, GRAY, BLACK } Color_t;

/* lista de adiacență */
typedef struct Adj {
    int          v;
    struct Adj  *next;
} Adj_t;

/* graful: vector de liste de adiacență și număr de noduri */
typedef struct {
    int    n;
    Adj_t *adj[MAXN];
} Graf_t;

/* coadă FIFO */
typedef struct {
    int data[MAXN];
    int front, rear;
} Queue_t;

void initQueue(Queue_t *q) {
    q->front = q->rear = -1;
}

bool isEmpty(Queue_t *q) {
    return q->front == -1;
}

void enqueue(Queue_t *q, int x) {
    if (q->rear == MAXN-1) return;
    if (isEmpty(q)) q->front = 0;
    q->data[++q->rear] = x;
}

int dequeue(Queue_t *q) {
    if (isEmpty(q)) return -1;
    int v = q->data[q->front++];
    if (q->front > q->rear) q->front = q->rear = -1;
    return v;
}

/* adaugă muchie neorientată */
void addEdge(Graf_t *g, int u, int v) {
    Adj_t *p = malloc(sizeof *p);
    p->v = v; p->next = g->adj[u]; g->adj[u] = p;
    p = malloc(sizeof *p);
    p->v = u; p->next = g->adj[v]; g->adj[v] = p;
}

/* BFS CLR (Cormen-Leiserson-Rivest) */
void BFS_CLR(Graf_t *g, int s) {
    static Color_t color[MAXN];
    static int d[MAXN], pred[MAXN];
    Queue_t Q;

    // 1) inițializare
    for (int u = 0; u < g->n; u++) {
        color[u] = WHITE;
        d[u]     = INT_MAX;
        pred[u]  = -1;
    }
    // 2) inițializăm sursa
    color[s] = GRAY;
    d[s]     = 0;
    pred[s]  = -1;

    initQueue(&Q);
    enqueue(&Q, s);

    // 3) parcurgere
    while (!isEmpty(&Q)) {
        int u = dequeue(&Q);
        printf("Procesăm nodul %d, dist=%d\n", u, d[u]);
        for (Adj_t *p = g->adj[u]; p; p = p->next) {
            int v = p->v;
            if (color[v] == WHITE) {
                color[v] = GRAY;
                d[v]     = d[u] + 1;
                pred[v]  = u;
                enqueue(&Q, v);
            }
        }
        color[u] = BLACK;
    }

    // 4) afișare rezultate
    printf("\nNod | dist | pred\n");
    printf("----+------+-----\n");
    for (int u = 0; u < g->n; u++) {
        printf("%4d|%6d|%6d\n", u,
               d[u]==INT_MAX ? -1 : d[u],
               pred[u]);
    }
}

/* exemplu de utilizare */
int main(void) {
    Graf_t g;
    g.n = 6;
    for (int i = 0; i < g.n; i++) g.adj[i] = NULL;

    // definim muchii
    addEdge(&g, 0,1);
    addEdge(&g, 0,2);
    addEdge(&g, 1,3);
    addEdge(&g, 1,4);
    addEdge(&g, 2,4);
    addEdge(&g, 3,5);
    addEdge(&g, 4,5);

    printf("BFS CLR incepand de la 0:\n");
    BFS_CLR(&g, 0);
    return 0;
}
