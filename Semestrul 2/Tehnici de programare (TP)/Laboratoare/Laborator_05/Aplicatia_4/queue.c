#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

#define COADA_CAP 100

int TEST = 555;

struct Coada {
    Element_t data[COADA_CAP];
    int front, rear;
};

Coada_t makeQueue() {
    Coada_t q = (Coada_t)malloc(sizeof(struct Coada));
    if (q == NULL) {
        perror("eroare alocare dinamica coada");
        return NULL;
    }
    q->front = q->rear = 0;
    return q;
}

StatusCode_t enqueue(Coada_t q, Element_t el) {
    if (q != NULL && (q->rear + 1) % COADA_CAP != q->front) {
        q->data[q->rear] = el;
        q->rear = (q->rear + 1) % COADA_CAP;
        return COADA_OK;
    }
    return COADA_FULL;
}

StatusCode_t dequeue(Coada_t q, Element_t* el) {
    if (q != NULL && q->front != q->rear) {
        *el = q->data[q->front];
        q->front = (q->front + 1) % COADA_CAP;
        return COADA_OK;
    }
    return COADA_EMPTY;
}

StatusCode_t peekFront(Coada_t q, Element_t* el) {
    if (q != NULL && q->front != q->rear) {
        *el = q->data[q->front];
        return COADA_OK;
    }
    return COADA_EMPTY;
}

StatusCode_t destroyQueue(Coada_t q) {
    free(q);
    return COADA_OK;
}

void printStatus() {
    printf("TEST ESTE %d\n", TEST);
}
