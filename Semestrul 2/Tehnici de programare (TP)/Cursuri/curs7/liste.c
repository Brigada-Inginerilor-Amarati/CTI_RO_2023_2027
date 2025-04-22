#include <stdio.h>
#include <stdlib.h>

/*
typedef struct {
  int value;
} payload_t;
*/

typedef unsigned long long payload_t;

typedef struct NODE
{
  payload_t info;
  struct NODE *next;
} node_t;

node_t *make_node(payload_t info)
{

  node_t *node = malloc(sizeof(node_t));

  if (node == NULL)
    return NULL;

  *node = (struct NODE){info, NULL};

  return node;
}

// tipul lista este de fapt un pointer la primul nod al listei
typedef node_t *list_t;

// primeste o lista si un nod si adauga nodul la inceputul listei, returneaza
// lista
list_t add_front(list_t list, node_t *node)
{
  if (list == NULL)
  {
    node->next = NULL;
    return node;
  }

  node->next = list;
  list = node;

  return list;
}

// adaugare la pozitia k
list_t add_position(list_t list, size_t k, node_t *node)
{
  if (k == 0)
    return add_front(list, node);

  size_t i = 0;
  list_t iterator = NULL;
  for (iterator = list; i < k - 1 && iterator->next != NULL;
       iterator = iterator->next, i++)
    ;

  node->next = iterator->next;
  iterator->next = node;

  return list;
}

// sterge primul nod din lista
list_t delete_front(list_t list)
{
  node_t *temp = list;
  list = list->next;
  free(temp);
  return list;
}

// sterge nodul de pe pozitia k
list_t delete_position(list_t list, size_t k)
{
  if (k == 0)
    return delete_front(list);

  size_t i = 0;
  list_t iterator = NULL;

  for (iterator = list; i < k - 2 && iterator->next->next != NULL;
       iterator = iterator->next, i++)
    ;

  if (iterator->next->next == NULL)
  {

    node_t *temp = iterator->next;
    iterator->next = NULL;
    free(temp);
  }
  else
  {

    node_t *temp = iterator->next->next;
    iterator->next->next = iterator->next->next->next;
    free(temp);
  }

  return list;
}

// afisarea listei
void print_list(list_t list)
{
  for (node_t *iterator = list; iterator != NULL; iterator = iterator->next)
  {
    printf("%llu ", iterator->info);
  }
}

int main(void)
{

  list_t list = NULL;

  for (unsigned long long i = 10; i > 0; i--)
    list = add_front(list, make_node(i));

  print_list(list);

  for (int i = 0; i < 5; i++)
  {
    list = add_position(list, 5, make_node(100 * i));
    printf("\n");
    print_list(list);
  }

  list = add_position(list, 100, make_node(100));

  for (int i = 0; i < 5; i++)
  {
    list = delete_front(list);
    printf("\n");
    print_list(list);
  }

  for (int i = 0; i < 5; i++)
  {
    list = delete_position(list, 100);
    printf("\n");
    print_list(list);
  }

  return 0;
}
