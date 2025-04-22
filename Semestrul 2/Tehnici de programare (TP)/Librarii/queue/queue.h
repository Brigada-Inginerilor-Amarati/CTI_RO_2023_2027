#ifndef __QUEUE_H
#define __QUEUE_H

// libraries
#include <stdio.h>
#include <stdlib.h>

// constants
#define QUEUE_DEBUG 0
#define QUEUE_DYNAMIC 0
#define QUEUE_CHUNK 16

// data structures
typedef int queue_data;
typedef struct QUEUE *queue;

// FUNCTIONS

// INITIALIZATION
queue init_queue(size_t);

// GETTERS
size_t get_queue_size(queue);
size_t get_queue_capacity(queue);

// QUEUE SIZE FUNCTIONS
int queue_is_empty(queue);
int queue_is_empty(queue);
queue queue_realloc(queue);

// QUEUE OPERATIONS
queue enqueue(queue, queue_data);
queue dequeue(queue);
void move_queue(queue);
queue_data head(queue);
queue_data tail(queue);

// DEBUGGING
void print_queue(queue);

// FREE
void free_queue(queue);

#endif
