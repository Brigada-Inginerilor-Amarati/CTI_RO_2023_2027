#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NODURI 100
#define DEBUG 1

typedef struct Graf{
    int nrNoduri;
    int matriceAdiacenta[MAX_NODURI][MAX_NODURI];
}Graf_T;


void initGraf(Graf_T *graf) {
    graf->nrNoduri = 0;
    memset(graf->matriceAdiacenta, 0, sizeof(graf->matriceAdiacenta));
}

void afisareGraf(Graf_T *graf) {
    printf("Numar noduri: %d\n", graf->nrNoduri);
    for(int i = 0; i < graf->nrNoduri; i++) {
        for(int j = 0; j < graf->nrNoduri; j++) {
            printf("%d ", graf->matriceAdiacenta[i][j]);
        }
        printf("\n");
    }
}

void celMaiLungDrum(Graf_T *graf, int nod_start, int *vizitat, int nod_final, int *lungimeMAX, int lungimeCurenta){
    if(nod_start == nod_final){
        if(lungimeCurenta > *lungimeMAX){
            *lungimeMAX = lungimeCurenta;
        }
        return;
    }    

    vizitat[nod_start] = 1;

    if(DEBUG) {
        printf("Vizitam nodul %d, lungime curenta: %d\n", nod_start, lungimeCurenta);
    }

    for(int i = 0; i < graf->nrNoduri; i++){
        if(graf->matriceAdiacenta[nod_start][i] != 0 && vizitat[i] == 0){
            celMaiLungDrum(graf, i, vizitat, nod_final, lungimeMAX, lungimeCurenta + graf->matriceAdiacenta[nod_start][i]);
        }
    }

    vizitat[nod_start] = 0; // backtrack
}


int main(int argc, char **argv){
    if(argc != 2){
        perror("Usage: ./p <filename> \n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if(f == NULL){
        perror("Error opening file\n");
        return 1;
    }

    Graf_T graf;
    initGraf(&graf);

    int nrNoduri = 0;
    fscanf(f, "%d", &nrNoduri);
    graf.nrNoduri = nrNoduri;   

    for(int i = 0; i < nrNoduri; i++){
        for(int j = 0; j < nrNoduri; j++){
            fscanf(f, "%d", &graf.matriceAdiacenta[i][j]);
        }
    }

    fclose(f);

    if(DEBUG) {
        afisareGraf(&graf);
    }

    int nod_start = 0;
    int nod_final = nrNoduri - 1; // presupunem ca nodul final este ultimul nod

    int vizitat[MAX_NODURI] = {0};
    int lungimeMAX = 0;
    celMaiLungDrum(&graf, nod_start, vizitat, nod_final, &lungimeMAX, 0);

    printf("Lungimea maxima a drumului de la nodul %d la nodul %d este: %d\n", nod_start, nod_final, lungimeMAX);


    return 0;
}