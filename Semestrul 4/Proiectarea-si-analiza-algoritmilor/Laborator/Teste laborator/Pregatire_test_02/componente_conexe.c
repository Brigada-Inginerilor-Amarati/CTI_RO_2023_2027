#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100

/* --- nod în lista de adiacență simplă --- */
typedef struct Adj {
    int          v;
    struct Adj  *next;
} Adj_t;

/* --- graful: vector de liste de adiacență și număr de noduri --- */
static Adj_t *StrAdj[MAXN];
static int    N;

/* --- tabloul de marcaj și contorul global --- */
static int marc[MAXN];
static int id;

/* --- adaugă muchie neorientată în graf --- */
void addEdge(int u, int v) {
    Adj_t *p = malloc(sizeof *p);
    p->v    = v;
    p->next = StrAdj[u];
    StrAdj[u] = p;
    p = malloc(sizeof *p);
    p->v    = u;
    p->next = StrAdj[v];
    StrAdj[v] = p;
}

/* --- recursiv: parcurge și tipărește componenta lui x --- */
void Componenta(int x) {
    marc[x] = id;
    printf("%d ", x);
    for (Adj_t *t = StrAdj[x]; t; t = t->next) {
        if (marc[t->v] == 0) {
            Componenta(t->v);
        }
    }
}

/* --- determină și tipărește toate componentele conexe --- */
void ComponenteConexe() {
    id = 0;
    // init marcaj
    for (int i = 0; i < N; i++)
        marc[i] = 0;
    // pentru fiecare nod nevizitat
    for (int x = 0; x < N; x++) {
        if (marc[x] == 0) {
            id++;
            Componenta(x);
            printf("\n");
        }
    }
}

/* --- exemplu de utilizare --- */
int main(void) {
    // definim un graf cu 8 noduri 0..7
    N = 8;
    for (int i = 0; i < N; i++)
        StrAdj[i] = NULL;

    // componenta 1: 0-1-2
    addEdge(0, 1);
    addEdge(1, 2);

    // componenta 2: 3-4
    addEdge(3, 4);

    // componenta 3: 5-6-7-5 (ciclu)
    addEdge(5, 6);
    addEdge(6, 7);
    addEdge(7, 5);

    printf("Componente conexe:\n");
    ComponenteConexe();

    return 0;
}
