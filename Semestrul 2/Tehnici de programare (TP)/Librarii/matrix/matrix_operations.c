#include "matrix_operations.h"
#include "matrix_block.h"
#include "matrix_conversion.h"
#include "matrix_std.h"

int comparator(const void *p, const void *q)
{
  matrix_data_t l = *((matrix_data_t *)p);
  matrix_data_t r = *((matrix_data_t *)q);
  return (int)(l - r);
}

void sort_matrix_std(matrix_std_t m)
{
  matrix_block_t b = {0, 0, NULL};

  b = init_matrix_block(m.rows, m.rows);

  convert_matrix_to_block(m, b);

  qsort((void *)b.data, b.rows * b.collumns, sizeof(b.data[0]), comparator);

  convert_block_to_matrix(b, m);

  free_matrix_block(b);
}

matrix_std_t add_matrix_std(matrix_std_t a, matrix_std_t b)
{

  if (a.rows != b.rows || a.collumns != b.collumns)
  {
    perror("Invalid matrix addition: a->rows != b->rows or a->collumns != "
           "b->collumns");
    exit(1);
  }

  matrix_std_t c = init_matrix_std(a.rows, a.collumns);

  matrix_size_t i, j;

  for (i = 0; i < a.rows; i++)
  {
    for (j = 0; j < a.collumns; j++)
    {
      c.data[i][j] = a.data[i][j] + b.data[i][j];
    }
  }

  return c;
}

matrix_std_t copy_matrix_std(matrix_std_t origin)
{

  matrix_std_t copy = init_matrix_std(origin.rows, origin.collumns);

  for (matrix_size_t i = 0; i < origin.rows; i++)
    for (matrix_size_t j = 0; j < origin.collumns; j++)
      copy.data[i][j] = origin.data[i][j];

  return copy;
}

matrix_std_t multiply_matrix_std(matrix_std_t a, matrix_std_t b)
{

  if (a.collumns != b.rows)
  {
    perror("Invalid matrix multiplication: a->collumns != b->rows");
    exit(1);
  }

  matrix_std_t c = init_matrix_std(a.rows, b.collumns);

  for (matrix_size_t i = 0; i < a.rows; i++)
  {
    for (matrix_size_t j = 0; j < b.collumns; j++)
    {
      c.data[i][j] = 0;
      for (matrix_size_t k = 0; k < a.collumns; k++)
      {
        c.data[i][j] += a.data[i][k] * b.data[k][j];
      }
    }
  }

  return c;
}

matrix_std_t transpose_matrix_std(matrix_std_t m)
{
  matrix_std_t t = init_matrix_std(m.collumns, m.rows);

  matrix_size_t i, j;

  for (i = 0; i < m.rows; i++)
  {
    for (j = 0; j < m.collumns; j++)
      t.data[j][i] = m.data[i][j];
  }

  return t;
}

void rotate_left_matrix_std(matrix_std_t m)
{
  for (matrix_size_t i = 0; i < m.rows; i++)
  {
    matrix_data_t temp = m.data[i][0];

    for (matrix_size_t j = 1; j < m.collumns; j++)
    {
      m.data[i][j - 1] = m.data[i][j];
    }

    m.data[i][m.collumns - 1] = temp;
  }
}

void rotate_right_matrix_std(matrix_std_t m)
{
  for (matrix_size_t i = 0; i < m.rows; i++)
  {
    matrix_data_t temp = m.data[i][m.collumns - 1];

    for (matrix_size_t j = m.collumns - 1; j > 0; j--)
    {
      m.data[i][j] = m.data[i][j - 1];
    }

    m.data[i][0] = temp;
  }
}

void rotate_matrix_std(matrix_std_t m, int option)
{
  switch (option)
  {
  case 0:
    rotate_left_matrix_std(m);
    break;
  case 1:
    rotate_right_matrix_std(m);
    break;
  default:
    perror("Invalid rotation option -> left : 0 / right : 1");
    exit(1);
  }
}
