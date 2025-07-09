#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100   // capacitatea maximă a grafului

typedef int Key_t;
typedef int Info_t;

/* --- lista de adiacență: stochează cheia vecinului --- */
typedef struct Adj {
    Key_t        key_adj;
    struct Adj  *next;
} Adj_t;

/* --- nod din lista principală --- */
typedef struct Node {
    Key_t        key;
    Info_t       info;
    struct Node *next_node;
    Adj_t       *adjacency_list;
} Node_t;

typedef Node_t *Graph_t;

/* tabloul de marcaj */
static bool marc[MAXN];

/* utilitar: găsește nodul cu cheia k */
static Node_t *IndicaNod(Graph_t g, Key_t k) {
    for (Node_t *p = g; p; p = p->next_node)
        if (p->key == k)
            return p;
    return NULL;
}

/* ----------------------------------------------------
   DFS recursiv pe nodul x din graful g
   ---------------------------------------------------- */
static void CautaInAdancime_node(Graph_t g, Node_t *x) {
    marc[x->key] = true;
    printf("Vizitez nodul %d\n", x->key);
    for (Adj_t *a = x->adjacency_list; a; a = a->next) {
        if (!marc[a->key_adj]) {
            Node_t *y = IndicaNod(g, a->key_adj);
            if (y) CautaInAdancime_node(g, y);
        }
    }
}

/* ----------------------------------------------------
   Wrapper: pornește DFS de la cheia 'start'
   ---------------------------------------------------- */
void CautaInAdancime(Graph_t g, Key_t start) {
    // 1) resetare marcaje
    for (int i = 0; i < MAXN; i++) marc[i] = false;
    // 2) găsește nodul de start și pornește DFS
    Node_t *start_node = IndicaNod(g, start);
    if (start_node)
        CautaInAdancime_node(g, start_node);
}

/* ----------------------------------------------------
   Funcții de construire a grafului
   ---------------------------------------------------- */
void InitGraf(Graph_t *g) {
    *g = NULL;
}

void InserNod(Graph_t *g, Key_t k) {
    if (IndicaNod(*g, k)) return;  // deja există
    Node_t *new_node = malloc(sizeof *new_node);
    new_node->key = k;
    new_node->info = 0;
    new_node->adjacency_list = NULL;
    new_node->next_node = *g;
    *g = new_node;
}

void InserArc(Graph_t g, Key_t k1, Key_t k2) {
    Node_t *n1 = IndicaNod(g, k1);
    Node_t *n2 = IndicaNod(g, k2);
    if (!n1 || !n2) return;
    // adaugă k2 în lista lui n1
    Adj_t *a1 = malloc(sizeof *a1);
    a1->key_adj = k2;
    a1->next = n1->adjacency_list;
    n1->adjacency_list = a1;
    // adaugă k1 în lista lui n2 (graf neorientat)
    Adj_t *a2 = malloc(sizeof *a2);
    a2->key_adj = k1;
    a2->next = n2->adjacency_list;
    n2->adjacency_list = a2;
}

/* ----------------------------------------------------
   Exemplu de utilizare
   ---------------------------------------------------- */
int main(void) {
    Graph_t g;
    InitGraf(&g);

    // creăm 4 noduri cu cheile 0,1,2,3
    for (int i = 0; i < 4; i++)
        InserNod(&g, i);

    // adăugăm câteva arce
    InserArc(g, 0, 1);
    InserArc(g, 0, 2);
    InserArc(g, 1, 2);



    // rulăm DFS pornind de la 0
    printf("DFS pornind din nodul 0:\n");
    CautaInAdancime(g, 0);

    return 0;
}
