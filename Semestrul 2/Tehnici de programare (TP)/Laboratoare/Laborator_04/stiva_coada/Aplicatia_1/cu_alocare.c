/*Aplicatia 1:

Sa se defineasca si implementeze un tip de date Stack_t si operatiile specifice unei stive astfel:

Stack_t push(Stack_t, Element_t);
Element_t pop(Stack_t); 
Element_t peek(Stack_t);

a) structura de date va fi implementata in mod static (fara redimensionarea capacitatii); se vor verifica operatiile la depasire de overflow si underflow;

b) structura de date va fi implementata in mod dinamic (cu utilizarea operatiilor de gestiune dinamica a memoriei); in continuare operatiile pot da flag-uri de eroare (var globala)
*/

#include <stdio.h>
#include <stdlib.h>

#define STACK_CHUNK 10

typedef enum {STACK_OK, STACK_EMPTY, STACK_FULL} Stack_Code_t;

Stack_Code_t error_code;

typedef int Stack_Data_t;

typedef struct
{
    size_t stack_pointer;
    size_t capacity;
    Stack_Data_t *data;
}Stack_t;

Stack_Code_t init_Stack(Stack_t *stiva, size_t cap)
{
    *stiva = (Stack_t) {0, 0, NULL};

    stiva->data = (Stack_Data_t*) malloc(cap * sizeof(Stack_Data_t));

    if(stiva->data == NULL)
    {
        stiva->capacity = 0;
        return STACK_EMPTY;
    }

    stiva->capacity = cap;
    return STACK_OK;
}

Stack_Code_t is_empty(Stack_t *stiva)
{
    if(stiva-> stack_pointer == 0)
    {
        return STACK_EMPTY;
    }

    return STACK_OK;
}

Stack_Code_t is_full(Stack_t *stiva)
{
    if(stiva-> stack_pointer >= stiva -> capacity)
    {
        return STACK_FULL;
    }

    return STACK_OK;
}

Stack_Data_t peek(Stack_t *stiva)
{
    if(is_empty(stiva) == STACK_EMPTY)
    {
        return 0;
    }

    return (stiva-> data[stiva->stack_pointer - 1]);
}

Stack_Code_t push(Stack_t *stiva, Stack_Data_t data)
{
    if(is_full(stiva) == STACK_FULL)
    {
        stiva->capacity += STACK_CHUNK;

        stiva->data = (Stack_Data_t *) realloc(stiva->data, stiva->capacity * sizeof(Stack_Data_t));

        if(stiva->data == NULL)
        {
            stiva->capacity = 0;
            return STACK_FULL;
        }
    }

    stiva->data[stiva->stack_pointer ++] = data;
    return STACK_OK;
}

Stack_Code_t pop(Stack_t *stiva)
{
    if(is_empty(stiva) == STACK_EMPTY)
    {
        return STACK_EMPTY;
    }

    stiva->stack_pointer --;

    if(is_empty(stiva) == STACK_EMPTY)
    {
        return STACK_EMPTY;
    }

    return STACK_OK;
}

int main(void) {
    Stack_t stiva;
    size_t initial_capacity = 10;

    // Inițializarea stivei
    if (init_Stack(&stiva, initial_capacity) != STACK_OK) {
        printf("Eroare la inițializare.\n");
        return EXIT_FAILURE;
    }

    // Adăugarea unor elemente în stivă
    for (int i = 0; i < 15; i++) {
        if (push(&stiva, i) == STACK_FULL) {
            printf("Stiva este plină, nu se poate adăuga %d.\n", i);
        }
    }

    // Afișarea elementului din vârful stivei
    printf("Elementul din vârful stivei: %d\n", peek(&stiva));

    // Scoaterea unor elemente din stivă
    for (int i = 0; i < 10; i++) {
        if (pop(&stiva) == STACK_EMPTY) {
            printf("Stiva este goală, nu se poate scoate element.\n");
        }
    }

    // Eliberarea memoriei alocate pentru stivă
    free(stiva.data);

    return 0;
}