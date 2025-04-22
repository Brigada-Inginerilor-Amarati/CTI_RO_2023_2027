#include "p_queue.h"



int main(void){
    Pq_t coada = makePQ(10);

    //verificam daca este ok creata coada
    if(coada == NULL){
        printf("eroare la crearea cozii \n");
        return -1;
    }
    coada = enqueue(coada, 3, 3);
    coada = enqueue(coada, 1, 1);
    coada = enqueue(coada, 2, 2);

    Element_t el = dequeue(coada);

    print_element(el);

    printf("-------------------\n");

    afisare_coada(coada);
    return 0;
}