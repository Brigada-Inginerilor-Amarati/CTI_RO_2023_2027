/*
1 Se genereaza aleator un vector A formati din numere naturale, 

din intervalul 1-100, pe un total de  200 pozitii. 

Se genereaza tot aleator un numar natural B, in intervalul 1-2. 

Se parcurge  vectorul A, “eliminand” din el elementele de pe pozitii impare, 

daca B=1 sau pare daca B=2. Dupa fiecare parcurgere se afiseaza numarul iteratiei 

si vectorul. Se continua pana cand mai este doar un singur element.

Exemplu

intrare:
A= 2 5 7 8 9 10 1 3 6 4 (simplificat)
B=1

Afiseaza:
Iteratia 1: 5 8 10 3 4
Iteratia 2: 8 3
Iteratia 3: 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned Element_t;

typedef struct Nod{
    Element_t valoare;
    struct Nod *nodul_urmator;
}Nod_t;

typedef Nod_t* Lista_t;

Nod_t* makeNod(Element_t value){
    Nod_t* nod = malloc(sizeof(Nod_t));

    if(nod == NULL){
        return NULL;
    }

    nod->valoare = value;
    nod->nodul_urmator = NULL;

    return nod;
}

Lista_t addFront(Lista_t lista, Nod_t *nod){
    if(!lista){
        return nod;
    }

    nod->nodul_urmator = lista;
    lista = nod;

    return lista;
}

Lista_t addPosition(Lista_t lista, Nod_t *nod, int pozitie){
    if(pozitie == 0){
        return addFront(lista, nod);
    }

    Lista_t aux = lista;

    while(pozitie > 1 && aux->nodul_urmator != NULL){
        aux = aux->nodul_urmator;
        pozitie--;
    }

    nod->nodul_urmator = aux->nodul_urmator;
    aux->nodul_urmator = nod;

    return lista;
}

Lista_t removeFront(Lista_t lista){
    Nod_t *nod = lista;

    lista = lista->nodul_urmator;

    free(nod);

    return lista;
}

Lista_t removePosition(Lista_t lista, int pozitie){
    if(pozitie == 0){
        return removeFront(lista);
    }

    Lista_t aux = lista;

    while(pozitie > 1 && aux->nodul_urmator->nodul_urmator){
        aux = aux->nodul_urmator;
        pozitie--;
    }

    Nod_t *nod = aux->nodul_urmator;
    aux->nodul_urmator = aux->nodul_urmator->nodul_urmator;

    free(nod);

    return lista;
}

void printList(Lista_t lista){
    for(Nod_t *nod =  lista; nod; nod = nod->nodul_urmator){
        printf("%u ", nod->valoare);
    }

    printf("\n");
}

Lista_t eliminare(Lista_t lista, int B, int index){
    for(Nod_t *nod =  lista; nod; nod = nod->nodul_urmator){
        if(B == 1 && index % 2 == 1){
            lista = removePosition(lista, index);
        }

        if(B == 2 && index % 2 == 0){
            lista = removePosition(lista, index);
        }

        index++;
    }

    return lista;
}

Nod_t* eliminate(Nod_t* head, int B, int index) {
    if (head == NULL) {
        return NULL;
    }
    if ((B == 2 && index % 2 == 1) || (B == 1 && index % 2 == 0)) {
        Nod_t* next = head->nodul_urmator;
        free(head);
        return eliminate(next, B, index + 1);
    } else {
        head->nodul_urmator = eliminate(head->nodul_urmator, B, index + 1);
        return head;
    }
}

int main(void){

    srand(time(NULL));

    Lista_t lista = NULL;

    for(int i = 0; i < 10; i++){
        lista = addFront(lista, makeNod(rand() % 100 + 1));
    }

    printList(lista);

    int B = rand() % 2 + 1;

    printf("%d \n", B);

    int iteratie = 1;

    while (lista && lista->nodul_urmator)
    {
        lista = eliminate(lista, B, 0);
        printf("Iteratia %d : ", iteratie++);
        printList(lista);
    }
    

    return 0;
}