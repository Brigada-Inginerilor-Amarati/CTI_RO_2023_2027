/*
Problema 1: Coada Circulară
Implementați o coadă circulară folosind un vector de dimensiune fixă.

Cerințe:

Implementați funcțiile de inițializare, adăugare (enqueue) și eliminare (dequeue).
Coada trebuie să gestioneze situațiile de depășire și subutilizare a capacității (coada plină și coada goală).
Testați funcționalitatea cozii cu operațiuni diverse.
Observații:
Programul livrat va trebui să se compileze fără niciun fel de mesaje din partea compilatorului.
Programul trebuie să respecte indentarea specificată.

Cum functioneaza o coada circulara?
O coada circulara este o structura de date in care elementele sunt adaugate la un capat si eliminate de la celalalt capat. 
Daca se ajunge la capatul vectorului, se revine la inceputul acestuia. Astfel, coada circulara nu are un capat fix, ci se roteste in jurul vectorului.   
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5

typedef struct{
    int data[SIZE];
    int head;
    int tail;
    unsigned short stare;   //  0 cand este goala, 1 cand are elemente
}coadaCirculara_t;          //  altfel ar fi confuzie intre conditiile de la coada plina si coada goala, ca sunt aceleasi, prin asta difera, stare

coadaCirculara_t *makeCoada(){
    coadaCirculara_t *coada = malloc(sizeof(coadaCirculara_t));

    if(!coada){
        printf("eroare la alocarea memoriei\n");
        return NULL;
    }

    coada->head = 0;
    coada->tail = 0;
    coada->stare = 0;   //  initializam starea pe 0 deoarece la inceput nu avem elem

    return coada;
}

coadaCirculara_t *enqueue(coadaCirculara_t *coada, int value){
    if(coada->tail == coada->head && coada->stare == 1){    //  daca starea e 1 adc daca are elemente
        printf("coada plina\n");                            //  inseamna ca nu mai putem adauga
        return coada;
    }

    coada->data[coada->tail] = value;
    coada->tail = (coada->tail + 1) % SIZE;
    coada->stare = 1;   //  actualizam starea pe 1 cand adaugam un elem

    return coada;
}

coadaCirculara_t *dequeue(coadaCirculara_t *coada, int *element_scos){
    if(coada->head == coada->tail && coada->stare == 0){    //  daca starea e 0 adc nu are elemente
        printf("coada goala\n");                            //  inseamna ca nu mai putem scoate
        return coada;                                       //  cititorul atent observa ca fara aceasta stare, conditiile la coada plina si coada goala sunt asemenea
    }

    *element_scos = coada->data[coada->head];
    coada->head = (coada->head + 1) % SIZE;

    if (coada->head == coada->tail) //  daca nu mai avem elem dupa ce am scos, actualizam starea pe 0
        coada->stare = 0;

    return coada;
}

void printCoada(coadaCirculara_t *coada){
    int i = coada->head;

    if (i == coada->tail) {             //  daca i == coada->tail din prima, nu inseamna ca am terminat de parcurs
        printf("%d ", coada->data[i]);  //  inseamna ca coada e plina si vom parcurge primul elem ca sa scapam de contitia asta
        i = (i + 1) % SIZE;
    }

    while(i != coada->tail){
        printf("%d ", coada->data[i]);
        i = (i + 1) % SIZE;
    }

    printf("\n");
}


int main(void){

    srand(time(NULL));
    coadaCirculara_t *coada = makeCoada();

    if(!coada){
        return -1;
    }

    for(int i = 0; i < SIZE; i++){
        coada = enqueue(coada, i);
    }

    printCoada(coada);

    int el = 0;
    coada = dequeue(coada, &el);
    coada = dequeue(coada, &el);

    coada = enqueue(coada, 13 + rand() % 1);
    coada = enqueue(coada, 13 + rand() % 1);

    printCoada(coada);
    printf("%d \n", el);
    
    return 0;
}
