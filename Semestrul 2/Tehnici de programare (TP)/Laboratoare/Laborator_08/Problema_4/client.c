#include "lista.h"

int main(void){
    List_t lista = NULL;

    lista = addFront(lista, makeNode(30));
    lista = addFront(lista, makeNode(20));
    lista = addFront(lista, makeNode(10));
    lista = addFront(lista, makeNode(0));
    printList(lista);
    lista = addPosition(lista, makeNode(40), 2);
    //lista = addLast(lista, makeNode(50));
    printList(lista);

    lista = removeFront(lista);
    lista = removePosition(lista, 2);
    printList(lista);

    freeList(lista);
    return 0;
}