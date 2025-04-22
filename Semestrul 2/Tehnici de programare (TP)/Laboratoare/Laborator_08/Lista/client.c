#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/*
    Implementati o functie care primeste un tablou de intregi si 

    numarul sau de elemente si returneaza o lista cu elementele din tablou.
*/

List_t vector_to_lista(Element_t *vector, int numar_elemente){
    List_t lista = NULL;

    for(int i = 0; i < numar_elemente; i++){
        lista = addPosition(lista, i, makeNode(vector[i]));
    }

    return lista;
}

/*
    Implementati o functie care primeste o lista si 

    returneaza un tablou de intregi cu elementele listei.
*/

Element_t* lista_to_vector(List_t lista){
    unsigned n = 0;

    for(Node_t* nod = lista; nod; nod = nod->next_nod){
        n++;
    }

    Element_t *vector = malloc(n * sizeof(Element_t));
    unsigned i = 0;
    for(Node_t* nod = lista; nod && i < n; nod = nod->next_nod, i++){
        vector[i] = nod->value;
    }

    return vector;
}

void afiseaza_vector(unsigned *vector, int n){
    for(int i = 0; i < n; i++){
        printf("v[%d] = %d \n", i, vector[i]);
    }
}

int get_size_lista(List_t lista){
    int lungime = 0;

    for(Node_t* nod = lista; nod; nod = nod->next_nod){
        lungime++;
    }   

    return lungime;
}

int main(void){
    List_t lista = NULL;

    lista = addFront(lista, makeNode(10));
    printList(lista);

    //lista = removeFront(lista); //NU UITA SA PUI LISTA =
    //printList(lista);

    Node_t *nod = makeNode(13);
    lista = addFront(lista, nod); //niciodata fara asta ca bulim programu
    printList(lista);

    lista = addPosition(lista, 1, makeNode(3));
    printList(lista);

    lista = removePosition(lista, 4);
    printList(lista);
    //freeList(lista);

    List_t lista_din_vector = NULL;

    Element_t v[5] = {1,2,3,4,5};

    lista_din_vector = vector_to_lista(v, 5);

    printList(lista_din_vector);

    freeList(lista_din_vector);

    unsigned *vector_din_lista = lista_to_vector(lista);
    afiseaza_vector(vector_din_lista, get_size_lista(lista));
    free(vector_din_lista);
    freeList(lista);

    return 0;
}