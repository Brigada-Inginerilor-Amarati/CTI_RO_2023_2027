#ifndef __LISTA_H
#define __LISTA_H

#include <stdio.h>
#include <stdlib.h>

/*
 Modificati implementarea inceputa la curs astfel incat sa pastrati si
 
  un pointer la ultimul element al listei: reimplementati functiile de inserare 
  
  si stergere in acest context.
*/

typedef unsigned Element_t;

typedef struct NODE *Node_t;
typedef struct LIST *List_t;

//initializare, creare, afisare, free
Node_t makeNode(Element_t input);
void printList(List_t lista);
void freeList(List_t lista);

//adaugare
List_t addFront(List_t lista, Node_t input_nod);
List_t addLast(List_t lista, Node_t input_nod);
List_t addPosition(List_t lista, Node_t input_nod, unsigned pozitie);

//stergere
List_t removeFront(List_t lista);
List_t removePosition(List_t lista, unsigned pozitie);

#endif