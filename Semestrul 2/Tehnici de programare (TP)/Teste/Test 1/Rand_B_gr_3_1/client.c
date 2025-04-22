#include <stdio.h>
#include <stdlib.h>
#include "coada.h"

#define Q_CAP 10

int main(void)
{
    PQ_t coada = MakeQ(Q_CAP);

    enqueue(coada, 1);
    enqueue(coada, 2);
    enqueue(coada, 3);
    enqueue(coada, 4);
    enqueue(coada, 5);
    enqueue(coada, 6);
    print_queue(coada);

    Element_t element_scos = dequeue(coada);
    printf("\n");

    print_queue(coada);

    printf("\nElement scos : %u \n", element_scos);

    

    //PQ_t F = filter(coada, par);
    //printf("%u\n", dequeue(F));
    //print_queue(coada);
    coada = inverseaza_ordinea(coada, 3);
    print_queue(coada);
    printf("\n");

    free_coada(coada);


    //printf("%u\n", dequeue(F));
    return 0;
}