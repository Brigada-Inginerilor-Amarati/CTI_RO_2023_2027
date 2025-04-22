#include <stdio.h>
#include <stdlib.h>

typedef enum
{
  Q_OK,
  Q_EMPTY,
  Q_FULL
} QueueCodes_t;

typedef unsigned Element_t;

typedef struct
{
  Element_t *data;
  size_t tail;
  size_t capacity;
} Queue_t;

Queue_t make_queue(size_t cap)
{
  Queue_t q = {NULL, 0, cap};

  q.data = malloc(cap * sizeof(Element_t));

  if (q.data == NULL)
  {
    q.capacity = 0;
    return q;
  }

  return q;
}

QueueCodes_t enque(Queue_t *q, Element_t el)
{
  if (q->tail < q->capacity)
  {
    q->data[q->tail++] = el;
    return Q_OK;
  }

  return Q_FULL;
}

QueueCodes_t deque(Queue_t *q, Element_t *el)
{
  if (q->tail > 0)
  {
    *el = q->data[--q->tail];
    return Q_OK;
  }

  return Q_EMPTY;
}

int main(void)
{
  Queue_t q = make_queue(10);

  QueueCodes_t err_code;

  if ((err_code = enque(&q, 100)) == Q_FULL)
  {
    printf("Queue is full\n");
  }

  Element_t value;

  if ((err_code = deque(&q, &value)) == Q_EMPTY)
  {
    printf("Queue is empty\n");
  }

  printf("Am scos %u din coada\n", value);

  return 0;
}
