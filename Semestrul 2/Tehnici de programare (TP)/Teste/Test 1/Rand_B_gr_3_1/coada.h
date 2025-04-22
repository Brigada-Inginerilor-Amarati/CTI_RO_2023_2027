#ifndef __COADA_H
#define __COADA_H

typedef unsigned Element_t;
typedef struct Coada* PQ_t;


PQ_t MakeQ(int cap);

Element_t dequeue(PQ_t coada);

void enqueue(PQ_t coada, Element_t element_de_adaugat);
int par(Element_t x);
PQ_t filter(PQ_t A, int(*cond)(Element_t));
PQ_t inverseaza_ordinea(PQ_t coada, int k);
void print_queue(PQ_t q);

void free_coada(PQ_t coada);
#endif