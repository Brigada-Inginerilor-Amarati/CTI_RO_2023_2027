// faceti un program care sa ilustreze functiile unei liste dublu inlantuite


#include <stdio.h>  
#include <stdlib.h>
#include <time.h>


typedef int Element_t;

typedef struct nod{
    Element_t value;

    struct nod *next_node;
    struct nod *previous_node;
}Node_t;

typedef Node_t *List_t;

Node_t *makeNode(Element_t data){
    Node_t *nod_creat = malloc(sizeof(Node_t));

    if(!nod_creat){
        printf("eroare la alocarea memoriei\n");
        return NULL;
    }

    nod_creat->value = data;
    nod_creat->next_node = NULL;
    nod_creat->previous_node = NULL;

    return nod_creat;
}

List_t addFirst(List_t lista, Element_t data){
    Node_t *nod_creat = makeNode(data);

    if(!nod_creat){
        return NULL;
    }

    if(!lista){
        return nod_creat;
    }

    nod_creat->next_node = lista;
    lista->previous_node = nod_creat;

    //actualizam lista
    lista = nod_creat;


    return lista;
}

List_t addLast(List_t lista, Element_t data){
    Node_t *nod_creat = makeNode(data);

    if(!nod_creat){
        return NULL;
    }

    if(!lista){
        return nod_creat;
    }

    Node_t *nod_curent = lista;

    //parcurgem lista pana la ultimul nod 
    while(nod_curent->next_node){
        nod_curent = nod_curent->next_node;
    }

    //legam ultimul la nodul creat
    nod_curent->next_node = nod_creat;
    nod_creat->previous_node = nod_curent;

    return lista;
}


List_t addIndex(List_t lista, Element_t data, int index){
    Node_t *nod_creat = makeNode(data);

    if(!nod_creat){
        return NULL;
    }

    if(!lista){
        return nod_creat;
    }

    if(index == 0){
        free(nod_creat);
        return addFirst(lista, data);
    }

    Node_t *nod_curent = lista;

    while (nod_curent->next_node && index > 1)
    {
        nod_curent = nod_curent->next_node;
        index--;
    }

    if(!nod_curent->next_node){
        free(nod_creat);
        return addLast(lista, data);
    }

    nod_creat->next_node = nod_curent->next_node;
    nod_curent->next_node->previous_node = nod_creat;

    nod_curent->next_node = nod_creat;
    nod_creat->previous_node = nod_curent;

    return lista;
}

List_t removeFirst(List_t lista){
    if(!lista){
        printf("lista e goala\n");
        return NULL;
    }

    Node_t *nod = lista;

    lista = lista->next_node;
    lista->previous_node = NULL;

    free(nod);
    return lista;
}

List_t removeLast(List_t lista){
    if(!lista){
        printf("lista e goala\n");
        return NULL;
    }

    Node_t *nod_curent = lista;

    while(nod_curent->next_node){
        nod_curent = nod_curent->next_node;
    }

    Node_t *temp = nod_curent;
    nod_curent->previous_node->next_node = NULL;
    free(temp);

    return lista;
}

List_t removeIndex(List_t lista, int index){
    if(!lista){
        printf("lista e goala\n");
        return NULL;
    }

    if(index == 0){
        return removeFirst(lista);
    }

    Node_t *nod_curent = lista;

    while (nod_curent->next_node->next_node && index > 1)
    {
        nod_curent = nod_curent->next_node;
        index--;
    }


    Node_t *temp = nod_curent->next_node;
     // If removing the last node, just update the next_node of the current node to NULL
    if (!temp->next_node) {
        nod_curent->next_node = NULL;
    } else {
        // If not removing the last node, link the current node to the next of the next node
        nod_curent->next_node = temp->next_node;
        // And also link back the next node to the current node, if it's not NULL
        // if (nod_curent->next_node->next_node) {
        //     nod_curent->next_node->next_node->previous_node = nod_curent;
        // }

        nod_curent->next_node->previous_node = nod_curent;
    }
    free(temp);
    return lista;
}


void printLista(List_t lista){
    Node_t *nod_curent = lista;

    while(nod_curent){
        printf("%d ", nod_curent->value);
        nod_curent = nod_curent->next_node;
    }
    printf("\n");

}


int main(void){
    srand(time(NULL));
    List_t lista = NULL;

    int size = 5 ; //1 + rand() % 10;

    printf("NR ELEMENTE INSERATE INITIAL : %d \n", size);

    for(int i = 0; i < size; i++){
        lista = addFirst(lista, i);
    }

    //lista = addLast(lista, size);

    printLista(lista);
    printf("\n");

    //lista = addIndex(lista, 13 + rand() % 1, size + 1);

    printf("-----------\n");

    printLista(lista);

    printf("delete \n");

    //lista = removeFirst(lista);

    //printLista(lista);

    printf("delete last\n");

    //lista = removeLast(lista);

    //printLista(lista);

    printf("delete index\n");

    lista = removeIndex(lista, size - 1);

    printLista(lista);

    return 0;
}