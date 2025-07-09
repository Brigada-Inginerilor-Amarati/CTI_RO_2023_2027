#include <stdio.h>
#include <stdlib.h>

#define MAX_NODURI 100
#define DEBUG 1

typedef struct ArboreBinar{
    int cheie;
    struct ArboreBinar *stanga;
    struct ArboreBinar *dreapta;
}ArboreBinar_T;

ArboreBinar_T* init_nod(int cheie){
    ArboreBinar_T *nod = (ArboreBinar_T*) malloc(sizeof(ArboreBinar_T));

    if(nod == NULL){
        perror("Eroare la alocarea memoriei pentru nod\n");
        return NULL; // caz de tratat ulterior
    }

    nod->cheie = cheie;
    nod->stanga = NULL;
    nod->dreapta = NULL;

    return nod;
}

ArboreBinar_T *inserare(ArboreBinar_T *radacina, int cheie){
    if(radacina == NULL){
        return init_nod(cheie);
    }

    if(cheie < radacina->cheie){
        radacina->stanga = inserare(radacina->stanga, cheie);
    }
    else if(cheie > radacina->cheie){
        radacina->dreapta = inserare(radacina->dreapta, cheie);
    }

    return radacina;
}

void gasireStramosi(ArboreBinar_T *radacina, int cheie, int *stramosi, int *index){
    if(radacina == NULL){
        return;
    }

    if(cheie < radacina->cheie){
        stramosi[(*index)++] = radacina->cheie; // adaugam stramosul in vector
        gasireStramosi(radacina->stanga, cheie, stramosi, index);
    }
    else if(cheie > radacina->cheie){
        stramosi[(*index)++] = radacina->cheie; // adaugam stramosul in vector
        gasireStramosi(radacina->dreapta, cheie, stramosi, index);
    }
    else {
        // am gasit nodul cu cheia cautata
        return;
    }
}

ArboreBinar_T *gasire_Stramos_Comun(ArboreBinar_T *radacina, int cheie1, int cheie2){
    if(radacina == NULL){
        return NULL;
    }

    int stramosi1[MAX_NODURI], stramosi2[MAX_NODURI];
    int index1 = 0, index2 = 0;
    gasireStramosi(radacina, cheie1, stramosi1, &index1);
    gasireStramosi(radacina, cheie2, stramosi2, &index2);

    for(int i = index1 - 1; i >= 0; i--){
        for(int j = index2 - 1; j >= 0; j--){
            if(stramosi1[i] == stramosi2[j]){
                return init_nod(stramosi1[i]); // returnam nodul cu cheia comuna
            }
        }
    }
    
    return NULL; // nu s-a gasit un stramos comun
}

int main(int argc, char **argv){
    if(argc != 2){
        perror("Utilizare: ./main <fisier_input>\n");
        return 1;
    }

    FILE *fisier = fopen(argv[1], "r");
    if(fisier == NULL){
        perror("Eroare la deschiderea fisierului\n");
        return 1;
    }

    ArboreBinar_T *radacina = NULL;
    int cheie;
    while(fscanf(fisier, "%d", &cheie) == 1){
        radacina = inserare(radacina, cheie);
    }   

    fclose(fisier);

    int cheie1, cheie2;
    printf("Introduceti cele doua chei pentru a gasi stramosul comun:\n");
    scanf("%d %d", &cheie1, &cheie2);
    ArboreBinar_T *stramosComun = gasire_Stramos_Comun(radacina, cheie1, cheie2);
    if(stramosComun != NULL){
        printf("Stramosul comun al nodurilor cu cheile %d si %d este: %d\n", cheie1, cheie2, stramosComun->cheie);
        free(stramosComun); // eliberam memoria alocata pentru nodul rezultat
    } else {
        printf("Nu s-a gasit un stramos comun pentru cheile %d si %d.\n", cheie1, cheie2);
    }

    return 0;
}