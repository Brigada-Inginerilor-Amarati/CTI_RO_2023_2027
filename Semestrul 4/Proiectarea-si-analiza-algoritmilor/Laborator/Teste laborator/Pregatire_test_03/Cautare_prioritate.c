
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_NODES 50
#define NEVAZUT 99999

typedef struct Nod {
    int nume;
    int cost;
    struct Nod* urm;
} Nod;

Nod* StrAdj[MAX_NODES];  // Listele de adiacență
int marc[MAX_NODES];     // Tablou de marcaje
int parinte[MAX_NODES];  // Tablou de părinți

typedef struct {
    int noduri[MAX_NODES];
    int prioritati[MAX_NODES];
    int size;
} CoadaPrioritati;

// Inițializare listă adiacență
void initGraf(int N) {
    for (int i = 0; i < N; i++) {
        StrAdj[i] = NULL;
    }
}

// Adăugare muchie (nedirecționată)
void adaugaMuchie(int u, int v, int cost) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->nume = v;
    nou->cost = cost;
    nou->urm = StrAdj[u];
    StrAdj[u] = nou;

    Nod* nou2 = (Nod*)malloc(sizeof(Nod));
    nou2->nume = u;
    nou2->cost = cost;
    nou2->urm = StrAdj[v];
    StrAdj[v] = nou2;
}

// Coada de priorități
void Initializeaza(CoadaPrioritati* q) {
    q->size = 0;
}

int Vid(CoadaPrioritati* q) {
    return q->size == 0;
}

int Extrage(CoadaPrioritati* q) {
    int min = 0;
    for (int i = 1; i < q->size; i++) {
        if (q->prioritati[i] < q->prioritati[min]) {
            min = i;
        }
    }
    int nod = q->noduri[min];
    for (int i = min; i < q->size - 1; i++) {
        q->noduri[i] = q->noduri[i + 1];
        q->prioritati[i] = q->prioritati[i + 1];
    }
    q->size--;
    return nod;
}

int Actualizeaza(CoadaPrioritati* q, int nod, int prioritate) {
    for (int i = 0; i < q->size; i++) {
        if (q->noduri[i] == nod) {
            if (prioritate < q->prioritati[i]) {
                q->prioritati[i] = prioritate;
                return 1;
            }
            return 0;
        }
    }
    q->noduri[q->size] = nod;
    q->prioritati[q->size] = prioritate;
    q->size++;
    return 1;
}

// Căutare bazată pe prioritate (PFS)
void CautaPrioritar(int k) {
    CoadaPrioritati q;
    Initializeaza(&q);

    if (Actualizeaza(&q, k, NEVAZUT)) {
        parinte[k] = -1;
    }

    while (!Vid(&q)) {
        int nod = Extrage(&q);
        if (marc[nod] == -NEVAZUT) marc[nod] = 0;

        marc[nod] = -marc[nod];

        for (Nod* t = StrAdj[nod]; t != NULL; t = t->urm) {
            if (marc[t->nume] < 0) {
                if (Actualizeaza(&q, t->nume, t->cost)) {
                    marc[t->nume] = -t->cost;
                    parinte[t->nume] = nod;
                }
            }
        }
    }
}

// Determinare AAM cu PFS
void ArboreMinim(int N) {
    for (int i = 0; i < N; i++) {
        marc[i] = -NEVAZUT;
    }
    for (int i = 0; i < N; i++) {
        if (marc[i] == -NEVAZUT) {
            CautaPrioritar(i);
        }
    }
}

// Afișare rezultat
void afiseazaArbore(int N) {
    int costTotal = 0;
    printf("Muchii in arborele de acoperire minim:");
    for (int i = 0; i < N; i++) {
        if (parinte[i] != -1) {
            for (Nod* t = StrAdj[i]; t; t = t->urm) {
                if (t->nume == parinte[i]) {
                    printf("%d - %d (cost: %d)", parinte[i] + 1, i + 1, t->cost);
                    costTotal += t->cost;
                    break;
                }
            }
        }
    }
    printf("Cost total: %d", costTotal);
}

// Program principal
int main() {
    int N = 6;
    initGraf(N);

    adaugaMuchie(0, 1, 6);
    adaugaMuchie(0, 2, 1);
    adaugaMuchie(0, 3, 5);
    adaugaMuchie(1, 2, 5);
    adaugaMuchie(1, 4, 3);
    adaugaMuchie(2, 3, 5);
    adaugaMuchie(2, 4, 6);
    adaugaMuchie(2, 5, 4);
    adaugaMuchie(3, 5, 2);
    adaugaMuchie(4, 5, 6);

    ArboreMinim(N);
    afiseazaArbore(N);

    return 0;
}
