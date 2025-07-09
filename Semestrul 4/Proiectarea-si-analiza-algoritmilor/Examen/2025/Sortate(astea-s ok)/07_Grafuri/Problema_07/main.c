#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DEBUG 0
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

void dfsComponente(Graf_T* graf, int nod_start, int *vizitat){
    vizitat[nod_start] = 1;

    for(int i = 0; i < graf->nrNoduri; i++){
        if(graf->matriceAdiacenta[nod_start][i] != 0 && vizitat[i] == 0){
            dfsComponente(graf, i, vizitat);
        }
    }
}


int nrComponenteConexe(Graf_T* graf){
    int nrComponente = 0;
    int vizitat[MAX_NODURI] = {0};

    for(int i = 0; i < graf->nrNoduri; i++){
        if(vizitat[i] == 0){
            nrComponente++;
            dfsComponente(graf, i, vizitat);
        }
    }

    return nrComponente;
}

void grafciclic(Graf_T* graf, int nod_start, int nod_final, int *vizitat, int *contor){
    if(nod_start == nod_final){
        *contor = *contor + 1;
        return;
    }

    vizitat[nod_start] = 1;

    for(int i = 0; i < graf->nrNoduri; i++){
        if(graf->matriceAdiacenta[nod_start][i] != 0 && vizitat[i] == 0){
            grafciclic(graf, i, nod_final, vizitat, contor);
        }
    }

    vizitat[nod_start] = 0; // backtrack
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

    int nrNoduri, nrMuchii;
    if(fscanf(f, "%d %d", &nrNoduri, &nrMuchii) != 2) {
        fprintf(stderr, "Error reading number of nodes and edges\n");
        fclose(f);
        return 1;
    }

    graf.nrNoduri = nrNoduri;
    graf.nrMuchii = nrMuchii;

    for(int i = 0; i < nrMuchii; i++){
        int nod1, nod2;

        if(fscanf(f, "%d %d", &nod1, &nod2) != 2) {
            fprintf(stderr, "Error reading edge %d\n", i + 1);
            fclose(f);
            return 1;
        }

        graf.matriceAdiacenta[nod1 - 1][nod2 - 1] = 1;
        graf.matriceAdiacenta[nod2 - 1][nod1 - 1] = 1; // assuming undirected graph
    }

    if(DEBUG) {
        afisareGraf(&graf);
    }

    fclose(f);

    int componenteConexe = nrComponenteConexe(&graf);
    printf("Numarul de componente conexe: %d\n", componenteConexe);

    int nod_start, nod_final;
    int contor = 0;
    int flag = 0;
    // verificam tot graful pentru cicluri
    for(nod_start = 0; nod_start < graf.nrNoduri; nod_start++) {
        for(nod_final = 0; nod_final < graf.nrNoduri; nod_final++) {
            if(nod_start != nod_final) {
                int vizitat[MAX_NODURI] = {0};
                contor = 0;
                grafciclic(&graf, nod_start, nod_final, vizitat, &contor);
                if(contor > 1){
                    flag = 1;
                   // printf("1\n");
                    break;
                }

            }
        }
    }   

    if(flag == 0) {
        printf("0\n");
    }
    else{
        printf("1\n");
    }



    return 0;
}