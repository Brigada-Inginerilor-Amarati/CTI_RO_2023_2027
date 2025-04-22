#include "matrix_block.h"

matrix_block_t init_matrix_block(matrix_size_t rows, matrix_size_t collumns)
{
  matrix_block_t b = {rows, collumns, NULL};
  b.data = (matrix_data_t *)malloc(
      (unsigned long)rows * (unsigned long)collumns * sizeof(matrix_data_t));

  if (b.data == NULL)
  {
    printf("Memory allocation failed\n");
    exit(1);
  }

  return b;
}

void read_matrix_block_data(matrix_block_t m, FILE *file)
{
  for (matrix_size_t i = 0; i < m.rows; i++)
    for (matrix_size_t j = 0; j < m.collumns; j++)
      if (fscanf(file, "%lf", &m.data[i * m.collumns + j]) != 1)
      {
        printf("Invalid input\n");
        exit(1);
      }
}

void print_matrix_block(matrix_block_t m, FILE *file)
{
  for (matrix_size_t i = 0; i < m.rows; i++)
  {
    for (matrix_size_t j = 0; j < m.collumns; j++)
    {
      fprintf(file, "%lf ", m.data[i * m.collumns + j]);
    }
    fprintf(file, "\n");
  }
}

void free_matrix_block(matrix_block_t b)
{
  free(b.data);
  b.rows = 0;
  b.collumns = 0;
  b.data = NULL;
}

matrix_data_t sum_matrix_block(matrix_block_t b)
{
  matrix_data_t sum = 0;
  for (matrix_size_t i = 0; i < b.rows * b.collumns; i++)
    sum += b.data[i];

  return sum;
}
