#include <stdio.h>
#include <stdlib.h>

/*
|-----|---------------------|
|  el |  pointer la urm nod |
|-----|---------------------|
*/

//asta este elementul din prima casuta a nodului
typedef unsigned Element_t;

//asta este un nod din lista
typedef struct Node{
    Element_t value;
    struct Node* next_nod;
}Node_t;

//lista e un pointer la primul element din lista
typedef Node_t* List_t;

//cream un nod oarecare, care nu e legat la nicio lista
Node_t* makeNode(Element_t value){
    Node_t* nod;

    if((nod = malloc(sizeof(Element_t))) == NULL){
        return NULL;
    }

    //actualizam campurile nodului
    nod->value = value;
    nod->next_nod = NULL;

    return nod;
}

List_t addFront(List_t lista, Node_t *nod){
    if(!lista){
        return nod;
    }

    nod->next_nod = lista;

    lista = nod;

    return lista;
}

List_t addPosition(List_t lista, unsigned pozitie, Node_t *nod){
    
    if(pozitie == 0){
        return addFront(lista, nod);
    }

    List_t aux = lista;

    while (pozitie > 1 && aux->next_nod != NULL){
        aux = aux -> next_nod;
        pozitie--;
    }

    nod->next_nod = aux->next_nod;
    aux->next_nod = nod;

    return lista;
}

List_t removeFront(List_t lista){
    Node_t* nod = lista;

    lista = lista->next_nod;

    free(nod);

    return lista;
}

// List_t removePosition(List_t lista, unsigned pozitie){
//     if(pozitie == 0){
//         return removeFront(lista);
//     }

//     List_t aux = lista;
//     Node_t * nod; //aici vom stoca nodul peste care vrem sa sarim

//     if (pozitie == 1)
//     {
//         nod = aux->next_nod;
//         aux->next_nod = aux->next_nod->next_nod;
//         free(nod);
//         return lista;
//     }

    

//     while (pozitie > 2 && aux->next_nod->next_nod){
//         aux = aux->next_nod;
//         pozitie--;
//     }
//     //acum ne aflam cu 2 elemente inainte
    
//     if(aux->next_nod->next_nod){
//         nod = aux->next_nod->next_nod;
//         aux->next_nod->next_nod = aux->next_nod->next_nod->next_nod;
//     }
//     else{
//         nod = aux->next_nod;
//         aux->next_nod = NULL;
//     }
//     free(nod);
//     return lista;
// }

List_t removePosition(List_t lista, unsigned pozitie){
    if(pozitie == 0){
        return removeFront(lista);
    }

    List_t aux = lista;

    while (pozitie > 1 && aux->next_nod->next_nod)
    {
        aux = aux->next_nod;
        pozitie--;
    }

    Node_t *nod = aux->next_nod;
    aux->next_nod = aux->next_nod->next_nod;
    free(nod);

    return lista;
}


void printList(List_t lista){
    for(Node_t *nod = lista; nod != NULL; nod = nod->next_nod){
        printf("%u ", nod->value);
    }
    printf("\n");
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

    return 0;
}