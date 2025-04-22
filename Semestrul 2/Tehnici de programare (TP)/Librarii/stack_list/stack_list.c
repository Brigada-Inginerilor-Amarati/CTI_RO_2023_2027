#include "stack_list.h"

// INIT - initialize the stack with an empty list and size 0
stack_list_t init_stack(void) { return init_list(); }

// FREE
void free_stack(stack_list_t stack) { free_list(stack); }

// DISPLAY
void print_stack(stack_list_t stack) { print_list(stack); }

// SIZE - return the size of the stack
size_t get_size(stack_list_t stack) { return get_list_size(stack); }

// ISEMPTY - check if the stack is empty
int is_empty(stack_list_t stack) { return get_list_size(stack) == 0; }

// OPERATIONS

// PUSH - add an element to the top of the stack
stack_list_t push(stack_list_t stack, payload_t info)
{
  return add_head_node(stack, create_node(info));
}

// POP - remove the top element from the stack
stack_list_t pop(stack_list_t stack) { return remove_head_node(stack); }

// PEEK - return the top element of the stack
payload_t peek(stack_list_t stack)
{
  return get_node_data(get_list_head(stack));
}
