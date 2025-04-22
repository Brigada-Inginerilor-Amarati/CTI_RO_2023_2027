#include "files.h"

#include "matrix_data.h"
#include "matrix_operations.h"
#include "matrix_std.h"

#define INPUT_FILE_NAME "date.txt"
#define OUTPUT_FILE_NAME "output.txt"

/*
10 11 12 13 14
15 16 17 18 19
20 21 22 23 24
25 26 27 28 29
30 31 32 33 34
*/

/*
01 + 12 + 23 + 34
02 + 13 + 24
03 + 14
04
*/

/*
10 + 21 + 32 + 43
20 + 31 + 42
30 + 41
40
*/

/*
4. [Pbinfo783]

Implementati o functie care primeste o matrice cu n linii şi n coloane şi
elemente numere naturale. Să se determine suma elementelor de pe cele două
diagonale vecine (si ulterioarele) cu diagonala principală.
*/

void pbinfo783(matrix_std_t m)
{

  matrix_data_t sum = 0;
  // upper

  for (matrix_size_t offset = 1; offset < m.collumns; offset++)
  {
    sum = 0;
    for (matrix_size_t index = 0; index < m.rows; index++)
    {
      if (index + offset < m.collumns)
      {
        sum += m.data[index][index + offset];
      }
    }
    printf("Suma Diagonala Upper %lu -> %lf\n", offset, sum);
  }

  // lower

  for (matrix_size_t offset = 1; offset < m.collumns; offset++)
  {
    sum = 0;
    for (matrix_size_t index = 0; index < m.rows; index++)
    {
      if (index + offset < m.collumns)
      {
        sum += m.data[index + offset][index];
      }
    }
    printf("Suma Diagonala Lower -%lu -> %lf\n", offset, sum);
  }
}

/*
5. [PbInfo208]

Implementati o functie care primeste  două numere naturale nenule n şi m şi
construieşte în memorie si returneaza o matrice cu n linii şi m coloane astfel
încât, parcurgând tabloul linie cu linie de sus în jos şi fiecare linie de la
stânga la dreapta, să se obţină şirul primelor n*m pătrate perfecte impare ,
ordonat strict crescător.
*/

matrix_std_t pbinfo208(matrix_size_t n, matrix_size_t m)
{

  matrix_std_t matrix = init_matrix_std(n, m);

  matrix_size_t value = 1;

  for (matrix_size_t i = 0; i < matrix.rows; i++)
  {
    for (matrix_size_t j = 0; j < matrix.collumns; j++)
    {
      matrix.data[i][j] = value * value;
      value += 2;
    }
  }

  return matrix;
}

int main(void)
{

  FILE *input_file = open_file(INPUT_FILE_NAME, "r");

  matrix_std_t a = {0, 0, NULL};

  if (fscanf(input_file, "%ld %ld", &a.rows, &a.collumns) != 2)
  {
    printf("Invalid input -> a\n");
    return 1;
  };

  a = init_matrix_std(a.rows, a.collumns);

  read_data_matrix_std(a, input_file);

  matrix_std_t b = transpose_matrix_std(a);

  matrix_std_t c = multiply_matrix_std(b, a);

  print_matrix_std(c, stdout);

  free_matrix_std(a);
  free_matrix_std(b);
  free_matrix_std(c);
  return 0;
}

/*



FILE *output_file = open_file(OUTPUT_FILE_NAME, "w");

matrix_std_t a = {0, 0, NULL};
matrix_std_t b = {0, 0, NULL};

if (fscanf(input_file, "%d %d", &a.rows, &a.collumns) != 2) {
  printf("Invalid input -> a\n");
  return 1;
};

a = init_matrix_std(a.rows, a.collumns);

read_data_matrix_std(&a, input_file);

pbinfo783(&a);

matrix_std_t c = pbinfo208(3, 3);

print_matrix_std(&c, stdout);

free_matrix_std(&a);

free_matrix_std(&c);
printf("Original Matrix:\n");
print_matrix_std(&a, stdout);

rotate_matrix_std(&a, 0);

printf("Left Rotation:\n");
print_matrix_std(&a, stdout);

rotate_matrix_std(&a, 1);

printf("Right Rotation:\n");
print_matrix_std(&a, stdout);

free_matrix_std(&a);

close_file(input_file);
close_file(output_file);

if (fscanf(input_file, "%d %d", &b.rows, &b.collumns) != 2) {
  printf("Invalid input -> b\n");
  return 1;
};

b = init_matrix_std(b.rows, b.collumns);

read_data_matrix_std(&b, input_file);

matrix_std_t c = {0, 0, NULL};
matrix_std_t d = {0, 0, NULL};

c = multiply_matrix_std(&a, &b);

print_matrix_std(&c, output_file);

d = multiply_matrix_std(&a, &c);

print_matrix_std(&d, output_file);

free_matrix_std(&a);

free_matrix_std(&b);

free_matrix_std(&c);
free_matrix_std(&d);
*/
