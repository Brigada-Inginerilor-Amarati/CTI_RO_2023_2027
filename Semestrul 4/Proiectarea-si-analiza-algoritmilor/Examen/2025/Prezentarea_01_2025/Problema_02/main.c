#include <stdio.h>
#include <stdlib.h>

#define MAX_NODURI 20
#define DEBUG 0

typedef struct ArboreBinar{
    int index[MAX_NODURI]; // indexul nodului in arbore
    int parinte[MAX_NODURI]; // parintele nodului
    int nr_noduri; // numarul de noduri in arbore
}ArboreBinar_T;

void init_arbore(ArboreBinar_T *arbore, int nr_noduri){
    arbore->nr_noduri = nr_noduri;
    for(int i = 0; i < nr_noduri; i++){
        arbore->index[i] = -1; // initializare index
        arbore->parinte[i] = -1; // initializare parinte
    }
}

int pas_max;

void parcurgere_adancime(ArboreBinar_T *arbore, int nod_curent, int *pas){
    for(int i = 0; i < arbore->nr_noduri; i++){
        if(arbore->parinte[i] == nod_curent){

            if(DEBUG){
                printf("Parcurgem nodul %d, pasul curent: %d\n", nod_curent, *pas);
            }

            // inseamna ca am coborat in arbore
            *pas = *pas + 1; 

            if(*pas > pas_max){
                pas_max = *pas; // actualizam pasul maxim
            }

            parcurgere_adancime(arbore, arbore->index[i], pas); // mergem la fiul curent

            *pas = *pas - 1; // revenim la pasul anterior
        }
    }
}

int main(int argc, char **argv){
    if(argc != 3){
        printf("Usage: %s <arb> <pacient>\n", argv[0]);
        return 1;
    }

    FILE *f_arbore = fopen(argv[1], "r");
    if(!f_arbore){
        perror("Could not open arbore file\n");
        return 1;
    }

    int nr_noduri;
    fscanf(f_arbore, "%d", &nr_noduri);
    ArboreBinar_T arbore;

    init_arbore(&arbore, nr_noduri);

    int parinte;

    // 0 este radacina
    for(int i = 0; i < nr_noduri; i++){
        fscanf(f_arbore, "%d", &parinte);
        arbore.index[i] = i + 1; // indexul nodului
        arbore.parinte[i] = parinte; // parintele nodului
    }

    fclose(f_arbore);

    FILE *f_pacient = fopen(argv[2], "r");
    if(!f_pacient){
        perror("Could not open pacient file\n");
        return 1;
    }

    int raspuns;
    int nod_curent = 1; // incepem de la radacina
    int este_diagnostic = 0;

    // cat timp avem ce citi din fisierul pacient
    // 0 -> inseamna NU -> stanga
    // 1 -> inseamna DA -> dreapta
    while(fscanf(f_pacient, "%d", &raspuns) == 1){
        int aux = 0;
        int aux2 = 0;

        if(raspuns == 0){
            for(int i = 0; i < arbore.nr_noduri; i++){
                if(arbore.parinte[i] == nod_curent){
                    nod_curent = arbore.index[i]; // mergem la stanga
                    aux = 1; // am gasit fiul stang
                    break; // iesim din bucla pt ca am gasit fiul stang
                }
            }
            
            if(aux == 0){
                este_diagnostic = 1; // nu am gasit fiul stang, deci nu mai avem unde sa mergem
            }
        }
        else{
            for(int i = 0; i< arbore.nr_noduri; i++){
                if(arbore.parinte[i] == nod_curent){
                    aux2 ++;
                }

                if(aux2 == 2){
                    nod_curent = arbore.index[i]; // asta este fiul drept
                    break; // iesim din bucla pt ca am gasit fiul drept
                }
            }

            if(aux2 != 2){
                este_diagnostic = 1; // nu am gasit fiul drept, deci nu mai avem unde sa mergem
            }
        }
    }

    fclose(f_pacient);

    int nr_intrebari_ramase_pana_la_diagnostic = 0;

    if(este_diagnostic == 1){
        printf("0");
    }
    else{
        parcurgere_adancime(&arbore, nod_curent, &nr_intrebari_ramase_pana_la_diagnostic);
        printf("%d\n\n", pas_max);
    }

    int pas = 0;
    pas_max = 0;
    parcurgere_adancime(&arbore, 1, &pas); // pornim de la radacina
    printf("%d \n", pas_max);

    return 0;
}