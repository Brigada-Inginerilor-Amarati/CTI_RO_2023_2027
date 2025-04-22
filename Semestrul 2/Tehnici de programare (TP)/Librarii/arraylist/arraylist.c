#include "arraylist.h"

// structures

struct NODE {
  payload_t payload;
  struct NODE *next;
};

struct ARRAY_LIST {
  struct NODE *item;
  size_t size;
  size_t capacity;
  struct NODE **hash_table;
};

// payload functions

payload_t create_payload(int value) {

#ifdef DEBUG
  fprintf(stderr, "Creating payload\n");
#endif

  payload_t payload = value;
  // strncpy(payload.name, name, sizeof(payload.name) - 1);
  return payload;
}

void print_payload(payload_t payload, FILE *file) {
  // fprintf(file, "KEY: %d / VALUE: %f / NAME: %s\n", payload.key,
  // payload.value, payload.name);
  fprintf(file, "%d ", payload);
}

// node functions

node_t create_node(payload_t info) {

#ifdef DEBUG
  fprintf(stderr, "Creating node\n");
#endif

  node_t node = (node_t)malloc(sizeof(struct NODE));

  if (node == NULL) {

#ifdef DEBUG
    fprintf(stderr, "Node allocation: FAIL\n");
#endif

    return NULL;
  }

#ifdef DEBUG
  fprintf(stderr, "Node allocation: SUCCESS\n");
#endif

  *node = (struct NODE){.payload = info, .next = NULL};
  return node;
}

void print_node_data(node_t node, FILE *file) {

  if (node == NULL)
    return;

  print_payload(node->payload, file);
}

node_t get_node(array_list_t list, size_t index) {

  if (list == NULL)
    return NULL;

#ifdef DEBUG
  fprintf(stderr, "Getting node at index %zu\n", index);
#endif

  return list->hash_table[index];
}

// arraylist functions

array_list_t init_array_list(void) {

#ifdef DEBUG
  fprintf(stderr, "Initializing array list\n");
#endif

  array_list_t list = (array_list_t)malloc(sizeof(struct ARRAY_LIST));

  // if the allocation fails, return NULL

  if (list == NULL) {

#ifdef DEBUG
    fprintf(stderr, "Array list allocation: FAIL\n");
#endif

    return NULL;
  }

#ifdef DEBUG
  fprintf(stderr, "Array list allocation: SUCCESS\n");
#endif

  *list = (struct ARRAY_LIST){
      .item = NULL, .size = 0, .capacity = 0, .hash_table = NULL};

  return list;
}

// insert and remove aux functions

void insert_index_to_array(array_list_t list, size_t index) {
  list->size++;
  for (size_t i = list->size - 1; i > index; i--)
    list->hash_table[i] = list->hash_table[i - 1];
}

void remove_index_from_array(array_list_t list, size_t index) {
  list->size--;
  for (size_t i = index; i < list->size; i++)
    list->hash_table[i] = list->hash_table[i + 1];
}

// realloc

void realloc_array_list(array_list_t list) {

  if (list == NULL)
    return;

  // if the list is empty -> alloc new memory for the hash table
  if (list->size == 0) {

#ifdef DEBUG
    fprintf(stderr, "List is empty\n");
#endif

    // reset the hash table
    list->hash_table = (struct NODE **)realloc(
        list->hash_table, sizeof(struct NODE *) * HASH_TABLE_CHUNK);

    // if the allocation fails, return NULL
    if (list->hash_table == NULL) {

#ifdef DEBUG
      fprintf(stderr, "Hash table allocation: FAIL\n");
#endif

      list = NULL;
      return;
    }

#ifdef DEBUG
    fprintf(stderr, "Hash table allocation: SUCCESS\n");
#endif

    list->capacity = HASH_TABLE_CHUNK;
  }

  // if the size has reached full capacity, reallocate
  else if (list->size == list->capacity) {

#ifdef DEBUG
    fprintf(stderr, "List has reached full capacity, realloc one more chunk "
                    "for the hash table\n");
#endif

    list->capacity += HASH_TABLE_CHUNK;
    list->hash_table = (struct NODE **)realloc(
        list->hash_table, sizeof(struct NODE *) * list->capacity);

    // if the reallocation fails, return NULL
    if (list->hash_table == NULL) {

#ifdef DEBUG
      fprintf(stderr, "Hash table reallocation: FAIL\n");
#endif

      list = NULL;
      return;
    }

#ifdef DEBUG
    fprintf(stderr, "Hash table reallocation: SUCCESS, new capacity: %zu\n",
            list->capacity);
#endif
  }
}

// add

array_list_t add_front_node(array_list_t list, node_t node) {

  if (list == NULL)
    return NULL;

  if (node == NULL)
    return list;

#ifdef DEBUG
  fprintf(stderr, "Adding new node to front\n");
#endif

  realloc_array_list(list);

#ifdef DEBUG
  fprintf(stderr, "New node added to front: SUCCESS, size increased to %zu\n",
          list->size + 1);
#endif

  insert_index_to_array(list, 0);
  node->next = list->item;
  list->item = node;
  list->hash_table[0] = node;
  return list;
}

