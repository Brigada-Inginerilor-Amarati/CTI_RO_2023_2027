#include <stdio.h>
#include <stdlib.h>
#include "stiva.h"

int main(void)
{   
    Stack_t stiva1 = initStack(10);

    push(stiva1, 10);
    push(stiva1, 20);
    push(stiva1, 30);
    push(stiva1, 10);
    push(stiva1, 10);
    push(stiva1, 10);
    push(stiva1, 10);
    push(stiva1, 10);
    printStack(stiva1);

    Stack_t stiva2 = initStack(6);
    push(stiva2, 1);
    push(stiva2, 1);
    push(stiva2, 1);
    push(stiva2, 1);
    push(stiva2, 1);
    printStack(stiva2);

    Stack_t stiva_suma = aduna_stive(stiva1, stiva2);
     Element_t element_peek;
    peek(stiva_suma, &element_peek);
    printf("\n %u \n", element_peek);
    printStack(stiva_suma);

    Vector_t vector = copiaza(stiva2, impar);
    afisare(vector);
    return 0;
}