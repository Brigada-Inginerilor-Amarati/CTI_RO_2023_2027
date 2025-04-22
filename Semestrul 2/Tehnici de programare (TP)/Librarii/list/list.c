#include "list.h"

// structures

struct NODE
{
  list_data_t data;
  struct NODE *next;
};

struct LIST
{
  struct NODE *head;
  struct NODE *rear;
};

// functions

// node

node_t create_node(list_data_t input_data)
{

  if (DEBUG)
    fprintf(stderr, "Creating node\n");

  node_t node = (node_t)malloc(sizeof(struct NODE));

  if (node == NULL)
  {
    if (DEBUG)
      fprintf(stderr, "Node allocation: FAIL\n");

    return NULL;
  }

  if (DEBUG)
    fprintf(stderr, "Node allocation: SUCCESS\n");

  *node = (struct NODE){input_data, NULL};

  return node;
}

void print_node_data(node_t node)
{
  if (node == NULL)
    return;

  printf("%d", node->data);
}

// getters

size_t get_list_size(list_t list)
{
  size_t index = 0;
  node_t current = list->head;

  while (current != NULL)
  {
    index++;
    current = current->next;
  }

  return index;
}

list_data_t get_node_data(node_t node) { return node->data; }

node_t get_next_node(node_t node) { return node->next; }

node_t get_list_head(list_t list) { return list->head; }

node_t get_list_rear(list_t list) { return list->rear; }

node_t move_list_head(list_t list)
{
  if (list == NULL)
    return NULL;

  if (list->head == NULL)
    return NULL;

  node_t temp = list->head;
  list->head = list->head->next;

  return temp;
}

// list operations -> initialisation, print all node data, free the list

list_t init_list(void)
{

  list_t list = (list_t)malloc(sizeof(struct LIST));

  if (list == NULL)
  {
    if (DEBUG)
      fprintf(stderr, "List allocation: FAIL\n");

    return NULL;
  }

  if (DEBUG)
    fprintf(stderr, "List allocation: SUCCESS\n");

  *list = (struct LIST){NULL, NULL};
  return list;
}

void print_list(list_t list)
{

  if (list == NULL)
  {
    if (DEBUG)
      fprintf(stderr, "List is NULL\n");
    return;
  }

  if (DEBUG)
    fprintf(stderr, "Printing list\n");

  node_t current = list->head;

  size_t i = 0;

  while (current != NULL)
  {
    printf("Node %zu: ", i++);
    print_node_data(current);
    printf("\n");
    current = current->next;
  }

  printf("NULL\n....................\n");
}

// list operations -> get the size of the list

void print_byte_data(list_t list)
{
  node_t current = list->head;

  size_t count = 0;
  while (current != NULL)
  {
    count++;
    current = current->next;
  }

  fprintf(stderr, "Node count: %zu\n", count);
  fprintf(stderr, "Size of a node: %zu\n", sizeof(struct NODE));
  fprintf(stderr, "Size of the full list: %zu\n", sizeof(struct NODE) * count);
}

void free_list(list_t list)
{

  if (DEBUG)
    fprintf(stderr, "Freeing list\n");

  print_byte_data(list);

  node_t current = list->head;

  while (current != NULL)
  {
    node_t temp = current;
    current = current->next;
    free(temp);
  }

  free(list);
}

// list operations -> add to front, rear or to a specific index

list_t add_head_node(list_t list, node_t node)
{

  if (list == NULL)
    return NULL;

  if (node == NULL)
    return list;

  // if list is empty, add node to head and rear
  if (list->head == NULL)
  {
    if (DEBUG)
      fprintf(stderr, "List is empty, adding node to head and rear\n");

    list->head = node;
    list->rear = node;
    return list;
  }

  if (DEBUG)
    fprintf(stderr, "New node added to front\n");

  node->next = list->head;
  list->head = node;

  return list;
}

list_t add_rear_node(list_t list, node_t node)
{

  if (list == NULL)
    return NULL;

  if (node == NULL)
    return list;

  // if list is empty, add node to head and rear

  if (list->head == NULL)
  {
    if (DEBUG)
      fprintf(stderr, "List is empty, adding node to head and rear\n");

    list->head = node;
    list->rear = node;
    return list;
  }

  if (DEBUG)
    fprintf(stderr, "New node added to rear\n");

  list->rear->next = node;
  list->rear = list->rear->next;

  return list;
}

list_t add_index_node(list_t list, node_t node, size_t index)
{

  if (list == NULL)
    return NULL;

  if (node == NULL)
    return list;

  if (index == 0)
    return add_head_node(list, node);

  node_t current = list->head;
  size_t i = 0;

  while (current != NULL && i < index - 1)
  {
    current = current->next;
    i++;
  }

  if (current == NULL)
    return add_rear_node(list, node);

  if (DEBUG)
    fprintf(stderr, "New node added to index %zu\n", index);

  node->next = current->next;
  current->next = node;

  return list;
}

// list operations -> pop front, rear or from a specific index

list_t remove_head_node(list_t list)
{

  if (list == NULL)
    return NULL;

  if (list->head == NULL)
  {
    if (DEBUG)
      fprintf(stderr, "List is empty, no action taken\n");

    return list;
  }

  if (list->head->next == NULL)
  {

    if (DEBUG)
      fprintf(stderr, "Removed last item in list\n");

    free(list->head);

    *list = (struct LIST){NULL, NULL};

    return list;
  }

  if (DEBUG)
    fprintf(stderr, "pop front / data: %d\n", list->head->data);

  node_t temp = list->head;
  list->head = list->head->next;
  free(temp);

  return list;
}

list_t remove_rear_node(list_t list)
{

  if (list == NULL)
    return NULL;

  if (list->head == NULL)
  {
    if (DEBUG)
      fprintf(stderr, "List is empty, no action taken\n");
    return list;
  }

  if (list->head->next == NULL)
  {

    if (DEBUG)
      fprintf(stderr, "Removed last item in list\n");

    free(list->head);
    *list = (struct LIST){NULL, NULL};

    return list;
  }

  if (DEBUG)
    fprintf(stderr, "pop rear / data: %d\n", list->rear->data);

  node_t iterator = list->head;

  while (iterator->next != list->rear)
  {
    iterator = iterator->next;
  }

  free(iterator->next);
  iterator->next = NULL;

  list->rear = iterator;

  return list;
}

list_t remove_index_node(list_t list, size_t index)
{

  if (list == NULL)
    return NULL;

  if (list->head == NULL)
  {
    if (DEBUG)
      fprintf(stderr, "List is empty, no action taken\n");
    return list;
  }

  // if the list has only one node, remove it

  if (list->head->next == NULL)
  {
    if (DEBUG)
      fprintf(stderr, "Removed last item in list\n");

    free(list->head);
    *list = (struct LIST){NULL, NULL};

    return list;
  }

  // if index is 0, remove front node

  if (index == 0)
    return remove_head_node(list);

  // if index is out of bounds, remove rear node

  node_t current = list->head;

  size_t i = 0;

  while (current->next != list->rear && i < index - 1)
  {
    current = current->next;
    i++;
  }

  if (current->next == list->rear)
    return remove_rear_node(list);

  if (DEBUG)
    fprintf(stderr, "Removed node at index %zu / data: %d\n", i + 1,
            current->next->data);

  node_t temp = current->next;

  current->next = current->next->next;

  free(temp);

  return list;
}
