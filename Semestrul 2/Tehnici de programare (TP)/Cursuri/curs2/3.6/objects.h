#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

typedef enum
{
  CIRCLE,
  TRIANGLE,
  RECTANGLE
} shape_t;

// circle
typedef struct circle
{
  double radius;
} circle_t;

// rectangle
typedef struct rectangle
{
  double length, width;
} rectangle_t;

// triangle
typedef struct triangle
{
  double a, b, c;
} triangle_t;

struct object;

typedef struct object object_t;

typedef struct
{
  object_t *(*generate_circle)(double);
  object_t *(*generate_rectangle)(double, double);
  object_t *(*generate_triangle)(double, double, double);
} factory_t;

typedef struct
{

  double (*get_perimeter)(const object_t *);
  double (*get_area)(const object_t *);
  void (*show_data)(const object_t *);
  const char *(*get_name)(void);

} object_methods_t;

typedef struct object
{

  shape_t type;

  union
  {
    circle_t circle;
    rectangle_t rectangle;
    triangle_t triangle;
  };

  object_methods_t methods;

} object_t;

factory_t init_factory(void);

#endif
