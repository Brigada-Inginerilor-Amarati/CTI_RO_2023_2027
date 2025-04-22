#include <stdio.h>
#include <stdlib.h>
#include "coada.h"

struct Coada{
    int capacity;
    int head;
    int tail;
    Element_t *data;
};

PQ_t MakeQ(int cap){
    PQ_t coada = (PQ_t) malloc(sizeof(struct Coada));
    if(coada == NULL){
        perror("alloc err");
        return NULL;
    }
    coada->tail = 0;
    coada->head = 0;
    coada->data = (Element_t*)malloc(cap*sizeof(Element_t));
    if(coada->data == NULL){
        coada->capacity = 0;
        return coada;
    }
    coada->capacity = cap;
    return coada;
}

Element_t dequeue(PQ_t coada){
    if(coada->head < coada->tail){
        Element_t element_scos = coada->data[coada->head];
        for(int i = 0; i < coada->tail - 1; i++)
        {
            coada->data[i] = coada->data[i +1];
        }

        coada->tail--;

        return element_scos;
    }
    else{
        exit(-1);
    }
}

void enqueue(PQ_t coada, Element_t element_de_adaugat)
{
    if(coada->tail < coada->capacity)
    {
        coada->data[coada->tail ++] = element_de_adaugat; 
    }
}

PQ_t filter(PQ_t A, int(*cond)(Element_t)){
    PQ_t R = MakeQ(A->tail);
    Element_t aux;
    unsigned iteratii = A->tail;
    for(int i = 0; i < iteratii; i++){
        aux = dequeue(A);
        if(!cond(aux)){
            enqueue(R, aux);
        }
    }
    return R;
}

int par(Element_t x){
    return x%2;
}

PQ_t inverseaza_ordinea(PQ_t coada, int k)
{
    Element_t aux;
    for(int i = coada->head; i < coada->head + k/2; i++)
    {
        aux = coada->data[i];
        coada->data[i] = coada->data[coada->head + k - 1- i];
        coada->data[coada->head + k - 1 - i] = aux;
    }
    return coada;
} 

void print_queue(PQ_t q) {
  for (size_t i = q->head; i < q->tail; i++) {
    printf("%u ", q->data[i]);
  }
}

void free_coada(PQ_t coada)
{
    if(coada != NULL)
    {
        free(coada->data);
        free(coada);
    }
}


