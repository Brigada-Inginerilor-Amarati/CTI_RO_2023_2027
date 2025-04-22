#ifndef TP_STACK_H
#define TP_STACK_H

typedef struct Stack* Stack_t;
typedef unsigned Element_t;

Stack_t init_Stack();

Stack_t push(Stack_t, Element_t);

Element_t pop(Stack_t);

Element_t peek(Stack_t);

#endif