#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100

/* forward decls */
typedef struct Node Node_t;
typedef struct Adj  Adj_t;

/* celulă în lista de noduri */
struct Node {
    int    key;
    Node_t *next;
    Adj_t  *incep;    // cap al listei de adiacență
    bool    visited;  // marcaj nod vizitat
};

/* celulă în lista de adiacență (multilistă Decker) */
struct Adj {
    Node_t *nod;       // pointer la nodul destinație
    Adj_t  *urm;       // următorul arc
    bool    marcArb;   // true dacă e arc de arbore
};

/* Graful e capul listei de noduri */
typedef Node_t *Graf_t;

/* coadă simplă de noduri */
typedef struct {
    Node_t *data[MAXN];
    int     front, rear;
} Queue_t;

static Queue_t Q;

/* operații coadă */
void initQueue() {
    Q.front = Q.rear = -1;
}

bool isEmpty() {
    return Q.front == -1;
}

void enqueue(Node_t *p) {
    if (Q.rear == MAXN-1) return;
    if (isEmpty()) Q.front = 0;
    Q.data[++Q.rear] = p;
}

Node_t *dequeue() {
    if (isEmpty()) return NULL;
    Node_t *p = Q.data[Q.front++];
    if (Q.front > Q.rear) Q.front = Q.rear = -1;
    return p;
}

/* construiește un nod nou și îl adaugă la capul listei de noduri */
Node_t *addNode(Graf_t *g, int key) {
    Node_t *p = malloc(sizeof *p);
    p->key     = key;
    p->next    = *g;
    p->incep   = NULL;
    p->visited = false;
    *g         = p;
    return p;
}

/* adaugă un arc neorientat între p și q */
void addArc(Node_t *p, Node_t *q) {
    Adj_t *a = malloc(sizeof *a);
    a->nod     = q; 
    a->marcArb = false;
    a->urm     = p->incep;
    p->incep   = a;

    a = malloc(sizeof *a);
    a->nod     = p;
    a->marcArb = false;
    a->urm     = q->incep;
    q->incep   = a;
}

/* BFS-based spanning tree */
void ArboreDeAcoperireCC(Graf_t g) {
    Node_t *n, *m;
    Adj_t  *arc;

    /* 1) inițializează marcajele */
    for (n = g; n; n = n->next) {
        n->visited = false;
        for (arc = n->incep; arc; arc = arc->urm)
            arc->marcArb = false;
    }

    initQueue();

    /* 2) pentru fiecare componentă */
    for (n = g; n; n = n->next) {
        if (!n->visited) {
            /* pornește din n */
            enqueue(n);
            n->visited = true;
            /* BFS */
            while (!isEmpty()) {
                n = dequeue();
                for (arc = n->incep; arc; arc = arc->urm) {
                    m = arc->nod;
                    if (!m->visited) {
                        enqueue(m);
                        m->visited = true;
                        /* marchează acest arc ca arbore */
                        arc->marcArb = true;
                        /* marcăm și copia inversă */
                        for (Adj_t *a2 = m->incep; a2; a2 = a2->urm) {
                            if (a2->nod == n) {
                                a2->marcArb = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

/* afișează arcele arborelui */
void printTree(Graf_t g) {
    printf("Arcele de arbore (u->v):\n");
    for (Node_t *u = g; u; u = u->next) {
        for (Adj_t *a = u->incep; a; a = a->urm) {
            if (a->marcArb) {
                printf("%d -> %d\n", u->key, a->nod->key);
            }
        }
    }
}

/* exemplu de utilizare */
int main(void) {
    Graf_t g = NULL;
    // nodurile 1..6
    Node_t *n1 = addNode(&g, 1);
    Node_t *n2 = addNode(&g, 2);
    Node_t *n3 = addNode(&g, 3);
    Node_t *n4 = addNode(&g, 4);
    Node_t *n5 = addNode(&g, 5);
    Node_t *n6 = addNode(&g, 6);

    // adăugăm arce
    addArc(n1,n2);
    addArc(n1,n3);
    addArc(n2,n4);
    addArc(n2,n5);
    addArc(n3,n5);
    addArc(n4,n6);
    addArc(n5,n6);

    ArboreDeAcoperireCC(g);
    printTree(g);

    return 0;
}
//     addArc(n1,n4);