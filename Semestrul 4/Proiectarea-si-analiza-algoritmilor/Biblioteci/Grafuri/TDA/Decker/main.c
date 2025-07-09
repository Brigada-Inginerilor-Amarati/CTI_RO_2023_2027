#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 16  // capacitatea maximă pentru noduri

// Tipuri asociate
typedef int TipPozitie;           // indicele nodului
typedef void* TipAtom;            // conținutul/atomul nodului

// TipArc: o pereche de poziții
typedef struct {
    TipPozitie p;
    TipPozitie q;
} TipArc;

// TDA Graf (Decker)
typedef struct {
    unsigned n;                    // număr de noduri
    TipPozitie pozitii[MAXN];      // vector de poziții (indicele 0..n-1)
    TipAtom atomi[MAXN];           // conținutul fiecărui nod
    unsigned short R[MAXN][MAXN];  // matrice de adiacență (relația R)
} TipGraf;

// 1. Crează: initializează graful vid
void Creaza(TipGraf *g) {
    g->n = 0;
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++)
            g->R[i][j] = 0;
        g->pozitii[i] = i;
        g->atomi[i] = NULL;
    }
}

// 2. Adiacent: returnează true dacă pRq
int Adiacent(TipPozitie p, TipPozitie q, const TipGraf *g) {
    if (p < 0 || p >= (int)g->n || q < 0 || q >= (int)g->n)
        return 0;
    return g->R[p][q];
}

// 3. Modifică: set f(p)=a
void Modifica(TipAtom a, TipPozitie p, TipGraf *g) {
    if (p < 0 || p >= (int)g->n)
        return;
    g->atomi[p] = a;
}

// 4. Furnizează: returnează f(p)
TipAtom Furnizeaza(TipPozitie p, const TipGraf *g) {
    if (p < 0 || p >= (int)g->n)
        return NULL;
    return g->atomi[p];
}

// 5. SuprimNod: elimină nodul p și toate arcele incidente
void SuprimNod(TipPozitie p, TipGraf *g) {
    if (p < 0 || p >= (int)g->n)
        return;
    int last = g->n - 1;
    // mută ultimul nod în poziția p
    if (p != last) {
        g->atomi[p] = g->atomi[last];
        // copiază coloana și rândul
        for (int i = 0; i < g->n; i++) {
            g->R[i][p] = g->R[i][last];
            g->R[p][i] = g->R[last][i];
        }
    }
    // șterge ultimul rând și coloană
    for (int i = 0; i < g->n; i++) {
        g->R[i][last] = 0;
        g->R[last][i] = 0;
    }
    g->n--;
}

// 6. SuprimArc: extrage e din relație
void SuprimArc(TipArc e, TipGraf *g) {
    if (e.p < 0 || e.q < 0 || e.p >= (int)g->n || e.q >= (int)g->n)
        return;
    g->R[e.p][e.q] = 0;
    g->R[e.q][e.p] = 0;  // graf neorientat
}

// 7. InserNod: adaugă poziția p fără arce
void InserNod(TipPozitie p, TipGraf *g) {
    if (g->n >= MAXN || p < 0)
        return;
    // pozițiile sunt implicit 0..n-1; pentru inserție se consideră poziție nouă la final
    g->n++;
    g->atomi[g->n - 1] = NULL;
    // relațiile noi sunt 0 (fără arce)
    for (int i = 0; i < g->n; i++) {
        g->R[i][g->n - 1] = 0;
        g->R[g->n - 1][i] = 0;
    }
}

// 8. InserArc: include e în relația R
void InserArc(TipArc e, TipGraf *g) {
    if (e.p < 0 || e.q < 0 || e.p >= (int)g->n || e.q >= (int)g->n)
        return;
    g->R[e.p][e.q] = 1;
    g->R[e.q][e.p] = 1;  // graf neorientat
}

// Exemplu de utilizare
void afisareGraf(const TipGraf *g) {
    printf("Numar noduri: %u\n", g->n);
    printf("Matrice Adiacentă:\n");
    for (unsigned i = 0; i < g->n; i++) {
        for (unsigned j = 0; j < g->n; j++)
            printf("%u ", g->R[i][j]);
        printf("\n");
    }
}

int main(void) {
    TipGraf g;
    Creaza(&g);

    // Inserare noduri (creștem g->n)
    InserNod(0, &g);
    InserNod(1, &g);
    InserNod(2, &g);

    // Set atom
    int a = 42;
    Modifica(&a, 1, &g);

    // Inserare arce
    TipArc e1 = {0, 1};
    TipArc e2 = {1, 2};
    InserArc(e1, &g);
    InserArc(e2, &g);

    afisareGraf(&g);
    
    printf("Adj(0,1)? %s\n", Adiacent(0,1,&g)?"da":"nu");
    printf("Atom la 1: %d\n", *(int*)Furnizeaza(1,&g));

    return 0;
}
