#ifndef __LISTA_H
#define __LISTA_H

#include <stdio.h>
#include <stdlib.h>

typedef int Element_t;

typedef struct NODE* Node_t;

typedef Node_t List_t;

//initializare, creare, afisare, free
Node_t makeNode(Element_t input);
void printList(List_t lista);
void freeList(List_t lista);


List_t addFront(List_t lista, Node_t input_nod);
List_t addPosition(List_t lista, Node_t input_nod, unsigned pozitie);

List_t removeFront(List_t lista);
List_t removePosition(List_t lista, unsigned pozitie);


//6 
List_t readFile(char* filepath);
void sortare_liste(List_t lista,List_t *l_pare, List_t *l_impare);
List_t removeNode_value(List_t lista, int valoare);
#endif