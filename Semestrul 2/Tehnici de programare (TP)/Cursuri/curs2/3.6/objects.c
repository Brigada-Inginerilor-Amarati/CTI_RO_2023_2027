#include "objects.h"

// NAME

const char *get_name_circle(void) { return "Circle"; }
const char *get_name_triangle(void) { return "Triangle"; }
const char *get_name_rectangle(void) { return "Rectangle"; }

// SHOW DATA

void show_data_circle(const object_t *obj)
{
  printf("Radius: %f\n", obj->circle.radius);
}

void show_data_triangle(const object_t *obj)
{
  printf("Sides: %f, %f, %f\n", obj->triangle.a, obj->triangle.b,
         obj->triangle.c);
}

void show_data_rectangle(const object_t *obj)
{
  printf("Length: %f, Width: %f\n", obj->rectangle.length,
         obj->rectangle.width);
}

// PERIMETER

double get_perimeter_circle(const object_t *obj)
{
  return 2 * PI * obj->circle.radius;
}

double get_perimeter_triangle(const object_t *obj)
{
  return obj->triangle.a + obj->triangle.b + obj->triangle.c;
}

double get_perimeter_rectangle(const object_t *obj)
{
  return 2 * (obj->rectangle.length + obj->rectangle.width);
}

// AREA

double get_area_circle(const object_t *obj)
{
  return PI * obj->circle.radius * obj->circle.radius;
}

double get_area_triangle(const object_t *obj)
{
  double p = (obj->triangle.a + obj->triangle.b + obj->triangle.c) / 2;
  return sqrt(p * (p - obj->triangle.a) * (p - obj->triangle.b) *
              (p - obj->triangle.c));
}

double get_area_rectangle(const object_t *obj)
{
  return obj->rectangle.length * obj->rectangle.width;
}

// CONSTUCTORS

void *alloc(size_t bytes)
{
  void *p = malloc(bytes);

  if (p == NULL)
  {
    perror("Memory allocation error");
    exit(1);
  }

  return p;
}

object_t *circle_constructor(double radius)
{
  object_t *circle = (object_t *)alloc(sizeof(object_t));

  circle->type = CIRCLE;
  circle->circle.radius = radius;
  circle->methods = (object_methods_t){.get_area = get_area_circle,
                                       .get_perimeter = get_perimeter_circle,
                                       .get_name = get_name_circle,
                                       .show_data = show_data_circle};

  return circle;
}

object_t *triangle_constructor(double a, double b, double c)
{
  object_t *triangle = (object_t *)alloc(sizeof(object_t));

  triangle->type = TRIANGLE;
  triangle->triangle.a = a;
  triangle->triangle.b = b;
  triangle->triangle.c = c;
  triangle->methods = (object_methods_t){
      .get_area = get_area_triangle,
      .get_perimeter = get_perimeter_triangle,
      .get_name = get_name_triangle,
      .show_data = show_data_triangle,
  };

  return triangle;
}

object_t *rectangle_constructor(double length, double width)
{

  object_t *rectangle = (object_t *)alloc(sizeof(object_t));

  rectangle->type = RECTANGLE;
  rectangle->rectangle = (rectangle_t){.length = length, .width = width};
  rectangle->methods = (object_methods_t){
      .get_area = get_area_rectangle,
      .get_perimeter = get_perimeter_rectangle,
      .get_name = get_name_rectangle,
      .show_data = show_data_rectangle,
  };

  return rectangle;
}

factory_t init_factory(void)
{
  return (factory_t){
      .generate_circle = circle_constructor,
      .generate_triangle = triangle_constructor,
      .generate_rectangle = rectangle_constructor,
  };
}
