#include "lista.h"

struct NODE{
    Element_t value;
    struct NODE *next_nod;
};

struct LIST{
    struct NODE *first_node;
    struct NODE *last_node;
};

Node_t makeNode(Element_t input){
    Node_t nod = malloc(sizeof(struct NODE));

    if(nod == NULL){
        return NULL;
    }

    nod->next_nod = NULL;
    nod->value = input;

    return nod;
}

List_t addFront(List_t lista, Node_t input_nod){
    if(lista == NULL){
        lista = malloc(sizeof(struct LIST));
        lista->first_node = input_nod;
        lista->last_node = input_nod;

        return lista;
    }

    input_nod->next_nod = lista->first_node;
    lista->first_node = input_nod;

    return lista;
}

List_t addLast(List_t lista, Node_t input_nod){
    if(lista == NULL){
        return addFront(lista, input_nod);
    }
    lista->last_node = input_nod;
    return lista;
}

List_t addPosition(List_t lista, Node_t input_nod, unsigned pozitie){
    if(pozitie == 0){
        return addFront(lista, input_nod);
    }

    Node_t nod = lista->first_node;
    
    while (pozitie > 1 && nod->next_nod != NULL) //daca exista alt nod dupa cel curent parcurgem
    {
        pozitie--;
        nod = nod->next_nod;
    }

    input_nod->next_nod = nod->next_nod;
    nod->next_nod = input_nod;

    if(input_nod->next_nod == NULL){
        lista->last_node = input_nod;
    }


    return lista;
}

List_t removeFront(List_t lista){
    Node_t nod = lista->first_node;
    lista->first_node = lista->first_node->next_nod;
    free(nod);
    return lista;
}

List_t removePosition(List_t lista, unsigned pozitie){
    if(pozitie == 0){
        return removeFront(lista);
    }

    Node_t nod = lista->first_node;

    while(pozitie > 1 && nod->next_nod->next_nod){
        pozitie--;
        nod = nod->next_nod;
    }

    Node_t temp = nod->next_nod;
    nod->next_nod = nod->next_nod->next_nod;
    free(temp);

    if (nod->next_nod == NULL){
        lista->last_node = nod;
    }
    

    return lista;
}

void printList(List_t lista){
    for(Node_t nod = lista->first_node; nod != NULL; nod = nod->next_nod){
        printf("%u ", nod->value);
    }
    printf("\n");
}

void freeList(List_t lista){
    Node_t nod;
    while (lista->first_node != NULL){ 
        nod = lista->first_node;
        lista->first_node = lista->first_node->next_nod;
        free(nod);
    }
    
    free(lista);
}