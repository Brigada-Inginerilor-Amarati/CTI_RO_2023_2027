#include <stdio.h>
#include <stdlib.h>

typedef unsigned Element_t;

// size_t -> unsigned long long
typedef enum
{
  ST_OK,
  ST_EMPTY,
  ST_FULL
} StackCodes_t;

typedef struct
{
  Element_t *data;
  size_t size;
  size_t capacity;
} Stack_t;

Stack_t make_stack(size_t cap)
{
  Stack_t st = {NULL, 0, cap};

  st.data = malloc(cap * sizeof(Element_t));

  if (st.data == NULL)
  {
    st.capacity = 0;
    return st;
  }

  return st;
}

// return the stack or an error code
Stack_t push(Stack_t st, Element_t el, StackCodes_t *code)
{
  if (st.size < st.capacity)
  {
    *code = ST_OK;
    st.data[st.size++] = el;
  }

  *code = ST_FULL;
  return st;
}

//
Element_t peek(Stack_t st, StackCodes_t *code)
{
  if (st.size > 0)
  {
    *code = ST_OK;
    return st.data[st.size - 1];
  }

  *code = ST_EMPTY;
  return 0;
}

int main(void)
{

  Stack_t st = make_stack(10);
  StackCodes_t st_code;

  st = push(st, 10, &st_code);
  st = push(st, 20, &st_code);
  st = push(st, 30, &st_code);
  st = push(st, 40, &st_code);

  return 0;
}
