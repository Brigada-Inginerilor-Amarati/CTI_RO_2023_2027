#ifndef __QUEUE_LIST_H
#define __QUEUE_LIST_H

#include "/Users/paulhondola/Faculta/Tehnici de Programare/libraries/headers/list.h"

typedef list_data_t payload_t;
typedef list_t queue_list_t;

// INIT
queue_list_t init_queue(void);

// FREE
void free_queue(queue_list_t queue);

// DISPLAY
void print_queue(queue_list_t queue);

// SIZE
size_t get_size(queue_list_t queue);

// ISEMPTY
int is_empty(queue_list_t queue);

// ENQUEUE
queue_list_t enqueue(queue_list_t queue, payload_t info);

// DEQUEUE
queue_list_t dequeue(queue_list_t queue);

// PEEK
payload_t head(queue_list_t queue);

#endif
