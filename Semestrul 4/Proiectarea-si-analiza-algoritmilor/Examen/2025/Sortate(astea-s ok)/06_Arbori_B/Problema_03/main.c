#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * @def DEFINES
*/

#define DEBUG 1

// asta este ordinul pentru arborele B
#define N 2 

// asta este numarul maxim de elemente de pe o pagina
#define NN (2 * N) 

/**
 * @def STRUCTURES 
*/

typedef struct Nod{
    // date din cerinta
    char sir_caractere[30];
    // structura care exista
    struct Pagina *pagina; // pointer catre subarbore
    int numar_elemente;
}Nod_T;

// asta este arborele in sine
typedef struct Pagina{
    int numar_chei;
    struct Pagina *parinte; // pointer catre pagina parinte
    Nod_T chei[NN + 1]; // vectori de noduri
}Pagina_T;

int nr_pagini_scindate = 0;
int inaltimea_arborelui = 0;

/**
 * @def FUNCTIONS
*/

/**
 * @brief Functie pentru inserare 
*/

Nod_T aux_inserare;

Pagina_T* insereaza(Pagina_T *pagina, char sir_caractere[30], Nod_T* nod){
    int i, s, d, mij;
    Pagina_T* q, *r;

    if(nod == NULL){
        strcpy(aux_inserare.sir_caractere, sir_caractere);
        aux_inserare.pagina = NULL;
        aux_inserare.numar_elemente = 1;
    }
    else{
        aux_inserare = *nod;
    }

    // daca nu exista radacina, atunci se creeaza una noua
    if(pagina == NULL){
        pagina = (Pagina_T*) calloc(sizeof(Pagina_T), 1);

        pagina->chei[++pagina->numar_chei] = aux_inserare;

        return pagina;
    }

    // se cauta binar pozitia cheii x in pagina curenta
    s = 1;
    d = pagina->numar_chei;

    while(s <= d){
        mij = (s + d) / 2;

        // gasit
        if(strcmp(aux_inserare.sir_caractere, pagina->chei[mij].sir_caractere) == 0){ 
            pagina->chei[mij].numar_elemente++;
            return pagina;
        }

        if(strcmp(aux_inserare.sir_caractere, pagina->chei[mij].sir_caractere) < 0){
            d = mij - 1;
        }
        else{
            s = mij + 1;
        }
    }

    // daca este pagina terminala sau daca se propaga insertia
    if(pagina->chei == NULL || nod){

        // se poate adauga un nod in pagina curenta daca
        if(pagina->numar_chei < NN){
            ++pagina->numar_chei;

            for(i = pagina->numar_chei; i > d + 1; i--){
                pagina->chei[i] = pagina->chei[i - 1];
            }

            pagina->chei[i] = aux_inserare;
        }

        // pagina curenta este plina => trebuie scindare
        else{
            Pagina_T *a = pagina;
            Pagina_T *b = (Pagina_T*) calloc(sizeof(Pagina_T), 1);
            pagina = (Pagina_T*) calloc(sizeof(Pagina_T), 1);

            // scindarea paginii curente

            for(i = 1; i <= N; i++){
                b->chei[i] = a->chei[i + N];
            }

            a->numar_chei = b->numar_chei = N;

            // aici se poate creste nr de scindari
            nr_pagini_scindate++;

            // cheia nodului v este cheia de scindare

            if((strcmp(aux_inserare.sir_caractere, a->chei[N].sir_caractere) > 0) && (strcmp(aux_inserare.sir_caractere, b->chei[1].sir_caractere) < 0)){
                pagina->chei[++pagina->numar_chei] = aux_inserare;
            }
            else{
                // ultima cheie a nodului este folosita la scindare
                if(strcmp(aux_inserare.sir_caractere, a->chei[N].sir_caractere) < 0){
                    pagina->chei[++pagina->numar_chei] = a->chei[N];

                    for(i = a->numar_chei; i > 1 && (strcmp(aux_inserare.sir_caractere, a->chei[i - 1].sir_caractere) < 0); i--){
                        a->chei[i] = a->chei[i - 1];
                    }
                    a->chei[i] = aux_inserare;
                }
                // prima cheie a nodului este folosita la scindare
                else{
                    pagina->chei[++pagina->numar_chei] = b->chei[1];

                    for(i = 1; i < b->numar_chei && (strcmp(aux_inserare.sir_caractere, b->chei[i + 1].sir_caractere) > 0); i++){
                        b->chei[i] = b->chei[i + 1];
                    }
                    b->chei[i] = aux_inserare;
                }
            }

            // se refac legaturile intre pagini
            b->parinte = pagina->chei[1].pagina; // prima legatura a paginii b devine legatura nodului parinte
            pagina->parinte = a; // prima legatura a nodului parinte devine fostul vecin stanga
            pagina->chei[1].pagina = b; // a doua legatura a nodului parinte devine fostul vecin dreapta
        }
    }
    else{
        // s-a ajuns la cel mai din stanga element
        if(d == 0){
            q = pagina->parinte;
        }
        else{
            q = pagina->chei[d].pagina;
        }

        r = insereaza(q, sir_caractere, NULL);
        
        /// daca pagina in care s-a inserat s-a scindat, atuncti arborele a crescut cu un nivel
        if(r != q){
            /*
                se incearca inserarea nodului din pagina scindata in pagina curenta
                in caz de succes, arborele nu va creste in inaltima
            */
            pagina = insereaza(pagina, r->chei[1].sir_caractere, &r->chei[1]);
            free(r); // se sterge pagina scindata
        }
    }
    
    return pagina;
}

