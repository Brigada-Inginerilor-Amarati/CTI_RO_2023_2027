#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// ---------------
// DEFINES
// ---------------

#define DEBUG 1
#define MAX_NODES 100
#define MAX_NAME_LENGTH 50

// ---------------
// STRUCTURES
// ---------------

typedef enum Gen{
    F = 0,
    M = 1
}Gen_T;

typedef struct Utilizator{
    char nume[MAX_NAME_LENGTH];
    Gen_T gen;
    int ID;
    char localitate[MAX_NAME_LENGTH];
}Utilizator_T;

typedef struct Graf{
    int numar_noduri;
    int matrice_adiacenta[MAX_NODES][MAX_NODES];
    Utilizator_T utilizatori[MAX_NODES];
}Graf_T;

typedef struct Coada{
    int elemente[MAX_NODES];
    int front;
    int rear;
}Coada_T;


// ---------------
// FUNCTIONS
// ---------------

/**
 * Queue functions
*/

void initCoada(Coada_T *coada){
    memset(coada->elemente, 0, sizeof(coada->elemente));
    coada->front = -1;
    coada->rear = -1;
}

int isEmpty(Coada_T *coada){
    return coada->front == -1;
}

int isFull(Coada_T *coada){
    return coada->rear == MAX_NODES - 1;
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

/**
 * Graph functions
*/

void initGraf(Graf_T *graf){
    graf->numar_noduri = 0;
    memset(graf->matrice_adiacenta, 0, sizeof(graf->matrice_adiacenta));
    memset(graf->utilizatori, 0, sizeof(graf->utilizatori));
}

void afisareGraf(Graf_T *graf){
    printf("Numar noduri: %d\n", graf->numar_noduri);
    printf("Matricea de adiacenta:\n");
    for(int i = 0; i < graf->numar_noduri; i++){
        for(int j = 0; j < graf->numar_noduri; j++){
            printf("%d ", graf->matrice_adiacenta[i][j]);
        }
        printf("\n");
    }

    printf("Utilizatori:\n");
    for(int i = 0; i < graf->numar_noduri; i++){
        printf("Nume: %s, Gen: %d, ID: %d, Localitate: %s\n", 
               graf->utilizatori[i].nume, 
               graf->utilizatori[i].gen, 
               graf->utilizatori[i].ID, 
               graf->utilizatori[i].localitate);
    }
}

// primii 3 prieteni ai prietenilor unui utilizator
void bfs(Graf_T *graf, int start_node){
    int vizitat[MAX_NODES] = {0};

    Coada_T coada;
    initCoada(&coada);

    enqueue(&coada, start_node);
    vizitat[start_node] = 1;

    while(isEmpty(&coada) == 0){
        int current_node = dequeue(&coada);

        printf("Vizitam nodul %d: %s\n", current_node, graf->utilizatori[current_node].nume);

        for(int i = 0; i < graf->numar_noduri; i++){
            if(graf->matrice_adiacenta[current_node][i] == 1 && !vizitat[i]){
                vizitat[i] = 1;
                enqueue(&coada, i);
            }
        }
    }
}

void primii3Prieteni(Graf_T *graf, int start_node){
    int vizitat[MAX_NODES] = {0};

    Coada_T coada;
    initCoada(&coada);

    enqueue(&coada, start_node);
    vizitat[start_node] = 1;

    int pas = 1;
    int contor = 0;

    while(isEmpty(&coada) == 0){
        int current_node = dequeue(&coada);

        //printf("Vizitam nodul %d: %s\n", current_node, graf->utilizatori[current_node].nume);

        pas++;

        for(int i = 0; i < graf->numar_noduri; i++){
            if(graf->matrice_adiacenta[current_node][i] == 1 && !vizitat[i]){
                vizitat[i] = 1;
                enqueue(&coada, i);
                
                if(pas > 2){
                    if(contor < 3){
                        printf("Prietenul %d al nodului %d: %s\n", contor + 1, current_node, graf->utilizatori[i].nume);
                        contor++;
                    } else {
                        break; // am gasit primii 3 prieteni
                    }
                }
            }
        }
    }
}

int main(int argc, char **argv){
    if(argc !=  2){
        printf("Utilizare: %s <fisier_input>\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if(!fin){
        printf("Eroare la deschiderea fisierului %s\n", argv[1]);
        return 1;
    }

    Graf_T graf;
    initGraf(&graf);

    int numar_utilizatori;
    fscanf(fin, "%d", &numar_utilizatori);
    graf.numar_noduri = numar_utilizatori;

    // citim matricea de adiacenta
    for(int i = 0; i < numar_utilizatori; i++){
        for(int j = 0; j < numar_utilizatori; j++){
            fscanf(fin, "%d", &graf.matrice_adiacenta[i][j]);
        }
    }

    // citim informatiile despre utilizatori
    for(int i = 0; i < numar_utilizatori; i++){
        int gen;
        fscanf(fin, "%s %d %d %s", graf.utilizatori[i].nume, &gen, &graf.utilizatori[i].ID, graf.utilizatori[i].localitate);
        graf.utilizatori[i].gen = (Gen_T)gen;
    }

    // afisam graful
    afisareGraf(&graf);

    // parcurgem graful in latime de la nodul 0
    printf("Parcurgere in latime de la nodul 0:\n");
    bfs(&graf, 0);

    // afisam primii 3 prieteni ai nodului 0
    printf("Primii 3 prieteni ai nodului 0:\n");
    primii3Prieteni(&graf, 0);

    printf("Primii 3 prieteni ai nodului 4\n");
    primii3Prieteni(&graf, 4);

    fclose(fin);


    return 0;
}
