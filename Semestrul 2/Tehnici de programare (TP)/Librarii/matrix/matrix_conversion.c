#include "matrix_conversion.h"

void convert_matrix_to_block(matrix_std_t matrix_std,
                             matrix_block_t matrix_block)
{

  for (matrix_size_t i = 0; i < matrix_std.rows; i++)
    for (matrix_size_t j = 0; j < matrix_std.collumns; j++)
      matrix_block.data[i * matrix_std.collumns + j] = matrix_std.data[i][j];
}

void convert_block_to_matrix(matrix_block_t matrix_block,
                             matrix_std_t matrix_std)
{

  for (matrix_size_t i = 0; i < matrix_block.rows; i++)
    for (matrix_size_t j = 0; j < matrix_block.collumns; j++)
      matrix_std.data[i][j] = matrix_block.data[i * matrix_block.collumns + j];
}
