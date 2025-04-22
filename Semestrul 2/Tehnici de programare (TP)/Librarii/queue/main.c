#include "queue.h"

int main()
{

  queue q = init_queue(QUEUE_CHUNK);

  for (int i = 0; i < 106; i++)
    q = enqueue(q, i);

  for (int i = 0; i < 50; i++)
    q = dequeue(q);

  for (int i = 106; i < 130; i++)
    q = enqueue(q, i);

  free_queue(q);

  return 0;
}
