#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef enum { STACK_OK, STACK_EMPTY, STACK_FULL } stack_code;

typedef char stack_data;

typedef struct {
    size_t top;
    size_t capacity;
    stack_data *data;
} stack;

stack init_stack(size_t cap);
stack push(stack *st, stack_data data);
stack_data pop(stack *st);
stack_data peek(stack *st);
void free_stack(stack *st);
int check_validity(char *str);

#endif /* STACK_H */
