#ifndef __LISTA_CIRCULARA
#define __LISTA_CIRCULARA

#include <stdio.h>
#include <stdlib.h>

typedef int Element_t;

typedef struct NODE *Node_t;
typedef struct NODE *List_t;

// Prototipurile funcțiilor
Node_t makeNode(Element_t data);
List_t append(List_t head_ref, Element_t data);
List_t deleteByValue(List_t head_ref, Element_t data);
List_t deleteByIndex(List_t head_ref, int index);
List_t insertAtIndex(List_t head_ref, Element_t data, int index);
void displayList(List_t head);
#endif
