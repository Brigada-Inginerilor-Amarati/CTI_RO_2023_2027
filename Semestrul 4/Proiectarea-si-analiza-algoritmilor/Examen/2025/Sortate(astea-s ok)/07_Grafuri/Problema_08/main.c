#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DEBUG 1
#define MAX_NODURI 100

typedef struct Graf {
    int nrNoduri;
    int nrMuchii;
    int matriceAdiacenta[MAX_NODURI][MAX_NODURI];
} Graf_T;

void initGraf(Graf_T *graf) {
    graf->nrNoduri = 0;
    graf->nrMuchii = 0;
    memset(graf->matriceAdiacenta, 0, sizeof(graf->matriceAdiacenta));
}

void afisareGraf(Graf_T *graf) {
    printf("Numar noduri: %d, Numar muchii: %d\n", graf->nrNoduri, graf->nrMuchii);
    for(int i = 0; i < graf->nrNoduri; i++) {
        for(int j = 0; j < graf->nrNoduri; j++) {
            printf("%d ", graf->matriceAdiacenta[i][j]);
        }
        printf("\n");
    }
}

void dijkstra(Graf_T *graf, int start_nod){
    int vizitat[MAX_NODURI] = {0};

    int costArray[MAX_NODURI] = {0};

    int parinte[MAX_NODURI] = {0};

    for(int i = 0; i < graf->nrNoduri; i++){
        costArray[i] = INT_MAX;
        parinte[i] = -1;
    }

    costArray[start_nod] = 0;
    vizitat[start_nod] = 1;

    int nod_curent = start_nod;

    for(int pas = 0; pas < graf->nrNoduri - 1; pas++){
        int min_cost = INT_MAX;

        // actualizare costuri
        for(int i = 0; i < graf->nrNoduri; i++){
            if(graf->matriceAdiacenta[nod_curent][i] != 0 && vizitat[i] == 0){
                int cost_nou = costArray[nod_curent] + graf->matriceAdiacenta[nod_curent][i];

                if(cost_nou < costArray[i]){
                    costArray[i] = cost_nou;
                    parinte[i] = nod_curent;
                }
            }
        }

        // gasire nod cu cost minim
        for(int i = 0; i < graf->nrNoduri; i++){
            if(costArray[i] < min_cost && vizitat[i] == 0){
                min_cost = costArray[i];
                nod_curent = i;
            }
        }

        // marcare nod curent ca vizitat
        vizitat[nod_curent] = 1;
    }

    // Afisare rezultate
    printf("Costuri minime de la nodul %d:\n", start_nod + 1);
    for(int i = 0; i < graf->nrNoduri; i++){
        if(i == start_nod){
            continue; // Nu afisam costul de la nodul start la el insusi
        }
        if(costArray[i] == INT_MAX){
            printf("0 ");
        } 
        else {
            printf("%d ", costArray[i]);    
        }
    }

    printf("\nExplicatie cu reconstructie:\n");

    for(int i = 0; i < graf->nrNoduri; i++){
        if(i == start_nod){
            continue; // Nu afisam drumul de la nodul start la el insusi
        }

        if(costArray[i] == INT_MAX){
            printf("0 - nu exista drum de la %d la %d \n", start_nod + 1, i + 1);
            continue; // Nu exista drum
        }

        printf("%d - distanta minima de la %d la %d( ", costArray[i], start_nod + 1, i + 1);

        int drum[MAX_NODURI];
        int drumIndex = 0;

        for(int j = i; j != -1; j = parinte[j]){
            drum[drumIndex++] = j + 1; // +1 pentru a afisa nodurile incepand de la 1
        }

        // Afisare drum inversat
        for(int j = drumIndex - 1; j >= 0; j--){
            printf("%d", drum[j]);

            if(j > 0) {
                printf(" -> ");
            }
        }
        printf(")\n");
    }
}


int main(int argc, char **argv){
    if(argc != 2){
        perror("Usage: <input_file>\n");
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if(!fin){
        perror("Error opening file\n");
        return 1;
    }

    Graf_T graf;
    initGraf(&graf);

    int nrNoduri, nrMuchii;
    if(fscanf(fin, "%d %d", &nrNoduri, &nrMuchii) != 2){
        fprintf(stderr, "Error reading number of nodes and edges\n");
        fclose(fin);
        return 1;
    }

    graf.nrNoduri = nrNoduri;
    graf.nrMuchii = nrMuchii;

    for(int i = 0; i < nrMuchii; i++){
        int nod1, nod2, pondere;

        fscanf(fin, "%d %d %d", &nod1, &nod2, &pondere);

        // e orientat
        graf.matriceAdiacenta[nod1 - 1][nod2 - 1] = pondere;
    }

    fclose(fin);

    if(DEBUG) {
        afisareGraf(&graf);
    }

    int start_nod = 0; // Nodul de start este 0 (primul nod)
    dijkstra(&graf, start_nod);


    return 0;
}