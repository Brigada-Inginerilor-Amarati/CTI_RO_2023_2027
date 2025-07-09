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

typedef struct Coada{
    int elemente[MAX_NODURI];
    int front;
    int rear;
}Coada_T;

void initCoada(Coada_T *coada){
    memset(coada->elemente, 0, sizeof(coada->elemente));
    coada->front = -1;
    coada->rear = -1;
}

int isEmpty(Coada_T *coada){
    return coada->front == -1;
}

int isFull(Coada_T *coada){
    return coada->rear == MAX_NODURI - 1;
}

void enqueue(Coada_T *coada, int element){
    if(isFull(coada)){
        printf("Coada este plina!\n");
        return;
    }

    if(isEmpty(coada)){
        coada->front = 0;
    }

    coada->rear++;
    coada->elemente[coada->rear] = element;
}

int dequeue(Coada_T *coada){
    if(isEmpty(coada)){
        printf("Coada este goala!\n");
        return -1;
    }

    int element = coada->elemente[coada->front];

    if(coada->front == coada->rear){
        coada->front = -1;
        coada->rear = -1;
    } 
    else {

        for(int i = 0; i < coada->rear; i++){
            coada->elemente[i] = coada->elemente[i + 1];
        }

        coada->rear--; 
    }

    return element;
}

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


void bfs(Graf_T *graf, int start, int *noduriBFS){
    int vizitat[MAX_NODURI] = {0};

    Coada_T coada;
    initCoada(&coada);

    enqueue(&coada, start);
    vizitat[start] = 1;

    int index = 0;

    while(!isEmpty(&coada)){
        int nodCurent = dequeue(&coada);

        noduriBFS[index++] = nodCurent;
        
        if(DEBUG) {
            printf("Vizitam nodul: %d\n", nodCurent + 1);
        }

        for(int i = 0; i < graf->nrNoduri; i++){
            if(graf->matriceAdiacenta[nodCurent][i] != 0 && vizitat[i] == 0){
                enqueue(&coada, i);
                vizitat[i] = 1;
            }
        }
    }
}

void dfs(Graf_T *graf, int nod_start, int *vizitat, int *noduriDFS, int *index){
    vizitat[nod_start] = 1;
    noduriDFS[*index] = nod_start;
    *index = *index + 1;

    if(DEBUG) {
        printf("Vizitam nodul: %d\n", nod_start + 1);
    }

    for(int i = 0; i < graf->nrNoduri; i++){
        if(graf->matriceAdiacenta[nod_start][i] != 0 && vizitat[i] == 0){
            dfs(graf, i, vizitat, noduriDFS, index);
        }
    }
}

int comparaVectori(int *v1, int *v2, int size) {
    for(int i = 0; i < size; i++) {
        if(v1[i] != v2[i]) {
            return 0; // Vectors are not equal
        }
    }
    return 1; // Vectors are equal
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

    for(int i = 0; i < graf.nrNoduri; i++){
        int noduriBFS[MAX_NODURI] = {0};
        int noduriDFS[MAX_NODURI] = {0};
        int vizitat[MAX_NODURI] = {0};
        int indexDFS = 0;
        bfs(&graf, i, noduriBFS);
        dfs(&graf, i, vizitat, noduriDFS, &indexDFS);

        if(comparaVectori(noduriBFS, noduriDFS, graf.nrNoduri)) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
    
    return 0;
}