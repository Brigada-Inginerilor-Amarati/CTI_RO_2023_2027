#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* @brief Structura fisierului de intrare
* @param numarAngajati - numarul de angajati
* nrAngajati linii cu:
* @param sef - parintele nodului @param nume - numele angajatului
* 
*/

#define MAX_NODURI 100
#define DEBUG 0 // 1 pentru debug, 0 pentru release

typedef struct ArboreGeneralizat{
    int numarAngajati;
    int ID[MAX_NODURI]; // index ul angajatilor-> generat unic
    char nume[MAX_NODURI][50]; // numele angajatilor
    int sef[MAX_NODURI]; // sef[i] = j -> angajatul i are ca sef angajatul j -> parintele basic
}ArboreGeneralizat_T;

typedef struct StructuraAditionala{
    int nivel;
    int numarAngajati;
}StructuraAditionala_T;

StructuraAditionala_T informatii[MAX_NODURI];

void initArbore(ArboreGeneralizat_T *arbore){
    arbore->numarAngajati = 0;
    for(int i = 0; i < MAX_NODURI; i++){
        arbore->ID[i] = -1;
        arbore->sef[i] = -1;
        strcpy(arbore->nume[i], "");
    }
}

void afisareArbore(ArboreGeneralizat_T *arbore){
    printf("Numar angajati: %d\n", arbore->numarAngajati);
    for(int i = 0; i < arbore->numarAngajati; i++){
        printf("Angajat ID: %d, Nume: %s, Sef: %d\n", arbore->ID[i], arbore->nume[i], arbore->sef[i]);
    }
}

void initInformatii() {
    for (int i = 0; i < MAX_NODURI; i++) {
        informatii[i].nivel = i + 1; // Nivelul 1 este index 0
        informatii[i].numarAngajati = 0;
    }
}


void AngajatiPeNivel(ArboreGeneralizat_T *arbore) {
    for (int i = 0; i < arbore->numarAngajati; i++) {
        int parinte = arbore->sef[i];
        int nivel = 0;

        while (parinte != -1) {
            nivel++;
            parinte = arbore->sef[parinte];
        }

        informatii[nivel].numarAngajati++;

        if (DEBUG) {
            printf("Angajat %s (ID: %d) este la nivelul %d\n", arbore->nume[i], arbore->ID[i], nivel + 1);
        }
    }

    printf("\nAngajati pe nivel:\n");
    for (int i = 0; i < MAX_NODURI; i++) {
        if (informatii[i].numarAngajati > 0) {
            printf("Nivel %d: %d angajati\n", i + 1, informatii[i].numarAngajati);
        }
    }
    printf("\n");
}

// cu coada

typedef struct Coada{
    int elemente[MAX_NODURI];
    int front;
    int rear;
}Coada_T;

void initCoada(Coada_T *coada) {
    coada->front = -1;
    coada->rear = -1;
}

void enqueue(Coada_T *coada, int element) {
    if (coada->rear == MAX_NODURI - 1) {
        printf("Coada plina!\n");
        return;
    }
    if (coada->front == -1) {
        coada->front = 0;
    }
    coada->rear++;
    coada->elemente[coada->rear] = element;
}

int dequeue(Coada_T *coada) {
    if (coada->front == -1 || coada->front > coada->rear) {
        printf("Coada goala!\n");
        return -1; // Indica ca coada este goala
    }

    coada->front++;
    return coada->elemente[coada->front - 1];
}

void AngajatiPeNivelCuCoada(ArboreGeneralizat_T* arbore) {
    Coada_T coada;
    initCoada(&coada);

    enqueue(&coada, 0); // Începem cu rădăcina (index 0)
    int nivelCurent = 1;

    while (coada.front <= coada.rear) {
        int numarAngajatiNivelCurent = coada.rear - coada.front + 1;

        printf("Nivel %d: %d angajati\n", nivelCurent, numarAngajatiNivelCurent);

        for (int i = 0; i < numarAngajatiNivelCurent; i++) {
            int angajatCurent = dequeue(&coada);

            if (DEBUG) {
                printf("Angajat %s (ID: %d) este la nivelul %d\n", arbore->nume[angajatCurent], arbore->ID[angajatCurent], nivelCurent);
            }

            // Adaugăm toți subordonații în coadă
            for (int j = 0; j < arbore->numarAngajati; j++) {
                if (arbore->sef[j] == angajatCurent) {
                    enqueue(&coada, j);
                }
            }
        }
        nivelCurent++;
    }
}



int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Utilizare: %s <fisier_intrare>\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL) {
        perror("Eroare la deschiderea fisierului\n");
        return 1;
    }

    ArboreGeneralizat_T arbore;
    initArbore(&arbore);
    initInformatii();

    fscanf(fin, "%d", &arbore.numarAngajati);

    if (DEBUG) {
        printf("Numar angajati: %d\n", arbore.numarAngajati);
    }

    int parinte = -1;
    int id = 0;
    char nume[50];

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

    fclose(fin);

    afisareArbore(&arbore);

    AngajatiPeNivel(&arbore);

    AngajatiPeNivelCuCoada(&arbore);

    return 0;
}
