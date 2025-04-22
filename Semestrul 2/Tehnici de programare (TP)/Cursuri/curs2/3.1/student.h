#ifndef __STUDENT_H
#define __STUDENT_H

#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

typedef struct
{
  char name[MAX_NAME_LENGTH];
  int grade;
} student_t;

typedef enum
{
  NAMES_ASCENDING,
  NAMES_DESCENDING,
  GRADES_ASCENDING,
  GRADES_DESCENDING
} sorting_method;

student_t read_student_data(FILE *file);

student_t *read_student_array(int count, FILE *file);

void print_student_data(student_t student, FILE *file);

void print_student_array(int count, student_t *student_arr, FILE *file);

void sort_student_array(int count, student_t *student_arr);

int compare_student_grades(const void *st1, const void *st2);

void sort_students(size_t count, student_t *arr, int method_count,
                   sorting_method methods[]);

#endif
