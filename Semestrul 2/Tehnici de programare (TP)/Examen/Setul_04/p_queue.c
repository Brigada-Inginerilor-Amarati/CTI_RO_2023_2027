#include "p_queue.h"

struct ELEMENT{
    int valoare;
    int prioritate;
};

struct PQ{
    Element_t *elemente;
    int capacitate;
    int head; // prim element
    int tail; //ultim element
};

Pq_t makePQ(int cap){
    Pq_t coada = malloc(sizeof(struct PQ));

    if(coada == NULL){
        printf("eroare alocare memorie coada \n");
        return NULL;
    }

    coada->head = 0;
    coada->tail = 0;
    coada->elemente = malloc(cap * sizeof(Element_t));

    if(coada->elemente == NULL){
        coada->capacitate = 0;
        return coada;
    }

    coada->capacitate = cap;

    return coada;
}

Pq_t enqueue(Pq_t coada, int val, int pr){
    Element_t element_input = malloc (sizeof(struct ELEMENT));

    element_input->prioritate = pr;
    element_input->valoare = val;


    if(coada->tail >= coada->capacitate){
        printf("Nu mai este loc in coada.\n");
        return coada;
    }

    if(coada->head == coada->tail){
        coada->elemente[coada->head] = element_input;
        coada->tail++; 
        return coada; 
    }

    for(int i = coada->head; i < coada->tail; i++){
        if(coada->elemente[i]->prioritate > element_input->prioritate){
            coada->tail++;
            for(int j = coada->tail - 1; j > i; j--){
                coada->elemente[j] = coada->elemente[j - 1];
            }

            coada->elemente[i] = element_input;
            break;

        }
    }

    return coada;
}

void afisare_coada(Pq_t coada){
    for(int i = coada->head; i < coada->tail; i++){
        printf("v: %d - p :%d \n", coada->elemente[i]->valoare, coada->elemente[i]->prioritate);
    }
    printf("\n");
}

Element_t dequeue(Pq_t coada) {
    if (coada->head < coada->tail) {
        Element_t element_scos = coada->elemente[coada->head];

        for (int i = 0; i < coada->tail - 1; i++) {
            coada->elemente[i] = coada->elemente[i + 1];
        }

        coada->tail--;

        return element_scos;
    } else {
        exit(-1);
    }
}

void print_element(Element_t element) {
    printf("v : %d - p : %d \n", element->valoare, element->prioritate);
}
