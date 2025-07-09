#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// ----------------
// Defines
// ----------------

#define DEBUG 1

// ----------------
// Structura de date
// ----------------

typedef struct ArboreBinar{
    int cheie;
    struct ArboreBinar* left;
    struct ArboreBinar* right;
}AB_T;

typedef AB_T* ArboreBinar_T;

// ------------------
// Functii
// ------------------

/**
 * @brief Initializeaza un arbore binar cu o cheie data.
 * 
 * @param key Cheia cu care se initializeaza arborele.
 * @return ArboreBinar_T Pointer catre arborele binar initializat.
 */

ArboreBinar_T initArboreBinar(int key){
    ArboreBinar_T ab = (ArboreBinar_T)malloc(sizeof(AB_T));

    if(ab == NULL){
        perror("Nu s-a putut aloca memoria cum trebuie\n");
        return NULL;
    }

    ab->cheie = key;
    ab->left = NULL;
    ab->right = NULL;

    return ab;
}

ArboreBinar_T insereazaRecursiv(ArboreBinar_T radacina, int cheie){
    // verificam daca radacina este NULL
    if(radacina == NULL){
        return initArboreBinar(cheie);
    }

    // daca cheia este mai mica decat cheia radacinii, inseram in subarborele stang
    if(cheie < radacina->cheie){
        radacina->left = insereazaRecursiv(radacina->left, cheie);
    }
    // daca cheia este mai mare decat cheia radacinii, inseram in subarborele drept
    else if(cheie > radacina->cheie){
        radacina->right = insereazaRecursiv(radacina->right, cheie);
    }

    return radacina;
}

ArboreBinar_T insereazaIterativ(ArboreBinar_T radacina, int cheie){
    ArboreBinar_T nodNou = initArboreBinar(cheie);

    if(nodNou == NULL){
        return NULL; // Eroare la alocarea memoriei
    }

    // daca arborele este gol, returnam nodul nou ca radacina

    if(radacina == NULL){
        return nodNou;
    }

    ArboreBinar_T curent = radacina;
    ArboreBinar_T parinte = NULL;

    while(curent != NULL){
        parinte = curent;

        if(cheie < curent->cheie){
            curent = curent->left;
        }
        else if(cheie > curent->cheie){
            curent = curent->right;
        }
        else{
            // Cheia deja exista in arbore, nu o inseram din nou
            free(nodNou);
            return radacina;
        }
    }

    // Inseram nodul nou ca fiu stang sau drept al parintelui
    if(cheie < parinte->cheie){
        parinte->left = nodNou;
    }
    else{
        parinte->right = nodNou;
    }

    return radacina;
}

/**
 * @brief Parcurge arborele binar in preordine si afiseaza cheile : radacina, stanga, dreapta.
 * 
 * @param radacina Radacina arborelui binar.
 */

void parcurgerePreordine(ArboreBinar_T radacina){
    if(radacina == NULL){
        return;
    }

    printf("%d ", radacina->cheie);
    parcurgerePreordine(radacina->left);
    parcurgerePreordine(radacina->right);
}

/**
 * @brief Parcurge arborele binar in postordine si afiseaza cheile : stanga, dreapta, radacina.
 * 
 * @param radacina Radacina arborelui binar.
 */

void parcurgerePostordine(ArboreBinar_T radacina){
    if(radacina == NULL){
        return;
    }

    parcurgerePreordine(radacina->left);
    parcurgerePreordine(radacina->right);
    printf("%d ", radacina->cheie);
}

/**
 * @brief Parcurge arborele binar in inordine si afiseaza cheile : stanga, radacina, dreapta.
 * 
 * @param radacina Radacina arborelui binar.
 */

void parcurgereInordine(ArboreBinar_T radacina){
    if(radacina == NULL){
        return;
    }

    parcurgerePreordine(radacina->left);
    printf("%d ", radacina->cheie);
    parcurgerePreordine(radacina->right);
}

/**
 * @brief Functia de eliberare a memoriei alocate pentru arborele binar.
 * @param radacina Radacina arborelui binar.
 */

void elibereazaMemorie(ArboreBinar_T radacina){
    if(radacina == NULL){
        return;
    }

    elibereazaMemorie(radacina->left);
    elibereazaMemorie(radacina->right);
    free(radacina);
}

int main(int argc, char** argv){
    if(argc != 2){
        perror("Incorrect number of arguments. Usage: ./ArboreBinar <filename>\n");
        return 1;
    }

    FILE* fin = fopen(argv[1], "r");

    if(fin == NULL){
        perror("Nu s-a putut deschide fisierul\n");
        return 1;
    }  

    ArboreBinar_T radacina = NULL;
    int tmp;

    while(fscanf(fin, "%d", &tmp) == 1){
        radacina = insereazaRecursiv(radacina, tmp);
    }

    fclose(fin);

    if(radacina == NULL){
        perror("Arborele nu a fost initializat corect\n");
        return 1;
    }
    printf("Parcurgere in preordine: ");
    parcurgerePreordine(radacina);
    printf("\n");

    printf("Parcurgere in postordine: ");
    parcurgerePostordine(radacina);
    printf("\n");

    printf("Parcurgere in inordine: ");
    parcurgereInordine(radacina);
    printf("\n");

    elibereazaMemorie(radacina);

    return 0;
}