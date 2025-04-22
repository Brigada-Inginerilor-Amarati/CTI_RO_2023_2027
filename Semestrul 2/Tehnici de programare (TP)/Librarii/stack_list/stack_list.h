#ifndef __STACK_LIST_H
#define __STACK_LIST_H

#include "/Users/paulhondola/Faculta/Tehnici de Programare/libraries/headers/list.h"

typedef list_data_t payload_t;
typedef list_t stack_list_t;

// INIT
stack_list_t init_stack(void);

// FREE
void free_stack(stack_list_t stack);

// DISPLAY
void print_stack(stack_list_t stack);

// SIZE
size_t get_size(stack_list_t stack);

// PUSH
stack_list_t push(stack_list_t stack, payload_t info);

// POP
stack_list_t pop(stack_list_t stack);

// PEEK
payload_t peek(stack_list_t stack);

// ISEMPTY
int is_empty(stack_list_t stack);

#endif
