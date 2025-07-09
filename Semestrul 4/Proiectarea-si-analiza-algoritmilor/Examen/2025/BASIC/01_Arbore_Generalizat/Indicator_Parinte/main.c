#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// ----------------
// DEFINES
// ----------------

#define DEBUG 1
#define MAX_NODURI 100

// ----------------
// STRUCTURI DE DATE
// ----------------

typedef struct ArboreGeneralizat{
    int index[MAX_NODURI]; // Indicele nodurilor
    int parinte[MAX_NODURI]; // Indicele parintelui pentru fiecare nod
    int numarNoduri; // Numarul de noduri in arbore
}ArboreGeneralizat_T;

// ------------------
// FUNCTII
// ------------------

/**
 * @brief Initializeaza un arbore generalizat.
 * 
 * @return ArboreGeneralizat_T pointer catre arborele generalizat initializat.
*/

ArboreGeneralizat_T* initArbore(){
    ArboreGeneralizat_T* arbore  =  (ArboreGeneralizat_T*) malloc(sizeof(ArboreGeneralizat_T));

    if(arbore == NULL){
        perror("Nu s-a putut aloca memoria pentru arborele generalizat\n");
        return NULL;
    }

    arbore->numarNoduri = 0;

    for(int i = 0; i < MAX_NODURI; i++){
        arbore->index[i] = -1; // Initializam indicii nodurilor cu -1
        arbore->parinte[i] = -1; // Initializam indicii parintilor cu -1
    }

    return arbore;
}

/**
 * @brief Insereaza un nod in arborele generalizat.
 * 
 * @param arbore Pointer catre arborele generalizat.
 * @param index Indexul nodului de inserat.
 * @param parinteIndex Indexul parintelui nodului de inserat.
 * @return int 0 daca inserarea a fost reusita, -1 in caz contrar.
*/  

int insereazaNod(ArboreGeneralizat_T* arbore, int index, int parinteIndex){
    if(arbore->numarNoduri >= MAX_NODURI){
        perror("Arborele generalizat este plin, nu se mai pot insera noduri\n");
        return -1;
    }

    // Verificam daca indexul nodului este valid
    if(index < 0 || index >= MAX_NODURI){
        perror("Indexul nodului este invalid\n");
        return -1;
    }

    // Verificam daca parintele este valid
    if(parinteIndex < -1 || parinteIndex >= MAX_NODURI){
        perror("Indexul parintelui este invalid\n");
        return -1;
    }

    // Verificam daca nodul deja exista
    for(int i = 0; i < arbore->numarNoduri; i++){
        if(arbore->index[i] == index){
            perror("Nodul cu acest index deja exista in arbore\n");
            return -1;
        }
    }

    arbore->numarNoduri++;
    arbore->index[arbore->numarNoduri - 1] = index;
    arbore->parinte[arbore->numarNoduri - 1] = parinteIndex;

    if(DEBUG){
        printf("Nodul cu index %d a fost inserat cu parintele %d\n", index, parinteIndex);
    }

    return 0;
}

/**
 * @brief Afiseaza arborele generalizat
 * 
 * @param arbore Pointer catre arborele generalizat.
*/

void afiseazaArbore(ArboreGeneralizat_T* arbore){
    if(arbore == NULL || arbore->numarNoduri == 0){
        printf("Arborele generalizat este gol\n");
        return;
    }

    printf("Arbore Generalizat:\n");
    for(int i = 0; i < arbore->numarNoduri; i++){
        printf("Nod %d: Parinte %d\n", arbore->index[i], arbore->parinte[i]);
    }
}

/*
    @brief Gaseste radacina arborelui generalizat.
    
*/

int gasesteRadacina(ArboreGeneralizat_T* arbore){
    if(arbore->numarNoduri < 0){
        perror("Arborele generalizat nu are noduri\n");
        return -1;
    }

    return arbore->index[0]; // Radacina este primul nod inserat
}

/**
 * @brief Gaseste primul nod fiu al unui nod dat
 * 
 */

int gasestePrimulFiu(ArboreGeneralizat_T* arbore, int index){
    for(int i = 0; i < arbore->numarNoduri; i++){
        if(arbore->parinte[i] == index){
            return arbore->index[i]; // Returneaza primul fiu al nodului
        }
    }

    return -1; // Daca nu exista fii, returnam -1
}

int gasesteFrateDreapta(ArboreGeneralizat_T* arbore, int index){
    int parinte = -1;

    for(int i = 0; i < arbore->numarNoduri; i++){
        if(arbore->index[i] == index){
            parinte = arbore->parinte[i]; // Gasim parintele nodului
            break;
        }
    }

    for(int i = index; i < arbore->numarNoduri; i++){
        if(arbore->parinte[i] == parinte && arbore->index[i] != index){
            return arbore->index[i]; // Returneaza primul frate drept al nodului
        }
    }

    return -1; // Daca nu exista frate drept, returnam -1
}

int gasesteUltimulFiu(ArboreGeneralizat_T* arbore, int index){
    int ultimFiu = -1;

    // sau doar il parcurgi invers
    for(int i = 0; i < arbore->numarNoduri; i++){
        if(arbore->parinte[i] == index){
            ultimFiu = arbore->index[i]; // Actualizam ultimul fiu
        }
    }

    return ultimFiu; // Returneaza ultimul fiu al nodului
}

