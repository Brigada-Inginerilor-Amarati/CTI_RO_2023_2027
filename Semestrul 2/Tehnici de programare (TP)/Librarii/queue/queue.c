#include "queue.h"

struct QUEUE
{
  size_t head;
  size_t tail;
  size_t capacity;
  queue_data *data;
};

// INITIALIZATION
queue init_queue(size_t capacity)
{

  // Allocate memory for the queue structure
  queue q = (queue)malloc(sizeof(struct QUEUE));

  if (q == NULL)
  {
    if (QUEUE_DEBUG)
      printf("Memory allocation failed\n");
    return NULL;
  }

  // Initialize the queue structure
  *q = (struct QUEUE){.head = 0, .tail = 0, .capacity = capacity, .data = NULL};

  // Allocate memory for the queue data
  q->data = (queue_data *)malloc(capacity * sizeof(queue_data));

  if (q->data == NULL)
  {
    if (QUEUE_DEBUG)
      printf("Memory allocation failed\n");

    free(q);
    return NULL;
  }

  if (QUEUE_DEBUG)
  {
    printf("Initialization successful\n");
    printf("Queue capacity set to: %zu\n", q->capacity);
  }

  return q;
}

// GETTERS
size_t get_head_position(queue q)
{
  if (QUEUE_DEBUG)
    printf("head position: %zu\n", q->head);
  return q->head;
}

size_t get_tail_position(queue q)
{
  if (QUEUE_DEBUG)
    printf("tail position: %zu\n", q->tail);
  return q->tail;
}

size_t get_capacity(queue q)
{
  if (QUEUE_DEBUG)
    printf("queue capacity: %zu\n", q->capacity);
  return q->capacity;
}

// QUEUE SIZE FUNCTIONS
int queue_is_empty(queue q)
{
  if (QUEUE_DEBUG && q->head == q->tail)
    printf("queue empty\n");
  return q->head == q->tail;
}

int queue_is_full(queue q)
{
  if (QUEUE_DEBUG && q->tail >= q->capacity)
    printf("queue full\n");
  return q->tail >= q->capacity;
}

queue queue_realloc(queue q)
{
  queue_data *temp = (queue_data *)realloc(
      q->data, (q->capacity + QUEUE_CHUNK) * sizeof(queue_data));

  if (temp == NULL)
  {
    if (QUEUE_DEBUG)
    {
      printf("memory reallocation failed\n");
      printf("queue capacity remains at: %zu\n", q->capacity);
      printf("no enqueue happened\n");
    }
    return q;
  }

  q->data = temp;
  q->capacity += QUEUE_CHUNK;

  if (QUEUE_DEBUG)
    printf("queue capacity increased to: %zu\n", q->capacity);

  return q;
}

// QUEUE OPERATIONS
queue enqueue(queue q, queue_data data)
{

  if (queue_is_full(q))
  {
    if (QUEUE_DYNAMIC)
    {
      size_t old_capacity = q->capacity;
      q = queue_realloc(q);
      if (old_capacity == q->capacity)
        return q;
    }
    else
    {
      if (QUEUE_DEBUG)
        printf("no enqueue happened\n");
      return q;
    }
  }

  if (QUEUE_DEBUG)
    printf("enqueue: %d\n", data);

  q->data[q->tail++] = data;

  return q;
}

void move_queue(queue q)
{
  for (size_t i = q->head; i < q->tail; i++)
  {
    q->data[i - q->head] = q->data[i];
  }
}

queue dequeue(queue q)
{
  if (queue_is_empty(q))
  {
    return q;
  }

  if (QUEUE_DEBUG)
  {
    printf("dequeue %d\n", q->data[q->head]);
  }

  q->head++;

  if (q->head == QUEUE_CHUNK)
  {
    if (QUEUE_DEBUG)
    {
      printf("chunk reached, resetting head position to 0\n");
    }

    move_queue(q);
  }

  return q;
}

queue_data head(queue q)
{
  if (queue_is_empty(q))
    return 0;
  if (QUEUE_DEBUG)
    printf("head: %d\n", q->data[q->head]);
  return q->data[q->head];
}

queue_data tail(queue q)
{
  if (queue_is_empty(q))
    return 0;
  if (QUEUE_DEBUG)
    printf("tail: %d\n", q->data[q->tail - 1]);
  return q->data[q->tail - 1];
}

// DEBUGGING
void print_queue(queue q)
{
  for (size_t i = q->head; i < q->tail; i++)
  {
    printf("%d ", q->data[i]);
  }
}

// FREE
void free_queue(queue q)
{
  if (QUEUE_DEBUG)
    printf("free queue\n");

  free(q->data);
  free(q);
}
