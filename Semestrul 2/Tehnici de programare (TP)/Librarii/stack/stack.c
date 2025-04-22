#include "stack.h"

// STACK STRUCTURE
struct STACK
{
  size_t top;
  size_t capacity;
  stack_data *data;
};

// INITIALIZATION
stack init_stack(size_t capacity)
{

  // allocate memory for the stack structure
  stack st = (stack)malloc(sizeof(struct STACK));

  if (st == NULL)
  {
    if (STACK_DEBUG)
      printf("memory allocation failed\n");
    return NULL;
  }

  // initialize the stack with the given capacity

  *st = (struct STACK){.top = 0, .capacity = capacity, .data = NULL};

  // allocate memory for the stack data
  st->data = (stack_data *)malloc(capacity * sizeof(stack_data));

  if (st->data == NULL)
  {
    if (STACK_DEBUG)
      printf("memory allocation failed\n");
    free(st);
    return NULL;
  }

  if (STACK_DEBUG)
  {
    printf("initialization successful\n");
    printf("stack capacity set to: %zu\n", st->capacity);
  }

  return st;
}

// GETTERS
size_t stack_size(stack st)
{
  if (STACK_DEBUG)
    printf("stack size: %zu\n", st->top);
  return st->top;
}

size_t stack_capacity(stack st)
{
  if (STACK_DEBUG)
    printf("stack capacity: %zu\n", st->capacity);
  return st->capacity;
}

// STACK SIZE FUNCTIONS
int stack_is_empty(stack st)
{
  if (STACK_DEBUG && st->top == 0)
    printf("stack empty\n");
  return st->top == 0;
}

int stack_is_full(stack st)
{
  if (STACK_DEBUG && st->top >= st->capacity)
    printf("stack full\n");
  return st->top >= st->capacity;
}

stack stack_realloc(stack st)
{
  stack_data *temp = (stack_data *)realloc(
      st->data, (st->capacity + STACK_CHUNK) * sizeof(stack_data));

  if (temp == NULL)
  {
    if (STACK_DEBUG)
    {
      printf("memory reallocation failed\n");
      printf("stack capacity remains at: %zu\n", st->capacity);
      printf("no push happened\n");
    }
    return st;
  }

  st->data = temp;
  st->capacity += STACK_CHUNK;

  if (STACK_DEBUG)
    printf("stack capacity increased to: %zu\n", st->capacity);

  return st;
}

// STACK OPERATIONS
stack push(stack st, stack_data data)
{

  // full -> dynamic -> realloc -> fail or not
  // full -> static -> no push

  if (stack_is_full(st))
  {
    if (STACK_DYNAMIC)
    {
      size_t old_capacity = st->capacity;
      st = stack_realloc(st);
      if (old_capacity == st->capacity)
        return st;
    }
    else
    {
      if (STACK_DEBUG)
        printf("no push happened\n");
      return 0;
    }
  }
  if (STACK_DEBUG)
    printf("push %d\n", data);

  st->data[st->top++] = data;
  return st;
}

stack pop(stack st)
{
  if (stack_is_empty(st))
  {
    return st;
  }

  if (STACK_DEBUG)
    printf("pop %d\n", st->data[st->top - 1]);

  st->top--;
  return st;
}

stack_data peek(stack st)
{
  if (stack_is_empty(st))
  {
    return 0;
  }

  if (STACK_DEBUG)
    printf("peek %d\n", st->data[st->top - 1]);

  return st->data[st->top - 1];
}

// PRINTING
void print_stack(stack st)
{
  for (size_t i = 0; i < st->top; i++)
  {
    printf("%d ", st->data[i]);
  }
}

// FREE MEMORY
void free_stack(stack st)
{

  if (STACK_DEBUG)
    printf("free stack\n");

  free(st->data);
  free(st);
}
