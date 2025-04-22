#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int head;
    int tail;
    int capacity;
} circularQueue_t;

circularQueue_t *makequeue(int cap) {
    circularQueue_t *coada = malloc(sizeof(circularQueue_t));

    if (!coada) {
        printf("eroare alocare memorie \n");
        return NULL;
    }

    coada->capacity = cap;
    coada->data = malloc(cap * sizeof(int));
    if (!coada->data) {
        printf("eroare alocare memorie data\n");
        free(coada);
        return NULL;
    }

    coada->head = -1;
    coada->tail = -1;

    return coada;
}

int isFull(circularQueue_t *coada) {
    return (coada->head == 0 && coada->tail == coada->capacity - 1) ||
           (coada->head == coada->tail + 1);
}

int isEmpty(circularQueue_t *coada) {
    return coada->head == -1;
}

circularQueue_t *enqueue(circularQueue_t *coada, int value) {
    if (isFull(coada)) {
        printf("coada e plina \n");
        return coada;
    }

    if (coada->head == -1) {
        coada->head = 0;
    }

    coada->tail = (coada->tail + 1) % coada->capacity;

    coada->data[coada->tail] = value;

    return coada;
}

int dequeue(circularQueue_t *coada){
    int element;

    if(isEmpty(coada)){
        printf("Coada este goala\n");
        return -1;
    }
    else{
        element = coada->data[coada->head];

        if(coada->head == coada->tail){
            coada->head = -1;
            coada->tail = -1;
        }
        else{
            coada->head = (coada->head + 1) % coada->capacity;
        }

        return element;
    }
}

void showCoada(circularQueue_t *coada) {
    if (isEmpty(coada)) {
        printf("coada este goala \n");
    } else {
        printf("front -> : %d ", coada->head);
        printf("Items -> ");
        int i;
        for (i = coada->head; i != coada->tail; i = (i + 1) % coada->capacity) {
            printf("%d ", coada->data[i]);
        }

        printf("%d ", coada->data[i]);
        printf("<- Rear \n");
    }
}

int main(void) {
    circularQueue_t *coada = makequeue(20);  // Am corectat alocarea pentru capacitatea dorită (20)

    for (int i = 0; i < 20; i++) {
        coada = enqueue(coada, i);
    }

    showCoada(coada);

    int scos = dequeue(coada);

    printf("Element scos %d \n", scos);

    showCoada(coada);
    
    free(coada->data);
    free(coada);
    return 0;
}