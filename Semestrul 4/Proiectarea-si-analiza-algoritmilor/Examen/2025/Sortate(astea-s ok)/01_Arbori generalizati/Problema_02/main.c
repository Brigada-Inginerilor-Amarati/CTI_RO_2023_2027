#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1
#define MAX_NODURI 100

typedef struct ArboreGeneralizat{
    int numarDirectoare;
    int parinteDirector[MAX_NODURI]; // Parintele directorului
    char numeDirector[MAX_NODURI][50]; // Numele directorului
}ArboreGeneralizat_T;

void initArbore(ArboreGeneralizat_T *arbore){
    arbore->numarDirectoare = 0;

    for(int i = 0; i < MAX_NODURI; i++){
        arbore->parinteDirector[i] = -1;
        strcpy(arbore->numeDirector[i], "");
    }
}

void afisareArbore(ArboreGeneralizat_T *arbore){
    for(int i = 0; i < arbore->numarDirectoare; i++){
        printf("Director: %s, Parinte: %d\n", arbore->numeDirector[i], arbore->parinteDirector[i] + 1);
    }
}

int inaltimeMAX = 0;

void inaltimeMaxima(ArboreGeneralizat_T *arbore, int *pas, int indexCurent){
    if(indexCurent == -1){
        return;
    }

    for(int i = 0; i < arbore->numarDirectoare; i++){
        if(arbore->parinteDirector[i] == indexCurent){
            *pas = *pas + 1;

            if(*pas > inaltimeMAX){
                inaltimeMAX = *pas;
            }

            if(DEBUG){
                printf("Pas: %d, Index Curent: %d, Nume Director: %s\n", *pas, i, arbore->numeDirector[i]);
            }

            inaltimeMaxima(arbore, pas, i);

            *pas = *pas - 1; // revenim la pasul anterior
        }
    }
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Utilizare: %s <fisier_intrare>\n", argv[1]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");

    if(fin == NULL){
        perror("Eroare la deschiderea fisierului\n");
        return 1;
    }

    ArboreGeneralizat_T arbore;
    initArbore(&arbore);

    fscanf(fin, "%d", &arbore.numarDirectoare);

    if(DEBUG){
        printf("Numar directoare: %d\n", arbore.numarDirectoare);
    }

    int parinte = -1;
    char nume[50];

    for(int i = 0; i < arbore.numarDirectoare; i++){
        fscanf(fin, "%d %s", &parinte, nume);

        if(DEBUG){
            printf("Citit director: %s, parinte: %d\n", nume, parinte);
        }

        strcpy(arbore.numeDirector[i], nume);

        arbore.parinteDirector[i] = parinte - 1; // Convertim la indexare de la 0
    }

    fclose(fin);

    if(DEBUG){
        printf("Arborele generalizat:\n");
        afisareArbore(&arbore);
    }

    int pas = 0;
    inaltimeMaxima(&arbore, &pas, 0); // Incepem de la radacina (-1)

    printf("Inaltimea maxima a arborelui generalizat este: %d\n", inaltimeMAX + 1);

    return 0;
}