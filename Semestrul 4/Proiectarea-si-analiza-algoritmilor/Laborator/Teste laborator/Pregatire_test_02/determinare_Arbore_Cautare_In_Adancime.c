#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* --- tipuri de bază --- */
typedef int Key_t;
typedef int Info_t;

/* --- forward declarations --- */
typedef struct Node   Node_t;
typedef struct Adj    Adj_t;

/* --- celulă în lista de adiacență (multilistă Decker) --- */
struct Adj {
    Node_t *nod;       // pointer la nodul destinație
    Adj_t  *urm;       // următorul arc
    bool    marcArb;   // true dacă arc e de arbore
};

/* --- celulă în lista de noduri --- */
struct Node {
    Key_t   key;        // cheia nodului
    Info_t  info;       // informație
    Node_t *urm;        // următorul nod în lista principală
    Adj_t  *incep;      // capul listei de adiacență
    bool    visited;    // marcaj vizitat
};

/* --- Graful: capul listei de noduri --- */
typedef Node_t *Graf_t;

/* --- Construiește un nou nod și-l adaugă la graf --- */
Node_t *addNode(Graf_t *g, Key_t key) {
    Node_t *p = malloc(sizeof *p);
    p->key     = key;
    p->info    = 0;
    p->visited = false;
    p->incep   = NULL;
    p->urm     = *g;
    *g         = p;
    return p;
}

/* --- Adaugă un arc neorientat între p și q în multilistă --- */
void addArc(Node_t *p, Node_t *q) {
    // inserție p→q
    Adj_t *a = malloc(sizeof *a);
    a->nod     = q;
    a->marcArb = false;
    a->urm     = p->incep;
    p->incep   = a;
    // inserție q→p (cea de-a doua copie)
    a = malloc(sizeof *a);
    a->nod     = p;
    a->marcArb = false;
    a->urm     = q->incep;
    q->incep   = a;
}

/* --- Căutare în adâncime recursivă pentru arbore de acoperire --- */
void ConstructieACA(Node_t *p) {
    p->visited = true;
    for (Adj_t *arc = p->incep; arc; arc = arc->urm) {
        Node_t *q = arc->nod;
        if (!q->visited) {
            // marchează arcul ca de arbore
            arc->marcArb = true;
            // marcăm reciproc (gasim copia în q->incep)
            for (Adj_t *arc2 = q->incep; arc2; arc2 = arc2->urm) {
                if (arc2->nod == p) {
                    arc2->marcArb = true;
                    break;
                }
            }
            ConstructieACA(q);
        }
    }
}

/* --- Procedura principală --- */
void ArboreDeAcoperireCA(Graf_t g) {
    // 1) inițializare: toate nodurile nevizitate, toate arcele marcArb=false
    for (Node_t *p = g; p; p = p->urm) {
        p->visited = false;
        for (Adj_t *a = p->incep; a; a = a->urm) {
            a->marcArb = false;
        }
    }
    // 2) pentru fiecare componentă, dacă nod nevizitat, lansez DFS
    for (Node_t *p = g; p; p = p->urm) {
        if (!p->visited) {
            ConstructieACA(p);
        }
    }
}

/* --- Afișează arborele de acoperire --- */
void printArboreCA(Graf_t g) {
    printf("Acele arce marcate ca de arbore (x->y):\n");
    for (Node_t *p = g; p; p = p->urm) {
        for (Adj_t *a = p->incep; a; a = a->urm) {
            if (a->marcArb) {
                printf("%d -> %d\n", p->key, a->nod->key);
            }
        }
    }
}

/* --- Exemplu de utilizare --- */
int main(void) {
    Graf_t g = NULL;
    // creăm nodurile 1..5, de ex.
    Node_t *n1 = addNode(&g, 1);
    Node_t *n2 = addNode(&g, 2);
    Node_t *n3 = addNode(&g, 3);
    Node_t *n4 = addNode(&g, 4);
    Node_t *n5 = addNode(&g, 5);
    // adăugăm arce
    addArc(n1,n2);
    addArc(n1,n3);
    addArc(n2,n4);
    addArc(n2,n5);
    addArc(n3,n5);

    ArboreDeAcoperireCA(g);
    printArboreCA(g);

    return 0;
}
