#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

// libraries

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constants

#define MAX_NAME_SIZE 100
#define HASH_TABLE_CHUNK 64
#define DEBUG 0

// structures

/*
typedef struct PAYLOAD {
  int key;
  double value;
  char name[MAX_NAME_SIZE];
} payload_t;
*/

typedef int payload_t;

typedef struct NODE *node_t;
typedef struct ARRAY_LIST *array_list_t;

// functions

// payload functions

payload_t create_payload(int value);
void print_payload(payload_t payload, FILE *file);

// node functions

node_t create_node(payload_t payload);
void print_node_data(node_t node, FILE *file);

// array list functions

array_list_t init_array_list(void);
void print_array_list(array_list_t arr_list, FILE *file);
void free_array_list(array_list_t arr_list);

// adding
array_list_t add_front_node(array_list_t arr_list, node_t new_node);
array_list_t add_rear_node(array_list_t arr_list, node_t new_node);
array_list_t add_index_node(array_list_t arr_list, node_t new_node,
                            size_t index);

// removing
array_list_t remove_front_node(array_list_t arr_list);
array_list_t remove_rear_node(array_list_t arr_list);
array_list_t remove_index_node(array_list_t arr_list, size_t index);

// getting
node_t get_node(array_list_t arr_list, size_t index);
payload_t get_payload(node_t node);
size_t get_size(array_list_t arr_list);
size_t get_capacity(array_list_t arr_list);

#endif
