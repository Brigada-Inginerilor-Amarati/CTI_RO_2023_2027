#include <stdio.h>
#include <stdlib.h>

#define Q_CAP 10

typedef enum {STATUS_OK, STATUS_EMPTY, STATUS_FULL} StatusCode_t;

typedef unsigned int Element_t;

typedef struct {
    Element_t *data;
    unsigned int cap;
    unsigned int tail; // tail - finalul cozii
    unsigned int head; // head - inceputul cozii
} Queue_t;

Queue_t makeQueue (unsigned int cap) {
    Queue_t coada;
    coada.tail = 0;
    coada.head = 0;
    if ((coada.data = malloc(cap * sizeof(Element_t))) == NULL) {
        coada.cap = 0;
        return coada;
    }
    coada.cap = cap;
    return coada;
}

StatusCode_t enqueue (Queue_t *coada, Element_t elem) {
    if (coada->tail < coada->cap) {
        coada->data[coada->tail] = elem;
        coada->tail ++;
        return STATUS_OK;
    }
    return STATUS_FULL;
}

StatusCode_t dequeue (Queue_t *coada, Element_t *elem) {
    if (coada->head < coada->tail) {
        *elem = coada->data[coada->head];
        coada->head ++;
        return STATUS_OK;
    }
    return STATUS_EMPTY;
}

StatusCode_t push(Queue_t *stiva_cu_coada, Element_t element_adaugat)
{
    return enqueue(stiva_cu_coada, element_adaugat);
}

Queue_t pop(Queue_t *stiva_cu_coada, Element_t *element_scos)
{
    Queue_t aux = makeQueue(Q_CAP);
    Element_t elem;
    for(int i = stiva_cu_coada->head; i < stiva_cu_coada->tail - 1; i++)
    {
        dequeue(stiva_cu_coada,&elem);
        enqueue(&aux, elem);
    }
    dequeue(stiva_cu_coada, element_scos);
    return aux;
}

int main (void) {
    Queue_t stiva_cu_coada = makeQueue(Q_CAP);

    push(&stiva_cu_coada, 10);

    push(&stiva_cu_coada, 20);

    push(&stiva_cu_coada, 30);

    push(&stiva_cu_coada, 40);

    Element_t element_scos;

    stiva_cu_coada = pop(&stiva_cu_coada, &element_scos);

    printf("%u \n", element_scos);

    return 0;
}