// double ended queue cu lista

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int data;
    struct node *next_node;
    struct node *prev_node;
} Node_t;

typedef struct deque{
    Node_t *head;
    Node_t *tail;
    int size;
}Deque_t;

Node_t *makeNode(int data){
    Node_t *nod_creat = malloc(sizeof(Node_t));

    if(!nod_creat){
        return NULL;
    }

    (*nod_creat) = (struct node) {data, NULL, NULL};

    return nod_creat;
}

Deque_t *makeDeque(){
    Deque_t *deque_creat = malloc(sizeof(Deque_t));

    if(!deque_creat){
        return NULL;
    }

    (*deque_creat) = (struct deque) {NULL, NULL, 0};

    return deque_creat;
}

//push

Deque_t *pushFirst(Deque_t *coada, Node_t *nod){
    if(coada->size == 0){
        coada->head = nod;
        coada->tail = nod;
        coada->size++;
        return coada;
    }

    nod->next_node = coada->head;
    coada->head->prev_node = nod;
    coada->head = nod;
    coada->size++;
    return coada;
}

Deque_t *pushLast(Deque_t *coada, Node_t *nod){
    if(coada->size == 0){
        coada->head = nod;
        coada->tail = nod;
        coada->size++;
        return coada;
    }

    nod->prev_node = coada->tail;
    coada->tail->next_node = nod;
    coada->tail = nod;
    coada->size++;
    return coada;
}

//pop
Deque_t *popFirst(Deque_t *coada) {
    if (coada->size == 0) {
        printf("Coada goala\n");
        return coada;
    }

    Node_t *nod = coada->head;
    if (coada->size == 1) {
        coada->head = NULL;
        coada->tail = NULL;
    } else {
        coada->head = coada->head->next_node;
        coada->head->prev_node = NULL;
    }
    free(nod);
    coada->size--;
    return coada;
}

Deque_t *popLast(Deque_t *coada) {
    if (coada->size == 0) {
        printf("Coada goala\n");
        return coada;
    }

    Node_t *nod = coada->tail;
    if (coada->size == 1) {
        coada->head = NULL;
        coada->tail = NULL;
    } else {
        coada->tail = coada->tail->prev_node;
        coada->tail->next_node = NULL;
    }
    free(nod);
    coada->size--;
    return coada;
}


//print

void printDeque(Deque_t *coada){
    Node_t *nod = coada->head;

    while(nod){
        printf("%d ", nod->data);
        nod = nod->next_node;
    }
    printf("\n");
}

//free

void freeDeque(Deque_t *coada){
    Node_t *nod = coada->head;

    while(nod){
        Node_t *aux = nod;
        nod = nod->next_node;
        free(aux);
    }

    free(coada);
}

//main

int main(void){
    srand(time(NULL));

    Deque_t *coada = makeDeque();

    for(int i = 0; i < 10; i++){
        Node_t *nod = makeNode(i);
        //Node_t *nod = makeNode(rand() % 100);
        coada = pushFirst(coada, nod);
    }

    printDeque(coada);

    for(int i = 0; i < 10; i++){
        Node_t *nod = makeNode(i + 10);
        //Node_t *nod = makeNode(rand() % 100);
        coada = pushLast(coada, nod);
    }

    printDeque(coada);

    coada = popFirst(coada);

    coada = popLast(coada);

    printDeque(coada);

    freeDeque(coada);

    return 0;
}