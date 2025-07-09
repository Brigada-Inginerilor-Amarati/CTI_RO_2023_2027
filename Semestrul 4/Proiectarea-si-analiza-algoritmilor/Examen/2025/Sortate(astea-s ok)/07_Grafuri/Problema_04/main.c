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

int cunoscutDeToti(Graf_T *graf){
    int index = -1;

    for(int i = 0; i < graf->nrNoduri; i++){
        int countLine = 0;
        int countColumn = 0;
        for(int j = 0; j < graf->nrNoduri; j++){
            if(graf->matriceAdiacenta[i][j] == 0 && i != j){
                countLine++;
            }  
            if(graf->matriceAdiacenta[j][i] != 0 && i != j){
                countColumn++;
            }
        }

        if(countLine == graf->nrNoduri - 1 && countColumn == graf->nrNoduri - 1){
            index = i;
            break;
        }
    }

    return index;
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

    int index = cunoscutDeToti(&graf);
    if(index != -1) {
        printf("Nodul cunoscut de toti este: %d\n", index);
    } else {
        printf("Nu exista un nod cunoscut de toti.\n");
    }

    return 0;
}