#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 16   // capacitatea maximă pentru noduri

// Tipuri generice (pot fi adaptate)
typedef int TipCheie;
typedef void* TipInfo;

// Elementul de graf: cheie + informație
typedef struct {
    TipCheie cheie;
    TipInfo info;
} TipElement;

// Referință la nod: index în tabloul de noduri
typedef int TipIndicNod;

// Referință la arc: pereche de indici în matrice
typedef struct {
    TipIndicNod u, v;
} TipIndicArc;

// Tipul de date abstract pentru graf (Shiflet)
typedef struct {
    unsigned n;                         // număr de noduri
    TipElement noduri[MAXN];           // lista nodurilor
    unsigned short A[MAXN][MAXN];      // matrice de adiacență
} TipGraf;

// (1) InitGraf: inițializează graful vid
void InitGraf(TipGraf *g) {
    g->n = 0;
    memset(g->A, 0, sizeof g->A);
}

// (2) GrafVid: returnează true dacă graful este vid
int GrafVid(const TipGraf *g) {
    return (g->n == 0);
}

// (3) GrafPlin: returnează true dacă structura e plină
int GrafPlin(const TipGraf *g) {
    return (g->n >= MAXN);
}

// (4) CheieElemGraf: returnează cheia unui element
TipCheie CheieElemGraf(const TipGraf *g, const TipElement *e) {
    (void)g;
    return e->cheie;
}

// (5) CautaCheieGraf: returnează true dacă cheia k există
int CautaCheieGraf(const TipGraf *g, TipCheie k) {
    for (unsigned i = 0; i < g->n; i++)
        if (g->noduri[i].cheie == k)
            return 1;
    return 0;
}

// funcție internă: găsește indexul nodului cu cheia k, sau -1
static TipIndicNod findIndex(const TipGraf *g, TipCheie k) {
    for (int i = 0; i < (int)g->n; i++)
        if (g->noduri[i].cheie == k)
            return i;
    return -1;
}

// (6) IndicaNod: obține referința la nod prin cheia k
void IndicaNod(const TipGraf *g, TipCheie k, TipIndicNod *indicNod) {
    *indicNod = findIndex(g, k);
}

// (7) IndicaArc: obține referința la arc dintre k1 și k2
void IndicaArc(const TipGraf *g, TipCheie k1, TipCheie k2, TipIndicArc *indicArc) {
    TipIndicNod u = findIndex(g, k1);
    TipIndicNod v = findIndex(g, k2);
    if (u >= 0 && v >= 0 && g->A[u][v]) {
        indicArc->u = u;
        indicArc->v = v;
    } else {
        indicArc->u = indicArc->v = -1;
    }
}

// (8) ArcVid: returnează true dacă referința la arc e vidă
int ArcVid(const TipGraf *g, TipIndicArc indicArc) {
    if (indicArc.u < 0 || indicArc.v < 0)
        return 1;
    return (g->A[indicArc.u][indicArc.v] == 0);
}

// (9) InserNod: inserează un nod izolat
void InserNod(TipGraf *g, TipElement e) {
    if (GrafPlin(g) || CautaCheieGraf(g, e.cheie))
        return;
    g->noduri[g->n++] = e;
}

// (10) InserArc: inserează un arc între nodurile k1 și k2
void InserArc(TipGraf *g, TipCheie k1, TipCheie k2) {
    TipIndicNod u = findIndex(g, k1);
    TipIndicNod v = findIndex(g, k2);
    if (u >= 0 && v >= 0)
        g->A[u][v] = g->A[v][u] = 1;  // graf neorientat
}

// (11) SuprimNod: șterge nodul și arcele incidente
void SuprimNod(TipGraf *g, TipIndicNod indicNod) {
    if (indicNod < 0 || indicNod >= (int)g->n)
        return;
    int last = g->n - 1;
    if (indicNod != last) {
        g->noduri[indicNod] = g->noduri[last];
        for (int i = 0; i < (int)g->n; i++) {
            g->A[i][indicNod] = g->A[i][last];
            g->A[indicNod][i] = g->A[last][i];
        }
    }
    for (int i = 0; i < (int)g->n; i++)
        g->A[i][last] = g->A[last][i] = 0;
    g->n--;
}

// (12) SuprimArc: șterge un arc
void SuprimArc(TipGraf *g, TipIndicArc indicArc) {
    if (!ArcVid(g, indicArc)) {
        g->A[indicArc.u][indicArc.v] = 0;
        g->A[indicArc.v][indicArc.u] = 0;
    }
}

// (13) ActualizNod: actualizează informația unui nod
void ActualizNod(TipGraf *g, TipIndicNod indicNod, TipInfo x) {
    if (indicNod < 0 || indicNod >= (int)g->n)
        return;
    g->noduri[indicNod].info = x;
}

// (14) FurnizeazaNod: returnează elementul unui nod
TipElement FurnizeazaNod(const TipGraf *g, TipIndicNod indicNod) {
    if (indicNod >= 0 && indicNod < (int)g->n)
        return g->noduri[indicNod];
    return (TipElement){0, NULL};
}

// (15) TraversGraf: parcurgere DFS cu afișare completă
static int visited[MAXN];
void dfs_print(const TipGraf *g, int u) {
    visited[u] = 1;
    printf("Nod: cheie=%d\n", g->noduri[u].cheie);
    for (int v = 0; v < (int)g->n; v++) {
        if (g->A[u][v] && !visited[v]) {
            dfs_print(g, v);
        }
    }
}

void TraversGraf(const TipGraf *g, void (*Vizita)(TipElement)) {
    // Inițializează vizitarea
    memset(visited, 0, sizeof visited);
    // Pentru fiecare componentă conexă, pornește DFS
    for (int i = 0; i < (int)g->n; i++) {
        if (!visited[i]) {
            dfs_print(g, i);
        }
    }
}

// Exemplu de utilizare
typedef struct { int val; } InfoInt;
int main(void) {
    TipGraf g;
    InitGraf(&g);

    // Noduri cu chei
    InserNod(&g, (TipElement){.cheie = 1, .info = NULL});
    InserNod(&g, (TipElement){.cheie = 2, .info = NULL});
    InserNod(&g, (TipElement){.cheie = 3, .info = NULL});
    InserArc(&g, 1, 2);
    InserArc(&g, 2, 3);

    printf("Traversare completă a grafului (DFS):\n");
    TraversGraf(&g, NULL);
    return 0;
}
