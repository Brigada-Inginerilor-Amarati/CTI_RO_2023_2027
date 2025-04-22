// Implementati un double ended queue 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

#define DEBUG 1

typedef struct{
    int data[MAX];
    int head;
    int tail;
    int stare;
}Deque_t;

Deque_t* makeDeque(){
    Deque_t *deque = malloc(sizeof(Deque_t));

    if(!deque){
        printf("eroare memorie \n");
        return NULL;
    }

    deque->head = 0;
    deque->tail = 0;
    deque->stare = 0;

    return deque;
}

Deque_t *pushFront(Deque_t *coada, int info){
    if(coada->head == coada->tail && coada->stare == 1){
        printf("coada plina \n");
        return coada;
    }

    if(coada->head == 0){
        coada->head = MAX - 1;
    }
    else{
        coada->head--;
    }

    coada->data[coada->head] = info;
    coada->stare = 1;

    if(DEBUG)
        printf("el adaugat %d \n", coada->data[coada->head]);

    return coada;
}

Deque_t *pushBack(Deque_t *coada, int info){
    if(coada->head == coada->tail && coada->stare == 1){
        printf("coada plina \n");
        return coada;
    }
    if(coada->tail == MAX - 1){
        coada->tail = 0;
        coada->data[coada->tail] = info;
        if(DEBUG)
            printf("el adaugat %d \n", coada->data[coada->tail]);
    }
    else{
        coada->data[coada->tail] = info;
        if(DEBUG)
            printf("el adaugat %d \n", coada->data[coada->tail]);
        coada->tail++;


    }

    coada->stare = 1;



    return coada;
}

Deque_t * popFront(Deque_t *coada, int *element_scos){
    if(coada->stare == 0){
        printf("coada goala \n");
        return coada;
    }

    *element_scos = coada->data[coada->head];

    if(coada->head == MAX - 1){
        coada->head = 0;
    }
    else{
        coada->head++;
    }

    if(coada->head == coada->tail){
        coada->stare = 0;
    }

    return coada;    
}

Deque_t * popBack(Deque_t *coada, int *element_scos){
    if(coada->stare == 0){
        printf("coada goala \n");
        return coada;
    }

    *element_scos = coada->data[coada->tail - 1];

    if(coada->tail == 0){
        coada->tail = MAX - 1;
    }
    else{
        coada->tail--;
    }

    if(coada->head == coada->tail){
        coada->stare = 0;
    }

    return coada;
}

void printCoada(Deque_t *coada){
    if(coada->stare == 0){
        printf("coada goala \n");
        return;
    }

    int i = coada->head;

    if(i == coada->tail){
         printf("%d ", coada->data[i]);  //  inseamna ca coada e plina si vom parcurge primul elem ca sa scapam de contitia asta
        i = (i + 1) % MAX;
    }

    while(i != coada->tail){
        printf("%d ", coada->data[i]);
        i = (i + 1) % MAX;
    }

    printf("\n");

}


int main(void){
    srand(time(NULL));

    Deque_t *coada = makeDeque();

    for(int i = 0; i < 10; i++){
        coada = pushFront(coada, i);
    }

    printCoada(coada);

    for(int i = 10; i < 20; i++){
        coada = pushBack(coada, i);
    }

    printCoada(coada);

    for(int i = 0; i < 10; i++){
        int element_scos;
        coada = popFront(coada, &element_scos);
        printf("element scos %d \n", element_scos);
    }

    printCoada(coada);

    for(int i = 0; i < 10; i++){
        int element_scos;
        coada = popBack(coada, &element_scos);
        printf("element scos %d \n", element_scos);
    }

    printCoada(coada);

    return 0;
}