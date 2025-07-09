#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PERMISIUNI 20
#define DEBUG 1

typedef struct Graf{
    int nr_noduri; // nr permisiuni active
    int is_risk;  // cate permisiuni trb sa aiba un angajat pentru a fi considerat risc
    int matrice_adiacenta[MAX_PERMISIUNI][MAX_PERMISIUNI];
}Graf_T;

void init_graf(Graf_T *graf){
    graf->nr_noduri = 0;
    graf->is_risk = 0;
    memset(graf->matrice_adiacenta, 0, sizeof(graf->matrice_adiacenta));
}

void afisare_graf(Graf_T *graf){
    printf("Nr noduri: %d\n", graf->nr_noduri);
    printf("Is risk: %d\n", graf->is_risk);
    printf("Matricea de adiacenta:\n");
    for(int i = 0; i < graf->nr_noduri; i++){
        for(int j = 0; j < graf->nr_noduri; j++){
            printf("%d ", graf->matrice_adiacenta[i][j]);
        }
        printf("\n");
    }
}

void warshall(Graf_T *graf){
    // prima cerinta a problemei
    int W[MAX_PERMISIUNI][MAX_PERMISIUNI];

    // initializare matrice W
    for(int i = 0; i < graf->nr_noduri; i++){
        for(int j = 0; j < graf->nr_noduri; j++){
            W[i][j] = (graf->matrice_adiacenta[i][j] == 0 ? 0 : 1);
        }
    }

    // algoritmul lui Warshall -> legaturi indirecte
    for(int k = 0; k < graf->nr_noduri; k++){
        for(int i = 0; i < graf->nr_noduri; i++){
            for(int j = 0; j < graf->nr_noduri; j++){
                if(W[i][j] == 0){
                    W[i][j] = W[i][k] && W[k][j];
                }
            }
        }
    }

    if(DEBUG){
        printf("Matricea W:\n");
        for(int i = 0; i < graf->nr_noduri; i++){
            for(int j = 0; j < graf->nr_noduri; j++){
                printf("%d ", W[i][j]);
            }
            printf("\n");
        }
    }

    // linia i -> permisiunea i
    // coloana j -> permisiunea j care depinde de permisiunea i

    int permisiuniMAX = 0;
    int index = -1;
    int contor = 0;

    for(int i = 0; i < graf->nr_noduri; i++){
        contor = 0;

        // sau W[j][i] == 1
        for(int j = 0; j < graf->nr_noduri; j++){
            if(W[i][j] == 1){
                contor++;
            }
        }

        if(contor > permisiuniMAX){
            permisiuniMAX = contor;
            index = i;
        }
    }

    printf("%d\n\n", index);

    // a doua cerinta a problemei
    for(int i = 0; i < graf->nr_noduri; i++){
        contor = 0;

        for(int j = 0; j < graf->nr_noduri; j++){
            if(W[i][j] == 1){
                contor++;
            }
        }

        if(contor >= graf->is_risk){
            printf("%d ", i);
        }
    }

    printf("\n");


}

int main(int argc, char **argv){
    if(argc != 2){
        perror("Utilizare incorecta: ./p <file_nume>\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");

    if(f == NULL){
        perror("Eroare la deschiderea fisierului\n");
        return 1;
    }

    Graf_T graf;
    init_graf(&graf);

    fscanf(f, "%d", &graf.is_risk);
    fscanf(f, "%d", &graf.nr_noduri);

    for(int i = 0; i < graf.nr_noduri; i++){
        for(int j = 0; j < graf.nr_noduri; j++){
            fscanf(f, "%d", &graf.matrice_adiacenta[i][j]);
        }
    }

    if(DEBUG){
        afisare_graf(&graf);
    }

    fclose(f);

    warshall(&graf);

    return 0;
}