array_list_t add_rear_node(array_list_t list, node_t node) {

  if (list == NULL)
    return NULL;

  if (node == NULL)
    return list;

  // if the list is empty, add the node to the front
  if (list->size == 0)
    return add_front_node(list, node);

#ifdef DEBUG
  fprintf(stderr, "Adding new node to end\n");
#endif

  realloc_array_list(list);

#ifdef DEBUG
  fprintf(stderr, "New node added to front: SUCCESS, size increased to %zu\n",
          list->size + 1);
#endif

  insert_index_to_array(list, list->size - 1);
  list->hash_table[list->size - 1] = node;
  list->hash_table[list->size - 2]->next = node;

  return list;
}

array_list_t add_index_node(array_list_t list, node_t node, size_t index) {

  if (list == NULL)
    return NULL;

  if (node == NULL)
    return list;

  if (index == 0)
    return add_front_node(list, node);

#ifdef DEBUG
  fprintf(stderr, "Adding node to index %zu\n", index);
#endif

  if (index >= list->size) {

#ifdef DEBUG
    fprintf(stderr, "Index out of bounds\nNew index set: %zu\n",
            list->size - 1);
#endif

    return add_rear_node(list, node);
  }

  realloc_array_list(list);

#ifdef DEBUG
  fprintf(stderr,
          "New node added to index %zu: SUCCESS, size increased to %zu\n",
          index, list->size + 1);
#endif

  insert_index_to_array(list, index);
  list->hash_table[index] = node;
  list->hash_table[index - 1]->next = node;
  node->next = list->hash_table[index + 1];
  return list;
}

// remove
array_list_t remove_front_node(array_list_t list) {

  if (list == NULL)
    return NULL;

  if (list->size == 0) {

#ifdef DEBUG
    fprintf(stderr, "List is empty\n");
#endif

    return list;
  }

#ifdef DEBUG
  fprintf(stderr, "Removing node from front\n");
#endif

  node_t aux = list->item;
  list->item = list->item->next;
  remove_index_from_array(list, 0);
  free(aux);
  return list;
}

array_list_t remove_rear_node(array_list_t list) {

  if (list == NULL)
    return NULL;

  if (list->size == 0) {

#ifdef DEBUG
    fprintf(stderr, "List is empty\n");
#endif

    return list;
  }

#ifdef DEBUG
  fprintf(stderr, "Removing node from end\n");
#endif

  node_t aux = list->hash_table[list->size - 1];
  list->hash_table[list->size - 1]->next = NULL;
  remove_index_from_array(list, list->size - 1);
  free(aux);
  return list;
}

array_list_t remove_index_node(array_list_t list, size_t index) {

  if (list == NULL)
    return NULL;

  // empty list case
  if (list->size == 0) {

#ifdef DEBUG
    fprintf(stderr, "List is empty\n");
#endif

    return list;
  }

  // if the index is 0, remove the first element
  if (index == 0)
    return remove_front_node(list);

#ifdef DEBUG
  fprintf(stderr, "Removing node from index %zu\n", index);
#endif

  // if the index is out of bounds, remove the last element
  if (index >= list->size) {
#ifdef DEBUG
    fprintf(stderr, "Index out of bounds\nNew index set: %zu\n",
            list->size - 1);
#endif

    return remove_rear_node(list);
  }

  node_t removed = list->hash_table[index];
  list->hash_table[index - 1]->next = list->hash_table[index + 1];
  remove_index_from_array(list, index);
  free(removed);
  return list;
}

// print
void print_array_list(array_list_t list, FILE *file) {

  if (list == NULL)
    return;

#ifdef DEBUG
  fprintf(stderr, "Printing array list -> size: %zu\n", list->size);
#endif

  for (size_t i = 0; i < list->size; i++)
    print_node_data(get_node(list, i), file);
}

// free
void print_byte_data(array_list_t list) {
  size_t list_size = sizeof(*list);
  size_t hash_table_size = sizeof(list->hash_table) * list->capacity;
  size_t node_size = sizeof(struct NODE) * list->size;

  fprintf(stderr, "TOTAL FREED MEMORY: %zu\n",
          list_size + hash_table_size + node_size);

  fprintf(stderr, "NODES: %zu(bytes) * %zu(count) = %zu(B) %.2f(KB) %.2f(MB)\n",
          sizeof(struct NODE), list->size, node_size, (float)node_size / 1024,
          (float)node_size / 1024 / 1024);
  fprintf(stderr,
          "HASH TABLE: %zu(bytes) * %zu(capacity) = %zu(B) %.2f(KB) "
          "%.2f(MB)\n",
          sizeof(list->hash_table), list->capacity, hash_table_size,
          (float)hash_table_size / 1024, (float)hash_table_size / 1024 / 1024);
  fprintf(stderr, "LIST: %zu(bytes)\n", list_size);
}

void free_array_list(array_list_t list) {

  if (list == NULL)
    return;

  for (size_t i = 0; i < list->size; i++) {

#ifdef DEBUG
    fprintf(stderr, "Freeing node at index %zu\n", i);
#endif

    free(list->hash_table[i]);
  }

#ifdef DEBUG
  print_byte_data(list);
#endif

  free(list->hash_table);
  free(list);
}

// getters

payload_t get_payload(node_t node) { return node->payload; }
size_t get_size(array_list_t arr_list) { return arr_list->size; }
size_t get_capacity(array_list_t arr_list) { return arr_list->capacity; }
