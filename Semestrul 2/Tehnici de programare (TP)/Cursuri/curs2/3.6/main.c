// Aplicația 3.6: Să se completeze exemplul de implementare a colecțiilor
// eterogene folosind pointeri la funcții cu tipul de elemente ​Triunghi​.
// Un triunghi este definit prin lungimile laturilor sale.

#include "objects.h"
#include <stdio.h>

#define COUNT 10

object_t **generate_objects(size_t count)
{
  factory_t factory = init_factory();

  object_t **objects = (object_t **)malloc(count * sizeof(object_t *));

  if (objects == NULL)
  {
    perror("Memory allocation error");
    exit(1);
  }

  for (size_t i = 0; i < count; i++)
  {
    switch (i % 3)
    {
    case 0:
      objects[i] = factory.generate_circle(i + 1);
      break;
    case 1:
      objects[i] = factory.generate_rectangle(i + 1, i + 2);
      break;
    case 2:
      objects[i] = factory.generate_triangle(i + 1, i + 2, i + 3);
      break;
    }
  }

  return objects;
}

void print_objects(object_t **objects, size_t count)
{
  for (size_t i = 0; i < count; i++)
  {
    printf("Object %zu: %s\n", i, objects[i]->methods.get_name());
    objects[i]->methods.show_data(objects[i]);
    printf("Area: %.2f\n", objects[i]->methods.get_area(objects[i]));
    printf("Perimeter: %.2f\n", objects[i]->methods.get_perimeter(objects[i]));
    printf("\n");
  }
}

void free_objects(object_t **objects, size_t count)
{
  for (size_t i = 0; i < count; i++)
  {
    free(objects[i]);
  }

  free(objects);
}

int main(void)
{

  object_t **objects = generate_objects(COUNT);

  print_objects(objects, COUNT);

  free_objects(objects, COUNT);

  return 0;
}
