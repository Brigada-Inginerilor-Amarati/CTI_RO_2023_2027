#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1
#define MAX_NODURI 100

typedef struct ArboreGeneralizat{
    int numarAngajati;
    int ID[MAX_NODURI]; // index ul angajatilor-> generat unic
    char nume[MAX_NODURI][50]; // numele angajatilor
    int sef[MAX_NODURI]; // sef[i] = j -> angajatul i are ca sef angajatul j -> parintele basic
}ArboreGeneralizat_T;

typedef struct ArboreBinar{
    int id[MAX_NODURI]; // ID-ul angajatului
    char nume[MAX_NODURI][50]; // Numele angajatului
    int stanga[MAX_NODURI]; // Indexul fiului stang
    int dreapta[MAX_NODURI]; // Indexul fiului drept
}ArboreBinar_T;

void initArbore(ArboreGeneralizat_T* arbore){
    arbore->numarAngajati = 0;

    for(int i = 0; i < MAX_NODURI; i++){
        arbore->ID[i] = -1;
        strcpy(arbore->nume[i], "");
        arbore->sef[i] = -1;
    }
}

int primFiu(ArboreGeneralizat_T *arbore, int index){
    for(int i = 0; i < arbore->numarAngajati; i++){
        if(arbore->sef[i] == index){
            return i; // gasim primul fiu al nodului index
        }
    }

    return -1; // nu exista fii pentru nodul index
}

int frateDreapta(ArboreGeneralizat_T *arbore, int primFiuIndex){
    for(int i = primFiuIndex + 1; i < arbore->numarAngajati; i++){
        if(arbore->sef[i] == arbore->sef[primFiuIndex]){
           // printf("Fratele drept al angajatului %d este: %d\n", arbore->ID[primFiuIndex], arbore->ID[i]);
            return i; // gasim primul frate drept
        }
    }

    return -1; // nu exista frate drept
}

void preordineArbGeneralizat(ArboreGeneralizat_T*arbore, int index){
    printf("%d ", arbore->ID[index]);

    int fiu = primFiu(arbore, index);

    while(fiu != -1){
        preordineArbGeneralizat(arbore, fiu);
        fiu = frateDreapta(arbore, fiu);
    }
}

void initArboreBinar(ArboreBinar_T* arbore){
    for(int i = 0; i < MAX_NODURI; i++){
        arbore->id[i] = -1;
        strcpy(arbore->nume[i], "");
        arbore->stanga[i] = -1;
        arbore->dreapta[i] = -1;
    }
}


void decideStangaDreapta(ArboreGeneralizat_T* arbore, int index, int *stanga, int* dreapta){
    *stanga = primFiu(arbore, index);

    *dreapta = frateDreapta(arbore, index);
}

void adaugaNod(ArboreBinar_T* arbore, int id, char* nume, int stanga, int dreapta){
    arbore->id[id - 1] = id; // ID-ul angajatului
    strcpy(arbore->nume[id - 1], nume); // Numele
    arbore->stanga[id - 1] = stanga; // Indexul fiului stang
    arbore->dreapta[id - 1] = dreapta; // Indexul fiului drept
}

void preordineArboreBinar(ArboreBinar_T*arbore, int index){
    if(index == -1){
        return; // nodul este null
    }

    printf("%d ", arbore->id[index]);

    preordineArboreBinar(arbore, arbore->stanga[index]);
    preordineArboreBinar(arbore, arbore->dreapta[index]);
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Utilizare: %s <fisier_intrare>\n", argv[1]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if(fin == NULL){
        printf("Eroare la deschiderea fisierului %s\n", argv[1]);
        return 1;
    }

    ArboreGeneralizat_T arbore;
    initArbore(&arbore);

    fscanf(fin, "%d", &arbore.numarAngajati);

    int parinte = -1;
    char nume[50];
    int id = 0;

    for (int i = 0; i < arbore.numarAngajati; i++) {
        fscanf(fin, "%d %s", &parinte, nume);

        if (DEBUG) {
            printf("Citit angajat: %s, parinte: %d\n", nume, parinte);
        }

        arbore.ID[i] = ++id;
        strcpy(arbore.nume[i], nume);

        if (parinte == -1) {
            arbore.sef[i] = -1; // Radacina
        } else {
            arbore.sef[i] = parinte - 1; // Ajustez indexul pentru ca ID-urile incep de la 1
        }
    }

    if(DEBUG){
        for(int i = 0; i < arbore.numarAngajati; i++){
            printf("Angajat ID: %d, Nume: %s, Sef: %d\n", arbore.ID[i], arbore.nume[i], arbore.sef[i]);
        }
        int primFiuIndex = primFiu(&arbore, 0);
        int frateIndex = frateDreapta(&arbore, primFiuIndex);

        printf("Primul fiu al radacinii: %d\n", arbore.ID[primFiuIndex]);
        printf("Fratele drept al primului fiu: %d\n", arbore.ID[frateIndex]);
    }

    printf("Parcurgere in preordine:\n");
    preordineArbGeneralizat(&arbore, 0);
    printf("\n");

    ArboreBinar_T arboreBinar;
    initArboreBinar(&arboreBinar);          
    int stanga, dreapta;
    decideStangaDreapta(&arbore, 0, &stanga, &dreapta);
    adaugaNod(&arboreBinar, arbore.ID[0], arbore.nume[0], stanga, dreapta);

    int index = 0;
    while (index < arbore.numarAngajati) {
        int fiuStanga, fiuDreapta;
        decideStangaDreapta(&arbore, index, &fiuStanga, &fiuDreapta);

        if (fiuStanga != -1) {
            adaugaNod(&arboreBinar, arbore.ID[fiuStanga], arbore.nume[fiuStanga], -1, -1);
            arboreBinar.stanga[index] = fiuStanga;
        }

        if (fiuDreapta != -1) {
            adaugaNod(&arboreBinar, arbore.ID[fiuDreapta], arbore.nume[fiuDreapta], -1, -1);
            arboreBinar.dreapta[index] = fiuDreapta;
        }
        
        index++;
    }   

    printf("Parcurgere in preordine a arborelui binar:\n");
    preordineArboreBinar(&arboreBinar, 0);
    printf("\n");

    return 0;
}