#include "products.h"

// SHOW DATA

void show_pc_data(product_t *p)
{
  printf("Calculator -> CPU: %s / Memorie: %dGB\n", p->data.pc.cpu,
         p->data.pc.memory);
}

void show_monitor_data(product_t *p)
{
  printf("Monitor -> Diagonala: %d / Rezolutie: %dx%d\n",
         p->data.monitor.diagonal, p->data.monitor.resolution_x,
         p->data.monitor.resolution_y);
}

// ALLOC NEW PRODUCT

void *alloc(size_t size)
{
  void *p = malloc(size);
  if (p == NULL)
  {
    printf("Memory allocation failed\n");
    exit(1);
  }

  return p;
}

// NEW PRODUCT

product_t *new_pc(char *cpu, int memory)
{
  product_t *p = (product_t *)alloc(sizeof(product_t));
  p->type = PC;
  strcpy(p->data.pc.cpu, cpu);
  p->data.pc.memory = memory;
  p->show_data = show_pc_data;
  return p;
}

product_t *new_monitor(int diagonal, int res_x, int res_y)
{
  product_t *p = (product_t *)alloc(sizeof(product_t));
  p->type = MONITOR;
  p->data.monitor.diagonal = diagonal;
  p->data.monitor.resolution_x = res_x;
  p->data.monitor.resolution_y = res_y;
  p->show_data = show_monitor_data;
  return p;
}

// FACTORY

factory_t init_factory(void)
{
  return (factory_t){.generate_pc = new_pc, .generate_monitor = new_monitor};
}
