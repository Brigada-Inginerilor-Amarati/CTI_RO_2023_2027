// implementati o coada cu liste

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int data;
    int priority;
    struct node *next_node;
} Node_t;

typedef struct queue{
    Node_t *head;
    Node_t *tail;
    int size;
}Queue_t;

Node_t *makeNode(int data, int priority){
    Node_t *nod_creat = malloc(sizeof(Node_t));

    if(!nod_creat){
        return NULL;
    }

    (*nod_creat) = (struct node) {data, priority, NULL};

    return nod_creat;
}

Queue_t *initQueue(){
    Queue_t *coada = malloc(sizeof(Queue_t));

    if(!coada){
        return NULL;
    }

    (*coada) = (struct queue) {NULL, NULL, 0};

    return coada;
}

//enqueue

Queue_t *enqueue(Queue_t *coada, Node_t *nod_to_add){
    coada->size++;

    if(coada->size == 1){
        coada->head = nod_to_add;
        coada->tail = nod_to_add;
        return coada;
    }

    coada->tail->next_node = nod_to_add;
    coada->tail = nod_to_add;

    return coada;
}
int priorityCheck(Node_t *main, Node_t *comparator){ //main este nodul 
    return main->priority < comparator->priority;
}

Queue_t *enqueuePriority(Queue_t *coada, Node_t *nod_to_add){
    coada->size++;

    if(coada->size == 1){
        coada->head = nod_to_add;
        coada->tail = nod_to_add;
        return coada;
    }

    //prioritar

    if (priorityCheck(nod_to_add, coada->head)) {
        nod_to_add->next_node = coada->head;
        coada->head = nod_to_add;
        
        if (coada->size == 1) {
            coada->tail = nod_to_add; // Actualizăm și coada->tail
    }
    return coada;
}

    Node_t *nod_anterior = coada->head;
    Node_t *nod_curent = coada->head->next_node;

    while(nod_curent){
        if(priorityCheck(nod_to_add, nod_curent)){
            nod_to_add->next_node = nod_curent;

            nod_anterior->next_node = nod_to_add;

            return coada;
        }

        nod_anterior = nod_anterior->next_node;
        nod_curent = nod_curent->next_node;
    }

    nod_anterior->next_node = nod_to_add;
    coada->tail = nod_to_add;

    return coada;
}

//dequeue

Queue_t *dequeue(Queue_t *coada){
    if(coada->size == 0){
        return coada;
    }

    if(coada->size == 1){
        coada->size = 0;
        free(coada->head);
        coada->head = NULL;
        coada->tail = NULL;
        return coada;
    }

    coada->size --;

    Node_t *nod_curent = coada->head;

    coada->head = coada->head->next_node;

    free(nod_curent);

    return coada;
}




//free

void freeQueue(Queue_t *coada){
    Node_t *nod_curent = NULL;

    for(int i = 0; i < coada->size; i++){
        nod_curent = coada->head;
        coada->head = coada->head->next_node;
        free(nod_curent);
    }

    free(coada);
}

//print

void printQueue(Queue_t *coada){
    Node_t *nod_curent = coada->head;

    for(int i = 0; i < coada->size; i++){
        printf("Data: %d, Priority: %d\n", nod_curent->data, nod_curent->priority);
        nod_curent = nod_curent->next_node;
    }
}

//main

int main(void){
    Queue_t *coada = initQueue();

    srand(time(NULL));

    printf("-----enqueue prioritate--------\n");

    for(int i = 0; i < 10; i++){
        Node_t *nod = makeNode(i, rand() % 100);
        coada = enqueuePriority(coada, nod);
    }


    printQueue(coada);

    printf("------------fara--------------\n");

    // for(int i = 0; i < 10; i++){
    //     Node_t *nod = makeNode(i, rand() % 100);
    //     coada = enqueue(coada, nod);
    // }

    // printQueue(coada);

    Node_t *nod13 = makeNode(10, 1313);
    coada = enqueue(coada, nod13);

    printQueue(coada);

    printf("-------------------------------\n");

    coada = dequeue(coada);

    printQueue(coada);

    freeQueue(coada);

    return 0;
}