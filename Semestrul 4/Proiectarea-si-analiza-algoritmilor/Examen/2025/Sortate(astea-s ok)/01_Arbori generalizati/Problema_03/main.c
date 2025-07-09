#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1
#define MAX_NODURI 100

typedef struct ArboreGeneralizat {
    int numarDirectoare;
    int primFiu[MAX_NODURI];
    int frateDrept[MAX_NODURI];
    char nume[MAX_NODURI][50];
} ArboreGeneralizat_T;

int directoarePeNivel[MAX_NODURI];

void initArbore(ArboreGeneralizat_T *arbore) {
    arbore->numarDirectoare = 0;
    for (int i = 0; i < MAX_NODURI; i++) {
        arbore->primFiu[i] = -1;
        arbore->frateDrept[i] = -1;
        strcpy(arbore->nume[i], "");
    }
}

void afisareArbore(ArboreGeneralizat_T *arbore) {
    for (int i = 0; i < arbore->numarDirectoare; i++) {
        printf("Nod: %s, Prim Fiu: %d, Frate Drept: %d\n",
               arbore->nume[i],
               arbore->primFiu[i] == -1 ? -1 : arbore->primFiu[i] + 1,
               arbore->frateDrept[i] == -1 ? -1 : arbore->frateDrept[i] + 1);
    }
}

void numaraRecursiv(ArboreGeneralizat_T *arbore, int index, int nivelCurent) {
    if (index == -1)
        return;

    // Incrementez numarul de noduri pe nivelul curent
    directoarePeNivel[nivelCurent]++;

    if (DEBUG) {
        printf("Directoriul %s este la nivelul %d\n", arbore->nume[index], nivelCurent + 1);
    }

    // Parcurg recursiv fiul pe nivelul urmator
    numaraRecursiv(arbore, arbore->primFiu[index], nivelCurent + 1);

    // Parcurg recursiv fratele drept pe acelasi nivel
    numaraRecursiv(arbore, arbore->frateDrept[index], nivelCurent);
}

void afiseazaDirectoarePeNivel() {
    printf("\nDirectoare pe fiecare nivel:\n");
    for (int i = 0; i < MAX_NODURI; i++) {
        if (directoarePeNivel[i] > 0) {
            printf("Nivel %d: %d directoare\n", i + 1, directoarePeNivel[i]);
        }
    }
}

void afiseazaDirectoareMaxim() {
    int max = 0;

    for (int i = 0; i < MAX_NODURI; i++) {
        if (directoarePeNivel[i] > max) {
            max = directoarePeNivel[i];
        }
    }

    printf("\nNumarul maxim de directoare pe un nivel este: %d\n", max);
}

int inaltimeMAX = 0;

void calculeazaInaltime(ArboreGeneralizat_T* arbore, int *pas, int index){
    if(index == -1){
        return;
    }

    (*pas)++;

    if (*pas > inaltimeMAX) {
        inaltimeMAX = *pas;
    }
    if (DEBUG) {
        printf("Nod %s la nivelul %d\n", arbore->nume[index], *pas);
    }

    calculeazaInaltime(arbore, pas, arbore->primFiu[index]);

    int primFiu = arbore->primFiu[index];

    while(primFiu != -1){
        primFiu = arbore->frateDrept[primFiu];
        calculeazaInaltime(arbore, pas, primFiu);
    }

    (*pas)--; // Decrementam pasul la intoarcerea din recursie
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Utilizare: %s <fisier_intrare>\n", argv[0]);
        return 1;
    }

    FILE *fisier = fopen(argv[1], "r");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului %s\n", argv[1]);
        return 1;
    }

    ArboreGeneralizat_T arbore;
    initArbore(&arbore);

    int numarDirectoare;
    fscanf(fisier, "%d", &numarDirectoare);
    arbore.numarDirectoare = numarDirectoare;

    int primFiu, frateDrept;
    char nume[50];

    for (int i = 0; i < numarDirectoare; i++) {
        fscanf(fisier, "%d %d %s", &primFiu, &frateDrept, nume);

        arbore.primFiu[i] = primFiu == -1 ? -1 : primFiu - 1;
        arbore.frateDrept[i] = frateDrept == -1 ? -1 : frateDrept - 1;
        strcpy(arbore.nume[i], nume);

        if (DEBUG) {
            printf("Nod %d: Prim Fiu: %d, Frate Drept: %d, Nume: %s\n",
                   i + 1, primFiu, frateDrept, nume);
        }
    }

    fclose(fisier);

    if (DEBUG) {
        printf("\nArborele generalizat:\n");
        afisareArbore(&arbore);
    }

    for (int i = 0; i < MAX_NODURI; i++) {
        directoarePeNivel[i] = 0;
    }

    numaraRecursiv(&arbore, 0, 0);

    afiseazaDirectoarePeNivel();

    afiseazaDirectoareMaxim();

    int pas = 0;
    calculeazaInaltime(&arbore, &pas, 0);

    printf("\nInaltimea maxima a arborelui este: %d\n", inaltimeMAX);

    return 0;
}
