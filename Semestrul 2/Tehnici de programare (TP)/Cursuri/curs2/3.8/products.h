#ifndef __PRODUCTS_H
#define __PRODUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PC_CPU_NAME 100

typedef enum
{
  PC,
  MONITOR
} product_type_t;

typedef struct pc
{

  char cpu[MAX_PC_CPU_NAME];
  int memory;

  void (*afisare)(struct pc *);

} pc_t;

typedef struct monitor
{

  int diagonal;
  int resolution_x;
  int resolution_y;

} monitor_t;

typedef struct product
{
  product_type_t type;
  union product_data
  {
    pc_t pc;
    monitor_t monitor;
  } data;

  void (*show_data)(struct product *);

} product_t;

typedef struct
{
  product_t *(*generate_pc)(char *cpu, int memory);
  product_t *(*generate_monitor)(int diagonal, int resolution_x,
                                 int resolution_y);
} factory_t;

factory_t init_factory(void);

#endif