void afisare(Pagina_T* arbore, int nivel){
    int i;

    if(arbore == NULL){
        return;
    }

    afisare(arbore->parinte, nivel + 1);

    for(i = 1; i <= arbore->numar_chei; i++){
        afisare(arbore->chei[i].pagina, nivel + 1);
    }

    printf("Nivel %d: ", nivel);

    for(i = 1; i <= arbore->numar_chei; i++){
        printf("%s(%d) ", arbore->chei[i].sir_caractere, arbore->chei[i].numar_elemente);
    }

    printf("\n");
}

void afisareSiNumarare(Pagina_T* arbore, int nivel, int* contorPagini){
    int i;
    if (arbore == NULL) return;

    
    
    (*contorPagini)++;

    afisareSiNumarare(arbore->parinte, nivel + 1, contorPagini);
    

    for(i = 1; i <= arbore->numar_chei; i++){
        
        afisareSiNumarare(arbore->chei[i].pagina, nivel + 1, contorPagini);
    }

    printf("Nivel %d: ", nivel);

    for(i = 1; i <= arbore->numar_chei; i++){
        printf("%s(%d) ", arbore->chei[i].sir_caractere, arbore->chei[i].numar_elemente);
    }

    printf("\n");
}

int inaltimeMAX;

// inaltimea 
void inaltime(Pagina_T* arbore, int nivel){
    int i;

    if(arbore == NULL){
        return;
    }

    inaltime(arbore->parinte, nivel + 1);

    for(i = 1; i <= arbore->numar_chei; i++){
        inaltime(arbore->chei[i].pagina, nivel + 1);
    }

    //printf("Nivel %d: ", nivel);
    if(nivel > inaltimeMAX){
        inaltimeMAX = nivel;
    }

    for(i = 1; i <= arbore->numar_chei; i++){
        //printf("%s(%d) ", arbore->chei[i].sir_caractere, arbore->chei[i].numar_elemente);
    }

    //printf("\n");
}




int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "Utilizare: %s <fisier_intrare>\n", argv[1]);
        return 1;
    }

    FILE *fisier = fopen(argv[1], "r");
    if(fisier == NULL){
        fprintf(stderr, "Eroare la deschiderea fisierului %s\n", argv[1]);
        return 1;
    }

    Pagina_T *radacina = NULL;

    int numar_elemente;
    char sir_caractere[30];

    fscanf(fisier, "%d", &numar_elemente);
    for(int i = 0; i < numar_elemente; i++){
        fscanf(fisier, "%s", sir_caractere);
        radacina = insereaza(radacina, sir_caractere, NULL);
    }

    fclose(fisier);
    printf("Arborele B rezultat:\n");
    afisare(radacina, 0);
    printf("\n");

    printf("Numarul de pagini scindate: %d\n", nr_pagini_scindate);

    int contorPagini = 0;
    afisareSiNumarare(radacina, 0, &contorPagini);
    printf("Numarul total de pagini: %d\n", contorPagini);

    inaltimeMAX = 0;
    inaltime(radacina, 0);
    printf("Inaltimea arborelui: %d\n", inaltimeMAX + 1);

    return 0;
}