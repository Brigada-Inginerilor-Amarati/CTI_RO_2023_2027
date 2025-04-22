#include <stdio.h>
#include <stdlib.h>
#include "stiva.h"

struct Stack{
    Element_t *data;
    unsigned int capacity;
    unsigned int tail;
};

struct Vector
{
    Element_t *data;
    unsigned int capacity;
};


Stack_t initStack(unsigned int dimensiune)
{
    Stack_t stiva = malloc(sizeof(struct Stack));
    stiva->capacity = dimensiune;
    stiva->data = malloc(dimensiune * sizeof(Element_t));
    stiva->tail = 0;
    return stiva;
}

StatusCode_t push(Stack_t stiva, Element_t element_adaugat)
{
    if(stiva->tail < stiva->capacity){
        stiva->data[stiva->tail++] = element_adaugat;
        return OK;
    }

    return EROARE_DEPASIRE_LIMITE;
}

StatusCode_t peek(Stack_t stiva, Element_t *element)
{
    if(stiva->tail > 0)
    {
        *element = stiva->data[stiva->tail - 1];
        return OK;
    }
    return EROARE_DEPASIRE_LIMITE;
}

Stack_t aduna_stive(Stack_t stiva1, Stack_t stiva2)
{
    unsigned int cap;
    if(stiva1->capacity > stiva2->capacity)
    {
        cap = stiva1->tail;
    }
    else{
        cap = stiva2->tail;
    }

    Stack_t stiva_suma = initStack(cap);

    unsigned int dif;

    if(stiva1->tail < cap){
        dif = cap - stiva1->tail;

        for(unsigned int i = 0; i < cap; i++)
        {
            if(i > cap - dif)
            {
                stiva_suma->data[i] = stiva2->data[i] ;
            }
            else
            {
                stiva_suma->data[i] = stiva1->data[i] + stiva2->data[i];
            }
        }
    }
    else{
        dif = cap - stiva2->tail;

        for(unsigned int i = 0; i < cap; i++)
        {
            if(i > cap - dif)
            {
                stiva_suma->data[i] = stiva1->data[i] ;
                stiva_suma->tail++;
            }
            else
            {
                stiva_suma->data[i] = stiva1->data[i] + stiva2->data[i];
                stiva_suma->tail++;
            }
        }
    }
    
    return stiva_suma;
}
/*
Stack_t aduna_stive(Stack_t stiva1, Stack_t stiva2) {
    unsigned int cap = (stiva1->tail > stiva2->tail) ? stiva1->tail : stiva2->tail;

    Stack_t stiva_suma = initStack(cap);

    for (unsigned int i = 0; i < cap; i++) {
        int val1 = (i < stiva1->tail) ? stiva1->data[i] : 0;
        int val2 = (i < stiva2->tail) ? stiva2->data[i] : 0;
        push(stiva_suma, val1 + val2);
    }

    return stiva_suma;
}

*/
/*
Stack_t aduna_stive(Stack_t stiva1, Stack_t stiva2) {
    unsigned int cap = (stiva1->capacity > stiva2->capacity) ? stiva1->capacity : stiva2->capacity;

    Stack_t stiva_suma = initStack(cap);

    for (unsigned int i = 0; i < cap; i++) {
        // Assuming 'data' is an array in the Stack_t struct
        int val1 = (i < stiva1->capacity) ? stiva1->data[i] : 0;
        int val2 = (i < stiva2->capacity) ? stiva2->data[i] : 0;
        stiva_suma->data[i] = val1 + val2;
    }

    return stiva_suma;
}*/

void printStack(Stack_t stiva) {
    if (stiva == NULL) {
        printf("Stack is NULL\n");
        return;
    }

    printf("Stack contents:\n");
    for (unsigned int i = 0; i < stiva->tail; i++) {
        printf("%d ", stiva->data[i]); // Assuming Element_t is int, adjust accordingly
    }
    printf("\n");
}

Vector_t makeVector(unsigned int cap)
{
    Vector_t vector = NULL;
    if((vector = malloc(sizeof(struct Vector))) == NULL)
    {
        vector->capacity = 0;
        return NULL;
    }

    vector->capacity = cap;
    vector->data = malloc(cap * sizeof(Element_t));
    if(vector->data == NULL)
    {
        return NULL;
    }
    return vector;
}

int impar(Element_t element)
{
    return element % 2;
}

Vector_t copiaza(Stack_t stiva, int (*cond)(Element_t))
{
    unsigned int cap = stiva->capacity;
    Vector_t vector = makeVector(cap);

    unsigned int index = 0;

    for(unsigned int i = 0; i < cap; i++)
    {
        if(cond(stiva->data[i]))
        {
            vector->data[index++] = stiva->data[i];
        }
    }
    vector->data = realloc(vector->data, index * sizeof(Element_t));
    vector->capacity = index;
    return vector;
}

void afisare(Vector_t vector)
{
    for(unsigned int i = 0; i < vector->capacity; i++)
    {
        printf("%u ", vector->data[i]);
    }
}