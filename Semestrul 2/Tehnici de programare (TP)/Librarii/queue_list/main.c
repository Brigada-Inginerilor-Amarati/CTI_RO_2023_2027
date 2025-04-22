#include "queue_list.h"

int main(void)
{

  queue_list_t queue = init_queue();

  for (int i = 0; i < 10; i++)
    queue = enqueue(queue, i);

  print_queue(queue);

  queue = dequeue(queue);

  printf("PEEK: %d\n", head(queue));

  print_queue(queue);

  free(queue);

  return 0;
}
