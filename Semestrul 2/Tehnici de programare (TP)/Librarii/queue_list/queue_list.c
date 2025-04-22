#include "queue_list.h"

// INIT - initialize the queue with an empty list and size 0
queue_list_t init_queue(void) { return init_list(); }

// FREE
void free_queue(queue_list_t queue) { free_list(queue); }

// DISPLAY
void print_queue(queue_list_t queue) { print_list(queue); }

// SIZE - return the size of the queue
size_t get_size(queue_list_t queue) { return get_list_size(queue); }

// OPERATIONS

// ENQUEUE - add an element to the top of the queue

queue_list_t enqueue(queue_list_t queue, payload_t info)
{
  return add_rear_node(queue, create_node(info));
}

// POP - remove the top element from the queue

queue_list_t dequeue(queue_list_t queue) { return remove_head_node(queue); }

// PEEK - return the top element of the queue

payload_t head(queue_list_t queue)
{
  return get_node_data(get_list_head(queue));
}

// ISEMPTY - check if the queue is empty

int is_empty(queue_list_t queue) { return get_list_size(queue) == 0; }
