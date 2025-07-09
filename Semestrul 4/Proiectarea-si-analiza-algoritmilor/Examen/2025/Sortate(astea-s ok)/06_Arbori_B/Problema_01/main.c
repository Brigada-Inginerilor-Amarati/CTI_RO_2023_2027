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
    int ID;
    int an_nastere;
    bool este_vaccinat;

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


/**
 * @def FUNCTIONS
*/

/**
 * @brief Functie pentru inserare 
*/

Nod_T aux_inserare;

Pagina_T* insereaza(Pagina_T *pagina, int ID, int an_nastere, bool este_vaccinat, Nod_T* nod){
    int i, s, d, mij;
    Pagina_T* q, *r;

    if(nod == NULL){
        aux_inserare.ID = ID;
        aux_inserare.an_nastere = an_nastere;
        aux_inserare.este_vaccinat = este_vaccinat;
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
        if(pagina->chei[mij].ID == aux_inserare.ID){ 
            pagina->chei[mij].numar_elemente++;
            return pagina;
        }

        if(ID < pagina->chei[mij].ID){
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

            // cheia nodului v este cheia de scindare

            if(aux_inserare.ID > a->chei[N].ID && aux_inserare.ID < b->chei[1].ID){
                pagina->chei[++pagina->numar_chei] = aux_inserare;
            }
            else{
                // ultima cheie a nodului este folosita la scindare
                if(aux_inserare.ID < a->chei[N].ID){
                    pagina->chei[++pagina->numar_chei] = a->chei[N];

                    for(i = a->numar_chei; i > 1 && a->chei[i - 1].ID > aux_inserare.ID; i--){
                        a->chei[i] = a->chei[i - 1];
                    }
                    a->chei[i] = aux_inserare;
                }
                // prima cheie a nodului este folosita la scindare
                else{
                    pagina->chei[++pagina->numar_chei] = b->chei[1];

                    for(i = 1; i < b->numar_chei && b->chei[i + 1].ID < aux_inserare.ID; i++){
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

        r = insereaza(q, ID, an_nastere, este_vaccinat, NULL);
        
        /// daca pafina in care s-a inserat s-a scindat, atuncti arborele a crescut cu un nivel
        if(r != q){
            /*
                se incearca inserarea nodului din pagina scindata in pagina curenta
                in caz de succes, arborele nu va creste in inaltima
            */

            pagina = insereaza(pagina, r->chei[1].ID, r->chei[1].an_nastere, r->chei[1].este_vaccinat, &r->chei[1]);
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
        printf("%d ", arbore->chei[i].ID);
        if(arbore->chei[i].este_vaccinat){
            printf("(vaccinat) ");
        }
        else{
            printf("(nevaccinat) ");
        }
        printf("(%d) ", arbore->chei[i].an_nastere);
    }

    printf("\n");
}

void cerinta(Pagina_T*arbore, int nivel){
    int i;

    if(arbore == NULL){
        return;
    }

    cerinta(arbore->parinte, nivel + 1);

    for(i = 1; i <= arbore->numar_chei; i++){
        cerinta(arbore->chei[i].pagina, nivel + 1);
    }

    //printf("Nivel %d: ", nivel);

    for(i = 1; i <= arbore->numar_chei; i++){
        if(arbore->chei[i].este_vaccinat == false && arbore->chei[i].an_nastere < 2000){
            printf("%d ", arbore->chei[i].ID);
            if(arbore->chei[i].este_vaccinat){
                printf("(vaccinat) ");
            }
            else{
                printf("(nevaccinat) ");
            }
            printf("(%d) ", arbore->chei[i].an_nastere);
        }
    }

    printf("\n");
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
    int ID, an_nastere;
    int aux;
    bool este_vaccinat;

    while(fscanf(fisier, "%d %d %d", &ID, &an_nastere, &aux) == 3){
        if(aux == 1){
            este_vaccinat = true;
        }
        else if(aux == 0){
            este_vaccinat = false;
        }
        else{
            fprintf(stderr, "Valoare invalida pentru este_vaccinat: %d\n", aux);
            fclose(fisier);
            return 1;
        }
        radacina = insereaza(radacina, ID, an_nastere, este_vaccinat, NULL);
    }

    if(DEBUG){
        printf("Arborele B:\n");
        afisare(radacina, 0);
    }
    
    printf("Cerinta:\n");
    cerinta(radacina, 0);

    fclose(fisier);

    return 0;
}
