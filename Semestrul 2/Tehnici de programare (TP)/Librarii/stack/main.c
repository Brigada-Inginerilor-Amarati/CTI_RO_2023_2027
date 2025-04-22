#include "stack.h"

int main(void)
{

  stack st = init_stack(32);

  for (int i = 0; i < 100; i++)
  {
    st = push(st, i);
  }

  for (int i = 0; i < 100; i++)
  {
    st = pop(st);
  }

  free_stack(st);

  return 0;
}
