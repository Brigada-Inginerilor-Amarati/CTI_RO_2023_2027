// Aplicația 3.1: ​Se cere un număr ​n și apoi un vector de ​n
// rezultate ale studenților la un examen.
// Fiecare rezultat este definit prin (nume,nota).​
// Se cere să se sorteze folosind ​qsort ​vectorul în ordinea notelor,
// notele cele mai mari fiind primele. Dacă două note sunt identice, rezultatele
// respective se vor sorta în ordinea alfabetică a numelor.

#include "student.h"

#define INPUT_FILE_NAME "date.txt"

FILE *open_file(const char *file_name, const char *mode)
{
  FILE *file = fopen(file_name, mode);

  if (file == NULL)
  {
    printf("Error opening file %s", file_name);
    exit(1);
  }

  return file;
}

void close_file(FILE *file)
{
  if (fclose(file) == EOF)
  {
    printf("Error closing file");
    exit(1);
  }
}

int main(void)
{
  FILE *input_file = open_file(INPUT_FILE_NAME, "r");

  student_t *students = NULL;

  int n = 0;

  if (fscanf(input_file, "%d", &n) != 1)
  {
    printf("Invalid input -> n\n");
    return 1;
  };

  students = read_student_array(n, input_file);

  int option_count = 2;
  sorting_method options[] = {NAMES_ASCENDING, GRADES_DESCENDING};

  sort_students((size_t)n, students, option_count, options);

  print_student_array(n, students, stdout);

  close_file(input_file);

  free(students);

  return 0;
}
