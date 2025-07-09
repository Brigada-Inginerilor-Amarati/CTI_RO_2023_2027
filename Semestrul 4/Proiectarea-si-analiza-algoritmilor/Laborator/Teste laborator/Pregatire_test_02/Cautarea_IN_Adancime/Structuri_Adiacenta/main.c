#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100   // capacitatea maximă pentru noduri

typedef int Key_t;

/* lista de adiacență: stochează cheia vecinului */
typedef struct Adj {
    Key_t        key_adj;
    struct Adj  *next;
} Adj_t;

/* nod al listei principale */
typedef struct Node {
    Key_t         key;
    Adj_t        *adjacency_list;
    struct Node  *next;
} Node_t, *Graph_t;

/* „marc” și contorul de ordine vizitare */
static int marc[MAXN];
static int id_counter;

/* utilitar: găsește nodul cu cheia k */
static Node_t *IndicaNod(Graph_t g, Key_t k) {
    for (Node_t *p = g; p; p = p->next)
        if (p->key == k)
            return p;
    return NULL;
}

/* --- Căutare în adâncime (pseudocod 10.4.1.2.a) --- */
static void CautaInAdancime(Graph_t g, int x) {
    Node_t *t = IndicaNod(g, x);
    if (!t) return;
    id_counter++;
    marc[x] = id_counter;
    printf("Vizitez %d (id=%d)\n", x, id_counter);
    for (Adj_t *a = t->adjacency_list; a; a = a->next) {
        int y = a->key_adj;
        if (marc[y] == 0)
            CautaInAdancime(g, y);
    }
}

/* Traversare1 */
void Traversare1(Graph_t g, int N) {
    id_counter = 0;
    for (int i = 0; i < N; i++)
        marc[i] = 0;
    for (int i = 0; i < N; i++) {
        if (marc[i] == 0) {
            CautaInAdancime(g, i);
            printf("\n");  // writeln după fiecare componentă
        }
    }
}

/* --- Construire graf simplu --- */
void InserNod(Graph_t *g, Key_t k) {
    if (IndicaNod(*g, k)) return;
    Node_t *n = malloc(sizeof *n);
    n->key = k;
    n->adjacency_list = NULL;
    n->next = *g;
    *g = n;
}

void InserArc(Graph_t g, Key_t u, Key_t v) {
    Node_t *nu = IndicaNod(g, u);
    Node_t *nv = IndicaNod(g, v);
    if (!nu || !nv) return;
    Adj_t *a = malloc(sizeof *a);
    a->key_adj = v;
    a->next = nu->adjacency_list;
    nu->adjacency_list = a;
    // neorientat
    a = malloc(sizeof *a);
    a->key_adj = u;
    a->next = nv->adjacency_list;
    nv->adjacency_list = a;
}

/* --- Exemplu de utilizare --- */
int main(void) {
    Graph_t g = NULL;
    int N = 6;  // nodurile 0..5

    // inserăm nodurile
    for (int i = 0; i < N; i++)
        InserNod(&g, i);

    // definim niște arce
    InserArc(g, 0, 1);
    InserArc(g, 0, 2);
    InserArc(g, 1, 3);
    InserArc(g, 1, 4);
    InserArc(g, 2, 4);
    InserArc(g, 3, 5);
    InserArc(g, 4, 5);

    printf("Traversare DFS cu marc și id:\n");
    Traversare1(g, N);

    return 0;
}
