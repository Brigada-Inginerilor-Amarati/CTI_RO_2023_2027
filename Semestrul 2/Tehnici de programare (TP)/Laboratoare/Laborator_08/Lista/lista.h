#ifndef __LISTA_H
#define __LISTA_H

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


Node_t* makeNode(Element_t value);

List_t addFront(List_t lista, Node_t *nod);
List_t addPosition(List_t lista, unsigned pozitie, Node_t *nod);

List_t removeFront(List_t lista);
List_t removePosition(List_t lista, unsigned pozitie);

void printList(List_t lista);
void freeList(List_t lista);

#endif