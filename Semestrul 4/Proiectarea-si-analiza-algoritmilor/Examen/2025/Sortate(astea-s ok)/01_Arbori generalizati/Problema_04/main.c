#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1
#define MAX_NODURI 100

typedef struct ArboreGeneralizat{
    int chei[MAX_NODURI];
    int parinte[MAX_NODURI];
    int numarNoduri;
}ArboreGeneralizat_T;

void initArbore(ArboreGeneralizat_T* arbore){
    arbore->numarNoduri = 0;
    for(int i = 0; i < MAX_NODURI; i++){
        arbore->chei[i] = 0;
        arbore->parinte[i] = -1;
    }
}

void adauga(int cheie, int parinte, ArboreGeneralizat_T* arbore){
    if(arbore->numarNoduri >= MAX_NODURI){
        printf("Arborele este plin!\n");
        return;
    }

    arbore->chei[arbore->numarNoduri] = cheie;
    arbore->parinte[arbore->numarNoduri] = parinte;
    arbore->numarNoduri++;

    if(DEBUG){
        printf("Adaugat nod: %d cu parinte: %d\n", cheie, parinte);
    }
}

void afiseazaArbore(ArboreGeneralizat_T* arbore){
    printf("Noduri in arbore:\n");
    for(int i = 0; i < arbore->numarNoduri; i++){
        printf("Nod %d: Cheie = %d, Parinte = %d\n", i, arbore->chei[i], arbore->parinte[i]);
    }
}

int inaltimeMaxima = 0;

void calculeazaInaltime(ArboreGeneralizat_T* arbore, int *pas, int index){
    for(int i = 0; i < arbore->numarNoduri; i++){
        if(arbore->parinte[i] == arbore->chei[index]){
            *pas = *pas + 1;

            if(*pas > inaltimeMaxima){
                inaltimeMaxima = *pas;
            }

            calculeazaInaltime(arbore, pas, arbore->chei[i]);

            *pas = *pas - 1; // revenim la nivelul anterior
        }
    }
}

int grad = 0;

void calculeazaGrad(ArboreGeneralizat_T* arbore){
    int nr = 0;
    int parinteCurent = -1;
    for(int i = 0; i < arbore->numarNoduri; i++){
        if(arbore->chei[i] == arbore->parinte[i]){
            continue;
        }

        if(arbore->parinte[i] == parinteCurent ){
            nr++;
        }
        else{
            if(nr > grad){
                grad = nr;
            }
            parinteCurent = arbore->parinte[i];
            nr = 1; // resetam numaratorul pentru noul parinte
        }
    }

    if(nr > grad){
        grad = nr; // verificam si ultimul grup de noduri
    }
    
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Utilizare: %s <fisier_intrare>\n", argv[0]);
        return 1;
    }

    FILE *fisier = fopen(argv[1], "r");
    if(fisier == NULL){
        printf("Eroare la deschiderea fisierului %s\n", argv[1]);
        return 1;
    }

    ArboreGeneralizat_T arbore;

    int nrNoduri;
    fscanf(fisier, "%d", &nrNoduri);
    if(nrNoduri > MAX_NODURI){
        printf("Numarul de noduri depaseste limita maxima (%d)\n", MAX_NODURI);
        fclose(fisier);
        return 1;
    }

    arbore.numarNoduri = nrNoduri;

    initArbore(&arbore);
    int cheie, parinte;
    while(fscanf(fisier, "%d %d", &cheie, &parinte) == 2){
        adauga(cheie, parinte, &arbore);
    }

    fclose(fisier);

    afiseazaArbore(&arbore);

    if(DEBUG){
        printf("Arborele a fost construit cu %d noduri.\n", arbore.numarNoduri);
    }

    int pas = 0;
    calculeazaInaltime(&arbore, &pas, 0); 
    printf("Inaltimea maxima a arborelui este: %d\n", inaltimeMaxima + 1);


    calculeazaGrad(&arbore);
    printf("Gradul maxim al arborelui este: %d\n", grad);


    return 0;
}