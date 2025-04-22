#ifndef __STIVA_H
    #define __STIVA_H

typedef int Element_t;

typedef struct Stack* Stack_t;

typedef struct Vector* Vector_t;

typedef enum {OK, EROARE_DEPASIRE_LIMITE} StatusCode_t;

Vector_t makeVector(unsigned int);

Stack_t initStack(unsigned int dimensiune);

StatusCode_t push(Stack_t, Element_t);

StatusCode_t peek(Stack_t, Element_t*);

Stack_t aduna_stive(Stack_t, Stack_t);

void printStack(Stack_t stiva);

Vector_t copiaza(Stack_t, int (*cond)(Element_t));

void afisare(Vector_t);

int impar(Element_t element);

#endif