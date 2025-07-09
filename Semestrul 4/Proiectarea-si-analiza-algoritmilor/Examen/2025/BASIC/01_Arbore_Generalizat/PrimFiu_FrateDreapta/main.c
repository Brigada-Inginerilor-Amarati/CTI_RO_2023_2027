#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// -------------
// DEFINES
// -------------
#define DEBUG 0
#define MAX_NODURI 100

// -------------
// STRUCTURI DE DATE
// -------------
typedef struct ArboreGeneralizat {
    int numarNoduri;
    int primFiu[MAX_NODURI];
    int frateDreapta[MAX_NODURI];
} ArboreGeneralizat_T;

// -------------
// FUNCȚII
// -------------
ArboreGeneralizat_T* initArbore() {
    ArboreGeneralizat_T *arbore = (ArboreGeneralizat_T *)malloc(sizeof(ArboreGeneralizat_T));

    if (arbore == NULL) {
        fprintf(stderr, "Eroare la alocarea memoriei pentru arbore.\n");
        exit(EXIT_FAILURE);
    }

    arbore->numarNoduri = 0;

    for (int i = 0; i < MAX_NODURI; i++) {
        arbore->primFiu[i] = -1;
        arbore->frateDreapta[i] = -1;
    }

    return arbore;
}

void inserareNod(ArboreGeneralizat_T *arbore, int primFiu, int frateDreapta) {
    if (arbore->numarNoduri >= MAX_NODURI) {
        fprintf(stderr, "Numărul maxim de noduri a fost atins.\n");
        return;
    }

    int index = arbore->numarNoduri;

    if (DEBUG) {
        printf("Inserare nod: %d, Prim fiu: %d, Frate drept: %d\n", index, primFiu, frateDreapta);
    }

    arbore->primFiu[index] = primFiu;
    arbore->frateDreapta[index] = frateDreapta;

    arbore->numarNoduri++;
}

void afisareArbore(ArboreGeneralizat_T *arbore) {
    printf("Număr noduri: %d\n", arbore->numarNoduri);
    for (int i = 0; i < arbore->numarNoduri; i++) {
        printf("Nod %d: Prim fiu = %d, Frate drept = %d\n",
               i,
               arbore->primFiu[i],
               arbore->frateDreapta[i]);
    }
}

void preordine(ArboreGeneralizat_T *arbore, int index) {
    if (index == -1) return;

    printf("Nod: %d\n", index);

    int fiu = arbore->primFiu[index];

    while (fiu != -1) {
        preordine(arbore, fiu);
        fiu = arbore->frateDreapta[fiu];
    }
}

void inordine(ArboreGeneralizat_T *arbore, int index) {
    if (index == -1) return;

    int fiu = arbore->primFiu[index];

    if (fiu != -1) {
        inordine(arbore, fiu);
    }

    printf("%d ", index);

    fiu = arbore->frateDreapta[fiu];

    while(fiu != -1) {
        inordine(arbore, fiu);
        fiu = arbore->frateDreapta[fiu];
    }
}

void postordine(ArboreGeneralizat_T* arbore, int index){
    int fiu = arbore->primFiu[index];

    while (fiu != -1) {
        postordine(arbore, fiu);
        fiu = arbore->frateDreapta[fiu];
    }

    printf("%d ", index);
}

// -------------
// MAIN
// -------------
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Utilizare: %s <fisier_intrare>\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");

    if (fin == NULL) {
        fprintf(stderr, "Eroare la deschiderea fișierului %s.\n", argv[1]);
        return 1;
    }

    ArboreGeneralizat_T *arbore = initArbore();

    int primFiu, frateDreapta;

    while (fscanf(fin, "%d %d", &primFiu, &frateDreapta) == 2) {
        inserareNod(arbore, primFiu, frateDreapta);
    }

    fclose(fin);

    afisareArbore(arbore);

    printf("Parcurgere preordine:\n");
    preordine(arbore, 1);

    printf("Parcurgere inordine:\n");
    inordine(arbore, 1);

    printf("Parcurgere postordine:\n");
    postordine(arbore, 1);

    return 0;
}
