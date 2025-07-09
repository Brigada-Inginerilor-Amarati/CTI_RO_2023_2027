#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DEBUG 1
#define MAX_NODURI 100

typedef struct Graf {
    int nrNoduri;
    int matriceAdiacenta[MAX_NODURI][MAX_NODURI];
} Graf_T;

void initGraf(Graf_T *graf) {
    graf->nrNoduri = 0;
    memset(graf->matriceAdiacenta, 0, sizeof(graf->matriceAdiacenta));
}

void legaturiDirecteMAX(Graf_T *graf, int *indexi, int *max){
    int index = 0;
    int valoriLegaturi[MAX_NODURI] = {0};
    for(int i = 0; i < graf->nrNoduri; i++){
        int count = 0;
        for(int j = 0; j < graf->nrNoduri; j++){
            if(graf->matriceAdiacenta[i][j] != 0){
                count++;
            }
        }
        valoriLegaturi[i] = count;

        if(*max < valoriLegaturi[i]){
            *max = valoriLegaturi[i];
        }
    }

    for(int i = 0; i < graf->nrNoduri; i++){
        if(valoriLegaturi[i] == *max){
            indexi[index++] = i;
        }
    }

}

void primAlg(Graf_T *graf, int start_nod, int *noduri){
    int vizitat[MAX_NODURI] = {0};

    int totalCost = 0;

    vizitat[start_nod] = 1;

    int index = 0;

    // noduri[index++] = start_nod;

    for(int i = 1; i < graf->nrNoduri; i++){
        int minCost = INT_MAX;
        int u = -1;
        int v = -1;

        // for pt multimea U, noduri vizitate
        for(int j = 0; j < graf->nrNoduri; j++){
            if(vizitat[j] == 1){
                // for pt multimea V, noduri nevizitate
                for(int k = 0; k < graf->nrNoduri; k++){
                    if(graf->matriceAdiacenta[j][k] != 0 && vizitat[k] == 0){
                        // gasim muchia cu costul minim
                        if(graf->matriceAdiacenta[j][k] < minCost){
                            minCost = graf->matriceAdiacenta[j][k];
                            u = j;
                            v = k;
                        }
                    } 
                }
            }
        }

        if(u != -1 && v != -1){
            vizitat[v] = 1;
            noduri[index++] = u; // adaugam nodul de start
            noduri[index++] = v;
            totalCost += minCost;
            if(DEBUG) {
                printf("Adaugam muchia (%d, %d) cu costul %d\n", u, v, minCost);
            }
        }
        else{
            if(DEBUG) {
                printf("Nu mai exista muchii de adaugat.\n");
            }
            break;
        }
    }
    
    printf("Cost total al arborelui acoperitor: %d\n", totalCost);

    if(DEBUG) {
        printf("Noduri in arborele acoperitor: ");
        for(int i = 0; i < index; i++) {
            printf("%d ", noduri[i]);
        }
        printf("\n");
    }
}

void KruskalAlg(Graf_T *graf, int *noduri){
    int S[MAX_NODURI] = {0};

    int totalCost = 0;
    int index = 0;

    for(int i = 0; i < graf->nrNoduri; i++){
        S[i] = i; // initializare fiecare nod in propriul set
    }

    for(int i = 0; i < graf->nrNoduri - 1; i++){
        int minCost = INT_MAX;
        int u = -1;
        int v = -1;

        for(int j = 0; j < graf->nrNoduri; j++){
            for(int k = 0; k < graf->nrNoduri; k++){
                if(graf->matriceAdiacenta[j][k] != 0 && S[j] != S[k]){
                    if(graf->matriceAdiacenta[j][k] < minCost){
                        minCost = graf->matriceAdiacenta[j][k];
                        u = j;
                        v = k;
                    }
                }
            }
        }

        for(int j = 0; j < graf->nrNoduri; j++){
            if(S[j] == S[v]){
                S[j] = S[u]; // unesc cele doua noduri
            }
        }

        if(u != -1 && v != -1){
            totalCost += minCost;
            noduri[index++] = u;
            noduri[index++] = v;
            if(DEBUG) {
                printf("Adaugam muchia (%d, %d) cu costul %d\n", u, v, minCost);
            }   
        }
    }

    printf("Cost total al arborelui acoperitor (Kruskal): %d\n", totalCost);
    if(DEBUG) {
        printf("Noduri in arborele acoperitor (Kruskal): ");
        for(int i = 0; i < index; i++) {
            printf("%d ", noduri[i]);
        }
        printf("\n");
    }
}

int verificaArbori(int *arb1, int *arb2, int size) {
    for(int i = 0; i < size; i++) {
        if(arb1[i] != arb2[i]) {
            return 0; // arborii nu sunt identici
        }
    }
    return 1; // arborii sunt identici
}


int main(int argc, char **argv){
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if(!f) {
        perror("Error opening file\n");
        return 1;
    }

    Graf_T graf;
    initGraf(&graf);

    fscanf(f, "%d", &graf.nrNoduri);
    for(int i = 0; i < graf.nrNoduri; i++) {
        for(int j = 0; j < graf.nrNoduri; j++) {
            fscanf(f, "%d", &graf.matriceAdiacenta[i][j]);
        }
    }   

    fclose(f);

    int indexi[MAX_NODURI] = {0};
    int max = 0;
    legaturiDirecteMAX(&graf, indexi, &max);
    printf("Noduri cu legaturi directe maxime (%d): ", max);
    for(int i = 0; i < graf.nrNoduri; i++) {
        if(indexi[i] != 0) {
            printf("%d ", indexi[i]);
        }
    }
    printf("\n");

    int noduri[MAX_NODURI] = {0};
    primAlg(&graf, 0, noduri);

    int noduriKruskal[MAX_NODURI] = {0};
    KruskalAlg(&graf, noduriKruskal);   

    if(verificaArbori(noduri, noduriKruskal, graf.nrNoduri * 2)) {
        printf("Arborii acoperitori obtinuti prin Prim si Kruskal sunt identici.\n");
    } else {
        printf("Arborii acoperitori obtinuti prin Prim si Kruskal NU sunt identici.\n");
    }
    
    return 0;
}