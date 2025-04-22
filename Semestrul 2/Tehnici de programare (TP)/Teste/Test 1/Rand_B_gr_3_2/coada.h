#ifndef __COADA_H
#define __COADA_H

typedef unsigned Element_t;
typedef struct Queue *PQ_t;

PQ_t initQueue(unsigned cap);

typedef enum {OK, Q_FULL}StatusCode_t;

StatusCode_t insereaza_element(PQ_t, Element_t, int (*cond)(const void*, const void *));

int compara(const void *a, const void *b);

Element_t scoate_element_vechi(PQ_t coada);

Element_t *extrage_primele_k_elemente(PQ_t coada, unsigned int k);

void afiseaza_coada(PQ_t coada);

#endif