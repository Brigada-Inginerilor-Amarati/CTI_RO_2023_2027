#ifndef __STACK_H
#define __STACK_H

// LIBRARIES
#include <stdio.h>
#include <stdlib.h>

// CONSTANTS
#define STACK_DEBUG 0
#define STACK_DYNAMIC 0
#define STACK_CHUNK 16

// STRUCTURES
typedef int stack_data;
typedef struct STACK *stack;

// FUNCTIONS

// INITIALIZATION
stack init_stack(size_t);

// GETTERS
size_t get_stack_size(stack);
size_t get_stack_capacity(stack);

// STACK SIZE FUNCTIONS
int stack_is_empty(stack);
int stack_is_full(stack);
stack stack_realloc(stack);

// STACK OPERATIONS
stack push(stack, stack_data);
stack pop(stack);
stack_data peek(stack);

// DEBUGGING
void print_stack(stack);

// FREE
void free_stack(stack);

#endif
