/*
Sa se defineasca si implementeze o biblioteca-C care ofera clientului 

un nou tip de date PCoada_t si setul de operatii aferente. 

Tipul de date PCoada_t implementeaza conceptul de coada cu prioritate, 

adica o structura de date Coada asupra careia sa adauga posibilitatea 

de a asigna fiecarui element o "prioritate". 

Biblioteca va implementa operatiile specifice tipului de date sub forma unor functii cu parametri specifici.

Operatiile de inserare si stergere se vor face in timp optim, 

cu respectarea prioritatii elementelor: se vor insera elemente la prima pozitie 

unde permite prioritatea si se va scoate cel mai "vechi" element. 

Gestionarea elementelor se va face folosind alocare dinamica de memorie.
*/

#ifndef __PQ_H
#define __PQ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct ELEMENT *Element_t;
typedef struct PQ *Pq_t;

//fa coada
Pq_t makePQ(int cap);

//adauga elem;

Pq_t enqueue(Pq_t coada, int val, int pr);

//afiseaza elemente

void afisare_coada(Pq_t coada);

//dequeue

Element_t dequeue(Pq_t coada);

void print_element(Element_t element);


#endif