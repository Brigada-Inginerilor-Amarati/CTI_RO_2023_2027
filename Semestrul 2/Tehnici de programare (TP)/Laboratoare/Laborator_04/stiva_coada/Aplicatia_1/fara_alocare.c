/*Aplicatia 1:

Sa se defineasca si implementeze un tip de date Stack_t si operatiile specifice unei stive astfel:

Stack_t push(Stack_t, Element_t);
Element_t pop(Stack_t); 
Element_t peek(Stack_t);

a) structura de date va fi implementata in mod static (fara redimensionarea capacitatii); se vor verifica operatiile la depasire de overflow si underflow;

b) structura de date va fi implementata in mod dinamic (cu utilizarea operatiilor de gestiune dinamica a memoriei); in continuare operatiile pot da flag-uri de eroare (var globala)*/

#include <stdio.h>
#include <stdlib.h>

typedef enum {STACK_OK, STACK_EMPTY, STACK_FULL} Stack_Code_t;

Stack_Code_t error_code;

typedef int Stack_Data_t;

typedef struct
{
    size_t stack_pointer;
    size_t capacity;
    Stack_Data_t *data;
}Stack_t;

Stack_t init_stack(size_t cap)
{
    Stack_t stiva;

    stiva.data = (Stack_Data_t*) malloc(cap * sizeof(Stack_Data_t));

    if(stiva.data == NULL)
    {
        stiva.capacity = 0; // setam capacitatea stivei la 0
        error_code = STACK_EMPTY;
        return stiva;
    }

    stiva.stack_pointer = 0;
    stiva.capacity = cap;
    error_code = STACK_OK;

    return stiva;
}

Stack_t push(Stack_t *stiva, Stack_Data_t data)
{
    if(stiva -> stack_pointer >= stiva -> capacity)
    {
        error_code = STACK_FULL;
        return *stiva;
    }

    error_code = STACK_OK;

    //daca este loc, adaugam elementul dat ca parametru in stiva
    stiva -> data[stiva -> stack_pointer++] = data;

    return *stiva;
}

Stack_Data_t peek(Stack_t *stiva)
{
    if(error_code == STACK_EMPTY)
    {
        return 0;
    }

    error_code = STACK_OK;

    return stiva -> data[stiva -> stack_pointer - 1];
}

Stack_Data_t pop(Stack_t *stiva)
{
    if(error_code != STACK_EMPTY)
    {
        error_code = STACK_OK;
        stiva -> stack_pointer --;
        return stiva -> data[stiva ->stack_pointer];
    }

    error_code = STACK_EMPTY;
    return 0;
}

int main(void)
{
    Stack_t stiva = init_stack(10);

    if(error_code == STACK_EMPTY)
    {
        perror("Stiva e goala.\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < 10; i++)
    {
        stiva = push(&stiva, i);

        if(error_code == STACK_FULL)
        {
            perror("Stiva e plina.\n");
            exit(EXIT_FAILURE);
        }

        printf("Elementul %d = %d\n", i+1, peek(&stiva));
    }

    free(stiva.data);


    return 0;
}


