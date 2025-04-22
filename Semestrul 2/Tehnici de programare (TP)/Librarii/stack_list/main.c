#include "stack_list.h"
int main(void)
{

  stack_list_t st = init_stack();

  for (int i = 0; i < 5; i++)
    st = push(st, i);

  print_stack(st);

  st = pop(st);

  printf("PEEK: %d\n", peek(st));

  print_stack(st);

  free_stack(st);

  return 0;
}
