#include "list.h"

int main(void)
{

  list_t list = init_list();

  if (list == NULL)
    return 1;

  for (int i = 0; i < 10; i++)
    list = add_head_node(list, create_node(i * 3.14));

  print_list(list);

  for (int i = 10; i < 20; i++)
    list = add_rear_node(list, create_node(i * 3.14));

  print_list(list);

  for (int i = 10; i < 20; i++)
    list = add_index_node(list, create_node(i * 3.14), 10);

  print_list(list);

  for (int i = 0; i < 30; i++)
    list = remove_index_node(list, 10);

  print_list(list);

  free_list(list);

  return 0;
}
