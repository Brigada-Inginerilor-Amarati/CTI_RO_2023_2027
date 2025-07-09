#ifndef GENERALTREE_H
#define GENERALTREE_H

#include <stdio.h>
#include <stdlib.h>

// Definirea tipurilor de date
typedef struct Nod {
    int cheie;
    struct Nod* primulFiu;
    struct Nod* frateDreapta;
} Nod;

typedef Nod* TipNod;
typedef TipNod TipArbore;
typedef int TipCheie;

// Funcții pentru arbore
TipNod Creazai(TipCheie v, TipArbore A1, TipArbore A2);
TipArbore Initializeaza();
void Insereaza(TipNod N, TipArbore A, TipNod T);
void Suprima(TipNod N);
TipNod Tata(TipNod radacina, TipNod N);
TipNod PrimulFiu(TipNod N);
TipNod FrateDreapta(TipNod N);
TipCheie Cheie(TipNod N);
void Preordine(TipNod N);
void Inordine(TipNod N);
void Postordine(TipNod N);

#endif

#include "generaltree.h"

// Crearea unui nod nou
TipNod Creazai(TipCheie v, TipArbore A1, TipArbore A2) {
    TipNod nod = (TipNod)malloc(sizeof(Nod));
    if (!nod) {
        printf("Eroare la alocarea memoriei!\n");
        exit(EXIT_FAILURE);
    }
    nod->cheie = v;
    nod->primulFiu = A1;
    nod->frateDreapta = A2;
    return nod;
}

// Inițializează un arbore vid
TipArbore Initializeaza() {
    return NULL;
}

// Inserează un nod ca fiu al unui alt nod
void Insereaza(TipNod N, TipArbore A, TipNod T) {
    if (T->primulFiu == NULL) {
        T->primulFiu = N;
    }
    else {
        TipNod temp = T->primulFiu;
        while (temp->frateDreapta != NULL) {
            temp = temp->frateDreapta;
        }
        temp->frateDreapta = N;
    }
}

// Suprimă un nod și toți descendenții săi
void Suprima(TipNod N) {
    if (N == NULL) return;
    Suprima(N->primulFiu);
    Suprima(N->frateDreapta);
    free(N);
}

// Returnează tatăl unui nod
TipNod Tata(TipNod radacina, TipNod N) {
    if (radacina == NULL || N == NULL) return NULL;
    if (radacina->primulFiu == N) return radacina;
    TipNod temp = radacina->primulFiu;
    while (temp != NULL) {
        if (temp->frateDreapta == N) return radacina;
        TipNod rezultat = Tata(temp, N);
        if (rezultat != NULL) return rezultat;
        temp = temp->frateDreapta;
    }
    return NULL;
}

// Returnează primul fiu al unui nod
TipNod PrimulFiu(TipNod N) {
    return (N != NULL) ? N->primulFiu : NULL;
}

// Returnează fratele drept al unui nod
TipNod FrateDreapta(TipNod N) {
    return (N != NULL) ? N->frateDreapta : NULL;
}

// Returnează cheia unui nod
TipCheie Cheie(TipNod N) {
    return (N != NULL) ? N->cheie : -1;
}

// Traversare în preordine
void Preordine(TipNod N) {
    if (N == NULL) return;
    printf("%d ", N->cheie);
    Preordine(N->primulFiu);
    Preordine(N->frateDreapta);
}

// Traversare în inordine
void Inordine(TipNod N) {
    if (N == NULL) return;
    Inordine(N->primulFiu);
    printf("%d ", N->cheie);
    Inordine(N->frateDreapta);
}

// Traversare în postordine
void Postordine(TipNod N) {
    if (N == NULL) return;
    Postordine(N->primulFiu);
    Postordine(N->frateDreapta);
    printf("%d ", N->cheie);
}

#include "generaltree.h"

int main() {
    TipArbore A = Initializeaza();
    TipNod radacina = Creazai(1, NULL, NULL);
    A = radacina;

    TipNod nod2 = Creazai(2, NULL, NULL);
    TipNod nod3 = Creazai(3, NULL, NULL);
    TipNod nod4 = Creazai(4, NULL, NULL);
    TipNod nod5 = Creazai(5, NULL, NULL);

    Insereaza(nod2, A, radacina);
    Insereaza(nod3, A, radacina);
    Insereaza(nod4, A, nod2);
    Insereaza(nod5, A, nod2);

    printf("Traversare in preordine: ");
    Preordine(A);
    printf("\n");

    printf("Traversare in inordine: ");
    Inordine(A);
    printf("\n");

    printf("Traversare in postordine: ");
    Postordine(A);
    printf("\n");

    Suprima(A);
    return 0;
}
