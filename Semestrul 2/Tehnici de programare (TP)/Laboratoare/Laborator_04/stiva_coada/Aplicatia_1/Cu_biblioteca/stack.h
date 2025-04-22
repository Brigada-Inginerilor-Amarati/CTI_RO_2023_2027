#ifndef __STACK_H

    #define __STACK_H


#include <stdio.h>
#include <stdlib.h>

#define STACK_CHUNK 16

typedef enum{STACK_OK, STACK_EMPTY, STACK_FULL} Stack_Code;

typedef int stack_data;

typedef struct
{
    size_t stack_pointer;
    size_t capacity;
    stack_data *data;
}stack;

Stack_Code init_stack(stack *stiva, size_t capacity);

Stack_Code is_empty(stack *stiva);

Stack_Code is_full(stack *stiva);

Stack_Code push(stack *stiva, stack_data element);

Stack_Code pop(stack *stiva);

Stack_Code peek(stack *stiva);

void free_stack(stack *stiva);


#endif