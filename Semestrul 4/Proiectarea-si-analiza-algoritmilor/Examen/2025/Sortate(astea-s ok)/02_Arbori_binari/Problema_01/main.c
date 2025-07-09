#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1
#define MAX_NODURI 100

int numarNoduri = 0;

typedef struct ArboreBinar{
    int cheie;
    struct ArboreBinar *stanga;
    struct ArboreBinar *dreapta;
}ArboreBinar_T;

ArboreBinar_T* initArboreBinar(int cheie){
   ArboreBinar_T* arbore = (ArboreBinar_T*)malloc(sizeof(ArboreBinar_T));

    if(arbore == NULL){
        printf("Eroare la alocarea memoriei pentru arbore\n");
        exit(EXIT_FAILURE);
    }

    arbore->cheie = cheie;
    arbore->stanga = NULL;
    arbore->dreapta = NULL;

    return arbore;
}

ArboreBinar_T* adaugaNod(ArboreBinar_T*arbore, int cheie){
    if(arbore == NULL){
        arbore = initArboreBinar(cheie);
        //printf("Nodul cu cheia %d a fost adaugat in arbore\n", cheie);
        return arbore;
    }

    if(cheie < arbore->cheie){
        arbore->stanga = adaugaNod(arbore->stanga, cheie);
    }
    else if(cheie > arbore->cheie){
       arbore->dreapta = adaugaNod(arbore->dreapta, cheie);
    }
    else {
        printf("Cheia %d exista deja in arbore\n", cheie);
    }

    return arbore;
}

int hMAX = 0;

void inaltime(ArboreBinar_T* arbore, int *h){
    if(arbore  == NULL){
        return;
    }

    *h = *h + 1;

    if(*h > hMAX){
        hMAX = *h;
    }

    inaltime(arbore->stanga, h);
    inaltime(arbore->dreapta, h);

    *h = *h - 1;
}

void preordine(ArboreBinar_T* arbore){
    if(arbore == NULL){
        return;
    }

    printf("%d ", arbore->cheie);
    preordine(arbore->stanga);
    preordine(arbore->dreapta);
}




int main(int argc, char **argv){
    if(argc != 2){
        printf("Utilizare: %s <fisier_intrare>\n", argv[1]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if(fin == NULL){
        printf("Eroare la deschiderea fisierului %s\n", argv[1]);
        return 1;
    }

    ArboreBinar_T* arbore = NULL;
    int cheie;
    
    fscanf(fin, "%d", &numarNoduri);

    for(int i = 0; i < numarNoduri; i++){
        fscanf(fin, "%d ", &cheie);
        arbore = adaugaNod(arbore, cheie);
    }

    fclose(fin);
    printf("Parcurgere in preordine:\n");
    preordine(arbore);
    printf("\n");

    int h = 0;
    inaltime(arbore, &h);
    printf("Inaltimea arborelui este: %d\n", hMAX);


    return 0;
}