/**
 * @brief parcurgere in preordine a arborelui generalizat
*/

void parcurgerePreordine(ArboreGeneralizat_T*arbore, int index){
    //getchar();
    printf("%d ", index); // Afisam nodul curent

    int primulFiu = gasestePrimulFiu(arbore, index);

    while(primulFiu != -1){
        parcurgerePreordine(arbore, primulFiu);
        primulFiu = gasesteFrateDreapta(arbore, primulFiu);
    }
}

void parcurgerePostordine(ArboreGeneralizat_T* arbore, int index){
    int primulFiu = gasestePrimulFiu(arbore, index);

    while(primulFiu != -1){
        parcurgerePostordine(arbore, primulFiu);
        primulFiu = gasesteFrateDreapta(arbore, primulFiu);
    }

    printf("%d ", index); // Afisam nodul curent dupa ce am parcurs toti fii
}

void parcurgereInordine(ArboreGeneralizat_T* arbore, int index){
    int primulFiu = gasestePrimulFiu(arbore, index);

    if(primulFiu != -1){
        parcurgereInordine(arbore, primulFiu); // Parcurgem primul fiu
    }

    printf("%d ", index); // Afisam nodul curent

    if(primulFiu == -1){
        return; // Daca nu are fii, iesim din functie
    }
    int frateDreapta = gasesteFrateDreapta(arbore, primulFiu);

    while(frateDreapta != -1){
        parcurgereInordine(arbore, frateDreapta); // Parcurgem fratii drepte
        frateDreapta = gasesteFrateDreapta(arbore, frateDreapta);
    }
}

/*
    @brief Calcularea inaltimii arborelui generalizat.
*/

int inaltimeArbore(ArboreGeneralizat_T* arbore, int index){
    if(index == -1){
        return 0; // Daca nu exista nod, inaltimea este 0
    }

    int inaltimeMaxima = 0;
    int primulFiu = gasestePrimulFiu(arbore, index);

    while(primulFiu != -1){
        int inaltimeCurenta = inaltimeArbore(arbore, primulFiu);
        if(inaltimeCurenta > inaltimeMaxima){
            inaltimeMaxima = inaltimeCurenta; // Actualizam inaltimea maxima
        }
        primulFiu = gasesteFrateDreapta(arbore, primulFiu);
    }

    return inaltimeMaxima + 1; // Adaugam 1 pentru nodul curent
}

int pas_max = 0;

void inaltime2(ArboreGeneralizat_T* arbore, int indexCurent, int*pas){
    for(int i = 0; i < arbore->numarNoduri; i++){
        if(arbore->parinte[i] == indexCurent){
            *pas = *pas + 1; // Incrementam pasul pentru fiecare fiu

            if(*pas > pas_max){
                pas_max = *pas; // Actualizam pasul maxim
            }

            inaltime2(arbore, arbore->index[i], pas); // Apel recursiv pentru fiecare fiu

            *pas = *pas - 1; // Decrementam pasul dupa ce am parcurs toti fii
        }
    }
}

// -------------------
// MAIN
// -------------------

int main(int argc, char **argv){
    if(argc != 2){
        perror("Numar incorect de argumente. Utilizare: ./ArboreGeneralizat <filename>\n");
        return 1;
    }

    FILE* fin = fopen(argv[1], "r");
    if(fin == NULL){
        perror("Nu s-a putut deschide fisierul\n");
        return 1;
    }

    // initializam arborele generalizat
    ArboreGeneralizat_T* arbore = initArbore();

    int i = 0, parinte = 0;
    while(fscanf(fin, "%d ", &parinte) == 1){
        if(insereazaNod(arbore, i + 1, parinte) == -1){
            fclose(fin);
            free(arbore);
            return 1;
        }

        i++;
    }

    fclose(fin);

    if(DEBUG){
        afiseazaArbore(arbore);
    }

    int radacina = gasesteRadacina(arbore);

    // parcurgem arborele in preordine
    printf("Parcurgere in preordine a arborelui generalizat:\n");
    if(radacina != -1){
        parcurgerePreordine(arbore, radacina);
    } else {
        printf("Arborele nu are radacina\n");
    }
    printf("\n");


    // parcurgem arborele in postordine
    printf("Parcurgere in postordine a arborelui generalizat:\n");
    if(radacina != -1){
        parcurgerePostordine(arbore, radacina);
    } else {
        printf("Arborele nu are radacina\n");
    }

    printf("\n");

    // parcurgem arborele in inordine
    printf("Parcurgere in inordine a arborelui generalizat:\n");
    if(radacina != -1){
        parcurgereInordine(arbore, radacina);
    } else {
        printf("Arborele nu are radacina\n");
    }
    printf("\n");

    // calculam inaltimea arborelui
    int inaltime = inaltimeArbore(arbore, radacina);
    printf("Inaltimea arborelui generalizat este: %d\n", inaltime);


    // calculam inaltimea arborelui folosind pasul
    int pas = 0;
    inaltime2(arbore, radacina, &pas);
    printf("Inaltimea arborelui generalizat folosind pasul este: %d\n", pas_max + 1);

    return 0;
}