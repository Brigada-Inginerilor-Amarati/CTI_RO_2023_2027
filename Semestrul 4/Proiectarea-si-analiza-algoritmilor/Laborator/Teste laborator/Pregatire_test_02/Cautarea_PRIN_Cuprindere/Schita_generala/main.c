#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 16

typedef struct Graf {
    int n;
    unsigned short matrice[MAXN][MAXN];
} Graf_t;

typedef struct Queue {
    int data[MAXN];
    int front, rear;
} Queue_t;

void initQueue(Queue_t *q) {
    q->front = q->rear = -1;
}

bool isEmpty(Queue_t *q) {
    return q->front == -1;
}

void enqueue(Queue_t *q, int value) {
    if (q->rear == MAXN - 1) return;
    if (isEmpty(q)) q->front = 0;
    q->data[++q->rear] = value;
}

int dequeue(Queue_t *q) {
    if (isEmpty(q)) return -1;
    int v = q->data[q->front++];
    if (q->front > q->rear) q->front = q->rear = -1;
    return v;
}

void bfs(const Graf_t *g, int src, int dest) {
    bool visited[MAXN] = { false };
    int parent[MAXN];   //
    Queue_t q;
    initQueue(&q);

    enqueue(&q, src);
    visited[src] = true;
    parent[src] = -1;

    while (!isEmpty(&q)) {
        int u = dequeue(&q);
        if (u == dest) break;
        for (int v = 0; v < g->n; v++) {
            if (g->matrice[u][v] && !visited[v]) {
                visited[v] = true;
                parent[v] = u;
                enqueue(&q, v);
            }
        }
    }

    if (!visited[dest]) {
        printf("Nu exista drum intre %d si %d\n", src, dest);
        return;
    }

    int path[MAXN], len = 0;
    for (int v = dest; v != -1; v = parent[v])
        path[len++] = v;

    printf("Drumul este: ");
    for (int i = len - 1; i >= 0; i--)
        printf("%d ", path[i]);
    putchar('\n');
}

int main(void) {
    Graf_t g;
    int src, dest;

    // Citire de la tastatură
    printf("Numar noduri (<=%d): ", MAXN);
    if (scanf("%d", &g.n) != 1 || g.n < 1 || g.n > MAXN) {
        fprintf(stderr, "Input invalid pentru n\n");
        return 1;
    }

    printf("Matrice de adiacenta (%d x %d):\n", g.n, g.n);
    for (int i = 0; i < g.n; i++)
        for (int j = 0; j < g.n; j++)
            scanf("%hu", &g.matrice[i][j]);

    printf("Sursa si destinatie: ");
    if (scanf("%d %d", &src, &dest) != 2 ||
        src < 0 || src >= g.n ||
        dest < 0 || dest >= g.n) {
        fprintf(stderr, "Input invalid pentru src/dest\n");
        return 1;
    }

    bfs(&g, src, dest);
    return 0;
}

