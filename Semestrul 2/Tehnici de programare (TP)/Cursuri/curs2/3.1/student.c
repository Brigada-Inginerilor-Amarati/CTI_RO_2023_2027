#include "student.h"

student_t read_student_data(FILE *file)
{
  fgetc(file);

  student_t student = {"", 0};

  if (fgets(student.name, MAX_NAME_LENGTH, file) == NULL)
  {
    printf("Invalid input -> not enough names\n");
    exit(1);
  }

  if (student.name[strlen(student.name) - 1] == '\n')
  {
    student.name[strlen(student.name) - 1] = '\0';
  }

  if (fscanf(file, "%d", &student.grade) != 1)
  {
    printf("Invalid input -> not enough grades\n");
    exit(1);
  }

  return student;
}

student_t *read_student_array(int count, FILE *file)
{
  student_t *arr = (student_t *)malloc((size_t)count * sizeof(student_t));

  if (arr == NULL)
  {
    printf("Error allocating memory");
    exit(1);
  }

  for (int i = 0; i < count; i++)
  {
    arr[i] = read_student_data(file);
  }

  return arr;
}

void print_student_data(student_t student, FILE *file)
{
  fprintf(file, "%s -> %d\n", student.name, student.grade);
}

void print_student_array(int count, student_t *arr, FILE *file)
{
  for (int i = 0; i < count; i++)
  {
    print_student_data(arr[i], file);
  }
}

int cmp_grades_ascending(const void *st1, const void *st2)
{
  student_t s1 = *(student_t *)st1;
  student_t s2 = *(student_t *)st2;

  return s1.grade - s2.grade;
}

int cmp_grades_descending(const void *st1, const void *st2)
{
  student_t s1 = *(student_t *)st1;
  student_t s2 = *(student_t *)st2;

  return s2.grade - s1.grade;
}

int cmp_names_ascending(const void *st1, const void *st2)
{
  student_t s1 = *(student_t *)st1;
  student_t s2 = *(student_t *)st2;

  return strcmp(s1.name, s2.name);
}

int cmp_names_descending(const void *st1, const void *st2)
{
  student_t s1 = *(student_t *)st1;
  student_t s2 = *(student_t *)st2;

  return strcmp(s2.name, s1.name);
}

void sort_students(size_t count, student_t *arr, int option_count,
                   sorting_method options[])
{

  for (int i = 0; i < option_count; i++)
  {
    switch (options[i])
    {
    case NAMES_ASCENDING:
      qsort(arr, count, sizeof(student_t), cmp_names_ascending);
      break;
    case NAMES_DESCENDING:
      qsort(arr, count, sizeof(student_t), cmp_names_descending);
      break;
    case GRADES_ASCENDING:
      qsort(arr, count, sizeof(student_t), cmp_grades_ascending);
      break;
    case GRADES_DESCENDING:
      qsort(arr, count, sizeof(student_t), cmp_grades_descending);
      break;
    default:
      printf("Invalid sorting method\n");
      exit(1);
      break;
    }
  }
}

int cmp_grades_and_names(const void *st1, const void *st2)
{
  student_t s1 = *(student_t *)st1;
  student_t s2 = *(student_t *)st2;

  if (s1.grade == s2.grade)
  {
    return strcmp(s1.name, s2.name);
  }

  return s2.grade - s1.grade;
}

void sort_students_grades_and_names(size_t count, student_t *arr,
                                    int (*cmp)(const void *, const void *))
{
  qsort(arr, count, sizeof(arr[0]), cmp);
}
