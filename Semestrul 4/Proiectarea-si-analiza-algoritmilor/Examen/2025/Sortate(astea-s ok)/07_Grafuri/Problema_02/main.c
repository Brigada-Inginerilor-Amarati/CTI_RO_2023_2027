#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODURI 100
#define DEBUG 1

typedef struct Graf{
    int nr_noduri;
    int matrice_adiacenta[MAX_NODURI][MAX_NODURI];
}Graf_T;


void init_graf(Graf_T *graf){
    graf->nr_noduri = 0;
    memset(graf->matrice_adiacenta, 0, sizeof(graf->matrice_adiacenta));
}

void afisare_graf(const Graf_T *graf){
    printf("Numar de noduri: %d\n", graf->nr_noduri);
    printf("Matricea de adiacenta:\n");
    for(int i = 0; i < graf->nr_noduri; i++){
        for(int j = 0; j < graf->nr_noduri; j++){
            printf("%d ", graf->matrice_adiacenta[i][j]);
        }
        printf("\n");
    }
}

void dfs(Graf_T *graf, int start, int lungimeCurenta, int *vizitat, int *maxLungime, int final){
    vizitat[start] = 1;

    for(int i = 0; i < graf->nr_noduri; i++){
        if(graf->matrice_adiacenta[start][i] == 1 && vizitat[i] == 1 && i == final){
            if(DEBUG){
                printf("1. Am gasit un ciclu de la nodul %d inapoi la nodul %d, lungime curenta: %d\n", start, i, lungimeCurenta);
            }
            lungimeCurenta++;
            if(lungimeCurenta > *maxLungime){
                *maxLungime = lungimeCurenta;
            }
            lungimeCurenta--;
        }

        else if(graf->matrice_adiacenta[start][i] == 1 && vizitat[i] == 0){
            if(DEBUG){
                printf("Vizitam nodul %d din nodul %d, lungime curenta: %d\n", i, start, lungimeCurenta);
              }
            lungimeCurenta++;
            dfs(graf, i, lungimeCurenta, vizitat, maxLungime, final);
            lungimeCurenta--;
        }
    }
    
    vizitat[start] = 0; // Backtrack
    // if(lungimeCurenta > *maxLungime){
    //     *maxLungime = lungimeCurenta;
    // }
}

void gasesteCelMaiLungCiclu(Graf_T *graf){
    int vizitat[MAX_NODURI] = {0};
    int maxLungime = 0;

    for(int i = 0; i < graf->nr_noduri; i++){
        memset(vizitat, 0, sizeof(vizitat));
        int lungimeCurenta = 0;
        dfs(graf, i, lungimeCurenta, vizitat, &maxLungime, i);
    }

    printf("Lungimea maxima a unui ciclu este: %d\n", maxLungime);
}


int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if(!f){
        perror("Could not open input file");
        return 1;
    }

    Graf_T graf;
    init_graf(&graf);

    int nr_noduri;
    if(fscanf(f, "%d", &nr_noduri) != 1 || nr_noduri < 1 || nr_noduri > MAX_NODURI){
        fprintf(stderr, "Invalid number of nodes\n");
        fclose(f);
        return 1;
    }

    graf.nr_noduri = nr_noduri;

    for(int i = 0; i < nr_noduri; i++){
        for(int j = 0; j < nr_noduri; j++){
            if(fscanf(f, "%d", &graf.matrice_adiacenta[i][j]) != 1){
                fprintf(stderr, "Invalid adjacency matrix input\n");
                fclose(f);
                return 1;
            }
        }
    }

    fclose(f);

    if(DEBUG){
        afisare_graf(&graf);
    }

    gasesteCelMaiLungCiclu(&graf);


    return 0;
}